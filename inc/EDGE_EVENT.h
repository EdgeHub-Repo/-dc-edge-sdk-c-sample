#ifndef __EDGE_EVENT_H__
#define __EDGE_EVENT_H__

typedef struct {
    void (*callback)(void);
} TCALLBACK_STRUCT;

typedef struct {
    void (*receive)(char *cmd, char *val);
} TRECEIVE_STRUCT;

#endif
