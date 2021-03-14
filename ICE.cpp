#include <iostream>
#include "Board.h"

int main()
{
    Board board;
    board.init();
    board.loadStart();
    board.print();
    board.printBitBoards();

    return 0;
}