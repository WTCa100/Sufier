#ifndef APP_UTILITIES_UI_MENU_H
#define APP_UTILITIES_UI_MENU_H

#include <stdbool.h>

#include "../logger.h"

#define BAD_OPTION -1

enum menu_options
{
    option_add = 1,
    option_display = 2,
    option_show_all = 3,
    option_edit = 4,
    option_delete = 5,
    option_file_management = 6,
    option_erase = 7,
    option_exit = 8,
    option_bad = -1
};

// Display

extern int ui_menu_display();
extern int ui_menu_file_display();

// Utilities

extern bool ui_menu_verify_input(int input);

#endif // APP_UTILITIES_UI_MENU_H