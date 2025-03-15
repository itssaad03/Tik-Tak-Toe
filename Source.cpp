#include <iostream>
#include <climits>

using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char player = 'X';
    char computer = 'O';

public:
    TicTacToe() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void displayBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "---------\n";
        }
    }

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return true;
        return false;
    }

    int evaluate() {
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == player) return 10;
                else if (board[row][0] == computer) return -10;
            }
        }
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == player) return 10;
                else if (board[0][col] == computer) return -10;
            }
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == player) return 10;
            else if (board[0][0] == computer) return -10;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == player) return 10;
            else if (board[0][2] == computer) return -10;
        }
        return 0;
    }

    int minimax(int depth, bool isMax) {
        int score = evaluate();
        if (score == 10) return score - depth;
        if (score == -10) return score + depth;
        if (!isMovesLeft()) return 0;

        if (isMax) {
            int best = INT_MIN;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player;
                        best = max(best, minimax(depth + 1, false));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
        else {
            int best = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = computer;
                        best = min(best, minimax(depth + 1, true));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

    pair<int, int> findBestMove() {
        int bestVal = INT_MIN;
        pair<int, int> bestMove = { -1, -1 };
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    int moveVal = minimax(0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        bestMove = { i, j };
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void playerMove() {
        int row, col;
        cout << "Enter row and column (1-3): ";
        cin >> row >> col;
        if (board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = player;
        }
        else {
            cout << "Invalid move. Try again.\n";
            playerMove();
        }
    }

    void playGame() {
        while (isMovesLeft()) {
            displayBoard();
            playerMove();
            if (evaluate() == 10) {
                displayBoard();
                cout << "Player Wins!\n";
                return;
            }
            if (!isMovesLeft()) break;
            pair<int, int> bestMove = findBestMove();
            board[bestMove.first][bestMove.second] = computer;
            if (evaluate() == -10) {
                displayBoard();
                cout << "Computer Wins!\n";
                return;
            }
        }
        displayBoard();
        cout << "Game Draw!\n";
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
