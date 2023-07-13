#include <stdio.h>
#include <stdlib.h>

#include "./list.h"
#include "../utilities/error_messages.h"
#include "../utilities/logger.h"

/// @brief This function created additional node.
/// After successful memory allocation, initial contact is assigned to `data` attribute.
/// @param contact_init
/// @return Valid node pointer or NULL after memory allocation fail.
Node_t* node_t_init(Contact_t* contact_init)
{
    Node_t* new_node = malloc(sizeof(Contact_t));

    if(new_node == NULL)
    {
        ERR_MSG(ERR_COULD_NOT_CREATE_NODE, ERR_REASON_MEM_ALLOC_FAIL);
        return NULL;
    }
    new_node->data = *contact_init;
    new_node->next = NULL;
    return new_node;
}

bool node_t_push_back(Contact_t* contact_add, Node_t* head)
{
    // Check if head is empty
    if(contact_add == NULL)
    {
        ERR_MSG(ERR_COULD_NOT_ADD_CONTACT, ERR_REASON_CONTACT_NULL);
        return 0;
    }
    if(head == NULL)
    {
        LOG("Head is empty");
        printf("Adding to head.\n");
        head = node_t_init(contact_add);
        
        // Check if memory was allocated succesfully
        if(head == NULL)
        {
            return 0;
        }
        return 1;
    }

    // If not, parse linked list until a free spot is present
    Node_t* tmp_pointer = head->next;
    while(tmp_pointer != NULL)
    {
        if(tmp_pointer == NULL)
        {

        }
    }

    return 0;
}