#include <stdio.h>

#include <Windows.h>

// cDelta = cMyPlay - cOpponentPlay
// cDelta = 23 for a draw. This % 3 = 2.
// cDelta = 21 || 24 for a win. Both of which % 3 = 0.
// cDelta = 22 || 25 for a loss. Both of which % 3 = 1

int main() {
    FILE* pFile;
    fopen_s(&pFile, "input.txt", "r");

    INT nSum = 0;
    CHAR cOpponentPlay, cMyPlay;

    while (!feof(pFile)) {
        fscanf_s(pFile, "%c %c\n", &cOpponentPlay, 1, &cMyPlay, 1);
        nSum += cMyPlay - 'X' + 1;

        switch ((cMyPlay - cOpponentPlay) % 3) {
        case 0:         // Win
            nSum += 6;
            break;
        case 1:         // Loss
            break;
        case 2:         // Draw
            nSum += 3;
            break;
        }
    }

    fclose(pFile);

    printf("Score: %i\n", nSum);
}