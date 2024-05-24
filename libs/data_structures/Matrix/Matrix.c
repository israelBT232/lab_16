//
// Created by MSI on 23.05.2024.
//
#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <mem.h>
#include "../../util/util.h"

int** allocateCells(int rows, int columns) {
    int** cells = (int**) malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++) {
        cells[i] = (int*) malloc(sizeof(int) * columns);
    }

    return cells;
}

matrix getMemMatrix(int rows, int columns) {
    return (matrix) {allocateCells(rows, columns), rows, columns};
}

matrix* getMemArrayOfMatrices(int matrixAmount, int rows, int columns) {
    matrix* matrices = (matrix*) malloc(sizeof(matrix) * matrixAmount);

    for (int i = 0; i < matrixAmount; i++) {
        matrices[i] = getMemMatrix(rows, columns);
    }

    return matrices;
}

void freeMemMatrix(matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->cells[i]);
    }

    free(matrix->cells);

    matrix->rows = 0;
    matrix->columns = 0;
}

void freeMemMatrices(matrix* matrices, int matrixAmount) {
    for (int i = 0; i < matrixAmount; i++) {
        freeMemMatrix(matrices + i);
    }
}


void inputMatrix(matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        printf("Введите %d строку матрицы:\n", i);

        int* row = matrix->cells[i];

        for (int j = 0; j < matrix->columns; j++) {
            scanf("%d", row + j);
        }
    }
}

void inputMatrices(matrix* matrices, int matrixAmount) {
    for (int i = 0; i < matrixAmount; i++) {
        inputMatrix(matrices + i);
    }
}

void outputMatrix(matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        int* row = matrix.cells[i];

        printf("[");

        for (int j = 0; j < matrix.columns; j++) {
            printf("%d", row[j]);

            if (j != (matrix.columns - 1)) {
                printf(", ");
            }
        }

        printf("]\n");
    }
}

void outputMatrices(matrix* matrices, int matrixAmount) {
    for (int i = 0; i < matrixAmount; i++) {
        outputMatrix(matrices[i]);
    }
}

void checkRowIndex(int rowIndex, int rowAmount) {
    assert(rowIndex > 0 && rowIndex < rowAmount);
}

void swapRows(matrix matrix, int row1Index, int row2Index) {
    if (row1Index == row2Index) {
        return;
    }

    checkRowIndex(row1Index, matrix.rows);
    checkRowIndex(row2Index, matrix.rows);

    int* row1 = matrix.cells[row1Index];
    int* row2 = matrix.cells[row2Index];

    matrix.cells[row1Index] = row2;
    matrix.cells[row2Index] = row1;
}

void swapColumns(matrix matrix, int column1Index, int column2Index) {
    for (int i = 0; i < matrix.rows; ++i) {
        int* row = matrix.cells[i];
        int cell1 = row[column1Index];
        int cell2 = row[column2Index];

        row[column1Index] = cell2;
        row[column2Index] = cell1;
    }
}

int indexOfMinRowByCriteria(matrix matrix, int (*criteria) (int*, int), int start, int end) {
    int minComparisonResult = criteria(matrix.cells[start], matrix.columns);
    int minIndex = start;

    for (int i = start + 1; i < end; i++) {
        int comparisonResult = criteria(matrix.cells[i], matrix.columns);

        if (comparisonResult < minComparisonResult) {
            minComparisonResult = comparisonResult;
            minIndex = i;
        }
    }

    return minIndex;
}

/**
 * uses insertion sort
 */
void sortRowsByCriteria(matrix matrix, int (*criteria)(const int*, int)) {
    for (int i = 0; i < matrix.rows; i++) {
        int* row = matrix.cells[i];
        int weight = criteria(row, matrix.columns);
        int j = i + 1;
        int currentWeight;

        while (j >= 0 && (currentWeight = criteria(matrix.cells[j], matrix.columns)) > weight) {
            matrix.cells[j + 1] = matrix.cells[j];
            weight = currentWeight;
            j--;
        }

        matrix.cells[j + 1] = row;
    }
}

int* getColumn(matrix matrix, int columnIndex) {
    int* column = malloc(sizeof(int) * matrix.rows);

    for (int i = 0; i < matrix.rows; i++) {
        column[i] = matrix.cells[i][columnIndex];
    }

    return column;
}

int indexOfMaxColumnByCriteria(matrix matrix, int start, int end, int (*criteria)(const int*, int)) {
    int maxColumnIndex = 0;
    int maxWeight = criteria(getColumn(matrix, start), matrix.rows);

    for (int i = start + 1; i < end; i++) {
        int weight = criteria(getColumn(matrix, i), matrix.rows);

        if (weight > maxWeight) {
            maxColumnIndex = i;
            maxWeight = weight;
        }
    }

    return maxColumnIndex;
}

void sortColumnsByCriteria(matrix matrix, int (*criteria)(const int*, int)) {
    for (int i = 0; i < matrix.columns; i++) {
        swapColumns(matrix, i, indexOfMaxColumnByCriteria(matrix, i + 1, matrix.columns, criteria));
    }
}

bool isSquareMatrix(matrix* matrix) {
    return matrix->rows == matrix->columns;
}

bool areTwoMatricesEqual(matrix* matrix1, matrix* matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->rows) {
        return false;
    }

    for (int i = 0; i < matrix1->rows; i++) {
        if (!memcpy(matrix1->cells[i], matrix2->cells[i], matrix1->columns)) {
            return false;
        }
    }

    return true;
}

bool isEMatrix(matrix* matrix) {
    if (!isSquareMatrix(matrix)) {
        return false;
    }

    for (int i = 0; i < matrix->rows; i++) {
        int* row = matrix->cells[i];

        for (int j = 0; j < matrix->columns; j++) {
            if (row[j] != ((i == j) ? 1 : 0)) {
                return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix* matrix) {
    if (!isSquareMatrix(matrix)) {
        return false;
    }

    for (int i = 0; i < matrix->rows; i++) {
        int* row = matrix->cells[i];

        for (int j = 0; j < matrix->columns; j++) {
            if (i == j) {
                continue;
            }

            if (row[j] != matrix->cells[j][i]) {
                return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix* matrix) {
    int** newCells = allocateCells(matrix->rows, matrix->columns);

    for (int i = 0; i < matrix->rows; i++) {
        int* row = matrix->cells[i];

        for (int j = 0; j < matrix->columns; j++) {
            newCells[j][i] = row[j];
        }
    }

    matrix->cells = newCells;
}

void transposeMatrix(matrix* matrix) {
    int** newCells = allocateCells(matrix->columns, matrix->rows);

    for (int i = 0; i < matrix->rows; i++) {
        int* row = matrix->cells[i];

        for (int j = 0; j < matrix->columns; j++) {
            newCells[j][i] = row[j];
        }
    }

    matrix->cells = newCells;
}

position positionOfValueByPredicate(matrix matrix, bool (*predicate)(int, int)) {
    int value = matrix.cells[0][0];
    int rowIndex = 0;
    int columnIndex = 0;

    for (int i = 0; i < matrix.rows; i++) {
        int* row = matrix.cells[i];

        for (int j = 0; j < matrix.columns; j++) {
            if (predicate(row[j], value)) {
                rowIndex = i;
                columnIndex = j;
            }
        }
    }

    return (position) {rowIndex, columnIndex};
}

bool isLessThan(int a, int b) {
    return a < b;
}

bool isMoreThan(int a, int b) {
    return a > b;
}

position getMinValuePos(matrix matrix) {
    return positionOfValueByPredicate(matrix, isLessThan);
}

position getMaxValuePos(matrix matrix) {
    return positionOfValueByPredicate(matrix, isMoreThan);
}

matrix multiply(matrix left, matrix right) {
    if (left.columns != right.rows) {
        fprintf(stderr, "Unable to multiply matrices because left matrix columns != right matrix rows");
        exit(EXIT_FAILURE);
    }

    int resultRows = left.rows;
    int resultColumns = right.columns;
    int** resultCells = allocateCells(resultRows, resultColumns);

    for (int i = 0; i < resultRows; ++i) {
        int* row = left.cells[i];

        for (int j = 0; j < resultColumns; ++j) {
            int sum = 0;

            for (int k = 0; k < left.columns; ++k) {
                sum += row[k] * right.cells[j][k];
            }

            resultCells[i][j] = sum;
        }
    }

    return (matrix) { resultCells, resultRows, resultColumns };
}

int countZeroRows(matrix matrix) {
    int count = 0;

    for (int i = 0; i < matrix.rows; i++) {
        if (countValues(matrix.cells[i], matrix.columns, 0) == 0) {
            count++;
        }
    }

    return count;
}
