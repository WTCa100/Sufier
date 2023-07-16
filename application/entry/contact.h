#ifndef APP_ENTRIES_CONTACT_H
#define APP_ENTRIES_CONTACT_H

#include <stdbool.h>

#define MAX_NAME_LENGHT 64                                                                                                                                                                                                                                                                                         
#define MAX_PHONE_LENGHT 15                                                                                                                                                                                                                                                                                             
#define MAX_EMAIL_LENGHT 320

//+------------------------+---+--------------------------+
//|                        |   |                          |
//| 64 Octests (loal part) | @ | 255 Octest (domain part) |
//|                        |   |                          |
//+------------------------+---+--------------------------+

typedef struct
{
    char name[MAX_NAME_LENGHT];
    char phone_number[MAX_PHONE_LENGHT];
    char email_address[MAX_EMAIL_LENGHT];
} Contact_t;

Contact_t contact_t_make(char in_name[MAX_NAME_LENGHT], char in_phone_number[MAX_PHONE_LENGHT], char in_email_address[MAX_EMAIL_LENGHT]);
void contact_t_show(Contact_t* this);
void contact_t_display_format(Contact_t* this);
bool contact_t_compare(Contact_t* this, Contact_t* com);

#endif // APP_ENTRIES_CONTACT_H
