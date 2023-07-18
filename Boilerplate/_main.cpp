#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    FILE* f;
    char* name;
    int size;
} queue;


queue* Create(char* name){
    queue* q = malloc(sizeof(queue));
    q ->name = name;
    q->size = 0;
}

void Push(queue* q, char el){
    q->f = fopen(q->name, "a");
    q->size++;
    fprintf(q->f, "%c", el);
    fclose(q->f);
}
char Pop(queue* q){
    q->size--;
    q->f = fopen(q->name, "r");
    FILE* tmp = fopen("TMPTMPTMP.txt", "w");
    char cur;
    fscanf(q->f, "%c", &cur);
    while(fscanf(q->f, "%c", &cur) != 0){
        fprintf(tmp, "%c", cur);
    }
    fclose(tmp);
    fclose(q->f);
    tmp = fopen("TMPTMPTMP.txt", "r");
    q->f = fopen(q->name, "w");
    while(fscanf(tmp, "%c", &cur) != 0){
        fprintf(q->f, "%c", cur);
    }
    fclose(tmp);
    fclose(q->f);
}

int main(){
    freopen("output.txt", "w", stdout);
    queue q;
    Create("input.txt");
    Push(q, '3');
    Push(q,'6');
    
    
    // tree* tr;
    // tr = create(5);
    // add_node(tr, 5, 2);
    // add_node(tr, 5, 3);
    // add_node(tr, 3, 1);
    // add_node(tr, 3, 10);
    // //vecc.sort
    // //comparator
    // //swap
    // printf("\n%d", dfscounter(tr->root));
}