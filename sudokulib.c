#include "sudokulib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FS_WRITE 101
#define DIR_SUDOKU_INPUT "./../data/"
#define DIR_SUDOKU_OUTPUT "./../solutions/"

sudokuArray readSudoku(char *sudokuFile) {
    char filename[128];
    sprintf(filename, "%s%s", DIR_SUDOKU_INPUT, sudokuFile);
    FILE *filePointer = fopen(filename, "r");
    if (!filePointer) {
        perror("Failed to open file");
        printf("Unable to open file %s\n", filename);
    }
    int c, value, col, row, i = 0;

    sudokuArray sudoku;
    sudoku = (struct Field *) malloc(sizeof(struct Field *) * 9);
    for (int j = 0; j < 9; j++) {
        sudoku[j] = (struct Field *) malloc(sizeof(struct Field) * 9);
    }

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
    return sudoku;
}

void writeSudoku(sudokuArray sudoku, char *sudokuFile) {
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

void printSudoku(sudokuArray sudoku) {
    for (int row = 0; row < 9; row++) {
        if (row == 0) {
            printf("\n_____________________________________\n");
        }
        for (int col = 0; col < 9; col++) {
            if (col == 0) {
                printf("|");
            }
            if (sudoku[row][col].value == 0) {
                printf(" _ |");
            } else {
                printf(" %d |", sudoku[row][col].value);
            }
        }
        if (row == 8) {
            printf("\n-------------------------------------\n");
        } else {
            printf("\n|---|---|---|---|---|---|---|---|---|\n");
        }
    }
}

int checkSudokuConflicts(sudokuArray sudoku) {
    int conflictsCount = 0;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int currentValue = sudoku[row][col].value;
            int result = 0;
            if (currentValue == 0) {
                continue;
            }
            int i = 9;
            while (i--) {
                // Horizontal check
                if (col != i) {
                    if (currentValue == sudoku[row][i].value) {
                        result++;
                    }
                }

                // Vertical check
                if (row != i) {
                    if (currentValue == sudoku[i][col].value) {
                        result++;
                    }
                }

                // Local check
                int rowOffset = (row / 3) * 3;
                int colOffset = (col / 3) * 3;
                int localRow = rowOffset + (i / 3);
                int localCol = colOffset + (i % 3);

                if (row == localRow && col == localCol) {
                    continue;
                }
                if (currentValue == sudoku[localRow][localCol].value) {
                    result++;
                }
            }
            conflictsCount += result;
        }
    }
    return conflictsCount > 1;
}

int isSudokuSolvable(sudokuArray S) {
    generatePossibilites(S);
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int possibilities = 0;
            if (S[row][col].value > 0) {
                continue;
            }
            for (int p = 1; p < 10; p++) {
                if (S[row][col].possibility[p] == 1) {
                    possibilities++;
                }
            }
            if (possibilities == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void generatePossibilites(sudokuArray S) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (S[row][col].value > 0) {
                continue;
            }
            int currentValue = S[row][col].value;
            int i = 9;
            int j = 10;
            while (j--) S[row][col].possibility[j] = 1;
            while (i--) {
                // Horizontal check
                if (S[row][i].value > 0) {
                    S[row][col].possibility[S[row][i].value] = 0;
                }

                // Vertical check
                if (S[i][col].value) {
                    S[row][col].possibility[S[i][col].value] = 0;
                }

                // Local check
                int rowOffset = (row / 3) * 3;
                int colOffset = (col / 3) * 3;
                int localRow = rowOffset + (i / 3);
                int localCol = colOffset + (i % 3);
                if (S[localRow][localCol].value) {
                    S[row][col].possibility[S[localRow][localCol].value] = 0;
                }
            }
        }
    }
}

void printPossibilities(int possibility[10]) {
    for (int i = 1; i < 10; i++) {
        if (possibility[i] == 0) {
            continue;
        } else {
            printf("%d ", i);
        }
    }
}

int countPossibilities(int possibility[10]) {
    int count = 0;
    for (int i = 1; i < 10; i++) {
        if (possibility[i] == 0) {
            continue;
        } else {
            count++;
        }
    }
    return count;
}

int getBestPossibility(sudokuArray S, int R, int C) {
    int counts[10];
    int k = 10;
    while (k--) { counts[k] = 0; }
    for (int col = 0; col < 9; col++) {
        for (int i = 1; i < 10; i++) {
            if (S[R][col].possibility[i] == 1) {
                counts[i]++;
            }
        }
    }
    int minCount = 9;
    int selectedValue = 0;
    for (int i = 1; i < 10; i++) {
        if (S[R][C].possibility[i] == 0) {
            continue;
        } else {
            if (counts[i] < minCount) {
                minCount = counts[i];
                selectedValue = i;
            }
        }
    }
    return selectedValue;
}

void resolveSudoku(sudokuArray S) {
    generatePossibilites(S);
    for (int p = 1; p < 9; p++) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (S[row][col].value > 0) {
                    continue;
                }
                if (countPossibilities(S[row][col].possibility) <= p) {
                    int value = getBestPossibility(S, row, col);
                    S[row][col].value = value;
                    generatePossibilites(S);
                }
            }
        }
    }
}
