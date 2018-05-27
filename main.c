#include <stdio.h>

#include "sudokulib.h"

int main() {
    printf("Sudoku application\n");
    char sudokuFile[] = "sudoku04.txt";
    sudokuArray sudoku = readSudoku(sudokuFile);
    printSudoku(sudoku);
    printf("\nResolved sudoku");
    resolveSudoku(sudoku);
    printSudoku(sudoku);
    writeSudoku(sudoku, sudokuFile);
    return 0;
}