#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUF 256

int main(void) {
    char s[STR_BUF];
    char *token, *s_iter;

    ssize_t i = 0;
    while (i < STR_BUF - 1) {
        if ((s_iter = fgets(s + i, STR_BUF - i, stdin)) == NULL) {
            if (feof(stdin)) {
                clearerr(stdin);
                break;
            } else {
                perror("fgets(): error occured!");
                return 1;
            }
        }
        i += strlen(s_iter);
    }
    clearerr(stdin);

    s_iter = s;
    while ((token = strsep(&s_iter, ",\n\t ")) != NULL)
        printf("token %s toklen %lu\n", token, strlen(token));
}
