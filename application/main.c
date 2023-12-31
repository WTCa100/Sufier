#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "entry/contact.c"
#include "entry/list.h"
#include "utilities/logger.h"
#include "utilities/input/input_handle.h"
#include "utilities/ui/menu.h"
#include "utilities/limits.h"
#include "utilities/file_management/csv_handle.h"

Node_t* hash_table[MAX_HASH_TABLE_ENTRIES] = {NULL};

uint16_t hash_key_calculate(char* entry);
bool hash_contact_add(Contact_t* contact_add);
bool hash_contact_delete(char* contact_delete);
bool hash_contact_edit(char* contact_edit);
bool hash_table_load();
bool hash_table_save();
void hash_contact_display(char* contact_display);
Contact_t* hash_contact_get(char* contact_get);
void hash_list_parse_linked(void);
void hash_destroy(void);

int main(int argc, char const *argv[])
{
    // Start log file for easier debug
    LOG_FILE_CREATE();

    int user_option = 0;
    // Core functionality
    do
    {
        int user_option_file = 0;
        do
        {
            user_option = ui_menu_display();
        } while (!ui_menu_verify_input(user_option, menu_main));
        LOG("User option: %d", user_option);

        switch (user_option)
        {
        case option_add:
            LOG("User Selection \"add\"");
            Contact_t tmp;
            if(input_get_contact_info(&tmp))
            {
                if(hash_contact_add(&tmp))
                {
                    printf("New contact has been added!\n");
                }
            }
            break;
        case option_display:
            LOG("User Selection \"display\"");
            char tmp_name_dsp[MAX_NAME_LENGHT];
            if(input_get_contact_name(tmp_name_dsp))
            {
                hash_contact_display(tmp_name_dsp);
            }
            break;
        case option_show_all:
            LOG("User Selection \"show all\"");
            hash_list_parse_linked();
            break;
        case option_edit:
            LOG("User Selection \"edit\"");
            char tmp_name_edt[MAX_NAME_LENGHT];
            if(input_get_contact_name(tmp_name_edt))
            {
                if(hash_contact_edit(tmp_name_edt))
                {
                    printf("Contact edited succesfully!\n");
                }
            }
            break;
        case option_delete:
            LOG("User Selection \"delete\"");
            char tmp_name_del[MAX_NAME_LENGHT];
            if(input_get_contact_name(tmp_name_del))
            {
                if(input_get_is_sure())
                {
                    if(hash_contact_delete(tmp_name_del))
                    {
                        printf("Contact has been deleted.\n");
                    }

                }
                else
                {
                    LOG("Aborted by the user. No changes were made.");
                    printf("Aborted by the user.\n");
                }
            }
            break;
        case option_file_management:
            LOG("User Selection \"file management\"")
            system("clear");
            do
            {
                user_option_file = ui_menu_file_display();
            } while (!ui_menu_verify_input(user_option_file, menu_file_management));
            
            switch (user_option_file)
            {
            case menu_file_load:
                LOG("User Selection \"table load\"");
                hash_table_load();
                break;
            case menu_file_save:
                LOG("User Selection \"table save\"");
                if(hash_table_save())
                {
                    printf("Table saved!\n");
                }
                break;
            case menu_file_back:
                LOG("User Selection \"back\"")
                break;
            }

            break;
        case option_erase:
            // Give extra caution measures!
            LOG("User Selection \"erase\" - !!!DANGER_ZONE!!!");
            printf("Warning! Completing this action will complete wipe all the data from the hash table.");
            printf("This cannot be un-done, and will lead to loss of data.\n");
            if(input_get_is_sure())
            {
                hash_destroy();
            }
            else
            {
                LOG("Aborted by the user. No changes were made.");
                printf("Aborted by the user.\n");
            }
            break;
        case option_exit:
            LOG("User Selection \"exit\"");
            printf("Exiting Sufier...\n");
            hash_destroy();
            break;
        default:
            LOG("User Selection uknown");
            break;
        }

        if(user_option != option_exit)
        {
            printf("Press any key to continue.\n");
            getchar();
            system("clear");
        }
    }   while(user_option != option_exit);

    LOG_FILE_PROGRAM_END();
    return 0;
}

/// @brief Calculate hash key with the following rules: Every digit of entry (contact_t -> name)
/// @param entry base to generate key
/// @return key (0 - MAX_HASH_TABLE_ENTRIES) if success. MAX_HASH_TABLE_ENTRIES + 1 if fail
uint16_t hash_key_calculate(char* entry)
{
    if(entry == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_GENERATE_HASH_KEY, ERR_REASON_CONTACT_NULL);
        return MAX_HASH_TABLE_ENTRIES + 1;
    }

    LOG("Calculating hash key for entry Name: %s", entry);

    uint16_t key = 0;
    for(int character = 0; character < strlen(entry); ++character)
    {
        if(!(entry[character] == ' '))
        {
            key += (uint16_t)(entry[character] - 'a');
        }
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
bool hash_contact_add(Contact_t* contact_add)
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
    uint16_t hash_key = hash_key_calculate(contact_add->name);

    // Check if key is valid
    if(hash_key > MAX_HASH_TABLE_ENTRIES)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_HASH_INVALID_KEY);
        return 0;
    }

    // Check for duplicates
    LOG("Checking if %s is a duplicated.", contact_add->name);
    Contact_t* tmp_dup_check = hash_contact_get(contact_add->name);

    if(tmp_dup_check != NULL)
    {
        LOG("Found a duplicate.");
        ERR_MSG(ERR_HASH_COULD_NOT_ADD_CONTACT, ERR_REASON_HASH_CONTACT_DUP);
        return false;
    }

    // If we are here then no duplicate was found. Reset the values.
    LOG("No duplicated contact with name %s was found. Proceeding.", contact_add->name);
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

/// @brief This function will search for given contact, and delet it if found.
/// @param contact_delete name of the contact
/// @return true if found and deleted, false otherwise
bool hash_contact_delete(char* contact_delete)
{
    LOG("Attempting to delete %s", contact_delete);
    if(contact_delete == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_DELETE_CONTACT, ERR_REASON_CONTACT_NULL);
        return 0;
    }

    // Generate key
    uint16_t hash_key = hash_key_calculate(contact_delete);

    // tmp variables
    uint16_t tmp_key = hash_key;
    bool was_full_loop = false;

    // Find contact to delete (similar to adding function)
    while(!was_full_loop)
    {
        LOG("Checking key: %d", tmp_key);
        // Check hashed head
        if(node_t_delete_contact(contact_delete, &hash_table[tmp_key]))
        {
            LOG("Deleted entry %s from hash table.", contact_delete);
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

/// @brief Searches for contact in the hash table and tries to change it's values to the new ones.
/// @param contact_edit name of the contact to be edited.
/// @return true if edited successfully, false otherwise 
bool hash_contact_edit(char* contact_edit)
{
    LOG("Attempting to edit contact with name %s", contact_edit);
    LOG("Trying to locate contact.");
    Contact_t* contact_old = hash_contact_get(contact_edit);
    if(contact_old == NULL)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_EDIT_CONTACT, ERR_REASON_HASH_TABLE_CONTACT_ABSENT);
        return false;
    }

    printf("Old contact Values: \n");
    contact_t_display_format(contact_old);
    LOG("Get new values.");
    Contact_t contact_new_info;
    if(input_get_contact_info(&contact_new_info))
    {
        LOG("Attempting to change contact data.");
        LOG("Check if new contact name can be a duplicate.");
        Contact_t* contact_check_dup = hash_contact_get(contact_new_info.name);
        
        // Basically check if the new contact is not a duplicate while also not being the same name as the one being currently edited.
        if(contact_check_dup != NULL && strcmp(contact_old->name, contact_new_info.name) != 0)
        {
            ERR_MSG(ERR_HASH_COULD_NOT_EDIT_CONTACT, ERR_REASON_HASH_CONTACT_NEW_NAME_DUP);
            return false;
        }
        
        // Check if values are the same
        if(contact_t_compare(contact_old, &contact_new_info))
        {
            LOG("New values are the same as old ones. Nothing to change.");
            printf("New values are the same as old ones. Nothing to change.\n");
            return true;
        }

        /** @todo Ask if user is sure (this cannot be undone!)*/
        if(input_get_is_sure())
        {
            LOG_CHANGE(contact_new_info.name, contact_new_info.phone_number, contact_new_info.email_address,
                    contact_old->name, contact_old->phone_number, contact_old->email_address);
            // Assing the values
            strcpy(contact_old->name, contact_new_info.name);
            strcpy(contact_old->phone_number, contact_new_info.phone_number);
            strcpy(contact_old->email_address, contact_new_info.email_address);
            return true;
        }
        else
        {
            LOG("Aborted by the user. No changes were made.");
            printf("Aborted by the user.\n");
            return false;
        }
        
    }
    
    ERR_MSG(ERR_HASH_COULD_NOT_EDIT_CONTACT, ERR_REASON_HASH_TABLE_CONTACT_ABSENT);
    return false;
}

/// @brief This function will start the process of loading .csv file contents into this file memory.
/// @return true if success, false otherwise.
bool hash_table_load()
{
    char path_to_table[MAX_INPUT_LENGHT];
    int contact_count = 0;        
    if(!input_get_file(path_to_table))
    {
        ERR_MSG(ERR_CSV_COULD_NOT_LOAD_TABLE, ERR_REASON_CSV_FILE_INVALID_PATH)
        return false;
    }

    contact_count = csv_parse_file(path_to_table);
    if(contact_count == -1)
    {
        return false;
    }

    Contact_t contact_list[contact_count];
    csv_load_table(path_to_table, contact_list, contact_count);
    for(int c_id = 0; c_id < contact_count; ++c_id)
    {
        printf("Loading %s\n", contact_list[c_id].name);
        if(hash_contact_add(&contact_list[c_id]))
        {
            printf("Successfully loaded %s.\n", contact_list[c_id].name);
        }
    }

    LOG("Successfully extracted contacts from file %s.", path_to_table);
    printf("Successfully extracted contacts from file %s.\n", path_to_table);
    return true;
}

/// @brief This function will start the process of saving the current hash table into a safe file
/// @return outcome of csv_save_table
bool hash_table_save()
{
    char path_to_table[MAX_INPUT_LENGHT];    
    if(!input_get_file(path_to_table))
    {
        ERR_MSG(ERR_CSV_COULD_NOT_LOAD_TABLE, ERR_REASON_CSV_FILE_INVALID_PATH)
        return false;
    }

    return csv_save_table(path_to_table, hash_table);
}

/// @brief Displays specified contact after finding it in hash_table
/// @param contact_display 
void hash_contact_display(char* contact_display)
{
    Contact_t* tmp_contact = hash_contact_get(contact_display);
    if(tmp_contact != NULL)
    {
        LOG("Displaying contact: %s", contact_display);
        contact_t_show(tmp_contact);
        return;
    }

    // No need for new error message as it's being displayed inside contact_t_show.
    return;
}

/// @brief This function will try to get poitner to contact_t instance if present inside hash table
/// @param contact_get name of the contact
/// @return non-NULL pointer if success, NULL if fail.
Contact_t* hash_contact_get(char* contact_get)
{
    uint16_t hash_key = hash_key_calculate(contact_get);

    if(hash_key > MAX_HASH_TABLE_ENTRIES)
    {
        ERR_MSG(ERR_HASH_COULD_NOT_FIND_CONTACT, ERR_REASON_HASH_INVALID_KEY);
        return NULL;
    }

    uint16_t tmp_key = hash_key;
    bool was_full_loop = false;
    // Search for contact in the entire linked list
    Node_t* contact_find;
    while(!was_full_loop)
    {
        LOG("Checking key: %d", tmp_key);
        // Check hashed head
        contact_find = node_t_find_contact(contact_get, hash_table[tmp_key]);
        if(contact_find != NULL)
        {
            LOG("Displaying contact found at hash val %d", tmp_key);
            return &contact_find->data;
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

    LOG("%s %s", ERR_HASH_COULD_NOT_FIND_CONTACT, ERR_REASON_HASH_TABLE_CONTACT_ABSENT);
    return NULL;
}

/// @brief This function will parse throught hash_table heads and if head is not null it will parse linked list with this head
void hash_list_parse_linked(void)
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