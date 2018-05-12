//
//  ChatUser.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef ChatUser_h
#define ChatUser_h

#include <stdio.h>

typedef struct _ChatUser {
    char *name;
    unsigned long userID;
    int isModerator;
    int isRoomOwner;
}ChatUser;

ChatUser *createUser(unsigned long id, const char *name);
void deleteUser(ChatUser *u);

#endif /* ChatUser_h */
