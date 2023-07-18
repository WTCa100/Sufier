#ifndef APP_UTILITIES_ERROR_MESSAGES
#define APP_UTILITIES_ERROR_MESSAGES

#include <stdio.h>
#include <string.h>

#include "logger.h"

/**
 * @brief Displays simple error messages in standarized LOG format
 * @param _MSG_ Error message
 * @param _FAIL_REASON_ Cause of error
 * @return void
 */
#define ERR_MSG(_MSG_, _FAIL_REASON_) \
{ \
    LOG("%s %s", _MSG_, _FAIL_REASON_); \
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
// Hash & Hash related errors
#define ERR_HASH_COULD_NOT_GENERATE_HASH_KEY "Error. Could not generate hash key."
#define ERR_HASH_COULD_NOT_ADD_CONTACT "Error. Could not add contact."
#define ERR_HASH_COULD_NOT_DELETE_CONTACT "Error. Could not delete contact."
#define ERR_HASH_COULD_NOT_FIND_CONTACT "Error. Could not find contact in hash table."
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

//=========//
// Reasons //
//=========//
// Common
#define ERR_REASON_MEM_ALLOC_FAIL "Memory allocation failed."
#define ERR_REASON_STR_EMPTY "Provided string is empty."
// Hash & Hash related errors
#define ERR_REASON_HASH_INVALID_KEY "Hash key is invalid."
#define ERR_REASON_HASH_TABLE_FULL "Hash table is full."
#define ERR_REASON_HASH_TABLE_CONTACT_ABSENT "No such contact in the hash table."
// Node
#define ERR_REASON_NODE_CONTACT_NOT_PRESENT "Given contact is not present in this linked list."
#define ERR_REASON_NODE_EMPTY "Linked list is empty."
#define ERR_REASON_NODE_FULL "Linked list has reached it's maximum capacity."
#define ERR_REASON_NODE_HEAD_NULL "Node head is NULL."
// Contact
#define ERR_REASON_CONTACT_NULL "Contact cannot be NULL."

#endif // APP_UTILITIES_ERROR_MESSAGES