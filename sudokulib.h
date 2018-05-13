#ifndef SUDOKU_SUDOKULIB_H_LOADED

    #define SUDOKU_SUDOKULIB_H_LOADED

    struct Field {
        int value;
        int valid;
        int possibility[10];
    } sudoku[9][9];

    // TODO sudoku is pass through a global namespace, consider passing via arguments

    void readSudoku(char *sudokuFile);

    void writeSudoku(char *sudokuFile);

    void printSudoku();

#endif
