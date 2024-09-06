#include "vec.h"
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_ssize_t.h>
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
    size_t new_size = v->size - 1;
    size_t mem_req = v->stride * new_size;

    if (v->size == 0)
        return ret;

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
    void *offset;

    if (v->mem_size < mem_req) {
        size_t new_size = 1;
        size_t new_mem_size;
        void *mem_new;

        if (v->size != 0)
            new_size = 2 * v->size;
        new_mem_size = v->stride * new_size;

        mem_new = realloc(v->mem, new_mem_size);
        if (mem_new == NULL)
            return 1;

        v->mem = mem_new;
        v->mem_size = new_mem_size;
    }

    offset = (char *)v->mem + v->size * v->stride;
    if (memcpy(offset, e, v->stride) == NULL)
        return 1;

    v->size++;

    return 0;
}

void *__vec_get(vector v, size_t i) { return (char *)v.mem + v.stride * i; }

int __vec_set(vector *v, size_t i, const void *e) {
    void *offset = (char *)v->mem + i * v->stride;
    if (memcpy(offset, e, v->stride) == NULL)
        return 1;
    return 0;
}

string string_init(const char *s) {
    size_t length = strlen(s) + 1;
    string str_c = VEC_INIT(char, length);

    if (memcpy(str_c.mem, s, length) == NULL) {
        return str_c;
    }

    str_c.size = length;
    return str_c;
}

char *string_c_str(string s) { return s.mem; }

// needs improvement, direct memcopy?
string string_concat(string *s, const char *s2) {
    VEC_POP_BACK(char, *s);
    int i = 0;
    do {
        VEC_PUSH_BACK(char, *s, s2[i++]);
    } while (s2[i - 1] != '\0');
    return *s;
}

size_t string_len(string s) { return s.size - 1; }

// better with a hashmap
static int __string_has_delim(const char *delim, char d) {
    for (size_t i = 0; delim[i] != '\0'; i++) {
        if (delim[i] == d)
            return 1;
    }
    return 0;
}

vector string_split(string s, const char *delim) {
    vector ret = VEC_INIT(string, 0);
    size_t length = string_len(s);
    string token = VEC_INIT(char, 0);

    for (size_t i = 0; i < length; i++) {
        char c = VEC_GET(char, s, i);

        if (__string_has_delim(delim, c)) {
            VEC_PUSH_BACK(char, token, '\0')
            VEC_PUSH_BACK(string, ret, token);
            token = VEC_INIT(char, 0);
        } else {
            VEC_PUSH_BACK(char, token, c);
        }
    }

    if (token.size != 0) {
        VEC_PUSH_BACK(char, token, '\0')
        VEC_PUSH_BACK(string, ret, token);
    }
    return ret;
}
