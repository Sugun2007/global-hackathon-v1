/**
 * @file ds.h
 * @brief Main header file for data structures library
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This header provides the main interface for the data structures library,
 * including error handling, memory management, and learning/debug utilities.
 */

#ifndef DS_H
#define DS_H

#include <stddef.h>  /* for size_t */

/**
 * @brief Error codes returned by data structure operations
 * 
 * The library uses these error codes to indicate the result of operations.
 * DS_OK indicates success, while other codes indicate specific error conditions.
 */
typedef enum ds_error {
    DS_OK = 0,        /**< Operation completed successfully */
    DS_ERR_OOM,       /**< Out of memory error */
    DS_ERR_INVALID,   /**< Invalid argument or operation */
    DS_ERR_NOTFOUND,  /**< Element not found */
    DS_ERR_NULLARG    /**< Null argument provided */
} ds_error_t;

/**
 * @brief Opaque type for linked list data structure
 * 
 * The actual structure definition is hidden from users.
 * All operations are performed through the public API functions.
 */
typedef struct ds_list ds_list_t;

/**
 * @brief Opaque type for stack data structure
 * 
 * The actual structure definition is hidden from users.
 * All operations are performed through the public API functions.
 */
typedef struct ds_stack ds_stack_t;

/**
 * @brief Opaque type for queue data structure
 * 
 * The actual structure definition is hidden from users.
 * All operations are performed through the public API functions.
 */
typedef struct ds_queue ds_queue_t;

/**
 * @brief Opaque type for tree data structure
 * 
 * The actual structure definition is hidden from users.
 * All operations are performed through the public API functions.
 */
typedef struct ds_tree ds_tree_t;

/**
 * @brief Memory allocation wrapper
 * 
 * Internal memory allocator used by the library. This function
 * provides a consistent interface for memory allocation across
 * all data structures.
 * 
 * @param n Number of bytes to allocate
 * @return Pointer to allocated memory, or NULL on failure
 * 
 * @note This function may be overridden for custom memory management
 */
void *ds_alloc(size_t n);

/**
 * @brief Memory deallocation wrapper
 * 
 * Internal memory deallocator used by the library. This function
 * provides a consistent interface for memory deallocation across
 * all data structures.
 * 
 * @param p Pointer to memory to deallocate
 * 
 * @note Safe to call with NULL pointer
 */
void ds_free(void *p);

/**
 * @brief Enable or disable learning mode
 * 
 * Learning mode provides additional debugging information and
 * may impact performance. When enabled, the library will provide
 * detailed information about operations for educational purposes.
 * 
 * @param enable Non-zero to enable learning mode, zero to disable
 * 
 * @note Learning mode is disabled by default
 */
void ds_enable_learning_mode(int enable);

/**
 * @brief Dump current state of all data structures
 * 
 * This function prints the current state of all active data structures
 * to stdout. Useful for debugging and learning purposes.
 * 
 * @note Only works when learning mode is enabled
 * @note The output format is implementation-defined
 */
void ds_dump_state(void);

/**
 * @mainpage Data Structures Library
 * 
 * @section ownership Ownership Rules
 * 
 * The library follows strict ownership rules to prevent memory leaks:
 * 
 * - **Library owns nodes**: The data structure library owns all internal
 *   nodes, links, and structural elements. These are automatically
 *   managed and should never be manually freed by the user.
 * 
 * - **Caller owns data**: The caller is responsible for managing the
 *   memory of the actual data stored in the structures (the payload).
 *   The library only stores pointers to this data and does not manage
 *   its lifetime.
 * 
 * @section memory Memory Management
 * 
 * The library uses custom allocator wrappers (ds_alloc/ds_free) to
 * provide consistent memory management. Users can override these
 * functions for custom memory management if needed.
 * 
 * @section errors Error Handling
 * 
 * All functions return ds_error_t codes to indicate success or failure.
 * Always check return values before using results.
 * 
 * @section learning Learning Mode
 * 
 * Enable learning mode with ds_enable_learning_mode(1) to get
 * additional debugging information and educational output.
 */

#endif /* DS_H */

