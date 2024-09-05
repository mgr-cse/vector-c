#include "vec.h"
#include <string.h>
#include <time.h>

vector __vec_init(size_t type_size, size_t n) {
    vector v = {0, type_size, 0, NULL};

    if (n != 0) {
        size_t mem_size = n * type_size;
        v.mem = malloc(mem_size);
        if (v.mem != NULL) {
            v.mem_size = mem_size;
        }
    }
    return v;
}

void __vec_clear(vector *v) {
    if (v->mem != NULL)
        free(v->mem);

    v->mem = NULL;
    v->mem_size = 0;
    v->size = 0;
}

// you may lose popped structs
// don't reference them
int __vec_pop_back(vector *v) {
    int ret = 0;

    if (v->size == 0)
        return ret;

    size_t new_size = v->size - 1;
    size_t mem_req = v->stride * new_size;

    if (mem_req == 0) {
        __vec_clear(v);
        return ret;
    }

    if (2 * mem_req <= v->mem_size) {
        void *mem_new = realloc(v->mem, mem_req);
        if (mem_new != NULL) {
            v->mem = mem_new;
            v->mem_size = mem_req;
        } else
            ret = 1;
    }

    v->size--;

    return ret;
}

int __vec_push_back(vector *v, const void *e) {
    size_t mem_req = v->stride * (v->size + 1);

    if (v->mem_size < mem_req) {
        size_t new_size = 1;
        if (v->size != 0)
            new_size = 2 * v->size;
        size_t new_mem_size = v->stride * new_size;

        void *mem_new = realloc(v->mem, new_mem_size);
        if (mem_new == NULL)
            return 1;

        v->mem = mem_new;
        v->mem_size = new_mem_size;
    }

    void *offset = v->mem + v->size * v->stride;
    if (memcpy(offset, e, v->stride) == NULL)
        return 1;

    v->size++;

    return 0;
}

void *__vec_get(vector v, size_t i) { return v.mem + v.stride * i; }

int __vec_set(vector *v, size_t i, const void *e) {
    void *offset = v->mem + i * v->stride;
    if (memcpy(offset, e, v->stride) == NULL)
        return 1;
    return 0;
}
