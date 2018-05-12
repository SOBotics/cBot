//
//  Privileges.c
//  cBot
//
//  Created by Ashish Ahuja on 08/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#include "Privileges.h"

#include <string.h>
#include <stdlib.h>

PrivLevel *createPrivilegeLevel(int level, const char *name) {
    PrivLevel *l = malloc(sizeof(PrivLevel));
    l->level = level;
    l->name = malloc(strlen(name) + 1);
    strcpy(l->name, name);
    
    return l;
}

void deletePrivilegeLevel(PrivLevel *l) {
    free(l->name);
    free(l);
}

PrivUser *createPrivilegeUser(unsigned int id, PrivLevel *l) {
    PrivUser *u = malloc(sizeof(PrivUser));
    u->id = id;
    u->level = l;
    
    return u;
}

void deletePrivilegeUser(PrivUser *u) {
    free(u);
}

/*
PrivUser *getPrivUserByID(ChatBot *bot, long userID) {
    PrivUser **privUsers = bot->privUsers;
    for(unsigned int i = 0; i < bot->numOfPrivUsers; i ++) {
        if(privUsers[i]->id == userID) {
            return privUsers[i];
        }
    }
    return NULL;
}

unsigned checkPrivilegeUser(ChatBot *bot, long userID) {
    PrivUser **users = bot->privUsers;
    ChatUser *user =
}

unsigned commandPrivilegeCheck(RunningCommand *command, ChatBot *bot) {
    long userID = command->message->user->id;
}*/
