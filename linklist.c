#include "suika.h"

void insert_point(LinkList* top, Point* p){
    if(!top)printf("error\r\n");
    while(top -> next){
        top = top->next;
    }
    LinkList* new = (LinkList*)malloc(sizeof(LinkList));
    new->p = p;
    top->next = new;
    new->previous = top;
}

void delete_point_in_linklist(LinkList* top,Point* p){
    if(!top)return;
    while(top){
        if(top->p == p){
            top -> p = NULL;
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

void delete_point(Point* p){
    LinkList* top = p -> above;
    while(top){
        if(top -> p)delete_point_in_linklist(top -> p -> below, p);
        top = top -> next;
    }
    top = p -> below;
    while(top){
        if(top -> p)delete_point_in_linklist(top -> p -> above, p);
        top = top -> next;
    }
    top = p -> right;
    while(top){
        if(top -> p)delete_point_in_linklist(top -> p -> left, p);
        top = top -> next;
    }
    top = p -> left;
    while(top){
        if(top -> p)delete_point_in_linklist(top -> p -> right, p);
        top = top -> next;
    }
}

Point* search_same_weight_linklist(LinkList* l, Point* p){
    while(l){
        if(l -> p && l -> p -> weight == p -> weight) return l -> p;
        l = l -> next;
    }
    return NULL;
}

int search_point_linklist(LinkList* l, Point* p){
    while(l){
        if(l -> p == p)return 1;
        l = l -> next;
    }
    return 0;
}

int search_adjoining_point(Point* center, Point* p){
    if(!center)return 0;
    if(center == p)return 1;
    int flag = 0;
    if(center -> above)flag |= search_point_linklist(center->above, p);
    if(center -> below)flag |= search_point_linklist(center->below, p);
    if(center -> left)flag |= search_point_linklist(center->left, p);
    if(center -> right)flag |= search_point_linklist(center->right, p);
    return flag;
}

void insert_above(Point* p, Point* q){
    if(!search_point_linklist(p->above, q))insert_point(p->above, q);
}

void insert_below(Point* p, Point* q){
    if(!search_point_linklist(p->below, q))insert_point(p->below, q);
}

void insert_right(Point* p, Point* q){
    if(!search_point_linklist(p->right, q))insert_point(p->right, q);
}

void insert_left(Point* p, Point* q){
   if(!search_point_linklist(p->left, q))insert_point(p->left, q);
}
