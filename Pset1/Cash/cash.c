#include <stdio.h>
#include <cs50.h>

int main(){
    int cantidad = 0;
    do{
        cantidad = get_int("Change owed: ");
    }while(cantidad < 1);
    int conteo = 0;
    while (cantidad !=0){
        if (cantidad >= 25){
            cantidad -=25;
        }
        else if (cantidad >=10){
            
            cantidad -=10;
        }
        else if (cantidad >=5){
            cantidad -=5;
        }
        else{
            cantidad --;
        }
        conteo++;
    }
    printf("%i\n",conteo);
    return 0;
}
