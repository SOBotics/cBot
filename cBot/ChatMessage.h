//
//  ChatMessage.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef ChatMessage_h
#define ChatMessage_h

#include <stdio.h>
#include "ChatUser.h"

typedef struct _ChatMessage {
    unsigned long id;
    unsigned long replyID;
    char *content;
    ChatUser *user;
}ChatMessage;

ChatMessage *createChatMessage(const char *text, unsigned long messageID, unsigned long replyID, ChatUser *user);
void deleteChatMessage(ChatMessage *message);

#endif /* ChatMessage_h */
