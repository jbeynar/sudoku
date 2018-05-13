#include <stdio.h>

#include "sudokulib.h"

int main() {
    printf("Sudoku application");
    readSudoku("sudoku04.txt");
    printSudoku();
    writeSudoku("sudoku04.txt");
    return 0;
}

//void sudokuWalk(void * callbackFunction()){
//    for (int row = 0; row < 9; row++) {
//        for (int col = 0; col < 9; col++) {
//            callbackFunction(sudoku[row][col]);
//        }
//    }
//}