//
//  Command.c
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#include "Command.h"

#include <stdlib.h>
#include <string.h>

Command *createCommand(char *name, unsigned privileges, void (*callback)(RunningCommand *, void *ctx)) {
    Command *c = malloc(sizeof(Command));
    c->name = name;
    c->callback = callback;
    c->privileges = privileges;
    return c;
}
