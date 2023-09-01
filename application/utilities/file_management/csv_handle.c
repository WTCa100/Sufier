#include <stdlib.h>

#include "./csv_handle.h"
#include "../logger.h"
#include "../error_messages.h"

int max_contact_count = MAX_LINKED_LIST_ENTRIES * MAX_HASH_TABLE_ENTRIES;

/// @brief This function will attempt to load data from given .csv files after an early line check.
/// @param path Where the csv file is located
/// @param container_contact Where extracted data shall be stored
/// @param contact_container_size How many entries are allowed.
/// @return true if no error false if at least one appears.
bool csv_load_table(char* path, Contact_t container_contact[], int contact_container_size)
{
    LOG("Attempting to load file from path %s with size %d.", path, contact_container_size);
    // 2 for 2 ','
    char buffer[MAX_EMAIL_LENGHT + MAX_NAME_LENGHT + MAX_PHONE_LENGHT + 2];
    char loaded_name[MAX_NAME_LENGHT];
    char loaded_phone[MAX_PHONE_LENGHT];
    char loaded_email[MAX_EMAIL_LENGHT];
    int contact_count = -1;

    LOG("Will open file from path %s", path);
    FILE* table_loading = fopen(path, "r");
    if(table_loading != NULL)
    {
        LOG("File opened. Parsing content...");
        while(fgets(buffer, sizeof(buffer), table_loading) != NULL)
        {             
            // get rid of the '/n' and replace it with '/0'
            buffer[strcspn(buffer, "\n")] = '\0';
            if(strcmp(buffer, "Name,Phone,Email") == 0)
            {
                continue;
            }
            // Check if buffer holds a valid line
            // This is only a initial check
            int is_line_good = csv_is_entry_good(buffer);
            switch (is_line_good)
            {
            case csv_return_good:
                break;
            case csv_return_bad_comma_count:
                LOG("Errornomous entry. %s - has bad comma count. Skipping...", buffer);
                break;
            case csv_return_spacebar_detected:
                LOG("Errornomous entry. %s - has illigal character ' '. Skipping...", buffer);
                break;
            default:
                LOG("Errornomous entry - skipping entry %s.", buffer);
                break;
            }
            
            ++contact_count; 
            if(is_line_good == 0)
            {
                LOG("Creating a valid contact_t entry. (From %s)", buffer);
                char* mod_buffer = (char*)malloc(strlen(buffer) + 1);
                strcpy(mod_buffer, buffer);

                // Tokenisize the modifiable buffer string
                char* token = strtok(mod_buffer, ",");

                // Copy the name
                strncpy(loaded_name, token, sizeof(loaded_name) - 1);
                token = strtok(NULL, ",");
                // Copy the phone number
                strncpy(loaded_phone, token, sizeof(loaded_phone) - 1);
                token = strtok(NULL, ",");
                // Copy the email address
                strncpy(loaded_email, token, sizeof(loaded_email) - 1);
                token = strtok(NULL, ",");
                free(mod_buffer);
            }
            else
            {
                LOG("Constructing empty container from invalid contact_t entry. (From %s). n = %d", buffer, contact_count);
                strcpy(loaded_name, "");
                strcpy(loaded_phone, "");
                strcpy(loaded_email, "");
            }

            if(contact_count < contact_container_size)
            {
                container_contact[contact_count] = contact_t_make(loaded_name, loaded_phone, loaded_email);
            }
        }
        LOG("All done, closing file.");
        fclose(table_loading);
    }
    else
    {
        ERR_MSG(ERR_COMMON_COULD_NOT_LOAD_FILE, ERR_REASON_COMMON_FILE_MISSING);
        return false;
    }

    return true;
}

/// @brief Checks if a given buffer line has any prohibited signs.
/// @param line
/// @return csv_enum value depending on the outcome.
/// @note Those sings are spacebars and bigger count of commas than 2.
int csv_is_entry_good(char* line)
{
    // Add verbose LOG here 
    char* line_ptr = line;

    // Look for commas and check if any ' ' occurs
    int comma_count = 0;
    while(*line_ptr != 0)
    {
        if(*line_ptr == ',')
        {
            ++comma_count;
            ++line_ptr;
            continue;
        }
        // There shall be no 
        if(*line_ptr == ' ')
        {
            return csv_return_spacebar_detected;
        }

        ++line_ptr;
    } 

    if(comma_count == 2)
    {
        return csv_return_good;
    }
    
    return csv_return_bad_comma_count;
}

/// @brief This function will attempt to given hash_table in a specified path.
/// @param path Where should the file be located
/// @param table Content to be extracted
/// @return true if extracted sucessfully false if any error occurs.
extern bool csv_save_table(char* path, Node_t* table[MAX_HASH_TABLE_ENTRIES])
{
    LOG("Attempting to save table at %s", path);
    if(table == NULL)
    {
        ERR_MSG(ERR_CSV_COULD_NOT_SAVE_TABLE, ERR_REASON_CSV_TABLE_EMPTY_OR_NULL);
        return false;
    }

    FILE* table_out = fopen(path, "w");
    if(table_out == NULL)
    {
        ERR_MSG(ERR_CSV_COULD_NOT_SAVE_TABLE, ERR_REASON_CSV_BAD_DIRECTORY);
        return false;
    }

    LOG("Will parse table (ref. %p)", table);
    for(int ll_id = 0; ll_id < MAX_HASH_TABLE_ENTRIES; ll_id++)
    {
        if(table[ll_id] == NULL)
        {
            LOG("Entry empty (%d). Skipping...", ll_id);
            continue;
        }

        Node_t* list_parser = table[ll_id];
        // Write header
        fprintf(table_out, "name,phone,email\n");
        while(list_parser != NULL)
        {
            fprintf(table_out, "%s,%s,%s\n", list_parser->data.name, list_parser->data.phone_number, list_parser->data.email_address);
            list_parser = list_parser->next;
        }
    }    

    // All done here.
    LOG("Successfully extracted hash_table into %s", path);
    fclose(table_out);
    return true;

}

/// @brief Function parses through CSV file and counts each line.
/// @param path_to_csv valid path to a csv file
/// @return Count of valid lines.
int csv_parse_file(char* path_to_csv)
{  
    LOG("Parsing %s", path_to_csv);
    FILE* csv = fopen(path_to_csv, "r");

    // Check if valid path
    if(csv == NULL)
    {
        ERR_MSG(ERR_CSV_COULD_NOT_PARSE_FILE, ERR_REASON_COMMON_FILE_MISSING);
        return -1;
    }

    // Start counting
    int counter = 0;
    char buffer[2048];
    while(fgets(buffer, sizeof(buffer), csv))
    {
        ++counter;
    }

    LOG("From %s got %d entires.", path_to_csv, counter);
    return counter;
}