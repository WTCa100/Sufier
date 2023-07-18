#ifndef APP_UTILITIES_INPUT_INPUT_HANDLE_H
#define APP_UTILITIES_INPUT_INPUT_HANDLE_H

#include <stdbool.h>

#define MAX_INPUT_LENGHT 500

#include "../../entry/contact.h"

// Get input

extern Contact_t input_get_contact_info(void);

// Validate input

extern bool input_is_name_valid(char* input_name);
extern bool input_is_phone_valid(char* input_phone);
extern bool input_is_email_valid(char* input_email);

// Utilities

extern void input_remove_double_spaces(char* input);

#endif //APP_UTILITIES_INPUT_INPUT_HANDLE_H