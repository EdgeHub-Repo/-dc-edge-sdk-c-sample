#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DatahubEdge.h"

// Function prototypes
int nsleep(long milliseconds);
void edgeAgent_Connected();
void edgeAgent_Disconnected();
void edgeAgent_Receive(char *cmd, char *val);
void loadLibraryFunctions(void *handle);
TOPTION_STRUCT setupOptions();
TNODE_CONFIG_STRUCT setupConfig(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num);
TEDGE_DEVICE_STATUS_STRUCT setupDeviceStatus(int device_num);
TEDGE_DATA_STRUCT setupData(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num, int array_size);

// Global variables
bool IsConnected = false;
void *handle;

// Function pointers for library functions
void (*SetConnectEventPtr)(void (*callback)(void));
void (*SetDisconnectEventPtr)(void (*callback)(void));
void (*SetMessageReceivedPtr)(void (*callback)(char *cmd, char *val));
void (*ConstructorPtr)(TOPTION_STRUCT option);
void (*ConnectPtr)(void);
void (*DisconnectPtr)(void);
int (*UploadConfigPtr)(ActionType action, TNODE_CONFIG_STRUCT edgeConfig);
int (*SendDataPtr)(TEDGE_DATA_STRUCT data);
int (*SendDeviceStatusPtr)(TEDGE_DEVICE_STATUS_STRUCT data);

int main(int argc, char *argv[]) {
    handle = dlopen("./DatahubEdge.so.1.0.5", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(1);
    }

    loadLibraryFunctions(handle);

    // Set Events
    SetConnectEventPtr(edgeAgent_Connected);
    SetDisconnectEventPtr(edgeAgent_Disconnected);
    SetMessageReceivedPtr(edgeAgent_Receive);

    // Setup and connect
    TOPTION_STRUCT options = setupOptions();
    ConstructorPtr(options);
    ConnectPtr();
    nsleep(2000);

    // Setup and upload config
    int device_num = 3, analog_tag_num = 5, discrete_tag_num = 5, text_tag_num = 1;
    TNODE_CONFIG_STRUCT config = setupConfig(device_num, analog_tag_num, discrete_tag_num, text_tag_num);
    UploadConfigPtr(Create, config);
    nsleep(2000);

    // Send device status
    TEDGE_DEVICE_STATUS_STRUCT status = setupDeviceStatus(device_num);
    SendDeviceStatusPtr(status);

    // Setup and send data
    int array_size = 0;
    TEDGE_DATA_STRUCT data = setupData(device_num, analog_tag_num, discrete_tag_num, text_tag_num, array_size);
    SendDataPtr(data);
    nsleep(2000);

    // Cleanup
    free(config.DeviceList);
    free(status.DeviceList);
    free(data.DeviceList);
    dlclose(handle);

    return 0;
}

void loadLibraryFunctions(void *handle) {
    *(void **)(&SetConnectEventPtr) = dlsym(handle, "SetConnectEvent");
    *(void **)(&SetDisconnectEventPtr) = dlsym(handle, "SetDisconnectEvent");
    *(void **)(&SetMessageReceivedPtr) = dlsym(handle, "SetMessageReceived");
    *(void **)(&ConstructorPtr) = dlsym(handle, "Constructor");
    *(void **)(&ConnectPtr) = dlsym(handle, "Connect");
    *(void **)(&DisconnectPtr) = dlsym(handle, "Disconnect");
    *(void **)(&UploadConfigPtr) = dlsym(handle, "UploadConfig");
    *(void **)(&SendDataPtr) = dlsym(handle, "SendData");
    *(void **)(&SendDeviceStatusPtr) = dlsym(handle, "SendDeviceStatus");
}

TOPTION_STRUCT setupOptions() {
    TOPTION_STRUCT options = {.AutoReconnect = true,
                              .ReconnectInterval = 1000,
                              .NodeId = "ENTER_NODEID_HERE",
                              .Heartbeat = 60,
                              .DataRecover = true,
                              .ConnectType = DCCS,
                              .Type = Gatway,
                              .UseSecure = false,
                              .OvpnPath = "",
                              .DCCS = {.CredentialKey = "ENTER_CREDENTIAL_KEY_HERE", .APIUrl = "ENTER_API_URL_HERE"}};
    return options;
}

TNODE_CONFIG_STRUCT setupConfig(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num) {
    TNODE_CONFIG_STRUCT config = {0};
    config.DeviceNumber = device_num;
    config.DeviceList = malloc(device_num * sizeof(TDEVICE_CONFIG_STRUCT));

    for (int i = 0; i < device_num; i++) {
        TDEVICE_CONFIG_STRUCT *device = &config.DeviceList[i];
        asprintf(&device->Id, "DeviceID_%d", i);
        asprintf(&device->Name, "DeviceName_%d", i);
        device->Type = "DType";
        device->Description = "DDESC";
        device->AnalogNumber = analog_tag_num;
        device->DiscreteNumber = discrete_tag_num;
        device->TextNumber = text_tag_num;

        device->AnalogTagList = malloc(analog_tag_num * sizeof(TANALOG_TAG_CONFIG));
        device->DiscreteTagList = malloc(discrete_tag_num * sizeof(TDISCRETE_TAG_CONFIG));
        device->TextTagList = malloc(text_tag_num * sizeof(TTEXT_TAG_CONFIG));

        for (int j = 0; j < analog_tag_num; j++) {
            asprintf(&device->AnalogTagList[j].Name, "TagName_ana_%d", j);
            device->AnalogTagList[j].Description = "description_update";
            device->AnalogTagList[j].ReadOnly = false;
            device->AnalogTagList[j].Deadband = 1;
            device->AnalogTagList[j].SpanHigh = 1000;
            device->AnalogTagList[j].SpanLow = 0;
            device->AnalogTagList[j].ArraySize = 0;
        }

        for (int j = 0; j < discrete_tag_num; j++) {
            asprintf(&device->DiscreteTagList[j].Name, "TagName_dis_%d", j);
        }

        for (int j = 0; j < text_tag_num; j++) {
            asprintf(&device->TextTagList[j].Name, "TagName_txt_%d", j);
            device->TextTagList[j].Description = "description_t";
            device->TextTagList[j].ReadOnly = false;
            device->TextTagList[j].ArraySize = 0;
            device->TextTagList[j].AlarmStatus = false;
        }
    }

    return config;
}

TEDGE_DEVICE_STATUS_STRUCT setupDeviceStatus(int device_num) {
    TEDGE_DEVICE_STATUS_STRUCT status = {0};
    status.DeviceNumber = device_num;
    status.DeviceList = malloc(device_num * sizeof(TDEVICE_LIST_STRUCT));

    for (int i = 0; i < device_num; i++) {
        asprintf(&status.DeviceList[i].Id, "DeviceID_%d", i);
        status.DeviceList[i].Status = 1;
    }

    return status;
}

TEDGE_DATA_STRUCT setupData(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num,
                            int array_size) {
    TEDGE_DATA_STRUCT data = {0};
    data.DeviceNumber = device_num;
    data.DeviceList = malloc(device_num * sizeof(TEDGE_DEVICE_STRUCT));

    for (int i = 0; i < device_num; i++) {
        TEDGE_DEVICE_STRUCT *device = &data.DeviceList[i];
        asprintf(&device->Id, "DeviceID_%d", i);
        device->AnalogTagNumber = analog_tag_num;
        device->DiscreteTagNumber = discrete_tag_num;
        device->TextTagNumber = 0;

        device->AnalogTagList = malloc(analog_tag_num * sizeof(TEDGE_ANALOG_TAG_STRUCT));
        device->DiscreteTagList = malloc(discrete_tag_num * sizeof(TEDGE_DISCRETE_TAG_STRUCT));

        for (int j = 0; j < analog_tag_num; j++) {
            asprintf(&device->AnalogTagList[j].Name, "TagName_ana_%d", j);
            device->AnalogTagList[j].Value = 10.0;
            device->AnalogTagList[j].ArraySize = array_size;
            if (array_size > 0) {
                device->AnalogTagList[j].ArrayList = malloc(array_size * sizeof(TEDGE_ANALOG_ARRAY_TAG_STRUCT));
                for (int k = 0; k < array_size; k++) {
                    device->AnalogTagList[j].ArrayList[k].Index = k;
                    device->AnalogTagList[j].ArrayList[k].Value = 10.0;
                }
            }
        }

        for (int j = 0; j < discrete_tag_num; j++) {
            asprintf(&device->DiscreteTagList[j].Name, "TagName_dis_%d", j);
            device->DiscreteTagList[j].Value = 0;
        }
    }

    return data;
}

void edgeAgent_Connected() {
    printf("Connect success\n");
    IsConnected = true;
}

void edgeAgent_Disconnected() {
    printf("Disconnected\n");
    IsConnected = false;
}

void edgeAgent_Receive(char *cmd, char *val) {
    if (strcmp(cmd, WirteValueCommand) == 0) {
        printf("write value: %s\n", val);
    } else if (strcmp(cmd, AckConfig) == 0) {
        printf("ack config: %s\n", val);
    }
}

int nsleep(long milliseconds) {
    struct timespec req, rem;
    req.tv_sec = milliseconds / 1000;
    req.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&req, &rem);
}
