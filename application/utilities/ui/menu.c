#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "menu.h"

#include "../logger.h"
#include "../error_messages.h"

int ui_menu_display()
{
    char buffer[20];
    int choice = 0;
    LOG("User at menu display.");
    printf("Sufier - your easy to access hash-table.\n");
    printf("1. Add contact.\n");
    printf("2. Display.\n");
    printf("3. Show all contacts.\n");
    printf("4. Edit contact.\n");
    printf("5. Delete Contact.\n");
    printf("6. File Management. (loading/saving etc.)\n");
    // This option leads to a different menu
    printf("7. Erase hash_table. (Danger Zone)\n");
    printf("8. Exit.\n");
    printf("Choose one option: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Replace '\n' with '\0' if necessery
    if(buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }
    LOG("User input: %s", buffer);
    if(isdigit(buffer[0]))
    {
        sscanf(buffer, "%d", &choice);
        return choice;
    }
    else
    {
        ERR_MSG(ERR_MENU_INVALID_OPTION, ERR_REASON_COMMON_INVALID_OPTION);
        return option_bad;
    }
}

int ui_menu_file_display()
{
    char buffer[20];
    int choice;
    printf("File management.\n");
    printf("1. Load table from file.\n");
    printf("2. Save current table to a file.\n");
    // printf("3. Delete file with table.\n"); Optional
    printf("3. Back.\n");
    fgets(buffer, sizeof(buffer), stdin);

    // Replace '\n' with '\0' if necessery
    if(buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }
    LOG("User input: %s", buffer);
    if(isdigit(buffer[0]))
    {
        choice = buffer[0] - '0';
        return choice;
    }
    else
    {
        ERR_MSG(ERR_MENU_INVALID_OPTION, ERR_REASON_COMMON_INVALID_OPTION);
        return option_bad;
    }

}

bool ui_menu_verify_input(int input)
{
    bool is_valid = (input >= option_add && input <= option_exit);
    if(is_valid)
    {
        LOG("%d is valid option", input);
    }
    else
    {
        LOG("%d is invalid option", input);
        printf("Invalid option!\n");
        getchar();
        system("clear");
    }
    return is_valid;
}
