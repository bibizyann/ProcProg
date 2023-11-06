// runing line
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<windows.h>

void main ()
{
const int size = 30;
int temp;
char a[100] = "Hello world                ";

while (1)
{
    system ("cls");
    temp = a[size-1];
    for (int i = size; i>0; i--) a[i] = a [i-1];
    
    a[0] = temp;
    for (int i =0; i<size; i++) printf("%c", a[i]);
    
    Sleep(10);
}
}
