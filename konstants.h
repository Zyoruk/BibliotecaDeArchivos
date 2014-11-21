#ifndef KONSTANTS_H
#define KONSTANTS_H

static const char* EMPTY_STRING = "";
static const char* TRIPLE_NULL = "000";
static const char* INVALID_VALUES = "IV";
static const char* NO_EXISTANT_FILE = "NEF";
static const char* NO_EXISTANT_DATA = "NED";
static const char* BACKUP_STRING = "backup";
static const char* NMA = "No monkeys allowed";
static const char* USER_ALREADY_EXISTS = "UAE";
static const char* INVALID_COMMAND ="Invalid Command";
static const char* INVALID_PASSWORD = "Invalid password.";
static const char* INVALID_USERNAME = "Invalid Username.";
static const char* FILE_NOT_CREATED = "File was not created.";
static const char* OVER_WRITE = "Do you want to overwrite the existant file ?";

//Directories
static const char* USERS_DIR = "../FSQL/users/";
static const char* DIRFILE = "../FSQL/databases/";
static const char* BACK_UPS_DIR = "../FSQL/backups/";

static const int ZE_ROW = 0;
static const int ONE_BYTE = 1;
static const int NOT_RAID = 99;
static const int MINUS_ONE = -1;
static const int BIG_A_SIZE = 256;
static const int METADATA_SIZE = 3;
static const int RAID_MODE_START = 7;
static const int DEFAULT_COLUMN_SIZE = 3;
static const int MAX_REGISTER_SIZE = 999;
static const int DEFAULT_REGISTER_SIZE = 4;
static const int REGISTER_SIZE_ADDRESS = 3;
static const int METADATA_COLUMN_START = 9;

static const char _Y_ = 'Y';
static const char _N_ = 'N';
static const char NULL_CHAR = '*';
static const char SPACE_CHAR = ' ';
static const char SINGLE_NULL = '0';

//NETWORK
static const int PORTNO = 21000;

static const char SERVER_INSTANCE = 1;

static const char* COLON = ":";
static const char* NI = "ni";
static const char* RAID_CNFG = "RaidConfig";
static const char* LOCAL = "127.0.0.1";
static const char* SERVER_IP1 = "192.168.0.20";
static const char* SERVER_IP2 = "192.168.0.40";
static const char* SERVER_IP3 = "192.168.0.60";
<<<<<<< HEAD
static const char* LOCAL = "127.0.0.1";
static const char SERVER_INSTANCE = 1;
static const char LAST_REG = "register";
=======

//Raids
>>>>>>> f8b036d595a52d01f6a0039da8fd27bc54f1c6bb
static const int RAID0 = 0;
static const int RAID1 = 1;
static const int RAID5 = 5;
static const int RAID10 = 10;

//UI
static const char* CREATE = "CREATE";
static const char* TABLE = "TABLE";
static const char* USING = "USING";
static const char* RAID = "RAID";
static const char* USER = "USER";
static const char* PASSWORD = "PASSWORD";
static const char* INDEX = "INDEX";
static const char* ON = "ON";
static const char* NYI = "NOT YET IMPLEMENTED";
static const char* INSERT = "INSERT";
static const char* INTO = "INTO";
static const char* SELECT = "SELECT";
static const char* ASTERISC = "*";
static const char* FROM = "FROM";
static const char* UPDATE = "UPDATE";
static const char* SET = "SET";
static const char* TO = "TO";
static const char* DELETE = "DELETE";
static const char* COMPRESS = "COMPRESS";
static const char* BACKUP = "BACKUP";
static const char* RESTORE = "RESTORE";
static const char* DROP = "DROP";
static const char* GRANT = "GRANT";
static const char* REVOKE = "REVOKE";


#endif
