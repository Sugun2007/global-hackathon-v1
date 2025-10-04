/**
 * @file ds_list.h
 * @brief Linked list data structure interface
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This header provides the interface for the linked list data structure.
 * The linked list supports insertion, deletion, and traversal operations.
 */

#ifndef DS_LIST_H
#define DS_LIST_H

#include "ds.h"
#include <stdio.h>  /* for FILE */

/**
 * @brief Create a new empty linked list
 * 
 * Allocates and initializes a new linked list structure.
 * 
 * @return Pointer to new list on success, NULL on memory allocation failure
 */
ds_list_t *ds_list_create(void);

/**
 * @brief Free a linked list and optionally its data
 * 
 * Deallocates all nodes in the list. If free_data is provided,
 * it will be called for each element's data pointer.
 * 
 * @param L Pointer to list to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if L is NULL
 */
ds_error_t ds_list_free(ds_list_t *L, void (*free_data)(void *));

/**
 * @brief Insert element at the front of the list
 * 
 * Adds a new element to the beginning of the list.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to insert
 * @return DS_OK on success, DS_ERR_NULLARG if L or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_list_push_front(ds_list_t *L, void *data);

/**
 * @brief Insert element at the back of the list
 * 
 * Adds a new element to the end of the list.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to insert
 * @return DS_OK on success, DS_ERR_NULLARG if L or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_list_push_back(ds_list_t *L, void *data);

/**
 * @brief Remove and return element from the front of the list
 * 
 * Removes the first element from the list and returns its data.
 * 
 * @param L Pointer to list
 * @return Pointer to data of removed element, or NULL if list is empty or L is NULL
 */
void *ds_list_pop_front(ds_list_t *L);

/**
 * @brief Remove element matching comparison criteria
 * 
 * Searches for and removes the first element that matches the comparison function.
 * 
 * @param L Pointer to list
 * @param data Pointer to data to match against
 * @param cmp Comparison function returning 0 for match
 * @return DS_OK on success, DS_ERR_NULLARG if L, data, or cmp is NULL, DS_ERR_NOTFOUND if no match
 */
ds_error_t ds_list_remove(ds_list_t *L, void *data, int (*cmp)(const void *, const void *));

/**
 * @brief Find element matching comparison criteria
 * 
 * Searches for the first element that matches the comparison function
 * when compared against the target data.
 * 
 * @param L Pointer to list
 * @param target Pointer to data to match against
 * @param cmp Comparison function returning 0 for match
 * @return Pointer to matching data, or NULL if not found or L/cmp/target is NULL
 */
void *ds_list_find(ds_list_t *L, void *target, int (*cmp)(const void *, const void *));

/**
 * @brief Get the number of elements in the list
 * 
 * Returns the current size (number of elements) of the list.
 * 
 * @param L Pointer to list
 * @return Number of elements in list, or 0 if L is NULL
 */
size_t ds_list_size(const ds_list_t *L);

/**
 * @brief Visualize the list structure
 * 
 * Prints a graphical representation of the list to the specified output stream.
 * Useful for debugging and learning purposes.
 * 
 * @param L Pointer to list
 * @param out Output stream (e.g., stdout, stderr)
 * 
 * @note Safe to call with NULL L or out
 */
void ds_list_visualize(const ds_list_t *L, FILE *out);

#endif /* DS_LIST_H */

