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

//========//
// Errors //
//========//
// Hash & Hash related errors
#define ERR_HASH_COULD_NOT_GENERATE_HASH_KEY "Error. Could not generate hash key."
#define ERR_HASH_COULD_NOT_ADD_CONTACT "Error. Could not add contact."
// Node
#define ERR_NODE_COULD_NOT_CREATE_NODE "Error. Could not create node."
#define ERR_NODE_COULD_NOT_ADD_CONTACT "Error. Could not add contact."
#define ERR_NODE_COULD_NOT_DELETE_NODE "Error. Could not delete node."
// Contact
#define ERR_CONTACT_COULD_NOT_DISPLAY_DATA "Error. Could not display contact."
#define ERR_CONTACT_COULD_NOT_BE_COMPARED "Error. Could not compare contacts."

//=========//
// Reasons //
//=========//
// Common
#define ERR_REASON_MEM_ALLOC_FAIL "Memory allocation failed."
// Hash & Hash related errors
#define ERR_REASON_HASH_INVALID_KEY "Hash key is invalid."
#define ERR_REASON_HASH_TABLE_FULL "Hash table is full."
// Node
#define ERR_REASON_NODE_FULL "Linked list has reached it's maximum capacity."
#define ERR_REASON_NODE_HEAD_NULL "Node head is NULL."
// Contact
#define ERR_REASON_CONTACT_NULL "Contact cannot be NULL."

#endif // APP_UTILITIES_ERROR_MESSAGES