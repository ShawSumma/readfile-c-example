
#include "./readfile.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: ./readfile FILENAME\n");
        return 1;
    }
    readfile_t read = file_read(argv[1]);
    if (read.error) {
        fprintf(stderr, "cannot read file: %s\n", argv[1]);
        return 1;
    }
    printf("FILE: %s\n", argv[1]);
    printf("SIZE: %zu\n", read.len);
    printf("--- BEGIN FILE ---\n");
    printf("%s\n", read.text);
    printf("--- END FILE ---\n");
    file_close(read);
    return 0;
}