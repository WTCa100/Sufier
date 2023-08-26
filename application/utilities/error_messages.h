#ifndef APP_UTILITIES_ERROR_MESSAGES
#define APP_UTILITIES_ERROR_MESSAGES

#include <stdio.h>
#include <string.h>

#include "logger.h"

/**
 * @brief Displays simple error messages in standarized LOG format. This inputs the message into stdout and a file stream
 * @param _MSG_ Error message
 * @param _FAIL_REASON_ Cause of error
 */
#define ERR_MSG(_MSG_, _FAIL_REASON_) \
{ \
    LOG("%s %s", _MSG_, _FAIL_REASON_); \
    ERR_MSG_DISPLAY(_MSG_, _FAIL_REASON_); \
}

/**
 * @brief Displays the error message in standrized format same as LOG but only in the terminal.
 * @param _MSG_ Error message
 * @param _FAIL_REASON_ Cause of error
 */
#define ERR_MSG_DISPLAY(_MSG_, _FAIL_REASON_) \
{ \
    printf("%s %s\n", _MSG_, _FAIL_REASON_); \
}

/**
 * @brief Displays error in format: _MSG_ - "Provided input exceedes the limit " _MAX_LENGHT_. 
 * @param _MSG_ Error message (where did the error occured)
 * @param _MAX_LENGHT_ Maximum lenght of specified variable such as name, phone, email etc.
 */
#define ERR_MSG_BAD_LENGHT(_MSG_, _MAX_LENGHT_) \
{ \
    LOG("%s %s %d", _MSG_, "Provided input exceedes the limit ", _MAX_LENGHT_); \
}

//========//
// Errors //
//========//
// Common / Misc
#define ERR_COMMON_PLAIN "Error ocured."
#define ERR_COMMON_COULD_NOT_LOAD_FILE "Error. Could not load file."
// Hash & Hash related errors
#define ERR_HASH_COULD_NOT_GENERATE_HASH_KEY "Error. Could not generate hash key."
#define ERR_HASH_COULD_NOT_ADD_CONTACT "Error. Could not add contact."
#define ERR_HASH_COULD_NOT_DELETE_CONTACT "Error. Could not delete contact."
#define ERR_HASH_COULD_NOT_FIND_CONTACT "Error. Could not find contact in hash table."
#define ERR_HASH_COULD_NOT_EDIT_CONTACT "Error. Could not edit desired contact."
// Node
#define ERR_NODE_COULD_NOT_CREATE_NODE "Error. Could not create node."
#define ERR_NODE_COULD_NOT_ADD_CONTACT "Error. Could not add contact."
#define ERR_NODE_COULD_NOT_DELETE_NODE "Error. Could not delete node."
#define ERR_NODE_COULD_NOT_FIND_CONTACT "Error. Could not find contact in given linked list."
// Contact
#define ERR_CONTACT_COULD_NOT_DISPLAY_DATA "Error. Could not display contact."
#define ERR_CONTACT_COULD_NOT_BE_COMPARED "Error. Could not compare contacts."
// Input
#define ERR_INPUT_INVALID_NAME "Error. Provided name is invalid."
#define ERR_INPUT_INVALID_PHONE_NUMBER "Error. Provided Phone Number is invalid."
#define ERR_INPUT_INVALID_EMAIL_ADDRESS "Error. Provided Email Address is invalid."
#define ERR_INPUT_COULD_NOT_CREATE_CONNTACT "Error. Could not create contact."
#define ERR_INPUT_UNABLE_TO_PROCEED "Error. Cannot proceed."
// Menu/Gui
#define ERR_MENU_INVALID_OPTION "Error. Cannot complete request."
// CSV
#define ERR_CSV_COULD_NOT_SAVE_TABLE "Error. Could not save file."

//=========//
// Reasons //
//=========//
// Common
#define ERR_REASON_COMMON_MEM_ALLOC_FAIL "Memory allocation failed."
#define ERR_REASON_COMMON_STR_EMPTY "Provided string is empty."
#define ERR_REASON_COMMON_BAD_CONTACT_ARGUMENT "One or more parameters are invalid."
#define ERR_REASON_COMMON_FILE_MISSING "No such file in directory."
#define ERR_REASON_COMMON_INVALID_OPTION "There is no such option. Please enter a valid option."
// Hash & Hash related errors
#define ERR_REASON_HASH_INVALID_KEY "Hash key is invalid."
#define ERR_REASON_HASH_TABLE_FULL "Hash table is full."
#define ERR_REASON_HASH_TABLE_CONTACT_ABSENT "No such contact in the hash table."
#define ERR_REASON_HASH_INVALID_CONTACT "Contact seems to have an invalid attribute/attributes."
#define ERR_REASON_HASH_CONTACT_DUP "Contact name duplicate conflict."
#define ERR_REASON_HASH_CONTACT_NEW_NAME_DUP "New name would conflict with existing records."
// Node
#define ERR_REASON_NODE_CONTACT_NOT_PRESENT "Given contact is not present in this linked list."
#define ERR_REASON_NODE_EMPTY "Linked list is empty."
#define ERR_REASON_NODE_FULL "Linked list has reached it's maximum capacity."
#define ERR_REASON_NODE_HEAD_NULL "Node head is NULL."
// Contact
#define ERR_REASON_CONTACT_NULL "Contact cannot be NULL."
// Input
#define ERR_REASON_INPUT_PHONE_INVALID_LENGHT "Phone number must contain at least 9 digits."
#define ERR_REASON_INPUT_PHONE_ONLY_DIGIT "Phone number must consists of numbers only."
#define ERR_REASON_INPUT_EMAIL_NO_AT "Email address must contain one '@' symbol."
#define ERR_REASON_INPUT_EMAIL_DOUBLE_DOT "Email address must not contain two consecutive dots \"..\"."
#define ERR_REASON_INPUT_EMAIL_NO_TLD_SEP "Email address must have a \".\" separating it's TLD."
#define ERR_REASON_INPUT_EMAIL_NO_TLD "Email address must have a valid TLD tag at the end."
// CSV
#define ERR_REASON_CSV_BAD_DIRECTORY "No such directory to be found."
#endif // APP_UTILITIES_ERROR_MESSAGES