//
//  ChatUser.c
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#include "ChatUser.h"
#include <stdlib.h>
#include <string.h>

ChatUser *createUser(unsigned long id, const char *name) {
    ChatUser *u = malloc(sizeof(ChatUser));
    
    u->userID = id;
    u->name = malloc(strlen(name) + 1);
    strcpy(u->name, name);
    
    u->isModerator = 0;
    u->isRoomOwner = 0;
    
    return u;
}

void deleteUser(ChatUser *u) {
    free(u->name);
    free(u);
}
