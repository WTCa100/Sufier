#ifndef APP_UTILITIES_UI_MENU_H
#define APP_UTILITIES_UI_MENU_H

#include <stdbool.h>

#include "../logger.h"

#define BAD_OPTION -1

enum menu_options
{
    option_add = 1,
    option_display = 2,
    option_exit = 3,
    option_bad = -1
};

extern int gui_menu_display();
extern bool gui_menu_verify_input(int input);

#endif // APP_UTILITIES_UI_MENU_H