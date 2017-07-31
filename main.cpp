#include <iostream>

using namespace std;

const int BOARD_SIZE = 8;
const int TILE = 1;
const int EMPTY = 0;
int board[8][8] = {
    TILE, TILE,  TILE,  EMPTY, TILE,  TILE,  TILE,TILE,
    TILE, EMPTY, TILE,  TILE,  TILE,  EMPTY, TILE, EMPTY,
    TILE, EMPTY, EMPTY, TILE,  EMPTY, EMPTY, TILE, TILE,
    TILE, TILE,  EMPTY, TILE,  EMPTY, EMPTY, EMPTY, TILE,
    TILE, EMPTY, EMPTY, TILE,  TILE,  TILE,  TILE, TILE,
    TILE, TILE,  TILE,  TILE,  EMPTY, TILE,  EMPTY, EMPTY,
    TILE, EMPTY, EMPTY, TILE,  EMPTY, TILE,  TILE,  TILE,
    TILE, TILE,  EMPTY, TILE,  TILE,  TILE,  EMPTY, TILE,

};

/**
 * Prints the current matrix status
 */
void print_matrix(int matrix[8][8]){

    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            if( matrix[i][j] == TILE ) cout << "X";
            else cout << " ";
        }
        cout << endl;
    }

}

int main()
{
    cout << "Hello World!" << endl;

    print_matrix(board);
    return 0;
}

