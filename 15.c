#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Element
{
    int Key;
    char* name;
    char* city;
    char* win;
    int lose;
    int draw;
    int points;
    struct Element* next;
    //Element* prev;
};

typedef struct Element Element;

void InitElement(Element* e, int Key, char* name,  char* city, int win, int lose, int draw, int points)
{
    e->next = NULL;
    e->Key = Key;
    e->name = name;
    e->city = city;
    e->win = win;
    e->lose = lose;
    e->draw = draw;
    e->points = points;
}

//для хранения односвязного списка достаточно иметь указатель только на его начало
typedef struct
{
    Element* First;
} List;


void InitList(List* L)
{
    L->First = NULL;
}


//вставить в конец списка L элемент e
void InsertEnd(List* L, Element* e) {
    if(L->First==NULL) {
        L->First = e;
        return;
    }
    //ищем последний элемент - это можно сделать рекурсивно
    Element* Current = L->First;

    while(Current->next!=NULL) {
        Current = Current->next;
    }
    //нашли конец списка - место для вставки
    e->next = NULL;
    Current->next = e;
}


//поиск элемента e в списке L
Element* Search(List* L, Element* e)
{
    Element* Current = L->First;
    //здесь можно было бы ввести указатель на функцию сравнения - на случай, если список состоит из Ваших собственных структур
    while(Current!=NULL && Current->Key!=e->Key) {
        Current = Current->next;
    }
    //вышли из цикла, если закончился список или нашли нужный элемент
    return Current;
}

Element* Search_name(List* L, char* e)
{
    Element* Current = L->First;
    char *c;
    
    //здесь можно было бы ввести указатель на функцию сравнения - на случай, если список состоит из Ваших собственных структур
    while(Current!=NULL) {
        c = Current->name;
        if (strcmp(e, c) == 0) {
            printf("\nKey = %d\tNext = %p\tName = %s\tcity = %s\twin = %d\tlose = %d\tdraw = %d\tpoints = %d\t", Current->Key, Current->next, Current->name, Current->city, Current->win, Current->lose, Current->draw, Current->points);
            return Current;
        }
        Current = Current->next;
    }
    //вышли из цикла, если закончился список или нашли нужный элемент
    
    return 0;
}


//вставить в список L элемент e после элемента WhereToInsert
void Insert(List* L, Element* WhereToInsert, Element* e) {
    if(L->First==NULL) {
        //пустой список
        L->First = e;
        return;
    }
    Element* p = Search(L, WhereToInsert);
    if(p==NULL) return;
    e->next = WhereToInsert->next;
    WhereToInsert->next = e;
}


//определить следующий элемент за e
Element* Successor(List* L, Element* e) {
    Element* p = Search(L, e);
    if(p!=NULL) return p->next;
    return NULL;
}

//определить предыдущий элемент перед e
Element* Predecessor(List* L, Element* e) {
    Element* Current = L->First;
    if(Current==NULL) return NULL;
    if(Current->Key==e->Key) return NULL;
    //здесь можно было бы ввести указатель на функцию сравнения - на случай, если список состоит из Ваших собственных структур
    while(Current->next!=NULL && Current->next->Key!=e->Key) {
        Current = Current->next;
    }
    //вышли из цикла, если закончился список или нашли нужный элемент
    return Current;
}

void Free(List*L, Element* e) {
    //освободить ресурсы, выделенные под 1 элемент
    free(e);
}

//удалить элемент e
void Delete(List* L, Element* e)
{
    Element* p = Search(L, e);
    if(p==NULL) return;
    Element* prev = Predecessor(L, e);
    Element* next = Successor(L, e);
    prev->next = next;
    Free(L, p);
}

void MakeAction(List* L, void (*f_ptr)(Element*), Element* e)
{
    if(e==NULL)
    e=L->First;
    if(e==NULL) return;
    f_ptr(e);
    if(e->next!=NULL)
    MakeAction(L, f_ptr, e->next);
}

void print_elem(Element* e)
{
 if(e==NULL)
 printf("\nNULL");
 printf("\nKey = %d\tNext = %p\tName = %s\tcity = %s\twin = %d\tlose = %d\tdraw = %d\tpoints = %d\t", e->Key, e->next, e->name, e->city, e->win, e->lose, e->draw, e->points);
}

void Rotate(List* L, Element* WhereToInsert, Element* e) {
    if(L->First==NULL) {
        //пустой список
        L->First = e;
        return;
    }
    Element* p = Search(L, WhereToInsert);
    if(p==NULL) return;
    Element* prev = Predecessor(L, e);
    Element* next = Successor(L, WhereToInsert);
    if (e == L->First) {
        L->First = WhereToInsert;
        e->next = WhereToInsert->next;
        WhereToInsert->next = e;
    } else if (WhereToInsert->next == NULL) {
        
        prev->next = WhereToInsert;
        WhereToInsert->next = e;
        e->next = NULL;
    } else {
        prev->next = WhereToInsert;
        WhereToInsert->next = e;
        e->next = next;
    }
}




void Filter(List* L, int key, int value) {
    Element* Current = L->First;

    // key = -1 -> < value
    // key = 0 -> == value
    // key = 1 -> > value
    if (key == -1) {
        while (Current != NULL) {
            if (Current->win < value) {
                printf("\nKey = %d\tNext = %p\tName = %s\tcity = %s\twin = %d\tlose = %d\tdraw = %d\tpoints = %d\t", Current->Key, Current->next, Current->name, Current->city, Current->win, Current->lose, Current->draw, Current->points);
            }
            Current = Current->next;
        }
    } else if (key == 0) {
        while (Current != NULL) {
            if (Current->win == value) {
                printf("\nKey = %d\tNext = %p\tName = %s\tcity = %s\twin = %d\tlose = %d\tdraw = %d\tpoints = %d\t", Current->Key, Current->next, Current->name, Current->city, Current->win, Current->lose, Current->draw, Current->points);
            }
            Current = Current->next;
        }
    } else if (key == 1) {
        while (Current != NULL) {
            if (Current->win > value) {
                printf("\nKey = %d\tNext = %p\tName = %s\tcity = %s\twin = %d\tlose = %d\tdraw = %d\tpoints = %d\t", Current->Key, Current->next, Current->name, Current->city, Current->win, Current->lose, Current->draw, Current->points);
            }
            Current = Current->next;
        }
    }
}
    


int main()
{
    Element* Barcelona = (Element*)malloc(sizeof(Element)); InitElement(Barcelona, 10, "Barcelona", "Barcelona", 10, 5, 3, 30);
    Element* Real = (Element*)malloc(sizeof(Element)); InitElement(Real, 20, "Real", "Madrid", 20, 2,6, 150);
    Element* Juventus = (Element*)malloc(sizeof(Element)); InitElement(Juventus, 30, "Juventus", "Juventus", 8, 3, 15, 20);
    Element* Arsenal = (Element*)malloc(sizeof(Element)); InitElement(Arsenal, 40, "Arsenal", "London", 15, 3, 6, 70);
    Element* PSG = (Element*)malloc(sizeof(Element)); InitElement(PSG, 50, "PSG", "Paris", 13, 7, 8,60);
    Element* Rostov = (Element*)malloc(sizeof(Element)); InitElement(Rostov, 60, "Rostov", "Rostov", 100, 0, 0, 1000);
 
    List L; InitList(&L);

    InsertEnd(&L, Barcelona);InsertEnd(&L, Real);InsertEnd(&L, Juventus);InsertEnd(&L, Arsenal);InsertEnd(&L, PSG);InsertEnd(&L, Rostov);
    printf("\ninitialization-----------\n");
    
    void (*p_print)(Element*); p_print = print_elem;
    MakeAction(&L, p_print, NULL);

    int choice;
    printf("\nChoose search for name / filter on win (1/0)");
    scanf("%d", &choice);


    if (choice == 1){ 
        printf("\nsearch for name-----------\n");
        printf("write a name of some team: ");
        char* a[100];
        scanf("%s", a);
        printf("%d", Search_name(&L, a));
    } else if (choice == 0) {
        int key, value;
        printf("write a key (\"-1\" - < value, \"0\" - == value, \"1\" - > value): "); scanf("%d", &key);
        printf("write value: "); scanf("%d", &value);
        Filter(&L, key, value);
    }
    return 0;
}
