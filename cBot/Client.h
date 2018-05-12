//
//  Client.h
//  cBot
//
//  Created by Ashish Ahuja on 07/05/18.
//  Copyright © 2018 SOBotics. All rights reserved.
//

#ifndef Client_h
#define Client_h

#include <stdio.h>
#include <pthread.h>
#include <curl/curl.h>

//Pass this to the CURL callback.
typedef struct _OutBuffer {
    size_t size;
    char *data;
}OutBuffer;

#define checkCURL(code) checkCurlError(code, __PRETTY_FUNCTION__, __FILE__, __LINE__)

typedef struct _Client {
    int isLoggedIn;
    CURL *curl;
    char *fkey;
    char *host;
}Client;

Client *createClient(const char *host, const char *cookiefile);
void loginWithEmailAndPassword(Client *client, const char* email, const char* password);
unsigned long connectClientToRoom(Client *client, unsigned roomID); //Connects to a chat room. Returns the current timestamp.

#endif /* Client_h */
