#include <stdio.h>
#include <string.h>

#include <Windows.h>

CHAR szCommon[64];
INT nCommonCount = 0;

VOID WINAPI AddCommon(CHAR cCharacter) {
    szCommon[nCommonCount] = cCharacter;
    nCommonCount++;
}

BOOL WINAPI IsCommon(CHAR cCharacter) {
    for (INT i = 0; i < nCommonCount; i++)
        if (szCommon[i] == cCharacter)
            return TRUE;
    return FALSE;
}

VOID WINAPI ResetCommon() {
    nCommonCount = 0;
}

INT WINAPI GetPriority(CHAR cCharacter) {
    if (cCharacter >= 'A' && cCharacter <= 'Z')
        return cCharacter - 'A' + 27;
    else
        return cCharacter - 'a' + 1;
}

int main() {
    FILE* pFile;
    fopen_s(&pFile, "input.txt", "r");

    INT nSum = 0;

    CHAR szBackpacks[3][64];

    while (!feof(pFile)) {
        fscanf_s(pFile, "%s\n%s\n%s\n",
            szBackpacks[0], sizeof(szBackpacks[0]),
            szBackpacks[1], sizeof(szBackpacks[1]),
            szBackpacks[2], sizeof(szBackpacks[2])
        );

        for (INT i = 0; i < strlen(szBackpacks[0]); i++)
            for (INT j = 0; j < strlen(szBackpacks[1]); j++)
                if (szBackpacks[0][i] == szBackpacks[1][j] && !IsCommon(szBackpacks[0][i]))
                    AddCommon(szBackpacks[0][i]);

        for (INT i = 0; i < strlen(szBackpacks[2]); i++)
            if (IsCommon(szBackpacks[2][i])) {
                nSum += GetPriority(szBackpacks[2][i]);
                break;
            }

        ResetCommon();
    }

    fclose(pFile);

    printf("Sum: %i\n", nSum);
}