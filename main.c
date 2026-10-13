#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Hasta {
    int id;
    char ad[50];
    char durum[20]; 
    struct Hasta* next;
} Hasta;


typedef struct Queue {
    Hasta* front;
    Hasta* rear;
} Queue;


typedef struct Stack {
    Hasta* top;
} Stack;


typedef struct LinkedList {
    Hasta* head;
} LinkedList;


Hasta* hasta_olustur(int id, const char* ad, const char* durum) {
    Hasta* yeni = (Hasta*)malloc(sizeof(Hasta));
    if (yeni == NULL) {
        printf("Bellek tahsis hatasi!\n");
        exit(1);
    }
    yeni->id = id;
    strcpy(yeni->ad, ad);
    strcpy(yeni->durum, durum);
    yeni->next = NULL;
    return yeni;
}


Queue* queue_olustur() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int id, const char* ad) {
    Hasta* yeni = hasta_olustur(id, ad, "bekliyor");
    if (q->rear == NULL) {
        q->front = q->rear = yeni;
        return;
    }
    q->rear->next = yeni;
    q->rear = yeni;
}

Hasta* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL; // Kuyruk boş
    }
    Hasta* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    temp->next = NULL;
    return temp;
}

void listele_kuyruk(Queue* q) {
    printf("--- Bekleyen Hastalar ---\n");
    if (q->front == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta* curr = q->front;
    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->id, curr->ad, curr->durum);
        curr = curr->next;
    }
}


Stack* stack_olustur() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack* s, Hasta* h) {
    if (h == NULL) return;
    strcpy(h->durum, "muayenede");
    h->next = s->top;
    s->top = h;
}

Hasta* pop(Stack* s) {
    if (s->top == NULL) {
        return NULL; 
    }
    Hasta* temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}

void listele_yigin(Stack* s) {
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (s->top == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta* curr = s->top;
    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->id, curr->ad, curr->durum);
        curr = curr->next;
    }
}


LinkedList* list_olustur() {
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    l->head = NULL;
    return l;
}

void ekle_gecmis(LinkedList* l, Hasta* h) {
    if (h == NULL) return;
    strcpy(h->durum, "tamamlandi");
    h->next = NULL;

    if (l->head == NULL) {
        l->head = h;
    } else {
        Hasta* curr = l->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = h;
    }
}

void listele_gecmis(LinkedList* l) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (l->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta* curr = l->head;
    while (curr != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", curr->id, curr->ad, curr->durum);
        curr = curr->next;
    }
}


int main() {
    Queue* bekleyen_kuyrugu = queue_olustur();
    Stack* muayene_yigini = stack_olustur();
    LinkedList* tamamlanan_listesi = list_olustur();

    enqueue(bekleyen_kuyrugu, 1, "Ahmet");
    enqueue(bekleyen_kuyrugu, 2, "Mehmet");
    enqueue(bekleyen_kuyrugu, 3, "Ayse");

  
    Hasta* h1 = dequeue(bekleyen_kuyrugu);
    push(muayene_yigini, h1);
    Hasta* h1_tamamlanan = pop(muayene_yigini);
    ekle_gecmis(tamamlanan_listesi, h1_tamamlanan);


    Hasta* h2 = dequeue(bekleyen_kuyrugu);
    push(muayene_yigini, h2);
    Hasta* h2_tamamlanan = pop(muayene_yigini);
    ekle_gecmis(tamamlanan_listesi, h2_tamamlanan);

 
    printf("=== Tum Islemler Sonrasi ===\n\n");
    listele_kuyruk(bekleyen_kuyrugu);
    printf("\n");
    listele_yigin(muayene_yigini);
    printf("\n");
    listele_gecmis(tamamlanan_listesi);

    return 0;
}
