#ifndef SUDOKU_SUDOKULIB_H_LOADED

    #define SUDOKU_SUDOKULIB_H_LOADED

    struct Field {
        int value;
        int valid;
        int possibility[10];
    };

    typedef struct Field ** sudokuArray;

    sudokuArray readSudoku(char *sudokuFile);

    void writeSudoku(sudokuArray sudoku, char *sudokuFile);

    void printSudoku(sudokuArray sudoku);

#endif
