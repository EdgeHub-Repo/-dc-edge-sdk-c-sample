#ifndef __OPTION_H__
#define __OPTION_H__

typedef enum {
    TCP,
    WebSocket
} Protocol;

typedef enum {
    MQTT,
    DCCS,
    AzureIotHub,
} ConnectType;

typedef enum {
    Gatway,
    Device
} EdgeType;

typedef enum {
    DataOn,
    DataOff,
    WriteValue,
    WriteConfig,
    ConfigAck
} MessageType;

// typedef enum {
// 	SCADA, Gateway, VirtualGroup
// } SCADAConfigType;

typedef enum {
    Analog,
    Discrete,
    Text
} TagType;

typedef enum {
    Fail,
    Success
} ResultType;

typedef enum {
    Create,
    Update,
    Delete,
    Delsert,
} ActionType;

typedef struct MQTT_OPTION_STRUCT {
    char* HostName;
    int Port;
    char* Username;
    char* Password;
    Protocol ProtocolType;
} TMQTT_OPTION_STRUCT, *PTMQTT_OPTION_STRUCT;

typedef struct DCCS_OPTION_STRUCT {
    char* CredentialKey;
    char* APIUrl;
} TDCCS_OPTION_STRUCT, *PTDCCS_OPTION_STRUCT;

typedef struct AZURE_IOT_HUB_OPTION_STRUCT {
    char* ConnectionString;
} TAZURE_IOT_HUB_OPTIONS_STRUCT, *PTAZURE_IOT_HUB_OPTIONS_STRUCT;

typedef struct OPTION_STRUCT {
    bool CacheConfig;
    bool AutoReconnect;
    int ReconnectInterval;
    char* NodeId;
    char* DeviceId;
    EdgeType Type;
    int Heartbeat;
    bool DataRecover;
    ConnectType ConnectType;
    bool UseSecure;
    char* OvpnPath;
    TMQTT_OPTION_STRUCT MQTT;
    TDCCS_OPTION_STRUCT DCCS;
    TAZURE_IOT_HUB_OPTIONS_STRUCT AzureIotHub;

} TOPTION_STRUCT, *PTOPTION_STRUCT;

#endif
