#include <openssl/evp.h>
#include <stdlib.h>
#include <string.h>

// Returns a malloc'd buffer you must free
char* base64_encode(const char* input)
{
    int input_len = (int)strlen(input);

    // Base64-encoded length: 4 * ceil(input_len / 3)
    int encoded_len = 4 * ((input_len + 2) / 3);

    // +1 for null terminator
    char* encoded = malloc((unsigned long long)encoded_len + 1);
    if (!encoded) {
        return NULL;
    }

    // EVP_EncodeBlock returns number of bytes written
    int actual_len = EVP_EncodeBlock(
        (unsigned char*)encoded, (const unsigned char*)input, input_len);

    encoded[actual_len] = '\0';  // Ensure null termination
    return encoded;
}

char* triple_encode(const char* input)
{
    char* pass1 = base64_encode(input);
    if (!pass1) {
        return NULL;
    }

    char* pass2 = base64_encode(pass1);
    free(pass1);
    if (!pass2) {
        return NULL;
    }

    char* pass3 = base64_encode(pass2);
    free(pass2);
    if (!pass3) {
        return NULL;
    }

    return pass3;
}
