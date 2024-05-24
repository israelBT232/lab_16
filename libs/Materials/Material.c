//
// Created by MSI on 11.03.2024.
//
#include "util.h"
#include <minmax.h>
#include <stdlib.h>

int findMax(const int* array, int size) {
    int max = array[0];

    for (int i = 1; i < size; ++i) {
        max = max(max, array[i]);
    }

    return max;
}

int findMin(const int* array, int size) {
    int min = array[0];

    for (int i = 1; i < size; ++i) {
        min = min(min, array[i]);
    }

    return min;
}

bool isSet(const long long* array, int size) {
    for (int i = 0; i < size; ++i) {
        long long value = array[i];

        for (int j = i + 1; j < size; j++) {
            if (i == j) continue;

            if (value == array[j]) return false;
        }
    }

    return true;
}

long long sum(const int* array, int size) {
    long long sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }

    return sum;
}

static int compareLL(const void* left, const void* right) {
    long long leftValue = *((const long long*) left);
    long long rightValue = *((const long long*) right);

    if (leftValue > rightValue) {
        return 1;
    }

    return (leftValue == rightValue) ? 0 : -1;
}

int countUniques(long long* array, int size) {
    if (size == 0) {
        return 0;
    }

    qsort(array, size, sizeof(long long), compareLL);

    int count = 0;

    for (int i = 0; i < size; ++i) {
        long long value = array[i];
        bool found = false;

        for (int j = i + 1; j < size; ++j) {
            long long current = array[j];

            if (current == value) {
                found = true;
                break;
            } else if (value > current) {
                break;
            }
        }

        if (!found) {
            count++;
        }
    }

    return count;
}

bool isNonDescending(const int* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        if (array[i + 1] < array[i]) {
            return false;
        }
    }

    return true;
}

int countValues(const int* array, int size, int value) {
    int count = 0;

    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            count++;
        }
    }

    return count;
}
