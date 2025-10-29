#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <turbob64.h>

char* triple_encode(const char* input)
{
    tb64ini(0, 0);

    size_t in_len = strlen(input);

    // Each Base64 encoding expands data by ~4/3 + padding
    size_t max_len1 = TB64ENCLEN(in_len);
    size_t max_len2 = TB64ENCLEN(max_len1);
    size_t max_len3 = TB64ENCLEN(max_len2);

    // Allocate all buffers (aligned allocation not required)
    unsigned char* buf1 = malloc(max_len1 + 1);
    unsigned char* buf2 = malloc(max_len2 + 1);
    unsigned char* buf3 = malloc(max_len3 + 1);

    if (!buf1 || !buf2 || !buf3) {
        free(buf1);
        free(buf2);
        free(buf3);
        (void)fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Pass 1
    size_t len1 = tb64enc((unsigned char*)input, in_len, buf1);
    buf1[len1] = '\0';

    // Pass 2
    size_t len2 = tb64enc(buf1, len1, buf2);
    buf2[len2] = '\0';

    // Pass 3
    size_t len3 = tb64enc(buf2, len2, buf3);
    buf3[len3] = '\0';

    free(buf1);
    free(buf2);

    return (char*)buf3;
}
