#include "body.h"
#include "object.h"
#include <iostream>

int main() {
    body dancer(20, 0, 10); 
    object ball(30, 0, 3);   

    dancer.print(0);
    for (int i = 0; i < 10; ++i) {
        dancer.seg_rotate();
        dancer.print(0);
        if (ball.is_grabbed_by(dancer)) {
            std::cout << "Object grabbed successfully!\n";
            break;
        }
    }

    return 0;
}
