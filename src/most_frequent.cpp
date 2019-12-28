//
// Created by Matthias Danetzky on 03/12/2019.
//

#include "most_frequent.h"

int sort_desc(const void *cmp1, const void *cmp2) {
    // Need to cast the void * to int *
    unsigned long a = *((unsigned long *) cmp1);
    unsigned long b = *((unsigned long *) cmp2);
    // The comparison
    return a > b ? -1 : (a < b ? 1 : 0);
    // A simpler, probably faster way:
    //return b - a;
}

unsigned long mostFrequent(unsigned long data[], byte dataSize) {
    // Sort the array
    qsort(data, dataSize, sizeof(data[0]), sort_desc);

    // find the max frequency using linear traversal
    int max_count = 1, curr_count = 1;
    unsigned long res = data[0];
    for (int i = 1; i < dataSize; i++) {
        if (data[i] == data[i - 1])
            curr_count++;
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                res = data[i - 1];
            }
            curr_count = 1;
        }
    }

    // If last element is most frequent
    if (curr_count > max_count) {
        res = data[dataSize - 1];
    }

    return res;
}