#include <stdio.h>

extern void process_image(char *input_filename, char *output_filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    process_image(argv[1], argv[2]);

    return 0;
}
