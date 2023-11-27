#include "suika.h"
Point Default = {.x = -1, .y = -1, .weight = nothing, .state = Dead, .above=NULL, .below=NULL, .left=NULL, .right=NULL};
Point Default2 = {.x = 1000, .y = 1000, .weight = nothing, .state = Dead, .above=NULL, .below=NULL, .left=NULL, .right=NULL};
// PointQueue pq; //PointQueueの先頭のpはNULLに設定

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

void show_board(Board *b){
    for(int i = 0;i < Board_SIZE;i++){
        for(int j = 0;j < Board_SIZE;j++){
            switch(b -> field[i][j]->weight){
                case nothing:
                    printf("\x1b[39m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("-");
                    }
                    break;
                case banana:
                    printf("\x1b[33m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
                case strawberry:
                    printf("\x1b[31m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
                case pear:
                    printf("\x1b[36m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
                case apple:
                    printf("\x1b[34m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
                case grape:
                    printf("\x1b[35m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
                case watermelon:
                    printf("\x1b[32m");
                    if(b->field[i][j] == &Default2){
                        printf("|");
                    }else{
                        printf("%c", b->field[i][j]->weight + '0');
                    }
                    break;
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
            if(b->field[TopX+i][LeftY+j]== p)b->field[TopX+i][LeftY+j] = &Default;
        }
    }
}

void make_graph(Board* b, Point* p){
    if(p->x < Board_SIZE - p->weight){ //下方向の接触
        for(int i = 0;i < p->weight;i++){
            if(b->field[p->x+p->weight][p->y+i] != &Default){
                insert_above(b->field[p->x+p->weight][p->y+i], p);
                insert_below(p, b->field[p->x+p->weight][p->y+i]);
            }
        }
    }
    if(p->y > 0){ //左方向の接触
        for(int i = 0;i < p->weight;i++){
            if(b->field[p->x+i][p->y-1] != &Default){
                insert_right(b->field[p->x+i][p->y-1], p);
                insert_left(p,b->field[p->x+i][p->y-1]);
            }
        }
    }
    if(p->y < Board_SIZE - p->weight){ //右方向の接触
        for(int i = 0;i < p->weight;i++){
            if(b->field[p->x+i][p->y+p->weight] != &Default){
                insert_left(b->field[p->x+i][p->y+p->weight], p);
                insert_right(p, b->field[p->x+i][p->y+p->weight]);
            }
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
    }// p->x p->y に配置

    //ここからはグラフの構築
    make_graph(b, p);
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
    int put = 0;
    for(int i = 0;i < p->weight;i++){
        if(topY+i >= 0 && topY+i+p->weight-1 < Board_SIZE){
            p->x = topX;
            p->y = topY + i;
            if(able_to_put(b, p)){ //他のPointを押しのけない
                update_board(b, p);
                put = 1;
                break;
            }
        }
    }
    if(put == 0){ //他のPointを押しのけないで置くことが不可能 上に押しのけるのは確定で、左か右かは不確定
        p -> x = topX;
        p -> y = topY;
        push_above(b, p -> above);
        if(GameOver)return;
        if(able_to_put_left(p -> left)){
            push_left(b, p -> left);
            update_board(b, p);
        }else if(able_to_put_right(p -> right)){
            push_right(b, p->right);
            p -> y ++;
            update_board(b, p);
        }
    }
}

Point* grown_one_direction(Board* b, LinkList* l, Point* p){
    Point* q;
    if((q = search_same_weight_linklist(l, p)) && q){
        release_board(b, p);
        release_board(b, q);
        delete_point(p);
        delete_point(q);
        q -> weight += 1;
        update_grown_point_board(b, q);
        make_graph(b, q);
        return q;
    }
    return NULL;
}

int search_point_num(LinkList* l){
    int num = 0;
    while(l){
        num += 1;
        l = l -> next;
    }
    return num;
}

void check_board(Board* b, Point* p){
    Point* merge = NULL;
    if((merge = grown_one_direction(b, p->above, p)) && merge);
    else if((merge = grown_one_direction(b, p->below, p)) && merge);
    else if((merge = grown_one_direction(b, p->left, p)) && merge );
    else if((merge = grown_one_direction(b  , p->right, p)) && merge);
    if(merge)check_board(b, merge);
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
                if(!able_to_put(b, p))p -> y --;
                update_board(b, p);
                break;
            }//elseの場合はdefaultの処理
        case 'a'://左に移動
            if(c =='a' && search_alive_point(b) && IsInBoard(p, 0, -1)){
                release_board(b, p);
                p -> y -= 1;
                if(!able_to_put(b, p))p -> y++;
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
                if(!able_to_put(b, p)){
                    GameOver = 1;
                }else{
                    update_board(b, p);
                }
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
    new -> above = malloc(sizeof(LinkList));
    new -> below = malloc(sizeof(LinkList));
    new -> right = malloc(sizeof(LinkList));
    new -> left = malloc(sizeof(LinkList));
    return new;
}

void under_line(Board* b, Point* p){
    int x = p -> x + p -> weight;
    while(p -> state == Alive && x < Board_SIZE){
        if(b->field[x][p -> y] == &Default){
            Default2.weight = p -> weight;
            b -> field[x][p -> y] = &Default2; 
        }else{
            break;
        }
        x++;
    }
}

void reset_line(Board* b, Point* p){
    int x = p -> x + p -> weight;
    while(p -> state == Alive && x < Board_SIZE){
        if(b->field[x][p -> y] == &Default2){
            b -> field[x][p -> y] = &Default;
        }else{
            break;
        }
        x++;
    }
}