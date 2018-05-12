//
//  Privileges.h
//  cBot
//
//  Created by Ashish Ahuja on 08/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef Privileges_h
#define Privileges_h

#include <stdio.h>

typedef struct _PrivLevel {
    int level;
    char *name;
}PrivLevel;

typedef struct _PrivUser {
    unsigned long id;
    PrivLevel *level;
}PrivUser;

PrivLevel *createPrivilegeLevel(int level, const char *name);
void deletePrivilegeLevel(PrivLevel *l);
PrivUser *createPrivilegeUser(unsigned int id, PrivLevel *l);
void deletePrivilegeUser(PrivUser *u);

#endif /* Privileges_h */
