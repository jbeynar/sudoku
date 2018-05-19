#include <stdio.h>

#include "sudokulib.h"

int main() {
    printf("Sudoku application\n");
    sudokuArray sudoku = readSudoku("sudoku04.txt");
    printSudoku(sudoku);
    printf("is correct? %d\n\n", checkSudokuConflicts(sudoku));
    writeSudoku(sudoku, "sudoku04.txt");
    generatePossibilites(sudoku);
    return 0;
}

//void sudokuWalk(void * callbackFunction()){
//    for (int row = 0; row < 9; row++) {
//        for (int col = 0; col < 9; col++) {
//            callbackFunction(sudoku[row][col]);
//        }
//    }
//}