#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char cipher_char(char value, int key);
bool is_digit(string value);
int main(int argc, string argv[])
{
    if (argc !=2 || !is_digit(argv[1])){
        printf("Usage: ./caesar key\n");
        return 1;
    }
    printf(".\n");
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    for(int i = 0; i<strlen(plaintext);i++){
        plaintext[i] = cipher_char(plaintext[i],key);
    }
    printf("ciphertext: %s\n",plaintext);
    return 0;
}

char cipher_char(char value, int key){
    if (isalpha(value) ==0){
        return value;
    }
    for(int i = 0; i<key;i++){
        if (value == 90 || value == 122){
            value -=26;
        }
        value ++;
    }
    return value;

}

bool is_digit(string value){
    for (int i = 0; i<strlen(value);i++){
        if(isalpha(value[i])!=0){
            return false;
        }
    }
    return true;
}
