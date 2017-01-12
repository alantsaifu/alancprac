#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

struct Vector {
    double *data;    // no place for x and n in readable code :-)
    size_t size;
};

struct Vector *newVector (size_t sz) {
    // Try to allocate vector structure.

    struct Vector *retVal = malloc (sizeof (struct Vector));
    if (retVal == NULL)
        return NULL;

    // Try to allocate vector data, free structure if fail.

    retVal->data = malloc (sz * sizeof (double));
    if (retVal->data == NULL) {
        free (retVal);
        return NULL;
    }

    // Set size and return.

    retVal->size = sz;
    return retVal;
}

void delVector (struct Vector *vector) {
    // Can safely assume vector is NULL or fully built.

    if (vector != NULL) {
        free (vector->data);
        free (vector);
    }
}