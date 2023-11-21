#include "suika.h"

void insert_point(Point* p){
    PointQueue* top = &pq;
    while(top->next){
        top = top->next;
    }
    PointQueue* q = top;
    PointQueue* new = malloc(sizeof(PointQueue));
    new->p = p;
    q->next = new;
    new->previous = q;
}

void delete_point(Point* p){
    PointQueue* top = pq.next;
    while(top->p){
        if(top->p == p){
            if(top->next){
                top->next->previous = top->previous;
            }
            if(top->previous){
                top->previous->next = top->next;
            }
        }
        top = top->next;
        if(!top)break;
    }
}

void show_PointQueue(){
    PointQueue* top = &pq;
    top = top -> next;
    while(top->p){
        printf("%d", top->p->weight);
        top = top -> next;
        if(!top)break;
    }
}
