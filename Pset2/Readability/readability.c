#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
float count_letters(string);
int main(void)
{
    string text = get_string("Text: ");
    float grade = count_letters(text);
    if (grade <=0){
        printf("Before Grade 1\n");
    }
    else if (grade >16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %.0f\n",grade);
    }
}

float count_letters(string text){
    int letters =0;
    int words = 0;
    int sentences = 0;
    for (int i = 0; i<strlen(text);i++){
        if (isalpha(text[i]) !=0){
            letters++;
        }
        else if(text[i] == ' '){
            words++;
        }
        else if(text[i] == '.' ||text[i] == '!' || text[i] == '?'){
            sentences++;
        }
    }
    words++;
    float L = ((float)letters/words)*100;
    float S = ((float)sentences/words)*100;
    float count = 0.0588 * L - 0.296 * S - 15.8;
    return count;
}
