#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#include "input_handle.h"
#include "../logger.h"
#include "../error_messages.h"

Contact_t input_get_contact_info(void)
{

    char buffer[MAX_INPUT_LENGHT];
    char tmp_name[MAX_NAME_LENGHT];
    char tmp_phone[MAX_PHONE_LENGHT];
    char tmp_mail[MAX_EMAIL_LENGHT];

    LOG("Getting contact info from user.");
    printf("To add new contact please specify: \n");
    printf("Name: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Remove tailing newline
    buffer[strcspn(buffer, "\n")] = '\0';
    LOG("Got %s", buffer);
    // Remove double spaces if present
    input_remove_double_spaces(buffer);
    if(input_is_name_valid(buffer))
    {
        sscanf(buffer, "%s\n", tmp_name);
    }

    // Clean buffer
    memset(buffer, 0, sizeof(buffer));

    printf("Phone Number: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    buffer[strcspn(buffer, "\n")] = '\0';
    LOG("Got %s", buffer);
    if(input_is_phone_valid(buffer))
    {
        sscanf(buffer, "%s\n", tmp_phone);
    }

    memset(buffer, 0, sizeof(buffer));

    printf("Email Address: ");
    fgets(buffer, sizeof(buffer), stdin);
    
    buffer[strcspn(buffer, "\n")] = '\0';
    LOG("Got %s", buffer);
    if(input_is_phone_valid(buffer))
    {
        sscanf(buffer, "%s\n", tmp_mail);
    }

    // Clean buffer
    memset(buffer, 0, sizeof(buffer));

    return contact_t_make(tmp_name, tmp_phone, tmp_mail);
}

/// @brief Checks if input is longer than the max ammount of characters
/// @param input_name provided name
/// @return 1 if valid 0 if not valid
bool input_is_name_valid(char* input_name)
{
    if(strlen(input_name) == 0)
    {
        ERR_MSG(ERR_INPUT_INVALID_NAME, ERR_REASON_STR_EMPTY);
        return false;
    }
    // Check lenght 
    if(strlen(input_name) > MAX_NAME_LENGHT)
    {
        ERR_MSG_BAD_LENGHT(ERR_INPUT_INVALID_NAME, MAX_NAME_LENGHT);
        return false;
    }
    return true;
}

bool input_is_phone_valid(char* input_phone)
{
    if(strlen(input_phone) == 0)
    {
        ERR_MSG(ERR_INPUT_INVALID_PHONE_NUMBER, ERR_REASON_STR_EMPTY);
        return false;
    }

    // Check lenght
    if(strlen(input_phone) > MAX_PHONE_LENGHT)
    { 
        ERR_MSG_BAD_LENGHT(ERR_INPUT_INVALID_PHONE_NUMBER, MAX_PHONE_LENGHT);
        return false;
    }
    
    // @todo Make sure to implement checking if only digits are present
    // Remember that phone numbers may have +[country number] so '+' may also appear at the beggining
    return true;
}

bool input_is_email_valid(char* input_email)
{

    if(strlen(input_email) == 0)
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_STR_EMPTY);
        return false;
    }

    // Check if full email address is within range
    if(strlen(input_email) > MAX_EMAIL_LENGHT)
    {
        ERR_MSG_BAD_LENGHT(ERR_INPUT_INVALID_EMAIL_ADDRESS, MAX_EMAIL_LENGHT);
        return false;
    }


    return true;
}

/// @brief This function will remove double spaces from input.
/// @param input 
/// @return 
void input_remove_double_spaces(char* input)
{
    LOG("Attempting to remove double spacing in input %s", input);
    char* p_to_str  = input;
    bool prev_space = false;
    // Parse through input string
    for(char* input_src = input; *input_src != 0; input_src++)
    {
        // if this current pointer and previous space is a space do nothing
        if(*input_src == ' ' && prev_space)
        {
            continue;
        }
        // assign value of input source into destination
        *p_to_str++ = *input_src;
        // Check for space before incrementation
        prev_space = (*input_src == ' ');
    }

    // Null termination
    *p_to_str = '\0';
    LOG("Sucessfully remove double spaces - new string %s", input);
    return;
}