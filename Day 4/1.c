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
        // Either lower or higher is equal to its counterpart
        // The first lower is smaller and the first higher is bigger, or vice versa.

        if (nFirstLower > nSecondLower && nFirstHigher < nSecondHigher ||
            nFirstLower < nSecondLower && nFirstHigher > nSecondHigher ||
            nFirstLower == nSecondLower || nFirstHigher == nSecondHigher)
            nCount++;
    }

    fclose(pFile);

    printf("Count: %i\n", nCount);
}