#define _CRT_SECURE_NO_WARNINGS

#include <box.h>
#include <magic.h>
#include <safe.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET_COLOR "\x1b[m"

char* hex_to_rgb(char* hex_color)
{
    int red;
    int green;
    int blue;
    char hex[HEX_LENGTH + 1] = {0};
    // printf("%s;", hex_color);
    if (hex_color[0] == '#') {
        strncpy(hex, hex_color + 1, HEX_LENGTH);
    } else {
        strncpy(hex, hex_color, HEX_LENGTH);
    }

    hex[HEX_LENGTH] = '\0';
    if (strlen(hex) == HEX_LENGTH) {
        char red_hex[3] = {0};
        char green_hex[3] = {0};
        char blue_hex[3] = {0};
        strncpy(red_hex, hex, 2);
        strncpy(green_hex, hex + 2, 2);
        strncpy(blue_hex, hex + 4, 2);
        red = (int)strtol(red_hex, NULL, RADIX);
        green = (int)strtol(green_hex, NULL, RADIX);
        blue = (int)strtol(blue_hex, NULL, RADIX);
        char* ansi_color = malloc(ANSI_LENGTH);
        (void)safe_snprintf(
            ansi_color, ANSI_LENGTH, "\x1b[38;2;%d;%d;%dm", red, green, blue);
        return ansi_color;
    }
    (void)safe_fprintf(stderr, "Invalid hex color code\n");
    // ✅ Still return heap memory (empty string)
    char* fallback = malloc(1);
    if (fallback) {
        fallback[0] = '\0';
    }
    return fallback;
}

// Function to print a Unicode colored box with text
void print_box(struct Box box)
{
    unsigned long long box_width = strlen(box.text1) + strlen(box.text2) + FIVE;
    char* text_color1 = hex_to_rgb(box.text_color_hex1);
    char* text_color2 = hex_to_rgb(box.text_color_hex2);
    char* sep_color = hex_to_rgb(box.sep_color_hex);
    char* box_color = hex_to_rgb(box.box_color_hex);
    // Top border
    if (box.error) {
        (void)safe_fprintf(stderr, "  %s\u250F", box_color);  // Top-left corner
        for (int i = 0; i < box_width; i++) {
            (void)safe_fprintf(stderr, "\u2501");
        }  // Horizontal line
        (void)safe_fprintf(
            stderr, "\u2513%s\n", RESET_COLOR);  // Top-right corner

        // Middle line with text
        (void)safe_fprintf(stderr,
                           "  %s\u2503%s ",
                           box_color,
                           RESET_COLOR);  // Left border
        (void)safe_fprintf(stderr,
                           "%s%s%s",
                           text_color1,
                           box.text1,
                           RESET_COLOR);  // First part of text
        (void)safe_fprintf(
            stderr, " %s\u2192%s ", sep_color, RESET_COLOR);  // Separator
        (void)safe_fprintf(stderr,
                           "%s%s%s",
                           text_color2,
                           box.text2,
                           RESET_COLOR);  // Second part of text
        (void)safe_fprintf(stderr,
                           " %s\u2503%s\n",
                           box_color,
                           RESET_COLOR);  // Right border

        // Bottom border
        (void)safe_fprintf(
            stderr, "  %s\u2517", box_color);  // Bottom-left corner
        for (int i = 0; i < box_width; i++) {
            (void)safe_fprintf(stderr, "\u2501");
        }  // Horizontal line
        (void)safe_fprintf(
            stderr, "\u251B%s\n", RESET_COLOR);  // Bottom-right corner
    } else {
        printf("  %s\u250F", box_color);  // Top-left corner
        for (int i = 0; i < box_width; i++) {
            printf("\u2501");
        }  // Horizontal line
        printf("\u2513%s\n", RESET_COLOR);  // Top-right corner

        // Middle line with text
        printf("  %s\u2503%s ", box_color, RESET_COLOR);  // Left border
        printf("%s%s%s",
               text_color1,
               box.text1,
               RESET_COLOR);  // First part of text
        printf(" %s\u2192%s ", sep_color, RESET_COLOR);  // Separator
        printf("%s%s%s",
               text_color2,
               box.text2,
               RESET_COLOR);  // Second part of text
        printf(" %s\u2503%s\n", box_color, RESET_COLOR);  // Right border

        // Bottom border
        printf("  %s\u2517", box_color);  // Bottom-left corner
        for (int i = 0; i < box_width; i++) {
            printf("\u2501");
        }  // Horizontal line
        printf("\u251B%s\n", RESET_COLOR);  // Bottom-right corner
    }
    free(text_color1);
    free(text_color2);
    free(sep_color);
    free(box_color);
}
