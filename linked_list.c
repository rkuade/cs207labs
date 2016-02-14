
//your code here
#include <stdlib.h>
#include <stdio.h>

typedef struct item {
    int value;
    struct item* rest;
} Item;

Item* new_item(int value){
    Item* newitem = (Item *) malloc(sizeof(Item));
    newitem->value = value;
    newitem->rest = NULL;
    return newitem;
}

Item* insert_front(Item* listptr, int value){
    Item* newitem = new_item(value);
    newitem->rest = listptr;
    return newitem;
}


int get(Item* listptr, int index){
    int ctr = 0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (ctr==index){
            return p->value;
        }
        ctr++;
    }
    return -1;
}


void free_all(Item* listptr) {
    Item *p;
    Item *next;
    for(p = listptr; p!= NULL; p = next){
        next = p->rest;
        free(p);
    }
}

int get_index(Item* listptr, int value) {
    int count =0;
    Item* p;
    for(p = listptr; p!= NULL; p = p->rest){
        if (p->value==value){
            return count;
        }
        count++;
    }
    return -1;
}

Item* remove_item(Item* listptr, int value) {
    int count = 0;
    int i;
    Item* p;
    Item* q; 
    for(p = listptr; p!= NULL; p = p->rest){
        if (p->value==value){
            q = p->rest;
            for(i=count-1; i>=0; i--){
                q = insert_front(q,get(listptr,i));
            }
            return q;
        }
        count++;
        
    }
    return NULL;
}

int main(){
    Item* listptr;
    int i;
    listptr = new_item(0);
    for (i=1; i < 6; i++){
        listptr=insert_front(listptr, i);
    }
    for (i=0; i < 6; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    listptr = remove_item(listptr, 3);
    for (i=0; i <= 5; i++){
        printf("i %d Item %d\n", i, get(listptr, i));
    }
    printf("Index for 3 %d\n", get_index(listptr, 3));
    free_all(listptr);
}
