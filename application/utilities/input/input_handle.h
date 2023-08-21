#ifndef APP_UTILITIES_INPUT_INPUT_HANDLE_H
#define APP_UTILITIES_INPUT_INPUT_HANDLE_H

#include <stdbool.h>

#define TLDS_PATH "utilities/input/TLDs.txt"

#include "../../entry/contact.h"
#include "./limits.h"

// Get input

extern bool input_get_contact_info(Contact_t* contact_new);
extern bool input_get_contact_name(char s_name[MAX_NAME_LENGHT]);
extern bool input_get_is_sure();

// Validate input

extern bool input_is_name_valid(char* input_name);
extern bool input_is_phone_valid(char* input_phone);
extern bool input_is_email_valid(char* input_email);

// Utilities

extern void input_remove_double_spaces(char* input);
extern bool input_check_email_TLD(char* input);
extern void input_str_to_lower(char* input);

#endif //APP_UTILITIES_INPUT_INPUT_HANDLE_H