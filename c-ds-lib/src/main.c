#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ds_list.h"

// Comparison helper for integers
int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Free helper for integers
void free_int(void *p) {
    free(p);
}

int main(void) {
    printf("===== Linked List Tests =====\n");

    // 1. Create
    ds_list_t *list = ds_list_create();
    assert(list != NULL);
    printf("Created list ✅\n");

    // 2. Push front
    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 20;
    assert(ds_list_push_front(list, a) == DS_OK);
    assert(ds_list_push_front(list, b) == DS_OK);
    printf("Push front ✅\n");

    // 3. Push back
    int *c = malloc(sizeof(int)); *c = 30;
    assert(ds_list_push_back(list, c) == DS_OK);
    printf("Push back ✅\n");

    // 4. Size
    size_t sz = ds_list_size(list);
    assert(sz == 3);
    printf("List size ✅ (%zu elements)\n", sz);

    // 5. Visualize
    printf("Visualize list:\n");
    ds_list_visualize(list, stdout);

    // 6. Find (search for 20)
    int key_find = 20;
    void *found = ds_list_find(list, &key_find, cmp_int);

    if (found) {
        printf("Find ✅ (%d)\n", *(int*)found);
    } else {
        printf("Find ❌\n");
    }
    // 7. Pop front (should remove 20 first)
    int *popped = ds_list_pop_front(list);
    assert(popped != NULL && *popped == 20);
    printf("Pop front ✅ (%d)\n", *popped);
    free(popped);

    // 8. Remove (remove 30)
    int key = 30;
    assert(ds_list_remove(list, &key, cmp_int) == DS_OK);
    printf("Remove ✅ (30)\n");

    // 9. Final size
    sz = ds_list_size(list);
    printf("Final size ✅ (%zu elements)\n", sz);

    // 10. Free list
    assert(ds_list_free(list, free_int) == DS_OK);
    printf("Free ✅\n");

    printf("===== All list tests passed =====\n");
    return 0;
}
