#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

int main() {
    vector v = VEC_INIT(vector, 0);
    
    char c;
    while ((c = getchar()) != '\n') {
        vector l = VEC_INIT(char, 0);
        do {
            VEC_PUSH_BACK(char, l, c);
        } while ((c = getchar()) != '\n');
        VEC_PUSH_BACK(char, l, c);
        VEC_PUSH_BACK(char, l, '\0');
        VEC_PUSH_BACK(vector, v, l);
    }
    
    printf("+++ Printing input\n");
    for (size_t i=0; i<v.size; i++) {
        vector l = VEC_GET(vector, v, i);
        char* s = (char*)l.mem;
        printf("%s", s);
    }

    // free memory
    while (v.size > 0) {
        vector l = VEC_GET(vector, v, v.size - 1);
        VEC_CLEAR(l);
        if(l.size == 0 && l.mem == NULL)
            printf("+++ line freed!\n");
        else
            printf("+++ Error in freeing line\n");
        
        void* old_addr = v.mem; 
        VEC_POP_BACK(vector, v);
        if (old_addr != v.mem)
            printf("+++ realloc called");
    }
}
