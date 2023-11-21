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
}Point;

typedef struct PointQueue{ //現在ボードに存在するPointをリンクリストで管理
    Point* p;
    struct PointQueue* next;
    struct PointQueue* previous;
} PointQueue;

typedef struct Board{
    Point*** field;
}Board;

extern PointQueue pq;

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


void insert_point(Point* p);
void delete_point(Point* p);
void show_PointQueue();//debug