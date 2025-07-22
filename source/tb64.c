#include <string.h>
#if defined __unix__ || __APPLE__
#    include <asm-generic/ioctls.h>
#    include <stdio.h>
#    include <sys/ioctl.h>
#    define SEVEN 7
#    define FIVE 5
#endif
#ifdef _WIN32
#    include <windows.h>
#    define CODEPAGE 65001
#endif
#include "include/base64.h"
#include "include/box.h"
#include "include/clip.h"

int main(int argc, char* argv[])
{
#if defined __unix__ || __APPLE__
    struct winsize win;
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    int width = (int)(win.ws_col) - 4;
#endif
#ifdef _WIN32
    SetConsoleOutputCP(CODEPAGE);
#endif
    if (argc != 2) {
        struct RawBox raw_box;
        raw_box = (struct RawBox) {
            .text1 = "Invalid Argument",
            .text_color_hex1 = "#DC143C",
            .text2 = "Please provide exactly one string as an argument",
            .text_color_hex2 = "#FFEA00",
            .sep_color_hex = "#FF7F50",
            .box_color_hex = "#7CFC00",
            .error = 1};
        print_box(raw_box);
        return 1;
    }
    const char* input = argv[1];
    char* encoded = triple_encode(input);
#if defined __unix__ || __APPLE__
    int length = (int)strlen(encoded) + SEVEN + FIVE;
    if (length > width) {
        struct RawBox raw_box;
        raw_box = (struct RawBox) {.text1 = "Output Size Exceeded",
                                   .text_color_hex1 = "#DC143C",
                                   .text2 = "Output too large",
                                   .text_color_hex2 = "#FFEA00",
                                   .sep_color_hex = "#FF7F50",
                                   .box_color_hex = "#7CFC00",
                                   .error = 1};
        print_box(raw_box);
        return 1;
    }
#elif _WIN32
    const int MAX_LENGTH = 64;
    if (strlen(encoded) > MAX_LENGTH) {
        struct RawBox raw_box;
        raw_box = (struct RawBox) {.text1 = "Output Size Exceeded",
                                   .text_color_hex1 = "#DC143C",
                                   .text2 = "Output too large",
                                   .text_color_hex2 = "#FFEA00",
                                   .sep_color_hex = "#FF7F50",
                                   .box_color_hex = "#7CFC00",
                                   .error = 1};
        print_box(raw_box);
        return 1;
    }
#endif
    struct RawBox raw_box;
    raw_box = (struct RawBox) {.text1 = "Encoded",
                               .text_color_hex1 = "#00CED1",
                               .text2 = encoded,
                               .text_color_hex2 = "#FFEA00",
                               .sep_color_hex = "#FF69B4",
                               .box_color_hex = "#7CFC00",
                               .error = 0};
    print_box(raw_box);
    if (cbcopy(encoded) != 0) {
        struct RawBox raw_box;
        raw_box = (struct RawBox) {.text1 = "Clipboard Error",
                                   .text_color_hex1 = "#DC143C",
                                   .text2 = "Failed to copy to clipboard",
                                   .text_color_hex2 = "#FFEA00",
                                   .sep_color_hex = "#FF7F50",
                                   .box_color_hex = "#7CFC00",
                                   .error = 1};
        print_box(raw_box);
        return 1;
    }
    return 0;
}
