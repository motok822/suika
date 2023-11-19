#include "suika.h"
Point Default = {.x = -1, .y = -1, .weight = nothing, .state = Dead};
PointQueue pq;

void initialize_board(Board* b){
    b->field = (Point***)malloc(sizeof(Point**)*Board_SIZE);
    for(int i = 0;i < Board_SIZE;i++){
        b->field[i] = (Point**)malloc(sizeof(Point*)*Board_SIZE);
    }
    for(int i = 0;i < Board_SIZE;i++){
        for(int j = 0;j < Board_SIZE;j++){
            b->field[i][j] = &Default;
        }
    }
}

void show_board(Board b){
    for(int i = 0;i < Board_SIZE;i++){
        for(int j = 0;j < Board_SIZE;j++){
            if(b.field[i][j]->weight == nothing){
                printf("-");
            }else{
                printf("%c", b.field[i][j]->weight + '0');
            }
        }
        printf("\r\n");
    }
}

int search_alive_point(Board* b){
    int flag = 0;
    for(int i = 0;i < Board_SIZE;i++){
        if(b->field[0][i]->state == Alive){
            flag = 1;
        }
    }
    return flag;
}

int IsInBoard(Point* p, int dx, int dy){
    if(p->x + dx >= 0 && p->y + dy >= 0 && p->x + p->weight - 1 + dx < Board_SIZE && p->y + p->weight - 1 + dy < Board_SIZE) return 1;
    return 0;
}

void release_board(Board* b, Point* p){
    int TopX = p->x;
    int LeftY = p->y;
    for(int i = 0;i < p->weight;i++){
        for(int j = 0;j < p->weight;j++){
            b->field[TopX+i][LeftY+j] = &Default;
        }
    }
}

void drop_point(Board* b, Point* p){
    while(1){
        p -> x++;
        if(p->x + p->weight > Board_SIZE){
            p->x --;
            break;
        }
        int flag = 0;
        for(int i = 0;i < p->weight;i++){
            if(b->field[p->x+p->weight-1][p->y+i] != &Default)flag = 1;
        }
        if(flag == 1){
            p->x --;
            break;
        }
    }
    p->state = Dead;
}   

void chech_board(Board* b, Point* p){
    
}

Point* get_character(int c, Board* b, Point* p){
    switch(c){
        case -1:
            update_board(b, p);
            break;
        case 'd':
            if(search_alive_point(b) && IsInBoard(p, 0, 1)){
                release_board(b, p);
                p-> y += 1;
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        case 'a':
            if(c =='a' && search_alive_point(b) && IsInBoard(p, 0, -1)){
                release_board(b, p);
                p -> y -= 1;
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        case 's':
            if(c == 's' && search_alive_point(b)){
                release_board(b, p);
                drop_point(b, p);
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        default:
            if(!search_alive_point(b)){
                p = new_point(RandomFruit);
                update_board(b, p);
            }else update_board(b, p);
            break;
        case '.': break;
    }
    return p;
}

void update_board(Board* b, Point* p){
    int TopX = p->x;
    int LeftY = p->y;
    for(int i = 0;i < p->weight;i++){
        for(int j = 0;j < p->weight;j++){
            b->field[TopX+i][LeftY+j] = p;
        }
    }
}

Point* new_point(int random){
    Point* new;
    new = malloc(sizeof(Point));
    new->x = 0;
    new->y = 0;
    new->state = Alive;
    if(random == 0){
        new->weight = banana;
    }else{
        new->weight = rand() % FruitKind + 1;
    }
    insert_point(new);
    return new;
}

void insert_point(Point* p){
    if(pq.p == NULL){
        pq.p = p;
        return;
    }
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
    PointQueue* top = &pq;
    while(top->p){
        if(top->p == p){
            if(!top->next){
                top->next->previous = top->previous;
            }
            if(!top->previous){
                top->previous->next = top->next;
            }
        }
        top = top->next;
        if(!top)break;
    }
}

void show_PointQueue(){
    PointQueue* top = &pq;
    while(top->p){
        printf("%d", top->p->weight);
        top = top -> next;
        if(!top)break;
    }
}

