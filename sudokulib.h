#ifndef SUDOKU_SUDOKULIB_H_LOADED

#define SUDOKU_SUDOKULIB_H_LOADED

struct Field {
    int value;
    int valid;
    int possibility[10];
};

typedef struct Field **sudokuArray;

sudokuArray readSudoku(char *sudokuFile);

void writeSudoku(sudokuArray sudoku, char *sudokuFile);

void printSudoku(sudokuArray sudoku);

int checkSudokuConflicts(sudokuArray sudoku);

int isSudokuSolvable(sudokuArray S);

void generatePossibilites(sudokuArray S);

void printPossibilities(int possibility[10]);

int countPossibilities(int possibility[10]);

int getBestPossibility(sudokuArray S, int R, int C);

void resolveSudoku(sudokuArray S);

#endif
