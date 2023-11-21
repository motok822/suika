#include "suika.h"
Point Default = {.x = -1, .y = -1, .weight = nothing, .state = Dead};
PointQueue pq; //PointQueueの先頭のpはNULLに設定

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

int touching(Board* b,Point* p, Point* q){
    int flag = 0;
    if(p->x > 0){
        for(int i = 0;i < p->weight+1;i++){
            if(p->y + i >= 0 && p->y + i < Board_SIZE){
                if(b->field[p->x-1][p->y+i] == q)flag = 1; 
            }
        }
    }
    if(p->x < Board_SIZE - p->weight){
        for(int i = 0;i < p->weight+1;i++){
            if(p->y + i >= 0 && p->y + i < Board_SIZE){
                if(b->field[p->x+p->weight][p->y+i] == q)flag = 1; 
            }
        }
    }
    if(p->y > 0){
        for(int i = 0;i < p->weight+1;i++){
            if(p->x + i >= 0 && p->x + i < Board_SIZE){
                if(b->field[p->x+i][p->y-1] == q)flag = 1; 
            }
        }
    }
    if(p->y < Board_SIZE - p->weight){
        for(int i = 0;i < p->weight+1;i++){
            if(p->x + i >= 0 && p->x + i < Board_SIZE){
                if(b->field[p->x+i][p->y+p->weight] == q)flag = 1; 
            }
        }
    }
    return flag;
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

int able_to_put(Board* b, Point* p){
    int topX = p-> x;
    int topY = p-> y;
    int flag = 1;
    for(int i = 0;i < p->weight;i++){
        for(int j = 0;j < p->weight;j++){
            if(b->field[topX+i][topY+j] != &Default)flag = 0;
        }
    }
    return flag;
}

void update_grown_point_board(Board* b, Point* p){
    int topX = p->x - 1;
    int topY = p->y - 1;
    for(int i = 0;i < p->weight;i++){
        if(topY+i >= 0 && topY+i+p->weight-1 < Board_SIZE){
            p->x = topX;
            p->y = topY + i;
            if(able_to_put(b, p)){ //他のPointを押しのけない
                update_board(b, p);
                break;
            }
        }
    }
}

void check_board(Board* b, Point* p){
    PointQueue* top = &pq;
    Point* mergeP = NULL;
    if(!top)return;
    while(top){
        if(top->p && top->p->weight == p -> weight && touching(b, top->p, p)){
            release_board(b, p);
            delete_point(p);
            release_board(b, top->p);
            top->p->weight += 1;
            update_grown_point_board(b, top->p);
            mergeP = top->p;
            break;
        }
        top = top->next;
    }
    if(mergeP)check_board(b, mergeP);
}

Point* get_character(int c, Board* b, Point* p){
    switch(c){
        case -1:
            update_board(b, p);
            break;
        case 'd'://右に移動
            if(search_alive_point(b) && IsInBoard(p, 0, 1)){
                release_board(b, p);
                p-> y += 1;
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        case 'a'://左に移動
            if(c =='a' && search_alive_point(b) && IsInBoard(p, 0, -1)){
                release_board(b, p);
                p -> y -= 1;
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        case 's'://drop
            if(c == 's' && search_alive_point(b)){
                release_board(b, p);
                drop_point(b, p);
                update_board(b, p);
                check_board(b, p);   
                break;
            }//elseの場合はdefaultの処理
        default: //Pointの追加
            if(!search_alive_point(b)){
                p = new_point(RandomFruit);
                update_board(b, p);
            }else update_board(b, p);
            break;
        case '.': break;
    }
    return p;
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
