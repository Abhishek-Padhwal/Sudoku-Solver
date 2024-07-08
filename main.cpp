#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

const int SIZE = 9;
const int EMPTY = 0;

void printSudoku(const vector<vector<int>>& board) {
    system("cls"); // For Linux/Unix systems, use "cls" for Windows

    cout << "+-------+-------+-------+" << endl;
    for (int row = 0; row < SIZE; ++row) {
        cout << "| ";
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == EMPTY) {
                cout << ". ";
            } else {
                cout << board[row][col] << " ";
            }
            if ((col + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((row + 1) % 3 == 0) cout << "+-------+-------+-------+" << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}

bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < SIZE; ++x) {
        if (board[row][x] == num || board[x][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == EMPTY) {
                for (int num = 1; num <= SIZE; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        printSudoku(board);
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = EMPTY;
                        printSudoku(board);
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> board = {
    {5, 3, 0, 6, 7, 0, 9, 0, 2},
    {0, 0, 2, 1, 0, 0, 3, 0, 8},
    {1, 9, 0, 3, 4, 2, 5, 6, 7},
    {0, 5, 0, 0, 0, 1, 4, 2, 3},
    {4, 2, 0, 8, 0, 3, 7, 0, 1},
    {7, 1, 0, 0, 2, 0, 8, 5, 6},
    {9, 0, 1, 5, 0, 7, 2, 8, 4},
    {2, 8, 0, 0, 1, 0, 0, 0, 5},
    {3, 0, 5, 2, 0, 6, 1, 7, 9}
};


    if (solveSudoku(board)) {
        cout << "Sudoku solved successfully!" << endl;
    } else {
        cout << "No solution exists for the given Sudoku." << endl;
    }

    return 0;
}
