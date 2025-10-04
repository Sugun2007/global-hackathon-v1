/**
 * @file ds_queue.h
 * @brief Queue data structure interface
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This header provides the interface for the queue data structure.
 * The queue supports FIFO (First In, First Out) operations.
 */

#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include "ds.h"
#include <stdio.h>  /* for FILE */

/**
 * @brief Create a new empty queue
 * 
 * Allocates and initializes a new queue structure.
 * 
 * @return Pointer to new queue on success, NULL on memory allocation failure
 */
ds_queue_t *ds_queue_create(void);

/**
 * @brief Free a queue and optionally its data
 * 
 * Deallocates all elements in the queue. If free_data is provided,
 * it will be called for each element's data pointer.
 * 
 * @param Q Pointer to queue to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if Q is NULL
 */
ds_error_t ds_queue_free(ds_queue_t *Q, void (*free_data)(void *));

/**
 * @brief Enqueue element at the rear of the queue
 * 
 * Adds a new element to the rear of the queue.
 * 
 * @param Q Pointer to queue
 * @param data Pointer to data to enqueue
 * @return DS_OK on success, DS_ERR_NULLARG if Q or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_queue_enqueue(ds_queue_t *Q, void *data);

/**
 * @brief Dequeue element from the front of the queue
 * 
 * Removes the front element from the queue and returns its data.
 * 
 * @param Q Pointer to queue
 * @return Pointer to data of dequeued element, or NULL if queue is empty or Q is NULL
 */
void *ds_queue_dequeue(ds_queue_t *Q);

/**
 * @brief Peek at the front element without removing it
 * 
 * Returns the data of the front element without modifying the queue.
 * 
 * @param Q Pointer to queue
 * @return Pointer to front element's data, or NULL if queue is empty or Q is NULL
 */
void *ds_queue_peek(const ds_queue_t *Q);

/**
 * @brief Check if queue is empty
 * 
 * Returns 1 if the queue is empty, 0 if it contains elements.
 * 
 * @param Q Pointer to queue
 * @return 1 if empty, 0 if not empty, 0 if Q is NULL
 */
int ds_queue_is_empty(const ds_queue_t *Q);

/**
 * @brief Get the number of elements in the queue
 * 
 * Returns the current size (number of elements) of the queue.
 * 
 * @param Q Pointer to queue
 * @return Number of elements in queue, or 0 if Q is NULL
 */
size_t ds_queue_size(const ds_queue_t *Q);

/**
 * @brief Visualize the queue structure
 * 
 * Prints a graphical representation of the queue to the specified output stream.
 * Useful for debugging and learning purposes.
 * 
 * @param Q Pointer to queue
 * @param out Output stream (e.g., stdout, stderr)
 * 
 * @note Safe to call with NULL Q or out
 */
void ds_queue_visualize(const ds_queue_t *Q, FILE *out);

#endif /* DS_QUEUE_H */

