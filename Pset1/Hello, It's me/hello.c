#include <stdio.h>
#include <cs50.h>

int main(){

    string nombre = get_string("What's your name: ");
    printf("hello, %s\n",nombre);
    return 0;
}
