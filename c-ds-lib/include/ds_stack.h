/**
 * @file ds_stack.h
 * @brief Stack data structure interface
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This header provides the interface for the stack data structure.
 * The stack supports LIFO (Last In, First Out) operations.
 */

#ifndef DS_STACK_H
#define DS_STACK_H

#include "ds.h"
#include <stdio.h>  /* for FILE */

/**
 * @brief Create a new empty stack
 * 
 * Allocates and initializes a new stack structure.
 * 
 * @return Pointer to new stack on success, NULL on memory allocation failure
 */
ds_stack_t *ds_stack_create(void);

/**
 * @brief Free a stack and optionally its data
 * 
 * Deallocates all elements in the stack. If free_data is provided,
 * it will be called for each element's data pointer.
 * 
 * @param S Pointer to stack to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if S is NULL
 */
ds_error_t ds_stack_free(ds_stack_t *S, void (*free_data)(void *));

/**
 * @brief Push element onto the top of the stack
 * 
 * Adds a new element to the top of the stack.
 * 
 * @param S Pointer to stack
 * @param data Pointer to data to push
 * @return DS_OK on success, DS_ERR_NULLARG if S or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_stack_push(ds_stack_t *S, void *data);

/**
 * @brief Pop element from the top of the stack
 * 
 * Removes the top element from the stack and returns its data.
 * 
 * @param S Pointer to stack
 * @return Pointer to data of popped element, or NULL if stack is empty or S is NULL
 */
void *ds_stack_pop(ds_stack_t *S);

/**
 * @brief Peek at the top element without removing it
 * 
 * Returns the data of the top element without modifying the stack.
 * 
 * @param S Pointer to stack
 * @return Pointer to top element's data, or NULL if stack is empty or S is NULL
 */
void *ds_stack_peek(const ds_stack_t *S);

/**
 * @brief Check if stack is empty
 * 
 * Returns 1 if the stack is empty, 0 if it contains elements.
 * 
 * @param S Pointer to stack
 * @return 1 if empty, 0 if not empty, 0 if S is NULL
 */
int ds_stack_is_empty(const ds_stack_t *S);

/**
 * @brief Get the number of elements in the stack
 * 
 * Returns the current size (number of elements) of the stack.
 * 
 * @param S Pointer to stack
 * @return Number of elements in stack, or 0 if S is NULL
 */
size_t ds_stack_size(const ds_stack_t *S);

/**
 * @brief Visualize the stack structure
 * 
 * Prints a graphical representation of the stack to the specified output stream.
 * Useful for debugging and learning purposes.
 * 
 * @param S Pointer to stack
 * @param out Output stream (e.g., stdout, stderr)
 * 
 * @note Safe to call with NULL S or out
 */
void ds_stack_visualize(const ds_stack_t *S, FILE *out);

#endif /* DS_STACK_H */

