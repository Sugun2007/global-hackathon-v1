/**
 * @file stack.c
 * @brief Stack data structure implementation
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This file implements the stack data structure using a linked list approach
 * with memory management and learning mode support.
 */

#include "ds_stack.h"
#include <stdlib.h>  /* for malloc, free */
#include <stdio.h>   /* for printf */

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
 * @brief Internal node structure for stack
 * 
 * Each node contains a pointer to data and a pointer to the next node.
 * The stack structure maintains a pointer to the top element.
 */
struct ds_stack_node {
    void *data;                    /**< Pointer to user data */
    struct ds_stack_node *next;    /**< Pointer to next node */
};

/**
 * @brief Internal stack structure
 * 
 * Contains top pointer and cached size for efficient operations.
 */
struct ds_stack {
    struct ds_stack_node *top;     /**< Pointer to top node */
    size_t size;                   /**< Number of elements in stack */
};

/**
 * @brief Create a new empty stack
 * 
 * Allocates and initializes a new stack structure with top set to NULL
 * and size set to 0.
 * 
 * @return Pointer to new stack on success, NULL on memory allocation failure
 */
ds_stack_t *ds_stack_create(void) {
    ds_stack_t *stack;
    
    // Allocate memory for stack structure
    stack = (ds_stack_t *)ds_alloc(sizeof(struct ds_stack));
    if (stack == NULL) {
        return NULL;
    }
    
    // Initialize stack to empty state
    stack->top = NULL;
    stack->size = 0;
    
    return stack;
}

/**
 * @brief Free a stack and optionally its data
 * 
 * Iterates through all nodes, optionally calls free_data for each element's
 * data pointer, then deallocates all nodes and the stack structure itself.
 * 
 * @param S Pointer to stack to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if S is NULL
 */
ds_error_t ds_stack_free(ds_stack_t *S, void (*free_data)(void *)) {
    struct ds_stack_node *current, *next;
    
    // Validate input parameter
    if (S == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Iterate through all nodes and free them
    current = S->top;
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
    
    // Free the stack structure
    ds_free(S);
    
    return DS_OK;
}

/**
 * @brief Push element onto the top of the stack
 * 
 * Adds a new element to the top of the stack. Updates top pointer
 * and increments size.
 * 
 * @param S Pointer to stack
 * @param data Pointer to data to push
 * @return DS_OK on success, DS_ERR_NULLARG if S or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_stack_push(ds_stack_t *S, void *data) {
    struct ds_stack_node *new_node;
    
    // Validate input parameters
    if (S == NULL || data == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Allocate memory for new node
    new_node = (struct ds_stack_node *)ds_alloc(sizeof(struct ds_stack_node));
    if (new_node == NULL) {
        return DS_ERR_OOM;
    }
    
    // Initialize new node
    new_node->data = data;
    new_node->next = S->top;
    
    // Update stack pointers
    S->top = new_node;
    S->size++;
    
    return DS_OK;
}

/**
 * @brief Pop element from the top of the stack
 * 
 * Removes the top element from the stack and returns its data.
 * Updates top pointer and decrements size.
 * 
 * @param S Pointer to stack
 * @return Pointer to data of popped element, or NULL if stack is empty or S is NULL
 */
void *ds_stack_pop(ds_stack_t *S) {
    struct ds_stack_node *old_top;
    void *data;
    
    // Validate input parameter
    if (S == NULL) {
        return NULL;
    }
    
    // Check if stack is empty
    if (S->top == NULL) {
        return NULL;
    }
    
    // Get old top and its data
    old_top = S->top;
    data = old_top->data;
    
    // Update stack pointers
    S->top = old_top->next;
    S->size--;
    
    // Free the old top node
    ds_free(old_top);
    
    return data;
}

/**
 * @brief Peek at the top element without removing it
 * 
 * Returns the data of the top element without modifying the stack.
 * 
 * @param S Pointer to stack
 * @return Pointer to top element's data, or NULL if stack is empty or S is NULL
 */
void *ds_stack_peek(const ds_stack_t *S) {
    // Validate input parameter
    if (S == NULL) {
        return NULL;
    }
    
    // Check if stack is empty
    if (S->top == NULL) {
        return NULL;
    }
    
    return S->top->data;
}

/**
 * @brief Check if stack is empty
 * 
 * Returns 1 if the stack is empty, 0 if it contains elements.
 * 
 * @param S Pointer to stack
 * @return 1 if empty, 0 if not empty, 0 if S is NULL
 */
int ds_stack_is_empty(const ds_stack_t *S) {
    if (S == NULL) {
        return 1;  // Consider NULL as empty
    }
    
    return (S->top == NULL) ? 1 : 0;
}

/**
 * @brief Get the number of elements in the stack
 * 
 * Returns the current size (number of elements) of the stack.
 * This is an O(1) operation since size is cached.
 * 
 * @param S Pointer to stack
 * @return Number of elements in stack, or 0 if S is NULL
 */
size_t ds_stack_size(const ds_stack_t *S) {
    if (S == NULL) {
        return 0;
    }
    
    return S->size;
}

/**
 * @brief Visualize the stack structure
 * 
 * Prints a graphical representation of the stack to the specified output stream.
 * Shows each element with its data value in stack order (top to bottom).
 * 
 * @param S Pointer to stack
 * @param out Output stream (e.g., stdout, stderr)
 */
void ds_stack_visualize(const ds_stack_t *S, FILE *out) {
    struct ds_stack_node *current;
    int count = 0;
    
    // Handle NULL parameters gracefully
    if (out == NULL) {
        out = stdout;  // Default to stdout
    }
    
    if (S == NULL) {
        fprintf(out, "Stack: NULL\n");
        return;
    }
    
    if (S->top == NULL) {
        fprintf(out, "Stack: [empty] (size: %zu)\n", S->size);
        return;
    }
    
    // Print stack header
    fprintf(out, "Stack: (size: %zu)\n", S->size);
    
    // Print each element (top to bottom)
    current = S->top;
    while (current != NULL) {
        fprintf(out, "  [%d]: ", count);
        
        if (current->data != NULL) {
            // Try to print as integer first (most common case)
            fprintf(out, "%d", *(int*)current->data);
        } else {
            fprintf(out, "NULL");
        }
        
        // Mark top element
        if (count == 0) {
            fprintf(out, " [TOP]");
        }
        
        fprintf(out, "\n");
        
        current = current->next;
        count++;
    }
    
    fprintf(out, "\n");
}

