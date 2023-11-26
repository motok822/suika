#include "suika.h"

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
    char str[100];
    int i = 0;
    while(1){
        system("clear");
        printf("Press '.' to close\r\n");        
        printf("You pressed '%c'\r\n", c);
        printf("%s\r\n", str);

        pos = get_character(c, &b, pos);
        show_board(b);
        // show_PointQueue();
        str[i] = (char)c;
        if ((c = getchar()) == '.') { // '.' を押すと抜ける
            break;
        }
        i++;
    }
    system("/bin/stty cooked");  // 後始末
    return 0;

}