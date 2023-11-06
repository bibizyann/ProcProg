#include <stdlib.h>
#include<stdio.h>
#include <math.h>
int main()
{
    int a,b,n,i;
    printf("Enter two numbers separated by space:");
    scanf("%d %d",&a,&b);

    for (i = 0; i < 6; i++) {
        printf("Enter your choice:\n 1.Addition\n 2.Subtraction\n 3.multiplication\n");
        printf(" 4.Division\n 5.Square of the sum of numbers\n 6.Quit\n");
        scanf("%d",&n);
        switch (n) {
            case 1:
                printf("The sum of %d and %d is %d \n", a, b, a + b);
                break;
            case 2:
                printf("The Subtraction of %d and %d is %d \n", a, b, a - b);
                break;
            case 3:
                printf("The multiplication of %d and %d is %d \n", a, b, a * b);
                break;
            case 4:
                printf("The division of %d and %d is %lf \n", a, b, (double)a / (double)b);
                break;
            case 5:
                printf("The Subtraction of %d and %d is %f \n", a, b, pow(a + b, 2));
                break;
            case 6:
                printf("You have finished the program!");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid operation \n");
        }
    }
    printf("Program completed successfully!");
    return 0;
}