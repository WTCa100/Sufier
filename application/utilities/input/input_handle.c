#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for strdup
#include <ctype.h>

#include "input_handle.h"
#include "../logger.h"
#include "../error_messages.h"

/// @brief Constructs a Contact_t instance, and puts it into a pointer passed by the user. It will prompt for name, phone an e-mail address.
/// In addition, it will modify input provided by the user (i.e. Delete whitespaces, turn e-mail into a lower case version). Additionally, it will 
/// verify every attribute passed in a attribute oriented function. 
/// @param contact_new refference to an existing instance 
/// @return 1 if contact_t was constructed 0 if not
bool input_get_contact_info(Contact_t* contact_new)
{

    char buffer[MAX_INPUT_LENGHT];
    char tmp_name[MAX_NAME_LENGHT]   = "";
    char tmp_phone[MAX_PHONE_LENGHT] = "";
    char tmp_mail[MAX_EMAIL_LENGHT]  = "";

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
    input_str_to_lower(buffer);
    if(input_is_email_valid(buffer))
    {
        sscanf(buffer, "%s\n", tmp_mail);
    }

    // Clean buffer
    memset(buffer, 0, sizeof(buffer));

    if(strlen(tmp_name) > 0 && strlen(tmp_phone) > 0 && strlen(tmp_mail) > 0)
    {
        *contact_new = contact_t_make(tmp_name, tmp_phone, tmp_mail);
        return true;
    }

    ERR_MSG(ERR_INPUT_COULD_NOT_CREATE_CONNTACT, ERR_REASON_BAD_CONTACT_ARGUMENT);
    return false;

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

/// @brief Checks if inputed phone number is within range of 9-15 and if consists only of numbers
/// @param input_phone 
/// @return 1 if all conditions are met 0 if at least one is not
bool input_is_phone_valid(char* input_phone)
{
    if(strlen(input_phone) == 0)
    {
        ERR_MSG(ERR_INPUT_INVALID_PHONE_NUMBER, ERR_REASON_STR_EMPTY);
        return false;
    }

    // Check lenght
    if(strlen(input_phone) != 9)
    {
        ERR_MSG(ERR_INPUT_INVALID_PHONE_NUMBER, ERR_REASON_INPUT_PHONE_INVALID_LENGHT);
        return false;
    }

    if(strlen(input_phone) > MAX_PHONE_LENGHT)
    { 
        ERR_MSG_BAD_LENGHT(ERR_INPUT_INVALID_PHONE_NUMBER, MAX_PHONE_LENGHT);
        return false;
    }


    // Check if it's all digit
    for(int i = 0; i < strlen(input_phone); i++)
    {
        if(!isdigit(input_phone[i]))
        {
            ERR_MSG(ERR_INPUT_INVALID_PHONE_NUMBER, ERR_REASON_INPUT_PHONE_ONLY_DIGIT)
            return false;
        }
    }
    LOG("%s is valid phone number.", input_phone);
    return true;
}

/// @brief Checkf is provided e-mail address is withing range of 1 and 320 characters, contains "\@" character, does not 2 consecutive dots and has a valid TLD.
/// @param input_email 
/// @return 1 if all conditions are met 0 if at least one is not
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

    /*
    After giving this topic a study, I decided to resign from checking e-mail address using RegEx. 
    Reason: When it comes to Regex implementation it is tricky, and despite having a simple check already implemented, there is no reason to check in-depth validity of the email.
    Most of on-line softwares are validating e-mails by sending a verification message. However in this simple program there is no need on checking the validity of an email as 
    it's provided either by the user or by different software piece that shall have a valid e-mail addresses already in it's memory. In addition, verification not base on regex will
    avoid potential ReDoS attempts. 

    Result: As a result there will be only 3 checks regarding email address.
    1. If '@' symbol exists - as it separates local part from domain part
    2. If there are no 2 consecutive '.' symbols - as this is prohibited by RFC 5322 (Page 13)
    3. If there is a valid TLD at the end of email address
    */
   // Look for @ symbol
    if(!strchr(input_email, '@'))
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_INPUT_EMAIL_NO_AT);
        return false;
    }

    if(!strrchr(strrchr(input_email, '@'), '.'))
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_INPUT_EMAIL_NO_TLD_SEP);
        return false;
    }
    // Check for double dot
    if(strstr(input_email, ".."))
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_INPUT_EMAIL_DOUBLE_DOT);
        return false;
    }

    if(!input_check_email_TLD(input_email))
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_INPUT_EMAIL_NO_TLD);
        return false;
    }

    LOG("%s is a valid email.", input_email);
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

/// @brief Checks if input has a valid TLD (Top-Level Domain) that is covered in TLDs.txt file. 
/// It will check only a slice of input, that is the first occurence of "." symbol after "@" symbol, and it will compare it to a lower case version of buffer entry.
/// @param input provided email
/// @return 1 - if input has TLD that is inside TLDs.txt 0 - if error occurs or no such extension in TLDs.txt.
extern bool input_check_email_TLD(char* input)
{
    FILE* Tld_list = fopen(TLDS_PATH, "r");
    char buffer[MAX_TLD_LENGHT]; // The longest TLD has 24 characters

    bool has_TLD = false;
    int line = 0;
    if(Tld_list == NULL)
    {
        ERR_MSG(ERR_COMMON_COULD_NOT_LOAD_FILE, ERR_REASON_FILE_MISSING);
        return false;
    }
    while(fgets(buffer, sizeof(buffer), Tld_list) != NULL)
    {
        if(line == 0)
        {
            ++line;
            continue;
        }
        input_str_to_lower(buffer);

        // Swap \n with \0
        if(buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        char* input_tld = strrchr(input, '.');
        if(strcmp(input_tld, buffer) == 0)
        {
            LOG("%s has valid TLD of \"%s\".", input, buffer);
            has_TLD = true;
            break;
        }
        ++line;
    }

    fclose(Tld_list);

    if(has_TLD)
    {
        return true;
    }
    else
    {
        ERR_MSG(ERR_INPUT_INVALID_EMAIL_ADDRESS, ERR_REASON_INPUT_EMAIL_NO_TLD);
        return false;
    }
}

/**
 * @brief Turns provided string into a lower case version
 * @param input string to change
 */
void input_str_to_lower(char* input)
{
    for(int i = 0; i < strlen(input); ++i)
    {
        input[i] = tolower(input[i]);
    }
}