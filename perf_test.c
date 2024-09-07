#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_time(clock_t begin, clock_t end) {
    double time_taken = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time taken %lf\n", time_taken);
}

char *my_gets(char *restrict s, int len) {
    int i = 0;
    while (i < len - 1) {
        char c = getchar();
        s[i++] = c;

        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return s;
}

int main(void) {
    int n = 10e6;
    char *s = (char *)malloc(sizeof(char) * n);
    // size_t len = 0;
    clock_t begin, end;

    printf("Input for my_gets():\n");
    begin = clock();
    my_gets(s, n);
    end = clock();
    print_time(begin, end);

    printf("Input for fgets():\n");
    begin = clock();
    fgets(s, n, stdin);
    end = clock();
    print_time(begin, end);
}
