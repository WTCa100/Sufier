#ifndef APP_UTILITIES_FILE_MANAGEMENT_CSV_HANDLE_H
#define APP_UTILITIES_FILE_MANAGEMENT_CSV_HANDLE_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "../../entry/contact.h"
#include "../../entry/list.h"
#include "../limits.h"

enum csv_good_return_codes
{
    csv_return_good = 0,
    csv_return_bad_comma_count = 1,
    csv_return_spacebar_detected = 2
};

extern int max_contact_count;

#define DEFAULT_TABLE_SAVE_DIR "../tables/"

// Handle loading 

extern bool csv_load_table(char* path, Contact_t container_contact[], int contact_container_size);

// Handle saving

extern bool csv_save_table(char* path, Node_t* table[MAX_HASH_TABLE_ENTRIES]);

// Utilities

extern int csv_is_entry_good(char* line);
extern int csv_parse_file(char* path_to_csv);


#endif // APP_UTILITIES_FILE_MANAGEMENT_CSV_HANDLE_H
