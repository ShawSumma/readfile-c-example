
#if !defined(READFILE_HEADER)
#define READFILE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(READFILE_CHUNK_SIZE)
#define READFILE_CHUNK_SIZE (64 /* chars */)
#endif

#if !defined(READFILE_GROWTH)
#define READFILE_GROWTH (4 /* times */)
#endif

struct readfile_t;
typedef struct readfile_t readfile_t;

struct readfile_t {
    size_t len;
    char *text;
    bool error: 1;
};

static void file_close(readfile_t file) {
    free(file.text);
}

static readfile_t file_read(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        readfile_t ret;
        ret.error = true;
        return ret;
    }
    size_t alloc = READFILE_CHUNK_SIZE * READFILE_GROWTH;
    char *buf = (char *) malloc(alloc);
    size_t len = 0;
    while (!feof(file)) {
        if (alloc - len >= READFILE_CHUNK_SIZE + 1) {
            alloc += READFILE_CHUNK_SIZE;
            alloc *= READFILE_GROWTH;
            buf = (char *) realloc((void *) buf, alloc);
        }
        int got = fread((void *) &buf[len], 1, READFILE_CHUNK_SIZE, file);
        len += got;
        if (got != READFILE_CHUNK_SIZE) {
            break;
        }
    }
    buf[len] = '\0';
    fclose(file);
    readfile_t ret;
    ret.text = buf;
    ret.len = len;
    return ret;
}

#endif
