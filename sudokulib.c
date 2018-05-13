#include "sudokulib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FS_WRITE 101
#define DIR_SUDOKU_INPUT "./../data/"
#define DIR_SUDOKU_OUTPUT "./../solutions/"

void readSudoku(char *sudokuFile) {
    char filename[128];
    sprintf(filename, "%s%s", DIR_SUDOKU_INPUT, sudokuFile);
    FILE *filePointer = fopen(filename, "r");
    if (!filePointer) {
        perror("Failed to open file");
        printf("Unable to open file %s\n", filename);
    }
    int c, value, col, row, i = 0;
    while ((c = getc(filePointer)) != EOF) {
        if (c == 32) {
            continue;
        } else if (c >= 48 && c <= 57) {
            value = c - 48;
            row = i / 9;
            col = i % 9;
            sudoku[row][col].value = value;
            if (value > 0) {
                sudoku[row][col].valid = 1;
            } else {
                sudoku[row][col].valid = 0;
            }
            i++;
        } else {
            perror("Invalid input data structure (digits should be separated with space)");
        }
    }
    if (i != 81) {
        perror("Invalid input data length (file should has 81 space separated digits)");
    }
    fclose(filePointer);
}

void writeSudoku(char *sudokuFile) {
    char filename[128];
    sprintf(filename, "%s%s", DIR_SUDOKU_OUTPUT, sudokuFile);
    FILE *filePointer = fopen(filename, "w+");
    if (!filePointer) {
        perror("Failed to open file");
        printf("Unable to open file %s\n", filename);
        exit(ERROR_FS_WRITE);
    }

    char chunk[3];
    char output[256];
    memset(output, 0, sizeof(output));
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sprintf(chunk, "%d ", sudoku[row][col].value);
            strcat(output, chunk);
        }
    }
    output[strlen(output) - 1] = NULL;
    fputs(output, filePointer);
    fclose(filePointer);
}

void printSudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            printf("%d ", sudoku[row][col].value);
        }
        printf("\n");
    }
}