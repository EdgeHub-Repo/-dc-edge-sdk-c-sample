#ifndef __CONST_H__
#define __CONST_H__

static const char *ConfigTopic = "/wisepaas/scada/%s/cfg";
static const char *DataTopic = "/wisepaas/scada/%s/data";
static const char *NodeConnTopic = "/wisepaas/scada/%s/conn";
static const char *DeviceConnTopic = "/wisepaas/scada/%s/%s/conn";
static const char *NodeCmdTopic = "/wisepaas/scada/%s/cmd";
static const char *DeviceCmdTopic = "/wisepaas/scada/%s/%s/cmd";
static const char *AckTopic = "/wisepaas/scada/%s/ack";
static const char *CfgAckTopic = "/wisepaas/scada/%s/cfgack";

static const char *CreateSql = "CREATE TABLE Data (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, message TEXT NOT NULL)";
static const char *InsertSql = "INSERT INTO Data (message) VALUES('%s')";
static const char *QuerysSql = "SELECT * FROM Data LIMIT %d;";
static const char *DeleteSql = "DELETE FROM Data WHERE id IN (%s)";

// const int hbt_sec = 1;
static const int rcov_sec = 1;
static const int rcov_limit = 10;

static const char *WirteValueCommand = "WV";
static const char *WriteConfigCommand = "WC";
static char *AckConfig = "AckConfig";

// #define MAX_TOPIC 100

#endif
