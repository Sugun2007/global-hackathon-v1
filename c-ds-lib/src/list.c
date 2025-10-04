/**
 * @file list.c
 * @brief Linked list data structure implementation
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This file implements the linked list data structure with memory management
 * and learning mode support for educational purposes.
 */

#include "ds_list.h"
#include <stdlib.h>  /* for malloc, free */
#include <stdio.h>   /* for printf */

/**
 * @brief Internal node structure for linked list
 * 
 * Each node contains a pointer to data and a pointer to the next node.
 * The list structure maintains pointers to head and tail for efficient operations.
 */
struct ds_list_node {
    void *data;                    /**< Pointer to user data */
    struct ds_list_node *next;     /**< Pointer to next node */
};

/**
 * @brief Internal list structure
 * 
 * Contains head and tail pointers for efficient insertion operations.
 * Size is cached for O(1) size queries.
 */
struct ds_list {
    struct ds_list_node *head;     /**< Pointer to first node */
    struct ds_list_node *tail;     /**< Pointer to last node */
    size_t size;                   /**< Number of elements in list */
};

/**
 * @brief Internal flag for learning mode
 * 
 * When enabled, memory operations are logged for educational purposes.
 */
static int learning_mode = 0;

/**
 * @brief Memory allocation wrapper with learning mode support
 * 
 * Allocates memory and optionally logs the operation when learning mode is enabled.
 * 
 * @param n Number of bytes to allocate
 * @return Pointer to allocated memory, or NULL on failure
 */
void *ds_alloc(size_t n) {
    void *ptr = malloc(n);
    
#ifdef DS_LEARNING_MODE
    if (learning_mode) {
        printf("[LEARN] malloc(%zu) = %p\n", n, ptr);
    }
#endif
    
    return ptr;
}

/**
 * @brief Memory deallocation wrapper with learning mode support
 * 
 * Deallocates memory and optionally logs the operation when learning mode is enabled.
 * 
 * @param p Pointer to memory to deallocate
 */
void ds_free(void *p) {
#ifdef DS_LEARNING_MODE
    if (learning_mode && p) {
        printf("[LEARN] free(%p)\n", p);
    }
#endif
    
    free(p);
}

/**
 * @brief Enable or disable learning mode
 * 
 * @param enable Non-zero to enable, zero to disable
 */
void ds_enable_learning_mode(int enable) {
    learning_mode = enable;
}

/**
 * @brief Dump current state of all data structures
 * 
 * Currently not implemented - placeholder for future functionality.
 */
void ds_dump_state(void) {
    if (learning_mode) {
        printf("[LEARN] ds_dump_state() - not yet implemented\n");
    }
}

/**
 * @brief Create a new empty linked list
 * 
 * Allocates and initializes a new linked list structure with head and tail
 * set to NULL and size set to 0.
 * 
 * @return Pointer to new list on success, NULL on memory allocation failure
 */
ds_list_t *ds_list_create(void) {
    ds_list_t *list;
    
    // Allocate memory for list structure
    list = (ds_list_t *)ds_alloc(sizeof(struct ds_list));
    if (list == NULL) {
        return NULL;
    }
    
    // Initialize list to empty state
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}

/**
 * @brief Free a linked list and optionally its data
 * 
 * Iterates through all nodes, optionally calls free_data for each element's
 * data pointer, then deallocates all nodes and the list structure itself.
 * 
 * @param L Pointer to list to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if L is NULL
 */
ds_error_t ds_list_free(ds_list_t *L, void (*free_data)(void *)) {
    struct ds_list_node *current, *next;
    
    // Validate input parameter
    if (L == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Iterate through all nodes and free them
    current = L->head;
    while (current != NULL) {
        next = current->next;
        
        // Call user's free function for data if provided
        if (free_data != NULL && current->data != NULL) {
            free_data(current->data);
        }
        
        // Free the node structure
        ds_free(current);
        current = next;
    }
    
    // Free the list structure
    ds_free(L);
    
    return DS_OK;
}

/**
 * @brief Insert element at the front of the list
 * 
 * Adds a new element to the beginning of the list. Updates head pointer
 * and increments size. For empty lists, also updates tail pointer.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to insert
 * @return DS_OK on success, DS_ERR_NULLARG if L or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_list_push_front(ds_list_t *L, void *data) {
    struct ds_list_node *new_node;
    
    // Validate input parameters
    if (L == NULL || data == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Allocate memory for new node
    new_node = (struct ds_list_node *)ds_alloc(sizeof(struct ds_list_node));
    if (new_node == NULL) {
        return DS_ERR_OOM;
    }
    
    // Initialize new node
    new_node->data = data;
    new_node->next = L->head;
    
    // Update list pointers
    L->head = new_node;
    if (L->tail == NULL) {
        // First element - update tail as well
        L->tail = new_node;
    }
    L->size++;
    
    return DS_OK;
}

/**
 * @brief Insert element at the back of the list
 * 
 * Adds a new element to the end of the list. Updates tail pointer
 * and increments size. For empty lists, also updates head pointer.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to insert
 * @return DS_OK on success, DS_ERR_NULLARG if L or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_list_push_back(ds_list_t *L, void *data) {
    struct ds_list_node *new_node;
    
    // Validate input parameters
    if (L == NULL || data == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Allocate memory for new node
    new_node = (struct ds_list_node *)ds_alloc(sizeof(struct ds_list_node));
    if (new_node == NULL) {
        return DS_ERR_OOM;
    }
    
    // Initialize new node
    new_node->data = data;
    new_node->next = NULL;
    
    // Update list pointers
    if (L->tail == NULL) {
        // First element - update both head and tail
        L->head = new_node;
        L->tail = new_node;
    } else {
        // Add to end - update tail
        L->tail->next = new_node;
        L->tail = new_node;
    }
    L->size++;
    
    return DS_OK;
}

/**
 * @brief Remove and return element from the front of the list
 * 
 * Removes the first element from the list and returns its data.
 * Updates head pointer and decrements size. If list becomes empty,
 * also updates tail pointer to NULL.
 * 
 * @param L Pointer to list
 * @return Pointer to data of removed element, or NULL if list is empty or L is NULL
 */
void *ds_list_pop_front(ds_list_t *L) {
    struct ds_list_node *old_head;
    void *data;
    
    // Validate input parameter
    if (L == NULL) {
        return NULL;
    }
    
    // Check if list is empty
    if (L->head == NULL) {
        return NULL;
    }
    
    // Get old head and its data
    old_head = L->head;
    data = old_head->data;
    
    // Update list pointers
    L->head = old_head->next;
    if (L->head == NULL) {
        // List became empty - update tail as well
        L->tail = NULL;
    }
    L->size--;
    
    // Free the old head node
    ds_free(old_head);
    
    return data;
}

/**
 * @brief Remove element matching comparison criteria
 * 
 * Searches for the first element that matches the comparison function
 * and removes it from the list. Updates size and pointer connections.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to match against
 * @param cmp Comparison function returning 0 for match
 * @return DS_OK on success, DS_ERR_NULLARG if L, data, or cmp is NULL, DS_ERR_NOTFOUND if no match
 */
ds_error_t ds_list_remove(ds_list_t *L, void *data, int (*cmp)(const void *, const void *)) {
    struct ds_list_node *current, *previous;
    
    // Validate input parameters
    if (L == NULL || data == NULL || cmp == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Search for matching node
    current = L->head;
    previous = NULL;
    
    while (current != NULL) {
        if (cmp(current->data, data) == 0) {
            // Found match - remove the node
            if (previous == NULL) {
                // Removing head node
                L->head = current->next;
                if (L->head == NULL) {
                    L->tail = NULL;  // List became empty
                }
            } else {
                // Removing middle or tail node
                previous->next = current->next;
                if (current == L->tail) {
                    L->tail = previous;  // Update tail if removing last node
                }
            }
            
            L->size--;
            ds_free(current);
            return DS_OK;
        }
        
        previous = current;
        current = current->next;
    }
    
    // No match found
    return DS_ERR_NOTFOUND;
}

/**
 * @brief Find element matching comparison criteria
 * 
 * Searches for the first element that matches the comparison function
 * when compared against the target data. The comparison function should
 * return 0 when the element matches the target.
 * 
 * @param L Pointer to list
 * @param target Pointer to data to match against
 * @param cmp Comparison function returning 0 for match
 * @return Pointer to matching data, or NULL if not found or L/cmp/target is NULL
 */
void *ds_list_find(ds_list_t *L, void *target, int (*cmp)(const void *, const void *)) {
    struct ds_list_node *current;
    
    // Validate input parameters
    if (L == NULL || target == NULL || cmp == NULL) {
        return NULL;
    }
    
    // Search through list
    current = L->head;
    while (current != NULL) {
        if (cmp(current->data, target) == 0) {
            // Found match
            return current->data;
        }
        current = current->next;
    }
    
    // No match found
    return NULL;
}

/**
 * @brief Get the number of elements in the list
 * 
 * Returns the current size (number of elements) of the list.
 * This is an O(1) operation since size is cached.
 * 
 * @param L Pointer to list
 * @return Number of elements in list, or 0 if L is NULL
 */
size_t ds_list_size(const ds_list_t *L) {
    if (L == NULL) {
        return 0;
    }
    
    return L->size;
}

/**
 * @brief Visualize the list structure
 * 
 * Prints a graphical representation of the list to the specified output stream.
 * Shows each node with its data value and connections between nodes.
 * 
 * @param L Pointer to list
 * @param out Output stream (e.g., stdout, stderr)
 */
void ds_list_visualize(const ds_list_t *L, FILE *out) {
    struct ds_list_node *current;
    int count = 0;
    
    // Handle NULL parameters gracefully
    if (out == NULL) {
        out = stdout;  // Default to stdout
    }
    
    if (L == NULL) {
        fprintf(out, "List: NULL\n");
        return;
    }
    
    if (L->head == NULL) {
        fprintf(out, "List: [empty] (size: %zu)\n", L->size);
        return;
    }
    
    // Print list header
    fprintf(out, "List: (size: %zu)\n", L->size);
    
    // Print each node
    current = L->head;
    while (current != NULL) {
        fprintf(out, "  [%d]: ", count);
        
        if (current->data != NULL) {
            // Try to print as integer first (most common case)
            fprintf(out, "%d", *(int*)current->data);
        } else {
            fprintf(out, "NULL");
        }
        
        // Mark special nodes
        if (current == L->head) {
            fprintf(out, " [HEAD]");
        }
        if (current == L->tail) {
            fprintf(out, " [TAIL]");
        }
        
        fprintf(out, "\n");
        
        current = current->next;
        count++;
    }
    
    fprintf(out, "\n");
}

