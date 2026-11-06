/*
Problem 04: Tic-Tac-Toe
    SDE1 · Beginner

Problem statement
Design and implement a Tic-Tac-Toe game in C++ for two players on a 3 
× 3 board.

Players take turns placing their marks (X or O) on an empty cell. The 
game must validate moves, detect wins, and identify draws.

Requirements
    1. Player: Each player has a name and a mark (X or O).
    2. Board: Maintain a 3 × 3 grid, initially empty.
    3. Make a move: A player can place their mark in a specified row and 
    column.
    4. Validate moves: Reject moves that are outside the board or target 
    an occupied cell.
    5. Manage turns: Players alternate turns after each successful move. 
    An invalid move must not change whose turn it is.
    6. Detect a win: A player wins by completing a row, column, or 
    diagonal with their mark.
    7. Detect a draw: The game is a draw when all cells are occupied and 
    neither player has won.
    8. Game over: Reject further moves after a win or draw.
    9. Display board: Display the current board after moves, using a 
    clear representation for empty cells.
    10. Start a new game: Reset the board, turn, and game status.
*/

/*

Board
    grid
    isVacant
    isGameOver

    move()

Player
    1/2

main
    while(!board.isGameOver)
        board.move([1,1], p1)

board could hold all the logic required
but lets say later if we wanted 1 of the players to be AI
then we just change the Game Class

and keep the board logic within that class for the mechanics
of the actual board
*/

/*
Game
    Players[2]
    Board

Board
    grid
    isVacant
    isGameOver
    move
Player
    char mark
    player number?
    name?

main
    game     
*/

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

class Board {
    private:
        vector<vector<char>> grid;
    public:
        Board() {            
            resetBoard();
        }

        bool isVacant(int x, int y) const {            
            return grid[x][y] == '.';
        }

        bool isFull() const {
            for(int i=0; i<3; i++) {
                for(int j=0; j<3; j++) {
                    if(grid[i][j] == '.')
                        return false;
                }
            }
            return true;
        }

        bool move(int x, int y, char mark) {

            if (x < 0 || x >= 3 || y < 0 || y >= 3)
                return false;

            if(!isVacant(x,y))
                return false;

            grid[x][y] = mark;
            return true;
        }

        bool checkWinner() const {
            
            for(int i=0; i<3; i++) {

                // row check
                if(grid[i][0] != '.' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                    return true;

                // col check
                if(grid[0][i] != '.' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                    return true;                
            }
            // d1 check
            if(grid[0][0] != '.' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
                return true;

            // d2 check
            if(grid[0][2] != '.' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
                return true;

            return false;
        }

        void resetBoard() {
            grid.assign(3, vector(3, '.'));
        }

        void printBoard() const {
            string res;
            for(int i=0; i<3; i++) {

                for(int j=0; j<3; j++) {
                    res += grid[i][j];
                }
                res += "\n";
            }
            cout << res << endl;
        }
};

class Player {
    private:
        int num;
        char mark;
    public:
        Player(int num, char mark) :num(num), mark(mark) {}

        char markBoard() const {
            return mark;
        }

        int getNum() const {
            return num;
        }
};

class Game {
    private:
        Board &board;
        vector<Player> &players;
        int current_player = 0;
        bool game_over = false;

    public:
        Game(Board &board, vector<Player> &players) : board(board), players(players) {

            if(players.size() != 2)
                throw invalid_argument("players not assigned correctly");

            if(players[0].getNum() == players[1].getNum())
                throw invalid_argument("players not assigned correctly");

            if(players[0].markBoard() == players[1].markBoard())
                throw invalid_argument("players not assigned correctly");

            // if(players[0].getNum() != 1 && players[1]. getNum() != 2)
            //     throw invalid_argument("players not assigned correctly");

            // if(players[0].markBoard() != '#' && players[1]. markBoard() != 'o')
            //     throw invalid_argument("players not assigned correctly");
        }

        void printBoard() {
            board.printBoard();
        }

        bool move(int x, int y) {

            // validation
            if(game_over)
                return false;

            // choose player
            Player &player = players[current_player];

            // make/validate move
            if (!board.move(x, y, player.markBoard())) {
                cout << "Invalid move\n";
                return false;
            }

            // fascade
            board.printBoard();

            // win branch
            if(board.checkWinner()) {
                cout << "Player " << player.getNum()
                     << " has won the game!\n";
                game_over = true;
                return true;
            }

            // draw branch
            if (board.isFull()) {
                cout << "The game is a draw!\n";
                game_over = true;
                return true;
            }

            current_player = 1 - current_player;
            return true;
        }

        void resetGame() {
            board.resetBoard();
            current_player = 0;
            game_over = false;
        }
};



int main() {


    Board board;
    Player p1(1,'X');
    Player p2(2,'O');
    vector<Player> players;
    players.push_back(p1);
    players.push_back(p2);

    Game game(board, players);    
    game.printBoard();

    game.move(0,0);    
    game.move(0,1);
    game.move(1,1);
    game.move(1,2);
    game.move(100,2);

    game.move(2,2);

    game.resetGame();


    return 0;
}
