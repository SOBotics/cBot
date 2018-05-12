//
//  Command.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef Command_h
#define Command_h

#include <stdio.h>
#include "RunningCommand.h"

typedef struct _Command {
    char *name;
    unsigned privileges;   //A bitmask of required privileges
    void (*callback)(RunningCommand *, void *);
}Command;

Command *createCommand(char *name, unsigned privileges, void (*callback)(RunningCommand *, void *));

#endif /* Command_h */
