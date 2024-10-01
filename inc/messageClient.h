#ifndef __MSG_CLIENT_H__
#define __MSG_CLIENT_H__

#include <stdbool.h>

#include "EDGE_AGENT_OPTION.h"

void MessageClientInit(TOPTION_STRUCT query);

bool MessageClientIsConnected();

int MessageClientPublishMessage(const char* topic, const char* message);

void MessageClientSubscribeMessage(const char* topic);

void MessageClientConnect();

void MessageClientDisconnect();

void MessageClientOnConnect(void (*handleConnect)());

void MessageClientOnDisconnect(void (*handleDisconnect)());

void MessageClientOnMessage(void (*handleMessage)(const char* topic, const char* message));

#endif
