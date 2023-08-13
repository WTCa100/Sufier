#ifndef APP_ENTRIES_LIST_H
#define APP_ENTRIES_LIST_H

#define MAX_LINKED_LIST_ENTRIES 10

#include <stdbool.h>

#include "./contact.h"


struct Node
{
    Contact_t        data;
    struct Node*     next;
};

typedef struct Node Node_t;

Node_t* node_t_init(Contact_t* contact_init);
bool    node_t_push_back(Contact_t* contact_add, Node_t* head);
bool    node_t_delete_contact(char* contact_delete, Node_t** head);
Node_t* node_t_find_contact(char* contact_search, Node_t* head);
void    node_t_parse_list(Node_t* head);
void    node_t_destroy(Node_t** head);

#endif // APP_ENTRIES_LIST_H