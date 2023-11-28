#include<stdio.h>
#include<stdlib.h>

#define Board_SIZE 20
#define Alive 1
#define Dead 0
#define FruitKind 4
#define RandomFruit 1
extern int GameOver;
extern int Score;

typedef enum{
    nothing, //white
    banana,  //yellow
    strawberry, //red
    pear,   //skyblue
    apple,  //blue
    grape,  //magenta
    watermelon,  //green
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
void show_board(Board* b);
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
void make_graph(Board* b, Point* p);
void under_line(Board* b, Point* p);
void reset_line(Board* b, Point* p);
void drop_all_point(Board* b);

void insert_point(LinkList* top,Point* p);
void delete_point(Point* p);
void delete_point_in_linklist(LinkList* top,Point* p);
int search_point_linklist(LinkList* l, Point* p);
int search_adjoining_point(Point* center, Point* p);
void show_PointQueue();//debug
Point* search_same_weight_linklist(LinkList* l, Point* p);
void insert_above(Point* p, Point* q);
void insert_below(Point* p, Point* q);
void insert_right(Point* p, Point* q);
void insert_left(Point* p, Point* q);
int search_point_num(LinkList* l);
void make_all_graph(Board* b);

void minus_left(Board* b, LinkList* top);
void delete_graph_left_linklist(Board* b, LinkList* top);
void make_graph_left_linklist(Board* b, LinkList* top);
void push_left(Board* b, LinkList* top);
void plus_right(Board* b, LinkList* top);
void delete_graph_right_linklist(Board* b, LinkList* top);
void make_graph_right_linklist(Board* b, LinkList* top);
void push_right(Board* b, LinkList* top);
void minus_above(Board* b, LinkList* top);
void delete_graph_above_linklist(Board* b, LinkList* top);
void make_graph_above_linklist(Board* b, LinkList* top);
void push_above(Board* b, LinkList* top);
int able_to_put_left(LinkList* top);
int able_to_put_right(LinkList* top);
// void insert_graph(GraphList* top, Graph* g);
// void insert_graph(GraphList* top, Graph* g);