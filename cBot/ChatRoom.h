//
//  ChatRoom.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef ChatRoom_h
#define ChatRoom_h

#include <stdio.h>
#include "ChatMessage.h"
#include "Command.h"

typedef struct _ChatBot ChatBot;
typedef struct _Client Client;

typedef struct _ChatRoom {
    Client *client;
    unsigned roomID;
    unsigned long lastUpdateTimestamp;
    unsigned long lastPostTimestamp;
    unsigned userCount;
    time_t lastEventTime;
    ChatUser **users;
    struct _PendingMessage *pendingMessageLinkedList;
    pthread_mutex_t clientLock;
    pthread_mutex_t pendingMessageLock;
}ChatRoom;

ChatRoom *createChatRoom(Client *client, unsigned roomID);
void enterChatRoom(ChatRoom *room);
ChatMessage **processChatRoomEvents(ChatRoom *room);    //Returns a NULL-terminated list of chat messages.
                                                        //The list must be freed when done.
ChatUser *getUserByID(ChatRoom *r, unsigned long id);
int isUserInRoom (ChatRoom *r, long userID);
void postMessage(ChatRoom *r, const char *text);
void postReply(ChatRoom *r, const char *text, ChatMessage *message);
void leaveRoom(ChatRoom *r);

#endif /* ChatRoom_h */
