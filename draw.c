#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

void print_pinguin(int n) {
    for (int i = 0; i < n; i++) { printf("   (O O)   "); }
    putchar('\n');
    for (int i=0;i<n;i++) printf("   / v \\   ");
    putchar('\n');
    for (int i=0;i<n;i++) printf("   /(_)\\   ");
    putchar('\n');
    for (int i=0;i<n;i++) printf("  ^ ^ ^ ^  ");
    putchar('\n');
}


void print_cat(int n) {
    for (int i=0;i<n;i++) printf("    ^_^    ");
    putchar('\n');
    for (int i=0;i<n;i++) printf("   /@ @\\   ");
    putchar('\n');
    for (int i=0;i<n;i++) printf("  (~~0~~)  ");
    putchar('\n');
}


int main(void) {
    print_pinguin(3);
    print_cat(4);
    return 0;
}
