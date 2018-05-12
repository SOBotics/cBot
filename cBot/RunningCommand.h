//
//  RunningCommand.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef RunningCommand_h
#define RunningCommand_h

#include <stdio.h>
#include <pthread.h>

#include "ChatMessage.h"

typedef struct _Command Command;

typedef struct _RunningCommand {
    Command *command;
    ChatMessage *message;
    int argc;
    char **argv;
    pthread_t thread;
    int finished; //Is 1 if the command has finished execution.
}RunningCommand;

RunningCommand *launchCommand(ChatMessage *msg, int argc, char **argv, Command **commandList, void *ctx);
void deleteRunningCommand(RunningCommand *command);

#endif /* RunningCommand_h */
