//
//  main.c
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>

#include "ChatRoom.h"
#include "commands.h"
#include "Bot.h"
#undef Client_h
#include "Client.h"

void unrecognizedCommand(RunningCommand *command, void *ctx) {
    ChatBot *bot = ctx;
    char *message;
    asprintf(&message, "Unrecognized command `%s`!", command->message->content);
    postReply(bot->room, message, command->message);
    free(message);
}

int main(int argc, const char * argv[]) {
    puts("Starting...");
    
#ifdef DEBUG
    puts("Debug mode is active.");
#endif
    
    if (curl_global_init(CURL_GLOBAL_ALL)) {
        fputs("Error initializing libcurl!", stderr);
        exit(EXIT_FAILURE);
    }
    
    Client *client = createClient("stackoverflow.com", "cookies");
    if (!client->isLoggedIn) {
        char *env_email, *env_pass;
        if (
            (env_email = getenv("ChatBotEmail")) == NULL ||
            (env_pass = getenv("ChatBotPass")) == NULL
            ) {
            //Get the email from the user
            printf("Email address: ");
            const unsigned maxEmailLen = 128;
            char email[maxEmailLen];
            fgets(email, maxEmailLen, stdin);
            email[maxEmailLen - 1] = 0;   //make sure it's null terminated
            
            char *password = getpass("Password: ");
            loginWithEmailAndPassword(client, email, password);
            //overwrite the password so it doesn't stay in memory
            memset(password, 0, strlen(password));
        }
        else {
            loginWithEmailAndPassword(client, env_email, env_pass);
            memset(env_pass, 0, strlen(env_pass));
        }
    }
    
    ChatRoom *room = createChatRoom(client, 167908);
    enterChatRoom(room);
    
    Command *commands[] = {
        createCommand("Put anything here; first command runs when no other commands match.", 0, unrecognizedCommand),
        createCommand("alive", 0, aliveCheck),
        createCommand("stop", 0, stopBot),
        createCommand("kill", 0, forceStopBot),
        createCommand("reboot", 0, rebootBot),
        NULL
    };
    
    ChatBot *bot = createChatBot("TestBot", "@tes", room, commands);
    postMessage(bot->room, "Started!");
   
    for (;;) {
        StopAction action = runChatBot(bot);
        if (action == ACTION_STOP) {
            puts("Stopping...");
            break;
        }
    }
    
    leaveRoom(bot->room);
    
    return 0;
}
