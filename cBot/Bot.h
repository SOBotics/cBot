//
//  Bot.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef Bot_h
#define Bot_h

#include <stdio.h>
#include "ChatRoom.h"
#include "Command.h"
#include "RunningCommand.h"

typedef enum {
    ACTION_NONE = 0,
    ACTION_STOP = 1,
    ACTION_REBOOT = 2
}StopAction;

typedef struct _ChatBot {
    ChatRoom *room;
    Command **commands;
    char *name;
    char *shortName;
    RunningCommand **runningCommands;
    size_t runningCommandCount;
    pthread_mutex_t runningCommandsLock;
    StopAction stopAction;
}ChatBot;

ChatBot *createChatBot(
                       const char *name,
                       const char *shortName,
                       ChatRoom *room,
                       Command **commands
                       );

StopAction runChatBot(ChatBot *chatbot);

#endif /* Bot_h */
