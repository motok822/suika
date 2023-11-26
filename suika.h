#include<stdio.h>
#include<stdlib.h>

#define Board_SIZE 25
#define Alive 1
#define Dead 0
#define FruitKind 4
#define RandomFruit 1


typedef enum{
    nothing, //0
    banana,  
    strawberry,
    orange,
    pear,
    apple,
    grape,
    melon,
    watermelon,
}fruit;

typedef struct Point{
    int x;
    int y;
    fruit weight;
    int state;
    struct LinkList* above;
    struct LinkList* below;
    struct LinkList* right;
    struct LinkList* left;
}Point;

typedef struct LinkList{
    Point* p;
    struct LinkList* next;
    struct LinkList* previous;
} LinkList;

// typedef struct Graph{ //盤面の状態をGraphを用いて管理する これはグラフの頂点
//     Point* p;
//     struct GraphList* above;
//     struct GraphList* below;
//     struct GraphList* right;
//     struct GraphList* left;
// } Graph;

// typedef struct GraphList{
//     Graph* g;
//     struct GraphList* next;
//     struct GraphList* before;
// } GraphList;

typedef struct Board{
    Point*** field;
}Board;

void initialize_board(Board* b);
void show_board(Board b);
void update_board(Board* b, Point* p);
void update_grown_point_board(Board* b, Point* p);
int able_to_put(Board* b, Point* p);
void release_board(Board* b, Point* p);
int search_alive_point(Board* b);
int IsInBoard(Point*p, int dx, int dy);
void drop_point(Board* b, Point* p);
Point* new_point(int random);
Point* get_character(int, Board*, Point*);
int touching(Board* b, Point* p, Point* q);
Point* grown_one_direction(Board* b, LinkList* l, Point* p);
void check_board(Board* b, Point* p);

void insert_point(LinkList* top,Point* p);
void delete_point(LinkList* top,Point* p);
int search_point_linklist(LinkList* l, Point* p);
int search_adjoining_point(Point* center, Point* p);
void show_PointQueue();//debug
Point* search_same_weight_linklist(LinkList* l, Point* p);
void insert_above(Point* p, Point* q);
void insert_below(Point* p, Point* q);
void insert_right(Point* p, Point* q);
void insert_left(Point* p, Point* q);

// void insert_graph(GraphList* top, Graph* g);
// void insert_graph(GraphList* top, Graph* g);