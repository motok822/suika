#include "suika.h"

void minus_left(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            release_board(b, top -> p);
            top -> p -> y--;
            minus_left(b, top -> p -> left);
            update_board(b, top -> p);
        }
        top = top -> next;
    }
}
void delete_graph_left_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            delete_point(top -> p);
            delete_graph_left_linklist(b, top -> p -> left);
        }
        top = top -> next;
    }
}
void make_graph_left_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            make_graph(b, top -> p);
            make_graph_left_linklist(b, top -> p -> left);
        }
        top = top -> next;
    }
}
void push_left(Board* b, LinkList* top){
    minus_left(b, top);
    delete_graph_left_linklist(b, top);
    make_graph_left_linklist(b, top);
}
void plus_right(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            release_board(b, top -> p);
            top -> p -> y++;
            plus_right(b, top -> p -> right);
            update_board(b, top -> p);
        }
        top = top -> next;
    }
}
void delete_graph_right_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            delete_point(top -> p);
            delete_graph_right_linklist(b, top -> p -> right);
        }
        top = top -> next;
    }
}
void make_graph_right_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            make_graph(b, top -> p);
            make_graph_right_linklist(b, top -> p -> right);
        }
        top = top -> next;
    }
}
void push_right(Board* b, LinkList* top){
    plus_right(b, top);
    delete_graph_right_linklist(b, top);
    make_graph_right_linklist(b, top);
}

void minus_above(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            release_board(b, top -> p);
            top -> p -> x--;
            minus_above(b, top -> p -> above);
            update_board(b, top -> p);
        }
        top = top -> next;
    }
}
void delete_graph_above_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            delete_point(top -> p);
            delete_graph_above_linklist(b, top -> p -> above);
        }
        top = top -> next;
    }
}
void make_graph_above_linklist(Board* b, LinkList* top){
    while(top){
        if(top -> p){
            make_graph(b, top -> p);
            make_graph_above_linklist(b, top -> p -> above);
        }
        top = top -> next;
    }
}
void push_above(Board* b, LinkList* top){
    minus_above(b, top);
    if(GameOver)return;
    delete_graph_above_linklist(b, top);
    make_graph_above_linklist(b, top);
}

int able_to_put_left(LinkList* top){
    int flag = 1;
    while(top){
        if(top -> p){
            if(top -> p -> y == 0)flag = 0;
            flag *= able_to_put_left(top -> p -> left);
        }
        top = top -> next;
    }
    return flag;
}

int able_to_put_right(LinkList* top){
    int flag = 1;
    while(top){
        if(top -> p){
            if(top -> p -> y >= Board_SIZE - top -> p -> weight - 1)flag = 0;
            flag *= able_to_put_right(top -> p -> right);
        }
        top = top -> next;
    }
    return flag;
}

int able_to_put_above(LinkList* top){
    int flag = 1;
    while(top){
        if(top -> p){
            if(top -> p -> x == 0)flag = 0;
            flag *= able_to_put_above(top -> p -> above);
        }
        top = top -> next;
    }
    return flag;
}

int able_to_put_above_self(Point *p){
    if(p -> x == 0)return 0;
    return 1;
}

int able_to_put_right_self(Point *p){
    if(p -> y + p -> weight >= Board_SIZE)return 0;
    return 1;
}

int able_to_put_left_self(Point *p){
    if(p -> y == 0)return 0;
    return 1;
}