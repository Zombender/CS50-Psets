#include <stdio.h>
#include "/workspaces/142470650/Pset1/cs50.c"

int main(){
    int height = 0;
    do {
        height = get_int("Height: ");
    }while(height < 1 || height > 8);

    for(int i =0; i<height;i++){
        for(int j = 0; j<height-i-1;j++){
            printf(" ");
        }
        for(int j = 0; j<i+1; j++){
            printf("#");
        }
        printf("  ");

        for (int j = 0;j<i+1;j++){
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
