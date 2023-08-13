#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "entry/contact.c"
#include "entry/list.h"
#include "utilities/logger.h"
#include "utilities/input/input_handle.h"
#include "utilities/ui/menu.h"

// later on change to 256
#define MAX_HASH_TABLE_ENTRIES 10

Node_t* hash_table[MAX_HASH_TABLE_ENTRIES] = {NULL};

uint16_t hash_calculate_key(Contact_t* entry);
bool hash_add_contact(Contact_t* contact_add);
bool hash_delete_contact(Contact_t* contact_delete);
void hash_display_contact(Contact_t* contact_display);
void hash_parse_linked_list(void);
void hash_destroy(void);

int main(int argc, char const *argv[])
{
    LOG_FILE_CREATE();
    int user_option = 0;
    do
    {
        do
        {
            user_option = ui_menu_display();
        } while (!ui_menu_verify_input(user_option));
        printf("User option: %d\n", user_option);

        switch (user_option)
        {
        case option_add:
            LOG("User Selection \"add\"");
            Contact_t tmp;
            if(input_get_contact_info(&tmp))
            {
                hash_add_contact(&tmp);
            }
            break;
        case option_display:
            LOG("User Selection \"display\"");
            hash_parse_linked_list();
            break;
        case option_exit:
            LOG("User Selection \"exit\"");
            hash_destroy();
            break;
        default:
            LOG("User Selection uknown");
            break;
        }

    }   while(user_option != option_exit);

    LOG_FILE_PROGRAM_END();
    return 0;
}

/// @brief Calculate hash key with the following rules: First letter of entry's name + every digit of phone number + size of TLD % MAX_HASH_TABLE_ENTRIES
/// @param entry base to generate key
/// @return key (0 - MAX_HASH_TABLE_ENTRIES) if success. MAX_HASH_TABLE_ENTRIES + 1 if fail
uint16_t hash_calculate_key(Contact_t* entry)
{
    if(entry == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_GENERATE_HASH_KEY, ERR_REASON_CONTACT_NULL);
        return MAX_HASH_TABLE_ENTRIES + 1;
    }

    LOG("Calculating hash key for entry Name: %s Phone: %s Email: %s", entry->name, entry->phone_number, entry->email_address);

    uint16_t key = entry->name[0] % 26;
    for(int digit = 0; digit < strlen(entry->phone_number); ++digit)
    {
        if(!(entry->phone_number[digit] == ' '))
        {
            key += (uint16_t)(entry->phone_number[digit] - '0');
        }
    }

    char* tmp_tld;  
    tmp_tld = strrchr(entry->email_address, '.');
    for(int TLD_char = 0; TLD_char < strlen(tmp_tld); ++TLD_char)
    {
        key += (uint16_t)tmp_tld[TLD_char];
    }

    LOG("Key created %d.", key % MAX_HASH_TABLE_ENTRIES);
    return key % MAX_HASH_TABLE_ENTRIES;
}

/// @brief This function will attempt to add contact at head of a hash_table at generated hash_key location.
/// After validating if provided Contact_t is a valid instance, function will also search if the entry is a duplicate.
/// Key created by using solely entry's name thus no 2 entries with the same name as it would lead to very big mess.
/// If no place was found at hash table head then it will push back the linked list if possible.
/// If not it will search for the next avilable spot to insert contact.
/// @param contact_add Contact to be inserted
/// @return 1 if success 0 if fail
bool hash_add_contact(Contact_t* contact_add)
{
    // Check if contact is valid
    if(contact_add == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_CONTACT_NULL);
        return 0;
    }

    if(!contact_t_check_atr(contact_add->name, contact_add->phone_number, contact_add->email_address))
    {
        ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_HASH_INVALID_CONTACT);
        return 0;
    }

    // Generate key
    uint16_t hash_key = hash_calculate_key(contact_add);

    // Check if key is valid
    if(hash_key > MAX_HASH_TABLE_ENTRIES)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_HASH_INVALID_KEY);
        return 0;
    }

    int tmp_key = hash_key;
    bool was_full_loop = false;

    while(!was_full_loop)
    {
        // Look for first free spot at generated hash
        LOG("Checking if head with key %d is empty.", tmp_key);
        if(hash_table[tmp_key] == NULL)
        {
            LOG("Head with key %d is empty!", tmp_key);
            hash_table[tmp_key] = node_t_init(contact_add);
            LOG("Succesfully added entry at head: %p", hash_table[tmp_key]);
            return 1;
        }

        // Add to the linked list with head at current hash key head
        LOG("Head was occupied. Will try to add to linked list.");
        if(node_t_push_back(contact_add, hash_table[tmp_key]))
        {
            LOG("Succesfully added entry to linked list with head at %p", hash_table[tmp_key]);
            return 1;
        }

        // If linked list was full search for next valid linked list
        ++tmp_key;

        // Assign zero if upper boundry is reached
        if(tmp_key == MAX_HASH_TABLE_ENTRIES)
        {
            tmp_key = 0;
        }

        // Break if full loop
        if(tmp_key == hash_key)
        {
            was_full_loop = true;
        }
    }

    // If we are here then there is no way that the value was added.
    ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_HASH_TABLE_FULL);
    return 0;
}

bool hash_delete_contact(Contact_t* contact_delete)
{
    if(contact_delete == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_DELETE_CONTACT, ERR_REASON_CONTACT_NULL);
        return 0;
    }

    // Generate key
    uint16_t hash_key = hash_calculate_key(contact_delete);

    // tmp variables
    uint16_t tmp_key = hash_key;
    bool was_full_loop = false;

    // Find contact to delete (similar to adding function)
    while(!was_full_loop)
    {
        LOG("Checking key: %d", hash_key);
        // Check hashed head
        if(node_t_delete_contact(contact_delete, &hash_table[tmp_key]))
        {
            LOG("Deleted entry from hash table!");
            return 1;
        }

        // If linked list was full search for next valid linked list
        ++tmp_key;

        // Assign zero if upper boundry is reached
        if(tmp_key == MAX_HASH_TABLE_ENTRIES)
        {
            tmp_key = 0;
        }

        // Break if full loop
        if(tmp_key == hash_key)
        {
            was_full_loop = true;
        }
    }

    return 1;
}

/// @brief Displays specified contact after finding it in hash_table
/// @param contact_display 
void hash_display_contact(Contact_t* contact_display)
{
    uint16_t hash_key = hash_calculate_key(contact_display);

    if(hash_key > MAX_HASH_TABLE_ENTRIES)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_FIND_CONTACT, ERR_REASON_HASH_INVALID_KEY);
        return;
    }

    uint16_t tmp_key = hash_key;
    bool was_full_loop = false;
    // Search for contact in the entire linked list
    Node_t* contact_find;
    while(!was_full_loop)
    {
        LOG("Checking key: %d", tmp_key);
        // Check hashed head
        contact_find = node_t_find_contact(contact_display, hash_table[tmp_key]);
        if(contact_find != NULL)
        {
            LOG("Displaying contact found at hash val %d", tmp_key);
            contact_t_show(&contact_find->data);
            return;
        }

        // If linked list was full search for next valid linked list
        ++tmp_key;

        // Assign zero if upper boundry is reached
        if(tmp_key == MAX_HASH_TABLE_ENTRIES)
        {
            tmp_key = 0;
        }

        // Break if full loop
        if(tmp_key == hash_key)
        {
            was_full_loop = true;
        }
    }

    ERR_MSG(ERR_HASH_COULD_NOT_FIND_CONTACT, ERR_REASON_HASH_TABLE_CONTACT_ABSENT);
    return;
}

/// @brief This function will parse throught hash_table heads and if head is not null it will parse linked list with this head
/// @param  
void hash_parse_linked_list(void)
{
    LOG("Parsing Linked List.");
    printf("Parsing hash table.\n");
    for(int hash_id = 0; hash_id < MAX_HASH_TABLE_ENTRIES; hash_id++)
    {
        printf("Start of linked list\n");
        if(hash_table[hash_id] != NULL)
        {
            LOG("At key %d - val %p", hash_id, hash_table[hash_id]);
            node_t_parse_list(hash_table[hash_id]);
        }
        else
        {
            LOG("At key %d - empty", hash_id);
            printf("-=Empty=-\n");
        }
        printf("End of linked list\n");
    }
    return;
}

/// @brief Function will deallocate memory for every linked list inside a hash table 
void hash_destroy(void)
{
    LOG("Destroying hash table.");
    for(int head_id = 0; head_id < MAX_HASH_TABLE_ENTRIES; head_id++)
    {
        LOG("Checking head %p.", hash_table[head_id]);
        if(hash_table[head_id] != NULL)
        {
            LOG("%p has value - deleting linked list.", hash_table[head_id]);
            node_t_destroy(&hash_table[head_id]);
        }
    }
    return;
}