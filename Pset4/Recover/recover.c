#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc<2){
        printf("Usage: ./recover card\n");
        return 1;
    }
    FILE *input = fopen(argv[1],"r");
    if (!input) return 1;

    FILE *output = NULL;

    BYTE buffer[512];
    int image_count = 0;
    char file_name[8];

    while(fread(buffer,sizeof(uint8_t),512,input)){
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if (output !=NULL){
                fclose(output);
            }
            sprintf(file_name, "%03i.jpg",image_count); //name
            output = fopen(file_name,"w");
            if(!output){
                return 1;
            }
            fwrite(&buffer,sizeof(BYTE),512,output);
            image_count++;
        }
        else if (output != NULL){
            fwrite(&buffer,sizeof(BYTE),512,output);
        }
    }
    fclose(input);
    fclose(output);
}
