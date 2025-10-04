/**
 * @file ds_tree.h
 * @brief Binary tree data structure interface
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This header provides the interface for the binary tree data structure.
 * The tree supports basic operations like insertion, deletion, and traversal.
 */

#ifndef DS_TREE_H
#define DS_TREE_H

#include "ds.h"
#include <stdio.h>  /* for FILE */

/**
 * @brief Create a new empty tree
 * 
 * Allocates and initializes a new tree structure.
 * 
 * @return Pointer to new tree on success, NULL on memory allocation failure
 */
ds_tree_t *ds_tree_create(void);

/**
 * @brief Free a tree and optionally its data
 * 
 * Deallocates all nodes in the tree. If free_data is provided,
 * it will be called for each node's data pointer.
 * 
 * @param T Pointer to tree to free
 * @param free_data Optional function to free node data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if T is NULL
 */
ds_error_t ds_tree_free(ds_tree_t *T, void (*free_data)(void *));

/**
 * @brief Insert element into the tree
 * 
 * Inserts a new element into the tree using the comparison function
 * to determine the correct position.
 * 
 * @param T Pointer to tree
 * @param data Pointer to data to insert
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return DS_OK on success, DS_ERR_NULLARG if T, data, or cmp is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_tree_insert(ds_tree_t *T, void *data, int (*cmp)(const void *, const void *));

/**
 * @brief Find element in the tree
 * 
 * Searches for an element in the tree using the comparison function.
 * 
 * @param T Pointer to tree
 * @param target Pointer to data to find
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return Pointer to matching data, or NULL if not found or T/cmp/target is NULL
 */
void *ds_tree_find(ds_tree_t *T, void *target, int (*cmp)(const void *, const void *));

/**
 * @brief Remove element from the tree
 * 
 * Removes an element from the tree using the comparison function.
 * 
 * @param T Pointer to tree
 * @param target Pointer to data to remove
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return DS_OK on success, DS_ERR_NULLARG if T, target, or cmp is NULL, DS_ERR_NOTFOUND if not found
 */
ds_error_t ds_tree_remove(ds_tree_t *T, void *target, int (*cmp)(const void *, const void *));

/**
 * @brief Get the number of elements in the tree
 * 
 * Returns the current size (number of elements) of the tree.
 * 
 * @param T Pointer to tree
 * @return Number of elements in tree, or 0 if T is NULL
 */
size_t ds_tree_size(const ds_tree_t *T);

/**
 * @brief Check if tree is empty
 * 
 * Returns 1 if the tree is empty, 0 if it contains elements.
 * 
 * @param T Pointer to tree
 * @return 1 if empty, 0 if not empty, 0 if T is NULL
 */
int ds_tree_is_empty(const ds_tree_t *T);

/**
 * @brief Visualize the tree structure
 * 
 * Prints a graphical representation of the tree to the specified output stream.
 * Useful for debugging and learning purposes.
 * 
 * @param T Pointer to tree
 * @param out Output stream (e.g., stdout, stderr)
 * 
 * @note Safe to call with NULL T or out
 */
void ds_tree_visualize(const ds_tree_t *T, FILE *out);

#endif /* DS_TREE_H */

