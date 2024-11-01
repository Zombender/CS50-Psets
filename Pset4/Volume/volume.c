// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    typedef uint8_t HEADER;
    HEADER header[HEADER_SIZE];
    fread(&header,sizeof(header),1,input);
    fwrite(&header,sizeof(header),1,output);
    int16_t content;
    while(fread(&content,sizeof(content),1,input)){
        content *=factor;
        fwrite(&content,sizeof(content),1,output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
