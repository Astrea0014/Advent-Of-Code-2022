#include <stdio.h>

#include <Windows.h>

int main() {
    FILE* pFile;
    fopen_s(&pFile, "input.txt", "r");

    INT nSum = 0;
    CHAR cOpponentPlay, cMyPlay;

    while (!feof(pFile)) {
        fscanf_s(pFile, "%c %c\n", &cOpponentPlay, 1, &cMyPlay, 1);

        switch (cMyPlay) {
        case 'X':
            nSum += cOpponentPlay - 'A' ? cOpponentPlay - 'A' : 3;
            break;
        case 'Y':
            nSum += cOpponentPlay - 'A' + 1 + 3;
            break;
        case 'Z':
            nSum += (cOpponentPlay - 'A' + 1 == 3 ? 1 : cOpponentPlay - 'A' + 1 + 1) + 6;
            break;
        }
    }

    printf("Score: %i\n", nSum);
}