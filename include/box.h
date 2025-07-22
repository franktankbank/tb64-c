#ifndef BOX_H
#define BOX_H

struct Box {
    char* text1;
    char* text_color_hex1;
    char* text2;
    char* text_color_hex2;
    char* sep_color_hex;
    char* box_color_hex;
    int error;
};

void print_box(struct Box box);

#endif  // BOX_H
