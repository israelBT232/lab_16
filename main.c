#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>

matrix createMatrixFromArray(const int* array, size_t rows, size_t columns) {
    matrix matrix = getMemMatrix(rows, columns);
    int arrayIndex = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.cells[i][j] = array[arrayIndex++];
        }
    }

    return matrix;
}

matrix* createArrayOfMatrixFromArray(const int* array, size_t matrixAmount, size_t rows, size_t columns) {
    matrix* matrices = getMemArrayOfMatrices(matrixAmount, rows, columns);
    int arrayIndex = 0;

    for (size_t k = 0; k < matrixAmount; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                matrices[k].cells[i][j] = array[arrayIndex++];
            }
        }
    }

    return matrices;
}

void test_countZeroRows() {
    matrix matrix = createMatrixFromArray((int[]) {
        1, 1, 0,
        0, 0, 0,
        0, 0, 1,
        0, 0, 0,
        0, 1, 1,
        }, 5, 3
    );

    assert(countZeroRows(matrix) == 2);

    freeMemMatrix(&matrix);
}
matrix createMatrixFromArray(const int* array, size_t rows, size_t columns) {
    matrix matrix = getMemMatrix(rows, columns);
    int arrayIndex = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.cells[i][j] = array[arrayIndex++];
        }
    }
    return matrix;
}
matrix* createArrayOfMatrixFromArray(const int* array, size_t matrixAmount, size_t rows, size_t columns) {
    matrix* matrices = getMemArrayOfMatrices(matrixAmount, rows, columns);
    int arrayIndex = 0;
    for (size_t k = 0; k < matrixAmount; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                matrices[k].cells[i][j] = array[arrayIndex++];
            }
        }
    }
    return matrices;
}

void test_createArrayOfMatrixFromArray() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t matrixAmount = 2;
    size_t rows = 3;
    size_t columns = 2;
    matrix* matrices = createArrayOfMatrixFromArray(array, matrixAmount, rows, columns);
    printf("Matrice 1 :\n");
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            printf("%d ", matrices[0].cells[i][j]);
        }
        printf("\n");
    }
    printf("Matrice 2 :\n");
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            printf("%d ", matrices[1].cells[i][j]);
        }
        printf("\n");
    }
    for (size_t k = 0; k < matrixAmount; k++) {
        for (size_t i = 0; i < rows; i++) {
            free(matrices[k].cells[i]);
        }
        free(matrices[k].cells);
    }
    free(matrices);
}

int main() {
    test_countZeroRows();
    test_createArrayOfMatrixFromArray()
}
