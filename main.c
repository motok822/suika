#include "suika.h"

int main(int argc, char* argv[]){
    Board b;
    initialize_board(&b);

    int c = -1;  // Dummy 

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる
    Point* pos;
    pos = (Point*)malloc(sizeof(Point));
    pos -> x = 0;
    pos -> y = 0;
    pos -> weight = banana;
    pos -> state = Alive;
    insert_point(pos);
    while(1){
        system("clear");
        printf("Press '.' to close\r\n");        
        printf("You pressed '%c'\r\n", c);

        pos = get_character(c, &b, pos);
        show_board(b);
        show_PointQueue();

        if ((c = getchar()) == '.') { // '.' を押すと抜ける
            break;
        }
    }
    system("/bin/stty cooked");  // 後始末
    return 0;

}