#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

int main(void) {
    vector v = VEC_INIT(vector, 0);

    int c;
    vector line = VEC_INIT(char, 0);

    printf("Enter input text, press Ctrl-D to quit:\n");
    while ((c = getchar()) != EOF) {
        VEC_PUSH_BACK(char, line, (char)c);

        if (c == '\n') {
            VEC_PUSH_BACK(char, line, '\0');
            VEC_PUSH_BACK(vector, v, line);
            line = VEC_INIT(char, 0);
        }
    }

    printf("+++ Printing input\n");
    for (size_t i = 0; i < v.size; i++) {
        vector l = VEC_GET(vector, v, i);
        char *s = (char *)l.mem;
        printf("%s", s);
    }

    // free memory
    while (v.size > 0) {
        vector l = VEC_GET(vector, v, v.size - 1);
        void *old_addr = NULL;

        VEC_CLEAR(l);
        if (l.size == 0 && l.mem == NULL)
            printf("+++ line freed!\n");
        else
            printf("+++ Error in freeing line\n");

        old_addr = v.mem;
        VEC_POP_BACK(vector, v);
        if (old_addr != v.mem)
            printf("+++ realloc called\n");
    }
}
