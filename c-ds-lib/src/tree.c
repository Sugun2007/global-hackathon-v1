/**
 * @file tree.c
 * @brief Binary tree data structure implementation
 * @author Data Structures Library
 * @version 1.0
 * @date 2024
 * 
 * This file implements the binary tree data structure with memory management
 * and learning mode support.
 */

#include "ds_tree.h"
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
 * @brief Internal node structure for binary tree
 * 
 * Each node contains a pointer to data and pointers to left and right children.
 * The tree structure maintains a pointer to the root node.
 */
struct ds_tree_node {
    void *data;                    /**< Pointer to user data */
    struct ds_tree_node *left;     /**< Pointer to left child */
    struct ds_tree_node *right;    /**< Pointer to right child */
};

/**
 * @brief Internal tree structure
 * 
 * Contains root pointer and cached size for efficient operations.
 */
struct ds_tree {
    struct ds_tree_node *root;     /**< Pointer to root node */
    size_t size;                   /**< Number of elements in tree */
};

/**
 * @brief Count nodes in subtree recursively
 * 
 * Helper function to count nodes in a subtree.
 * 
 * @param node Pointer to subtree root
 * @return Number of nodes in subtree
 */
static size_t count_nodes(struct ds_tree_node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

/**
 * @brief Free subtree recursively
 * 
 * Helper function to free all nodes in a subtree.
 * 
 * @param node Pointer to subtree root
 * @param free_data Function to free node data (may be NULL)
 */
static void free_subtree(struct ds_tree_node *node, void (*free_data)(void *)) {
    if (node == NULL) {
        return;
    }
    
    // Free left and right subtrees
    free_subtree(node->left, free_data);
    free_subtree(node->right, free_data);
    
    // Call user's free function for data if provided
    if (free_data != NULL && node->data != NULL) {
        free_data(node->data);
    }
    
    // Free the node
    ds_free(node);
}

/**
 * @brief Find minimum node in subtree
 * 
 * Helper function to find the leftmost node in a subtree.
 * 
 * @param node Pointer to subtree root
 * @return Pointer to minimum node
 */
static struct ds_tree_node *find_min(struct ds_tree_node *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * @brief Print subtree recursively
 * 
 * Helper function to print tree structure recursively.
 * 
 * @param node Pointer to subtree root
 * @param out Output stream
 * @param depth Current depth in tree
 */
static void print_subtree(struct ds_tree_node *node, FILE *out, int depth) {
    if (node == NULL) {
        return;
    }
    
    // Print right subtree (higher values)
    print_subtree(node->right, out, depth + 1);
    
    // Print current node
    for (int i = 0; i < depth; i++) {
        fprintf(out, "  ");
    }
    
    if (node->data != NULL) {
        fprintf(out, "%d\n", *(int*)node->data);
    } else {
        fprintf(out, "NULL\n");
    }
    
    // Print left subtree (lower values)
    print_subtree(node->left, out, depth + 1);
}

/**
 * @brief Create a new empty tree
 * 
 * Allocates and initializes a new tree structure with root set to NULL
 * and size set to 0.
 * 
 * @return Pointer to new tree on success, NULL on memory allocation failure
 */
ds_tree_t *ds_tree_create(void) {
    ds_tree_t *tree;
    
    // Allocate memory for tree structure
    tree = (ds_tree_t *)ds_alloc(sizeof(struct ds_tree));
    if (tree == NULL) {
        return NULL;
    }
    
    // Initialize tree to empty state
    tree->root = NULL;
    tree->size = 0;
    
    return tree;
}

/**
 * @brief Free a tree and optionally its data
 * 
 * Recursively frees all nodes in the tree, optionally calls free_data
 * for each node's data pointer, then deallocates the tree structure itself.
 * 
 * @param T Pointer to tree to free
 * @param free_data Optional function to free node data (may be NULL)
 * @return DS_OK on success, DS_ERR_NULLARG if T is NULL
 */
ds_error_t ds_tree_free(ds_tree_t *T, void (*free_data)(void *)) {
    // Validate input parameter
    if (T == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Free all nodes recursively
    free_subtree(T->root, free_data);
    
    // Free the tree structure
    ds_free(T);
    
    return DS_OK;
}

/**
 * @brief Insert element into the tree
 * 
 * Inserts a new element into the tree using the comparison function
 * to determine the correct position following binary search tree rules.
 * 
 * @param T Pointer to tree
 * @param data Pointer to data to insert
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return DS_OK on success, DS_ERR_NULLARG if T, data, or cmp is NULL, DS_ERR_OOM on memory failure
 */
ds_error_t ds_tree_insert(ds_tree_t *T, void *data, int (*cmp)(const void *, const void *)) {
    struct ds_tree_node *new_node, *current, *parent;
    
    // Validate input parameters
    if (T == NULL || data == NULL || cmp == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Allocate memory for new node
    new_node = (struct ds_tree_node *)ds_alloc(sizeof(struct ds_tree_node));
    if (new_node == NULL) {
        return DS_ERR_OOM;
    }
    
    // Initialize new node
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    // If tree is empty, make new node the root
    if (T->root == NULL) {
        T->root = new_node;
        T->size++;
        return DS_OK;
    }
    
    // Find insertion point
    current = T->root;
    parent = NULL;
    
    while (current != NULL) {
        parent = current;
        int comparison = cmp(data, current->data);
        
        if (comparison < 0) {
            current = current->left;
        } else if (comparison > 0) {
            current = current->right;
        } else {
            // Element already exists, free new node and return
            ds_free(new_node);
            return DS_OK;  // Consider this success (no duplicates)
        }
    }
    
    // Insert new node
    if (cmp(data, parent->data) < 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    T->size++;
    return DS_OK;
}

/**
 * @brief Find element in the tree
 * 
 * Searches for an element in the tree using the comparison function
 * following binary search tree rules.
 * 
 * @param T Pointer to tree
 * @param target Pointer to data to find
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return Pointer to matching data, or NULL if not found or T/cmp/target is NULL
 */
void *ds_tree_find(ds_tree_t *T, void *target, int (*cmp)(const void *, const void *)) {
    struct ds_tree_node *current;
    
    // Validate input parameters
    if (T == NULL || target == NULL || cmp == NULL) {
        return NULL;
    }
    
    // Search for element
    current = T->root;
    while (current != NULL) {
        int comparison = cmp(target, current->data);
        
        if (comparison < 0) {
            current = current->left;
        } else if (comparison > 0) {
            current = current->right;
        } else {
            // Found match
            return current->data;
        }
    }
    
    // Not found
    return NULL;
}

/**
 * @brief Remove element from the tree
 * 
 * Removes an element from the tree using the comparison function.
 * Handles three cases: leaf node, node with one child, node with two children.
 * 
 * @param T Pointer to tree
 * @param target Pointer to data to remove
 * @param cmp Comparison function for ordering (returns <0, 0, >0)
 * @return DS_OK on success, DS_ERR_NULLARG if T, target, or cmp is NULL, DS_ERR_NOTFOUND if not found
 */
ds_error_t ds_tree_remove(ds_tree_t *T, void *target, int (*cmp)(const void *, const void *)) {
    struct ds_tree_node *current, *parent, *successor, *successor_parent;
    
    // Validate input parameters
    if (T == NULL || target == NULL || cmp == NULL) {
        return DS_ERR_NULLARG;
    }
    
    // Find node to remove
    current = T->root;
    parent = NULL;
    
    while (current != NULL) {
        int comparison = cmp(target, current->data);
        
        if (comparison < 0) {
            parent = current;
            current = current->left;
        } else if (comparison > 0) {
            parent = current;
            current = current->right;
        } else {
            // Found node to remove
            break;
        }
    }
    
    if (current == NULL) {
        return DS_ERR_NOTFOUND;
    }
    
    // Case 1: Node has no children (leaf node)
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            T->root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        ds_free(current);
    }
    // Case 2: Node has one child
    else if (current->left == NULL || current->right == NULL) {
        struct ds_tree_node *child = (current->left != NULL) ? current->left : current->right;
        
        if (parent == NULL) {
            T->root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        ds_free(current);
    }
    // Case 3: Node has two children
    else {
        // Find successor (minimum in right subtree)
        successor = current->right;
        successor_parent = current;
        
        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }
        
        // Replace current data with successor data
        current->data = successor->data;
        
        // Remove successor
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        ds_free(successor);
    }
    
    T->size--;
    return DS_OK;
}

/**
 * @brief Get the number of elements in the tree
 * 
 * Returns the current size (number of elements) of the tree.
 * This is an O(1) operation since size is cached.
 * 
 * @param T Pointer to tree
 * @return Number of elements in tree, or 0 if T is NULL
 */
size_t ds_tree_size(const ds_tree_t *T) {
    if (T == NULL) {
        return 0;
    }
    
    return T->size;
}

/**
 * @brief Check if tree is empty
 * 
 * Returns 1 if the tree is empty, 0 if it contains elements.
 * 
 * @param T Pointer to tree
 * @return 1 if empty, 0 if not empty, 0 if T is NULL
 */
int ds_tree_is_empty(const ds_tree_t *T) {
    if (T == NULL) {
        return 1;  // Consider NULL as empty
    }
    
    return (T->root == NULL) ? 1 : 0;
}

/**
 * @brief Visualize the tree structure
 * 
 * Prints a graphical representation of the tree to the specified output stream.
 * Shows the tree rotated 90 degrees counter-clockwise (root at left, leaves at right).
 * 
 * @param T Pointer to tree
 * @param out Output stream (e.g., stdout, stderr)
 */
void ds_tree_visualize(const ds_tree_t *T, FILE *out) {
    // Handle NULL parameters gracefully
    if (out == NULL) {
        out = stdout;  // Default to stdout
    }
    
    if (T == NULL) {
        fprintf(out, "Tree: NULL\n");
        return;
    }
    
    if (T->root == NULL) {
        fprintf(out, "Tree: [empty] (size: %zu)\n", T->size);
        return;
    }
    
    // Print tree header
    fprintf(out, "Tree: (size: %zu)\n", T->size);
    fprintf(out, "Root at left, leaves at right:\n");
    
    // Print tree structure
    print_subtree(T->root, out, 0);
    
    fprintf(out, "\n");
}

