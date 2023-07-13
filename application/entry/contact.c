#include <stdio.h>
#include <string.h>

#include "../utilities/logger.h"
#include "./contact.h"

Contact_t contact_t_make(char in_name[MAX_NAME_LENGHT], char in_phone_number[MAX_PHONE_LENGHT], char in_email_address[MAX_EMAIL_LENGHT])
{
    LOG("Creating values to new contact");
    Contact_t new_contact;
    strcpy(new_contact.name,          in_name);
    strcpy(new_contact.phone_number,  in_phone_number);
    strcpy(new_contact.email_address, in_email_address);
    return new_contact;
}

void contact_t_show(Contact_t* this)
{
    LOG("Showing contact info.");
    printf("Name: %s\n",          this->name);
    printf("Phone Number: %s\n",  this->phone_number);
    printf("Email address: %s\n", this->email_address);
    return;
}