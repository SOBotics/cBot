//
//  commands.h
//  cBot
//
//  Created by Ashish Ahuja on 10/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef commands_h
#define commands_h

#include "Bot.h"

void stopBot(RunningCommand *command, void *ctx) {
    ChatBot *bot = ctx;
    postReply(bot->room, "Shutting down...", command->message);
    bot->stopAction = ACTION_STOP;
}

void rebootBot(RunningCommand *command, void *ctx) {
    ChatBot *bot = ctx;
    postReply(bot->room, "Rebooting...", command->message);
    bot->stopAction = ACTION_REBOOT;
}

void forceStopBot(RunningCommand *command, void *ctx) {
    abort();
}

void aliveCheck(RunningCommand *command, void *ctx) {
    ChatBot *bot = ctx;
    postReply(bot->room, "...", command->message);
}

#endif /* commands_h */
