#include <stdio.h>
#include <cs50.h>
#include <string.h>
//CREDIT NOT FINISHED YET

bool real_credit_card(string);
char *what_credit_card(string);

int main(){
    string credit_card = get_string(NULL,"Credit card: ");
    printf("%s",what_credit_card(credit_card));
    return 0;
}

bool real_credit_card(string credit_card){
    int len = strlen(credit_card);
    if (len !=13 && len !=15 && len !=16){
        return false;
    }
    return true;
}

/*
American express: 34 o 37. 15 digitos
Mastercard: 51,52,53,54,55. 16 digitos
Visa: 4. 13 y 16 digitos.
*/

char *what_credit_card(string credit_card){
    string sub_string = strcat(&credit_card[0],&credit_card[1]);
    printf("%s\n",sub_string);
    if (strcmp(credit_card,"34") == 1|| strcmp(sub_string,"37") == 1){
        return "American Express\n";
    }


    if (strcmp(sub_string,"51") == 1 || strcmp(sub_string,"52") == 1 || strcmp(sub_string,"53") == 1 || strcmp(sub_string,"54") == 1 || strcmp(sub_string,"55") == 1){
        return "Mastercard\n";
    }
    if (strcmp(&sub_string[0],"4") == 1){
        return "Visa\n";
    }
    return "Invalid";
}
