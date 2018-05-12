//
//  Bot.c
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Bot.h"
#include "ChatMessage.h"
#include "RunningCommand.h"
#include "cJSON.h"
#include "Client.h"

ChatBot *createChatBot(
                       const char *name,
                       const char *shortName,
                       ChatRoom *room,
                       Command **commands
                       ) {
    ChatBot *c = malloc(sizeof(ChatBot));
    
    c->name = malloc(strlen(name) + 1);
    strcpy(c->name, name);
    
    c->shortName = malloc(strlen(shortName) + 1);
    strcpy(c->shortName, shortName);
    
    c->room = room;
    c->commands = commands;
    c->runningCommands = NULL;
    c->runningCommandCount = 0;
    c->stopAction = ACTION_NONE;
    pthread_mutex_init(&c->runningCommandsLock, NULL);
    
    return c;
}

void deleteChatBot(ChatBot *b) {
    free(b->name);
    free(b->shortName);
    free(b);
}

void runCommand(ChatBot *bot, ChatMessage *message, char *command) {
    //Get the space separated components of this command.
    char **components = NULL;
    size_t componentCount = 0;
    
    char *component;
    while((component = strsep(&command, " "))) {
        components = realloc(components, (++componentCount) * sizeof(char*));
        components[componentCount - 1] = malloc(strlen(component) + 1);
        strcpy(components[componentCount - 1], component);
    }
    
    pthread_mutex_lock(&bot->runningCommandsLock);
    RunningCommand *c = launchCommand(message, (int)componentCount, components, bot->commands, bot);
    bot->runningCommands = realloc(bot->runningCommands, ++bot->runningCommandCount * sizeof(RunningCommand*));
    bot->runningCommands[bot->runningCommandCount - 1] = c;
    pthread_mutex_unlock(&bot->runningCommandsLock);
}

void prepareCommand(ChatBot *bot, ChatMessage *message, char *messageText) {
    char *command = strchr(messageText, ' ');
    if (command) {
        while (*(++command) == ' ');
        if (*command && bot->stopAction == ACTION_NONE) {
            runCommand(bot, message, command);
            return;
        }
    }
}

void processMessage(ChatBot *bot, ChatMessage *message) {
    char *messageText = malloc(strlen(message->content) + 1);
    strcpy(messageText, message->content);
    //Detects messages starting with the short name.
    if (strcasestr(messageText, bot->shortName) == messageText) {
        prepareCommand(bot, message, messageText);
        
    } else {
        deleteChatMessage(message);
    }
    free(messageText);
}

StopAction runChatBot(ChatBot *c) {
    //Get new messages and check if they were meant for the bot.
    ChatMessage **messages = processChatRoomEvents(c->room);
    if (messages != NULL) {
        ChatMessage *message;
        for (int i = 0; (message = messages[i]); i++) {
            processMessage(c, message);
        }
        free(messages);
    }
    
    //Clean up finished commands.
    for (int i = 0; i < c->runningCommandCount; i++) {
        if (c->runningCommands[i]->finished) {
            //Delete the command
            c->runningCommandCount--;
            int j = i;
            for (deleteRunningCommand(c->runningCommands[j]); j < c->runningCommandCount; j++) {
                c->runningCommands[i] = c->runningCommands[i+1];
            }
            c->runningCommands = realloc(c->runningCommands, c->runningCommandCount * sizeof(RunningCommand*));
        }
    }
    
    if (c->stopAction != ACTION_NONE) {
        if (c->room->pendingMessageLinkedList == NULL && (c->runningCommandCount == 0)) {
            return c->stopAction;
        }
    }
    
    return ACTION_NONE;
}







