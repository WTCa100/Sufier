#include <stdio.h>
#include <string.h>

#include "../utilities/logger.h"
#include "../utilities/error_messages.h"
#include "./contact.h"

Contact_t contact_t_make(char in_name[MAX_NAME_LENGHT], char in_phone_number[MAX_PHONE_LENGHT], char in_email_address[MAX_EMAIL_LENGHT])
{
    LOG("Creating values to new contact");
    Contact_t new_contact;
    strcpy(new_contact.name,          in_name);
    strcpy(new_contact.phone_number,  in_phone_number);
    strcpy(new_contact.email_address, in_email_address);

    LOG("Created entry: ");
    contact_t_display_format(&new_contact);
    
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

    LOG("Comparing: ");
    contact_t_display_format(this);
    printf("with: \n");
    contact_t_display_format(com);

    return (strcmp(this->name, com->name) == 0 &&
            strcmp(this->phone_number, com->phone_number) == 0 &&
            strcmp(this->email_address, com->email_address) == 0);
}