#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;


namespace Board{

    const int SIZE = 8;
    const int GOAL = 2;
    const int TILE = 1;
    const int EMPTY = 0;
    const int MATRIX[SIZE][SIZE] = {
        TILE, TILE,  TILE,  EMPTY, TILE,  TILE,  TILE,  TILE,
        TILE, EMPTY, TILE,  TILE,  TILE,  EMPTY, TILE,  EMPTY,
        TILE, EMPTY, EMPTY, TILE,  EMPTY, EMPTY, TILE,  TILE,
        TILE, TILE,  EMPTY, TILE,  EMPTY, EMPTY, EMPTY, TILE,
        TILE, EMPTY, EMPTY, TILE,  TILE,  TILE,  TILE,  TILE,
        TILE, TILE,  TILE,  TILE,  EMPTY, TILE,  EMPTY, EMPTY,
        TILE, EMPTY, EMPTY, TILE,  EMPTY, TILE,  TILE,  TILE,
        TILE, TILE,  EMPTY, TILE,  TILE,  TILE,  EMPTY, GOAL,

    };

    /**
     * Prints the current matrix status
     */
    std::string to_str(){

        string str;
        for(int i = 0; i < Board::SIZE; ++i){
            for(int j = 0; j < Board::SIZE; ++j){
                if( Board::MATRIX[i][j] == Board::TILE ) str += "X";
                else str+= " ";
            }
            str += "\n";
        }
        return str;
    }


}


const int UNVISITED = -1;
const int VISITING = -2;
const int NON_VISTABLE = -3;
const int VISITED = -4;
//int distance_matrix[Board::SIZE][Board::SIZE];
//int distance_matrix_status[Board::SIZE][Board::SIZE];
class DistanceGenerator{
public:


    int matrix_status[Board::SIZE][Board::SIZE];

    // Distance Matrix
    int matrix[Board::SIZE][Board::SIZE];

    DistanceGenerator(){
        std::fill_n(&matrix[0][0], sizeof(matrix) / sizeof(**matrix), 0);
        std::fill_n(&matrix_status[0][0], sizeof(matrix_status) / sizeof(**matrix_status), UNVISITED);
    }



    /**
     * Prints the current matrix status
     */
    std::string to_str(){


        std::ostringstream ss;
        ss << " " << endl;
        ss << "DISTANCE MATRIX:" << endl;
        ss << " " << endl;

        for(int i = 0; i < Board::SIZE; ++i){
            for(int j = 0; j < Board::SIZE; ++j){
                ss << setfill('0') << setw(2) << matrix[i][j] << " ";
            }
            ss << endl;
        }
        ss << endl;
        for(int i = 0; i < Board::SIZE; ++i){
            for(int j = 0; j < Board::SIZE; ++j){
                ss << setfill('0') << setw(2) << matrix_status[i][j] << " ";
            }
            ss << endl;
        }

        ss << endl;

        return ss.str();
    }


};


DistanceGenerator distance_generator;





/**
 * Prints the current matrix status
 */
void print_distance_matrix(){

    cout << " " << endl;
    cout << "DISTANCE MATRIX:" << endl;
    cout << " " << endl;

    for(int i = 0; i < Board::SIZE; ++i){
        for(int j = 0; j < Board::SIZE; ++j){
            cout << setfill('0') << setw(2) << distance_generator.matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < Board::SIZE; ++i){
        for(int j = 0; j < Board::SIZE; ++j){
            cout << setfill('0') << setw(2) << distance_generator.matrix_status[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

/**
 * Check whether cooridnates are in board
 */
bool check_in_board(int x_cord, int y_cord){
    if( x_cord < 0 or x_cord > 7 ) return false;
    if( y_cord < 0 or y_cord > 7 ) return false;
    if(Board::MATRIX[x_cord][y_cord] == Board::EMPTY) return false;
    return true;
}

/**
 * Treats the specific tile
 */
void treat_tile(int x_cord, int y_cord, int distance_to_goal){
    if( check_in_board(x_cord, y_cord) and distance_generator.matrix_status[x_cord][y_cord] == UNVISITED){
        distance_generator.matrix[x_cord][y_cord] = distance_to_goal + 1;
        distance_generator.matrix_status[x_cord][y_cord] = VISITING;
    }
}


/**
 * @brief visit_tile Visit the specified tile and treat neighbors
 * @param x_cord
 * @param y_cord
 * @param distance_to_goal
 */
void visit_tile(int x_cord, int y_cord, int distance_to_goal){

    int x_neigh, y_neigh;

    cout << "VISITING " << distance_generator.matrix_status[x_cord][y_cord] << " " << x_cord << " " << y_cord << " " << distance_to_goal << endl;
    // left neighbour
    x_neigh = x_cord-1; y_neigh = y_cord;
    treat_tile(x_neigh, y_neigh, distance_to_goal);

    // right neighbour
    x_neigh = x_cord+1; y_neigh = y_cord;
    treat_tile(x_neigh, y_neigh, distance_to_goal);

    // up neighbour
    x_neigh = x_cord; y_neigh = y_cord+1;
    treat_tile(x_neigh, y_neigh, distance_to_goal);

    // down neighbour
    x_neigh = x_cord; y_neigh = y_cord-1;
    treat_tile(x_neigh, y_neigh, distance_to_goal);

    // Mark node as visited
    distance_generator.matrix_status[x_cord][y_cord] = VISITED;
}

int main()
{
    cout << "------------------" << endl;
    cout << "-- Program init --" << endl;
    cout << "------------------" << endl;

    // Print board
    cout << Board::to_str() << endl;

    /// Distance Matrix initialization
    cout << " " << endl;
    cout << "(1) Initialization:" << endl;
    cout << " " << endl;


//    std::fill_n(&distance_matrix[0][0], sizeof(distance_matrix) / sizeof(**distance_matrix), 0);
//    std::fill_n(&distance_matrix_status[0][0], sizeof(distance_matrix) / sizeof(**distance_matrix), UNVISITED);
//    print_distance_matrix();

    cout << distance_generator.to_str() << endl;

    /// Calculate non-visitable
    cout << " " << endl;
    cout << "(2) Calcualte non-visitable:" << endl;
    cout << " " << endl;
    for(int i = 0; i < Board::SIZE; ++i){
        for(int j = 0; j < Board::SIZE; ++j){
            if( Board::MATRIX[i][j] == Board::EMPTY )
                distance_generator.matrix[i][j] = NON_VISTABLE;
        }
    }
    print_distance_matrix();

    cout << " " << endl;
    cout << "(3) Iterate through matrix:" << endl;
    cout << " " << endl;

    bool finished = false;
    const int goal_x = 7;
    const int goal_y = 7;
    distance_generator.matrix[goal_x][goal_y] = 0;
    distance_generator.matrix_status[goal_x][goal_y] = VISITING;

    int iterations = 0;

    while( !finished ){
        finished = true;
        print_distance_matrix();

        // Iterate full-board
        for(int i = 0; i < Board::SIZE; ++i){
            for(int j = 0; j < Board::SIZE; ++j){

                if( distance_generator.matrix_status[i][j] == VISITING ){
                    // visit tile
                    visit_tile(i, j, distance_generator.matrix[i][j]);
                    finished = false;
                }

            }
        }

//        // --------------------
//        if( iterations > 13 ) break;
//        iterations++;
//        // --------------------

    }

    cout << "------------------" << endl;
    cout << "-- Program END --" << endl;
    cout << "------------------" << endl;
    return 0;
}

