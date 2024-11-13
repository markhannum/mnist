#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned char buf[784];
    int magic, size, unused[4];
    size_t n;
    if (argc != 3) {
        printf("Usage: %s <labels-file> <image-file>\n", argv[0]);
        return 1;
    }
    FILE *labels = fopen(argv[1], "rb");
    FILE *images = fopen(argv[2], "rb");
    if (!labels || !images) {
        printf("Error opening files\n");
        return 1;
    }

    /* ignore */
    n = fread(&magic, sizeof(int), 1, labels);
    n = fread(&size, sizeof(int), 1, labels);

    /* just ignore */
    n = fread(unused, sizeof(int), 4, images);

    for (int i = 0 ; i < 10000; i++) {
        char label;
        n = fread(&label, 1, 1, labels);
        n = fread(buf, 1, 784, images);
        /*
        printf("%d ", label);
        for (int i = 0 ; i < 784; i++) {
            printf("%u ", (unsigned char)buf[i]);
        }
        printf("\n");
        */
        printf("%d\n", label);
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                unsigned char c = buf[i * 28 + j];
                if (c > 100) {
                    printf("X");
                } else {
                    printf(" ");
                }
                //printf("%u", c);
                if (j < 27) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
