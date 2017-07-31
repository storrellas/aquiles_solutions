#include <iostream>

using namespace std;

const int BOARD_SIZE = 8;
const int GOAL = 2;
const int TILE = 1;
const int EMPTY = 0;
const int BOARD[BOARD_SIZE][BOARD_SIZE] = {
    TILE, TILE,  TILE,  EMPTY, TILE,  TILE,  TILE,TILE,
    TILE, EMPTY, TILE,  TILE,  TILE,  EMPTY, TILE, EMPTY,
    TILE, EMPTY, EMPTY, TILE,  EMPTY, EMPTY, TILE, TILE,
    TILE, TILE,  EMPTY, TILE,  EMPTY, EMPTY, EMPTY, TILE,
    TILE, EMPTY, EMPTY, TILE,  TILE,  TILE,  TILE, TILE,
    TILE, TILE,  TILE,  TILE,  EMPTY, TILE,  EMPTY, EMPTY,
    TILE, EMPTY, EMPTY, TILE,  EMPTY, TILE,  TILE,  TILE,
    TILE, TILE,  EMPTY, TILE,  TILE,  TILE,  EMPTY, GOAL,

};


const int UNVISITED = -1;
const int VISITING = -2;
const int NON_VISTABLE = -3;
int distance_matrix[BOARD_SIZE][BOARD_SIZE];
int distance_matrix_status[BOARD_SIZE][BOARD_SIZE];

/**
 * Prints the current matrix status
 */
void print_board(const int matrix[BOARD_SIZE][BOARD_SIZE]){

    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            if( matrix[i][j] == TILE ) cout << "X";
            else cout << " ";
        }
        cout << endl;
    }
}

#include <iomanip>

/**
 * Prints the current matrix status
 */
void print_distance_matrix(){

    cout << " " << endl;
    cout << "DISTANCE MATRIX:" << endl;
    cout << " " << endl;

    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            cout << setfill('0') << setw(2) << distance_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            cout << setfill('0') << setw(2) << distance_matrix_status[i][j] << " ";
        }
        cout << endl;
    }
}

/* memset example */
#include <stdio.h>
#include <string.h>

int main()
{
    cout << "------------------" << endl;
    cout << "-- Program init --" << endl;
    cout << "------------------" << endl;

    // Print board
    print_board(BOARD);

    /// Distance Matrix initialization
    cout << " " << endl;
    cout << "(1) Initialization:" << endl;
    cout << " " << endl;

    std::fill_n(&distance_matrix[0][0], sizeof(distance_matrix) / sizeof(**distance_matrix), 0);
    std::fill_n(&distance_matrix_status[0][0], sizeof(distance_matrix) / sizeof(**distance_matrix), UNVISITED);
    print_distance_matrix();

    /// Calculate non-visitable
    cout << " " << endl;
    cout << "(2) Calcualte non-visitable:" << endl;
    cout << " " << endl;
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            if( BOARD[i][j] == EMPTY ) distance_matrix[i][j] = NON_VISTABLE;
        }
    }

    print_distance_matrix();


//    bool finished = false;
//    const int goal_x = 7;
//    const int goal_y = 7;
//    distance_matrix[goal_x][goal_y] = 0;

//    int i = 4;


//    int x, y;
//    while( !finished ){


//        for(int i = 0; i < BOARD_SIZE; ++i){
//            for(int j = 0; j < BOARD_SIZE; ++j){
//                if( [i][j] == EMPTY ) distance_matrix[i][j] = NON_VISTABLE;
//            }
//        }

//        // --------------------
//        if( i > 4 ) break;
//        i++;
//        // --------------------
//    }

    cout << "------------------" << endl;
    cout << "-- Program END --" << endl;
    cout << "------------------" << endl;
    return 0;
}

