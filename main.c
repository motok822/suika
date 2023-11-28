#include "suika.h"
int GameOver = 0;
int Score = 0;

int main(int argc, char* argv[]){
    Board b;
    initialize_board(&b);

    int c = -1;  // Dummy 

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる
    Point* pos;//AliveなPoint AliveなPointは1つ以下
    pos = (Point*)malloc(sizeof(Point));
    pos -> x = 0;
    pos -> y = 0;
    pos -> weight = banana;
    pos -> state = Alive;
    pos -> above = malloc(sizeof(LinkList));
    pos -> below = malloc(sizeof(LinkList));
    pos -> right = malloc(sizeof(LinkList));
    pos -> left = malloc(sizeof(LinkList));
    char str[1000];
    int i = 0;
    while(1){
        system("clear");
        printf("\x1b[39m");
        printf("Press '.' to close\r\n");        
        printf("You pressed '%c'\r\n", c);
        printf("Score: %d\r\n", Score);
        
        pos = get_character(c, &b, pos);
        LinkList* used = malloc(sizeof(LinkList));
        make_all_graph(&b);
        // show_all_point(pos, used);
        drop_all_point(&b);
        under_line(&b, pos);
        show_board(&b);
        reset_line(&b, pos);

        if(GameOver == 1){
            printf("GameOver\r\n");
            break;
        }
        if ((c = getchar()) == '.') { // '.' を押すと抜ける
            break;
        }
        i++;
    }
    system("/bin/stty cooked");  // 後始末
    return 0;
}