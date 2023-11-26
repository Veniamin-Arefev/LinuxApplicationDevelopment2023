#include "config.h"
#include "buf.h"
#include <stdio.h>


int main(int argc, char **argv) {

    float *values = 0;

/* Append 25 values */
    for (size_t i = 0; i < 25; i++)
        buf_push(values, rand() / (float) RAND_MAX);

/* Access 25 values using the normal [] operator */
    for (size_t i = 0; i < buf_size(values); i++)
        printf("values[%zu] = %f\n", i, values[i]);

/* Destroy/reset the buffer */
    buf_free(values);

    return 0;
}
