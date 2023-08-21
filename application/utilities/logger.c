#include "logger.h"

FILE* log_file = NULL;
char file_name[45] = "./logs/";
bool no_file_message_prompted = false;