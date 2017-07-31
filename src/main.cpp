#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

//#ifdef DEBUG

namespace Board{

    const int SIZE = 8;
    const int GOAL = 2;
    const int TILE = 1;
    const int EMPTY = -1;
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



class DistanceGenerator{
public:

    enum TILE_STATUS{
        UNVISITED,
        VISITING,
        VISITED
    };
    TILE_STATUS matrix_status[Board::SIZE][Board::SIZE];

    // Distance Matrix
    int matrix[Board::SIZE][Board::SIZE];

    DistanceGenerator(){
        std::fill_n(&matrix[0][0], sizeof(matrix) / sizeof(**matrix), 0);
        std::fill_n(&matrix_status[0][0], sizeof(matrix_status) / sizeof(**matrix_status), TILE_STATUS::UNVISITED);

        /// Calculate non-visitable
        set_non_visitable();
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

private:
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
        if( check_in_board(x_cord, y_cord) and matrix_status[x_cord][y_cord] == TILE_STATUS::UNVISITED){
            matrix[x_cord][y_cord] = distance_to_goal + 1;
            matrix_status[x_cord][y_cord] = VISITING;
        }
    }


    /**
     * @brief visit_tile Visit the specified tile and treat neighbors
     * @param x_cord
     * @param y_cord
     * @param distance_to_goal
     */
    void visit_tile(int x_cord, int y_cord){

        int x_neigh, y_neigh;
        int distance_to_goal = matrix[x_cord][y_cord];
#ifdef DEBUG
        cout << "VISITING " << matrix_status[x_cord][y_cord] << " " << x_cord << " " << y_cord << " " << distance_to_goal << endl;
#endif
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
        matrix_status[x_cord][y_cord] = TILE_STATUS::VISITED;
    }

    /**
     * Removes those tiles that are empty in board
     */
    void set_non_visitable(){
        for(int i = 0; i < Board::SIZE; ++i){
            for(int j = 0; j < Board::SIZE; ++j){
                if( Board::MATRIX[i][j] == Board::EMPTY )
                    matrix[i][j] = Board::EMPTY;
            }
        }
#ifdef DEBUG
        cout << distance_generator->to_str() << endl;
#endif
    }

public:

    /**
     * Analyse board to get distance_matrix
     */
    void analyse(){


        bool finished = false;
        const int goal_x = 7;
        const int goal_y = 7;
        matrix[goal_x][goal_y] = 0;
        matrix_status[goal_x][goal_y] = TILE_STATUS::VISITING;

        int iterations = 0;

        while( !finished ){
            finished = true;
#ifdef DEBUG
            cout << to_str() << endl;
#endif

            // Iterate full-board
            for(int i = 0; i < Board::SIZE; ++i){
                for(int j = 0; j < Board::SIZE; ++j){

                    if( matrix_status[i][j] == TILE_STATUS::VISITING ){
                        // visit tile
                        visit_tile(i, j);
                        finished = false;
                    }

                }
            }

    //        // --------------------
    //        if( iterations > 13 ) break;
    //        iterations++;
    //        // --------------------

        }

    }

};
DistanceGenerator* distance_generator = nullptr;


int main()
{
    cout << "------------------" << endl;
    cout << "-- Program init --" << endl;
    cout << "------------------" << endl;

    /// Print board
    cout << " " << endl;
    cout << "(1) Board:" << endl;
    cout << " " << endl;
    cout << Board::to_str() << endl;

    /// Distance Matrix initialization
    cout << " " << endl;
    cout << "(2) Initialization:" << endl;
    cout << " " << endl;
    distance_generator = new DistanceGenerator();
    cout << distance_generator->to_str() << endl;

    /// Iterate through matrix
    cout << " " << endl;
    cout << "(3) Iterate through matrix:" << endl;
    cout << " " << endl;

    distance_generator->analyse();
    cout << distance_generator->to_str() << endl;

    cout << "------------------" << endl;
    cout << "-- Program END --" << endl;
    cout << "------------------" << endl;
    delete distance_generator;
    return 0;
}

