#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>


char word[100], *mask, len, turn = 0, n;

char get_char(char s) {
    s = getchar();
    if (s != ' ' && s != '\n') {
        return s;
    } else {
        get_char(s);
    }
}

int check_end() {
    for (int i=0;i<len;i++) {
        if (mask[i] == 0) {
            return 1;
        }
    }
    return 0;
}

int letter(char q) {
    int flag = 0;
    for (int i=0;i<len;i++) {
        if (mask[i] == 0 && word[i] == q) {
            mask[i] = 1;
            flag = 1;

        }
    }
    if (flag == 1) {
        printf("Угадали\n");

        return 1;
    } else {
        printf("Не Угадали\n");
        return 0;
    }
}

void check_winners(int* players) {
    int max = -1;
    for (int i=0;i<n;i++) {
        if(players[i] > max) {
            max = players[i];
        }
    }
    printf("Победил(и) ");
    for (int i=0;i<n;i++) {
        if(players[i] == max) printf("%d ", i + 1);
    }
    printf("Игрок(и)");

}



int main(void) {
    system("chcp 65001");
    int *players, player = 0, q;
    printf("Введите слово: ");
    scanf("%s", &word);
    printf("П О Л Е   Ч У Д Е С\n");
    printf("Введите кол-во игроков ");
    scanf("%d", &n);
    printf("N = %d", n);
    players = calloc(n, sizeof(int));

    len = strlen(word);
    printf("|%s|%d|", word, strlen(word));
    mask = calloc(len, sizeof(char));



    while(check_end()) {
        printf("\n\nход %d\n", turn + 1);
        printf("Слово: ");
        for (int i=0;i<len;i++) {
            if (mask[i] == 0) printf("*");
            else if (mask[i] == 1) printf("%c", word[i]);
        }
        putchar('\n');

        printf("Угадывает игрок %d ", (turn % n) + 1);
        q = get_char(q);
        int p = letter(q);
        players[turn % n] += p;

        printf("\nОчки: \n");
        for (int i=0;i<n;i++) printf("Игрок[%d] = %d оч. \n", i + 1, players[i]);
        if (p != 1) {
            turn++;
        }

    }


    check_winners(players);
    return 0;
}
