#ifndef _VEC_H_
#define _VEC_H_

#include <stdlib.h>

#define VEC_INIT(type, n) __vec_init(sizeof(type), n)

#define VEC_PUSH_BACK(type, v, e)                                              \
    {                                                                          \
        const type __type_var__ = e;                                           \
        __vec_push_back(&v, (const void *)&__type_var__);                      \
    }

#define VEC_POP_BACK(type, v) __vec_pop_back(&v)

#define VEC_CLEAR(v) __vec_clear(&v)

#define VEC_GET(type, v, i) *(type *)__vec_get(v, i)

#define VEC_SET(type, v, i, e)                                                 \
    {                                                                          \
        const type __type_var__ = e;                                           \
        __vec_set(&v, i, (const void *)&__type_var__);                         \
    }

typedef struct {
    size_t size;
    size_t stride;

    size_t mem_size;
    void *mem;
} vector;

typedef vector string;

vector __vec_init(size_t type_size, size_t n);
int __vec_pop_back(vector *v);
void __vec_clear(vector *v);
int __vec_push_back(vector *v, const void *e);
void *__vec_get(vector v, size_t i);
int __vec_set(vector *v, size_t i, const void *e);

string string_init(const char *s);
char *string_c_str(string s);
string string_concat(string *s, const char *s2);
size_t string_len(string s);
vector string_split(string s, const char *delim);

#endif
