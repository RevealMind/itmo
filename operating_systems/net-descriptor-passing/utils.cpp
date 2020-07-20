#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

void show_error(char const * message){
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}



void write_str(int path, char const *s, char const* error) {
    ssize_t cur = 0;
    ssize_t len = static_cast<ssize_t>(strlen(s));
    ssize_t tmp;
    while (cur < len) {
        tmp = write(path, s + cur, static_cast<size_t>(len - cur));
        if (tmp == -1) {
            show_error(error);
        }
        cur += tmp;
    }
}

void write_str(int path, char const *s) {
    write_str(path, s, "Error was occurred while writing\n");
}