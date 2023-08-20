#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./list.h"
#include "../utilities/error_messages.h"
#include "../utilities/logger.h"

/// @brief This function created additional node.
/// After successful memory allocation, initial contact is assigned to `data` attribute.
/// @param contact_init
/// @return Valid node pointer or NULL after memory allocation fail.
Node_t* node_t_init(Contact_t* contact_init)
{
    Node_t* new_node = malloc(sizeof(Node_t));

    if(new_node == NULL)
    {
        ERR_MSG(ERR_NODE_COULD_NOT_CREATE_NODE, ERR_REASON_COMMON_MEM_ALLOC_FAIL);
        return NULL;
    }
    new_node->data = *contact_init;
    new_node->next = NULL;
    return new_node;
}

/// @brief Parses throught the entire list and displays contat information
/// @param head Initial node entry
void node_t_parse_list(Node_t* head)
{
    Node_t* tmp_pointer = head;
    LOG("Will parse throught list (head %p)", head);
    while(tmp_pointer != NULL)
    {
        contact_t_show(&tmp_pointer->data);
        printf(" |  |\n");
        printf("\\|  |/\n");
        printf(" \\  /\n");
        printf("  \\/\n");
        tmp_pointer = tmp_pointer->next;
    }
    printf("--== NULL ==--\n");
    LOG("Successfully parsed entire list (head at %p)", head);
    return;
}

/// @brief 
/// @param contact_add 
/// @param head 
/// @return 
bool node_t_push_back(Contact_t* contact_add, Node_t* head)
{
    LOG("Attempting to add new contact: Name: %s Phone: %s Email: %s", contact_add->name, contact_add->phone_number, contact_add->email_address);
    // Check if head is empty
    if(contact_add == NULL)
    {
        ERR_MSG(ERR_NODE_COULD_NOT_ADD_CONTACT, ERR_REASON_CONTACT_NULL);
        return 0;
    }
    if(head == NULL)
    {
        LOG("Head is empty");
        LOG("Adding to head.");
        head = node_t_init(contact_add);
        
        // Check if memory was allocated succesfully
        if(head == NULL)
        {
            return 0;
        }
        return 1;
    }

    // If not, parse linked list until a free spot is present
    LOG("Head not empty, will search for new node.");
    Node_t* tmp_prev    = head;
    Node_t* tmp_pointer = head->next;
    uint16_t pos = 1;
    while(pos < MAX_LINKED_LIST_ENTRIES)
    {
        LOG("Checking node %p (head at %p).", tmp_pointer, head)
        if(tmp_pointer == NULL)
        {
            LOG("Found free node.");
            tmp_pointer = node_t_init(contact_add);
            tmp_prev->next = tmp_pointer;
            LOG("Target added at %p.", tmp_pointer);
            LOG("Successfully added new contact into list with head at %p", head);
            return 1;
        }
        LOG("Occupied.");
        tmp_prev    = tmp_pointer;
        tmp_pointer = tmp_pointer->next;
        ++pos;
    }

    LOG("Could not find any free space in list with head %p", head);
    ERR_MSG(ERR_NODE_COULD_NOT_ADD_CONTACT, ERR_REASON_NODE_FULL);
    return 0;
}

/// @brief This function will display provided entry at linked list with given head
/// It will search for a specified entry until it reached end of linked list 
/// @param contact_search name of the contact to be found
/// @param head target linked list
/// @return NULL if contact_search is absent 
Node_t* node_t_find_contact(char* contact_search, Node_t* head)
{

    if(head == NULL)
    {
        LOG("%s %s",ERR_NODE_COULD_NOT_FIND_CONTACT, ERR_REASON_NODE_EMPTY);
        return NULL;
    }

    if(contact_search == NULL)
    {
        ERR_MSG(ERR_NODE_COULD_NOT_FIND_CONTACT, ERR_REASON_CONTACT_NULL);
        return NULL;
    }

    Node_t* tmp = head;
    LOG("Will try to find contact in list with head at: %p", head);
    LOG("Contact: Name: %s", contact_search);

    while (tmp != NULL)
    {
        LOG("Checking %p", tmp);
        if(strcmp(contact_search, tmp->data.name) == 0)
        {
            LOG("Found contact at %p", tmp);
            return tmp;
        }
        tmp = tmp->next;
    }
    

    LOG("%s%s", ERR_NODE_COULD_NOT_FIND_CONTACT, ERR_REASON_NODE_CONTACT_NOT_PRESENT);
    return NULL;
}

/// @brief Function will try to delete specified contact in linked list with given head.
/// Function will first check if head contains specified entry - delete it and create a new head.
/// If it's not at head it will traverse the entire linked list until the contact will be deleted or
/// if reached end of linked list.
/// @param contact_delete entry to be deleted
/// @param head linked list head pointer
/// @return 1 is success 0 if fail
bool node_t_delete_contact(char* contact_delete, Node_t** head)
{
    LOG("Attempting to delete contact: Name: %s - LL Head at %p", contact_delete, *head);
    // Check if contact is at head
    if(strcmp(contact_delete, (*head)->data.name) == 0)
    {
        LOG("Found contact at head %p", *head);
        Node_t* new_head = (*head)->next;
        (*head)->next = NULL;
        free(*head);
        *head = new_head;
        LOG("Deleted contact from head. New head %p", *head);
        return 1;
    }
    // Traverse linked list in order to find desired contact
    else
    {
        LOG("Not at head, will traverse linked list");
        Node_t* tmp_prev_pointer = (*head);
        Node_t* tmp_pointer = tmp_prev_pointer->next;
        while(tmp_pointer != NULL)
        {
            LOG("Checking %p", tmp_pointer);
            if(strcmp(tmp_pointer->data.name, contact_delete) == 0)
            {
                LOG("Deleting contact from %p", tmp_pointer);
                tmp_prev_pointer->next = tmp_pointer->next;
                tmp_pointer->next = NULL;
                free(tmp_pointer);
                LOG("Deleted contact from list (head at %p)", *head);
                return 1;
            }

            tmp_prev_pointer = tmp_pointer;
            tmp_pointer = tmp_pointer->next;
        }
    }

    LOG("Could not locate target");
    return 0;
}

/// @brief Destructs existing instance of linked list
/// @param head list head
void node_t_destroy(Node_t** head)
{
    if(*head == NULL && head == NULL)
    {
        LOG("Provided entry is already empty.");
        ERR_MSG(ERR_NODE_COULD_NOT_DELETE_NODE, ERR_REASON_NODE_HEAD_NULL);
        return;
    }

    // Parse throught the linked list and search for entries
    LOG("Attempting to destroy node with head at: %p", *head);
    Node_t* parser = (*head)->next;
    while(parser != NULL)
    {
        // Assign new value to head
        (*head)->next = parser->next;
        LOG("Checking %p", parser);

        // Free encountered value
        parser->next = NULL;
        free(parser);
        parser = (*head)->next;
    }

    // After every entry deleted - deallocate head
    LOG("Deleting head %p", (*head));
    (*head)->next = NULL;
    free(*head);
    *head = NULL;
    LOG("Deallocated linked list!");
    return;
}