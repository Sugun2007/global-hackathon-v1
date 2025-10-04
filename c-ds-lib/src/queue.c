/**
 * @file queue.c
 * @brief Queue data structure implementation
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This file implements the queue data structure using a linked list approach
 * with memory management and learning mode support.
 */

#include "ds_queue.h"
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
 * @brief Internal node structure for queue
 * 
 * Each node contains a pointer to data and a pointer to the next node.
 * The queue structure maintains pointers to front and rear for efficient operations.
 */
struct ds_queue_node {
    void *data;                    /**< Pointer to user data */
    struct ds_queue_node *next;    /**< Pointer to next node */
};

/**
 * @brief Internal queue structure
 * 
 * Contains front and rear pointers for efficient enqueue/dequeue operations.
 * Size is cached for O(1) size queries.
 */
struct ds_queue {
    struct ds_queue_node *front;   /**< Pointer to front node */
    struct ds_queue_node *rear;    /**< Pointer to rear node */
    size_t size;                   /**< Number of elements in queue */
};

/**
 * @brief Create a new empty queue
 * 
 * Allocates and initializes a new queue structure with front and rear
 * set to NULL and size set to 0.
 * 
 * @return Pointer to new queue on success, NULL on memory allocation failure
 */
ds_queue_t *ds_queue_create(void) {
    ds_queue_t *queue;
    
    // Allocate memory for queue structure
    queue = (ds_queue_t *)ds_alloc(sizeof(struct ds_queue));
    if (queue == NULL) {
        return NULL;
    }
    
    // Initialize queue to empty state
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    
    return queue;
}

/**
 * @brief Free a queue and optionally its data
 * 
 * Iterates through all nodes, optionally calls free_data for each element's
 * data pointer, then deallocates all nodes and the queue structure itself.
 * 
 * @param Q Pointer to queue to free
 * @param free_data Optional function to free element data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if Q is NULL
 */
ds_error_t ds_queue_free(ds_queue_t *Q, void (*free_data)(void *)) {
    struct ds_queue_node *current, *next;
    
    // Validate input parameter
    if (Q == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Iterate through all nodes and free them
    current = Q->front;
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
    
    // Free the queue structure
    ds_free(Q);
    
    return DS_OK;
}

/**
 * @brief Enqueue element at the rear of the queue
 * 
 * Adds a new element to the rear of the queue. Updates rear pointer
 * and increments size. For empty queues, also updates front pointer.
 * 
 * @param Q Pointer to queue
 * @param data Pointer to data to enqueue
 * @return DS_OK on success, DS_ERR_NULLARG if Q or data is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_queue_enqueue(ds_queue_t *Q, void *data) {
    struct ds_queue_node *new_node;
    
    // Validate input parameters
    if (Q == NULL || data == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Allocate memory for new node
    new_node = (struct ds_queue_node *)ds_alloc(sizeof(struct ds_queue_node));
    if (new_node == NULL) {
        return DS_ERR_OOM;
    }
    
    // Initialize new node
    new_node->data = data;
    new_node->next = NULL;
    
    // Update queue pointers
    if (Q->rear == NULL) {
        // First element - update both front and rear
        Q->front = new_node;
        Q->rear = new_node;
    } else {
        // Add to rear - update rear
        Q->rear->next = new_node;
        Q->rear = new_node;
    }
    Q->size++;
    
    return DS_OK;
}

/**
 * @brief Dequeue element from the front of the queue
 * 
 * Removes the front element from the queue and returns its data.
 * Updates front pointer and decrements size. If queue becomes empty,
 * also updates rear pointer to NULL.
 * 
 * @param Q Pointer to queue
 * @return Pointer to data of dequeued element, or NULL if queue is empty or Q is NULL
 */
void *ds_queue_dequeue(ds_queue_t *Q) {
    struct ds_queue_node *old_front;
    void *data;
    
    // Validate input parameter
    if (Q == NULL) {
        return NULL;
    }
    
    // Check if queue is empty
    if (Q->front == NULL) {
        return NULL;
    }
    
    // Get old front and its data
    old_front = Q->front;
    data = old_front->data;
    
    // Update queue pointers
    Q->front = old_front->next;
    if (Q->front == NULL) {
        // Queue became empty - update rear as well
        Q->rear = NULL;
    }
    Q->size--;
    
    // Free the old front node
    ds_free(old_front);
    
    return data;
}

/**
 * @brief Peek at the front element without removing it
 * 
 * Returns the data of the front element without modifying the queue.
 * 
 * @param Q Pointer to queue
 * @return Pointer to front element's data, or NULL if queue is empty or Q is NULL
 */
void *ds_queue_peek(const ds_queue_t *Q) {
    // Validate input parameter
    if (Q == NULL) {
        return NULL;
    }
    
    // Check if queue is empty
    if (Q->front == NULL) {
        return NULL;
    }
    
    return Q->front->data;
}

/**
 * @brief Check if queue is empty
 * 
 * Returns 1 if the queue is empty, 0 if it contains elements.
 * 
 * @param Q Pointer to queue
 * @return 1 if empty, 0 if not empty, 0 if Q is NULL
 */
int ds_queue_is_empty(const ds_queue_t *Q) {
    if (Q == NULL) {
        return 1;  // Consider NULL as empty
    }
    
    return (Q->front == NULL) ? 1 : 0;
}

/**
 * @brief Get the number of elements in the queue
 * 
 * Returns the current size (number of elements) of the queue.
 * This is an O(1) operation since size is cached.
 * 
 * @param Q Pointer to queue
 * @return Number of elements in queue, or 0 if Q is NULL
 */
size_t ds_queue_size(const ds_queue_t *Q) {
    if (Q == NULL) {
        return 0;
    }
    
    return Q->size;
}

/**
 * @brief Visualize the queue structure
 * 
 * Prints a graphical representation of the queue to the specified output stream.
 * Shows each element with its data value in queue order (front to rear).
 * 
 * @param Q Pointer to queue
 * @param out Output stream (e.g., stdout, stderr)
 */
void ds_queue_visualize(const ds_queue_t *Q, FILE *out) {
    struct ds_queue_node *current;
    int count = 0;
    
    // Handle NULL parameters gracefully
    if (out == NULL) {
        out = stdout;  // Default to stdout
    }
    
    if (Q == NULL) {
        fprintf(out, "Queue: NULL\n");
        return;
    }
    
    if (Q->front == NULL) {
        fprintf(out, "Queue: [empty] (size: %zu)\n", Q->size);
        return;
    }
    
    // Print queue header
    fprintf(out, "Queue: (size: %zu)\n", Q->size);
    
    // Print each element (front to rear)
    current = Q->front;
    while (current != NULL) {
        fprintf(out, "  [%d]: ", count);
        
        if (current->data != NULL) {
            // Try to print as integer first (most common case)
            fprintf(out, "%d", *(int*)current->data);
        } else {
            fprintf(out, "NULL");
        }
        
        // Mark special elements
        if (count == 0) {
            fprintf(out, " [FRONT]");
        }
        if (current == Q->rear) {
            fprintf(out, " [REAR]");
        }
        
        fprintf(out, "\n");
        
        current = current->next;
        count++;
    }
    
    fprintf(out, "\n");
}

