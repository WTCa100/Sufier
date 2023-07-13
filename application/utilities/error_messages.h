#ifndef APP_UTILITIES_ERROR_MESSAGES
#define APP_UTILITIES_ERROR_MESSAGES

#include <stdio.h>

#define ERR_MSG(_MSG_,  _FAIL_REASON_) \
{ \
    printf("%s", _MSG_);\
    printf(" ");\
    printf("%s\n", _FAIL_REASON_); \
}

// Errors
#define ERR_COULD_NOT_CREATE_NODE "Error. Could not create node."
#define ERR_COULD_NOT_ADD_CONTACT "Error. Could not add contact."

// Reasons
#define ERR_REASON_MEM_ALLOC_FAIL "Memory allocation failed."
#define ERR_REASON_CONTACT_NULL "Contact cannot be NULL."

#endif // APP_UTILITIES_ERROR_MESSAGES