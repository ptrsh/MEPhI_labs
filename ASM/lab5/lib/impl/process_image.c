#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include "stb_image.h"
#include "stb_image_write.h"

int process_image(char *input_filename, char *output_filename) {
    FILE *input = fopen(input_filename, "rb");
    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }
    int width, height, channels;
    unsigned char *image = stbi_load_from_file(input, &width, &height, &channels, 0);

    if (image == NULL) {
        printf("Could not load image\n");
        return 1;
    }

    unsigned char *gray_image = (unsigned char *) malloc(width * height);

    for (int i = 0; i < width * height * channels; i += channels) {
        unsigned char red = image[i];
        unsigned char green = image[i + 1];
        unsigned char blue = image[i + 2];

        unsigned char min_val = (red < green) ? ((red < blue) ? red : blue) : ((green < blue) ? green : blue);
        unsigned char max_val = (red > green) ? ((red > blue) ? red : blue) : ((green > blue) ? green : blue);

        unsigned char gray = (min_val + max_val) / 2;
        gray_image[i / channels] = gray;
    }

    stbi_write_bmp(output_filename, width, height, 1, gray_image);

    free(image);
    free(gray_image);
    return 0;
}
