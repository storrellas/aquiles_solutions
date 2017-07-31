#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

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
const int VISITED = -4;
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

bool check_in_board(int x_cord, int y_cord){
    if( x_cord < 0 or x_cord > 7 ) return false;
    if( y_cord < 0 or y_cord > 7 ) return false;
    if(BOARD[x_cord][y_cord] == EMPTY) return false;
    return true;
}

void visit_tile(int x_cord, int y_cord, int distance_to_goal){

    int x_neigh, y_neigh;

    cout << "VISITING " << distance_matrix_status[x_cord][y_cord] << " " << x_cord << " " << y_cord << " " << distance_to_goal << endl;
    // left neighbour
    x_neigh = x_cord-1; y_neigh = y_cord;
    if( check_in_board(x_neigh, y_neigh) and distance_matrix_status[x_neigh][y_neigh] == UNVISITED){
        distance_matrix[x_neigh][y_neigh] = distance_to_goal + 1;
        distance_matrix_status[x_neigh][y_neigh] = VISITING;
    }


    // right neighbour
    x_neigh = x_cord+1; y_neigh = y_cord;
    if( check_in_board(x_neigh, y_neigh) and distance_matrix_status[x_neigh][y_neigh] == UNVISITED){
        distance_matrix[x_neigh][y_neigh] = distance_to_goal + 1;
        distance_matrix_status[x_neigh][y_neigh] = VISITING;
    }


    // up neighbour
    x_neigh = x_cord; y_neigh = y_cord+1;
    if( check_in_board(x_neigh, y_neigh) and distance_matrix_status[x_neigh][y_neigh] == UNVISITED){
        distance_matrix[x_neigh][y_neigh] = distance_to_goal + 1;
        distance_matrix_status[x_neigh][y_neigh] = VISITING;
    }


    // down neighbour
    x_neigh = x_cord; y_neigh = y_cord-1;
    if( check_in_board(x_neigh, y_neigh) and distance_matrix_status[x_neigh][y_neigh] == UNVISITED){
        distance_matrix[x_neigh][y_neigh] = distance_to_goal + 1;
        distance_matrix_status[x_neigh][y_neigh] = VISITING;
    }


    // Mark node as visited
    distance_matrix_status[x_cord][y_cord] = VISITED;
}

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

    cout << " " << endl;
    cout << "(3) Iterate through matrix:" << endl;
    cout << " " << endl;

    bool finished = false;
    const int goal_x = 7;
    const int goal_y = 7;
    distance_matrix[goal_x][goal_y] = 0;
    distance_matrix_status[goal_x][goal_y] = VISITING;

    int iterations = 0;

    while( !finished ){

        print_distance_matrix();

        // Iterate full-board
        for(int i = 0; i < BOARD_SIZE; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j){

                if( distance_matrix_status[i][j] == VISITING ){
                    // treat tile
                    visit_tile(i, j, distance_matrix[i][j]);
//    cout << "In iteration" << endl;
//                    print_distance_matrix();
//cout << "END In iteration" << endl;
                }

            }
        }

        // --------------------
        if( iterations > 4 ) break;
        iterations++;
        // --------------------


        cout << endl;
    }

    cout << "------------------" << endl;
    cout << "-- Program END --" << endl;
    cout << "------------------" << endl;
    return 0;
}

