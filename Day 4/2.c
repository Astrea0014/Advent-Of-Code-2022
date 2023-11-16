#include <stdio.h>

#include <Windows.h>

int main() {
    FILE* pFile;
    fopen_s(&pFile, "input.txt", "r");

    INT nCount = 0;

    INT nFirstLower, nFirstHigher, nSecondLower, nSecondHigher;

    while (!feof(pFile)) {
        fscanf_s(pFile, "%i-%i,%i-%i\n", &nFirstLower, &nFirstHigher, &nSecondLower, &nSecondHigher);

        // Scenarios:
        // First lower must be bigger than second higher or vice versa.

        if (!(nFirstLower > nSecondHigher || nFirstHigher < nSecondLower))
            nCount++;
    }

    printf("Count: %i\n", nCount);
} 