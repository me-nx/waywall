#include "util/list.h"
#include "util/prelude.h"
#include <stdio.h>

int
main() {
    struct list_uint32 list = list_uint32_create();

    for (uint32_t i = 0; i < 100; i++) {
        list_uint32_append(&list, i);
    }
    ww_assert(list.len == 100);

    for (uint32_t i = 0; i < list.len; i++) {
        ww_assert(list.data[i] == i);
    }

    for (uint32_t i = 0; i < 100; i++) {
        list_uint32_remove(&list, 0);
        for (uint32_t j = 0; j < list.len; j++) {
            ww_assert(list.data[j] == j + i + 1);
        }
    }
    ww_assert(list.len == 0);

    ww_assert(list.cap > 0);
    for (uint32_t i = 0; i < list.cap; i++) {
        list_uint32_append(&list, i);
    }
    ww_assert(list.len == list.cap);

    for (int32_t i = list.len - 1; i >= 0; i--) {
        list_uint32_remove(&list, i);
        for (uint32_t j = 0; j < list.len; j++) {
            ww_assert(list.data[j] == j);
        }
    }
    ww_assert(list.len == 0);

    list_uint32_append(&list, 0);
    ww_assert(list.len == 1);
    list_uint32_remove(&list, 0);
    ww_assert(list.len == 0);

    for (uint32_t i = 0; i < 100; i++) {
        list_uint32_append(&list, i);
    }
    ww_assert(list.len == 100);

    list_uint32_remove_range(&list, 0, 2);
    ww_assert(list.len == 98);
    list_uint32_remove_range(&list, 10, 11);
    ww_assert(list.len == 97);
    list_uint32_remove_range(&list, 95, 97);
    ww_assert(list.len == 95);

    for (uint32_t i = 0; i < list.len; i++) {
        if (i < 10) {
            ww_assert(list.data[i] == i + 2);
        } else {
            ww_assert(list.data[i] == i + 3);
        }
    }

    list_uint32_destroy(&list);
}
