#include <stdio.h>
#include <string.h>

#include "../utilities/logger.h"
#include "../utilities/error_messages.h"
#include "./contact.h"

/// @brief This function will construct Contact_t with arguments provided by the user
/// @param in_name name that will be partly used in hashing function later on
/// @param in_phone_number phone number that will be entirely used in hashing function later on 
/// @param in_email_address new contact email address
/// @return Contact_t instance. Depening if all arguments are valid it can be fully constructed or empty.
/// @note If at least one of the arguments provided is invalid, function will return empty Contact_t instance.
Contact_t contact_t_make(char in_name[MAX_NAME_LENGHT], char in_phone_number[MAX_PHONE_LENGHT], char in_email_address[MAX_EMAIL_LENGHT])
{

    Contact_t new_contact;

    // Check if provided arguments are valid
    if(!contact_t_check_atr(in_name, in_phone_number, in_email_address))
    {
        LOG("Returining an empty contact.");
        strcpy(new_contact.name, "");
        strcpy(new_contact.phone_number, "");
        strcpy(new_contact.email_address, "");
        return new_contact;
    }

    LOG("Creating values to new contact");
    strcpy(new_contact.name,          in_name);
    strcpy(new_contact.phone_number,  in_phone_number);
    strcpy(new_contact.email_address, in_email_address);

    LOG("Created entry: Name: %s Phone: %s Email: %s", new_contact.name, new_contact.phone_number, new_contact.email_address);
    
    return new_contact;
}

/// @brief Function displays information about specified contact.
/// @note This function is dedicated for the user
/// @param this desired contact
void contact_t_show(Contact_t* this)
{
    if(this == NULL)
    {
        ERR_MSG(ERR_CONTACT_COULD_NOT_DISPLAY_DATA, ERR_REASON_CONTACT_NULL);
        return;
    }

    if(!contact_t_check_atr(this->name, this->phone_number, this->email_address))
    {
        ERR_MSG(ERR_CONTACT_COULD_NOT_DISPLAY_DATA, ERR_REASON_BAD_CONTACT_ARGUMENT);
        return;
    }

    LOG("Showing contact info.");
    contact_t_display_format(this);
    return;
}

/// @brief Displays desired contact in a standarized way
/// @param  this desired contact
void contact_t_display_format(Contact_t* this)
{
    if(this == NULL)
    {
        ERR_MSG(ERR_CONTACT_COULD_NOT_DISPLAY_DATA, ERR_REASON_CONTACT_NULL);
        return;
    }
    printf("Name: %s\n",          this->name);
    printf("Phone Number: %s\n",  this->phone_number);
    printf("Email address: %s\n", this->email_address);
}

bool contact_t_compare(Contact_t* this, Contact_t* com)
{
    if(this == NULL || com == NULL)
    {
        ERR_MSG(ERR_CONTACT_COULD_NOT_BE_COMPARED, ERR_REASON_CONTACT_NULL);
        return 0;
    }

    LOG("Comparing:\n %s - %s \n %s - %s \n %s - %s", this->name, com->name, this->phone_number, com->phone_number, this->email_address, com->phone_number);

    return (strcmp(this->name, com->name) == 0 &&
            strcmp(this->phone_number, com->phone_number) == 0 &&
            strcmp(this->email_address, com->email_address) == 0);
}

/// @brief This function will check if passed attributes are valid
/// @param check_name 
/// @param check_phone_number 
/// @param check_email_address 
/// @return 1 if all are valid 0 if at least on is invallid
bool contact_t_check_atr(char check_name[MAX_NAME_LENGHT], char check_phone_number[MAX_PHONE_LENGHT], char check_email_address[MAX_EMAIL_LENGHT])
{
    LOG("Checking arguments name: %s phone: %s mail: %s", check_name, check_phone_number, check_email_address);    
    if(strlen(check_name) == 0 || strlen(check_phone_number) == 0 || strlen(check_email_address) == 0)
    {
        LOG(ERR_REASON_BAD_CONTACT_ARGUMENT);
        return 0;
    }
    else
    {
        LOG("Provided arguments are valid")
        return 1;
    }
}