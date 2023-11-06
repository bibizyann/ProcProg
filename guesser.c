#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int main() {
    srand(time(NULL));
    int num, guess, try;
    try = 5;
    num = rand() % 100;
    guess = num + 1;
    while (guess != num && try > 0) {
        printf("Guess the number from 0 to 100! You have %d tries \n", try);
        scanf("%d", &guess);
        if (guess > num){
            printf("Wished number is less \n");
        }
        else {
            printf("Wished number is more \n");
        }
        try--;
    }
    if (try > 0){
        printf("Congratulations! You guessed it! \n");
    }
    else{
        printf("You out of tries(");
    }
    return 0;
}