#ifndef KONSTANTS_H
#define KONSTANTS_H

static const char* NO_EXISTANT_FILE = "NEF";
static const char* NO_EXISTANT_DATA = "NED";
static const char* USER_ALREADY_EXISTS = "UAE";
static const char* INVALID_VALUES = "IV";
static const char* INVALID_PASSWORD = "Invalid password.";
static const char* INVALID_USERNAME = "Invalid Username.";
static const char* EMPTY_STRING = "";
static const char* TRIPLE_NULL = "000";
static const char* OVER_WRITE = "Do you want to overwrite the existant file ?";
static const char* FILE_NOT_CREATED = "File was not created.";
static const char* BACKUP_STRING = "backup";
static const char* DIRFILE = "../FSQL/databases/";
static const char* BACK_UPS_DIR = "../FSQL/backups/";
static const char* USERS_DIR = "../FSQL/users/";

static const int ZE_ROW = 0;
static const int ONE_BYTE = 1;
static const int DEFAULT_COLUMN_SIZE = 3;
static const int DEFAULT_REGISTER_SIZE = 4;
static const int REGISTER_SIZE_ADDRESS = 3;
static const int MAX_REGISTER_SIZE = 999;
static const int METADATA_SIZE = 3;
static const int METADATA_COLUMN_START = 9;
static const int METADATA_COLUMN_START = 7;

static const char NULL_CHAR = '*';
static const char SINGLE_NULL = '0';
static const char _Y_ = 'Y';
static const char _N_ = 'N';

//NETWORK
static const char SERVER_IP1 = "192.168.0.20";
static const char SERVER_IP2 = "192.168.0.40";
static const char SERVER_IP3 = "192.168.0.60";
static const char LOCAL = "172.0.0.1";
static const char SERVER_INSTANCE = 1;
static const int RAID0 = 0;
static const int RAID1 = 1;
static const int RAID5 = 5;
static const int RAID10 = 10;
static const int PORTNO = 21000;
static const char* NI = "ni";

#endif
