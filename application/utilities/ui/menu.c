#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "menu.h"

#include "../logger.h"
#include "../error_messages.h"

int gui_menu_display()
{
    char buffer[20];
    int choice = 0;
    LOG("User at menu display.");
    printf("Sufier - your easy to access hash-table.\n");
    printf("1. Add contact.\n");
    printf("2. Display/Edit contacts.\n");
    printf("3. Exit.\n");
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
        ERR_MSG(ERR_MENU_INVALID_OPTION, ERR_REASON_MENU_INVALID_OPTION);
        return option_bad;
    }
}

extern bool gui_menu_verify_input(int input)
{
    bool is_valid = (input == option_add || input == option_display || input == option_exit);
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