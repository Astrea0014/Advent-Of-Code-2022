#include <stdio.h>
#include <string.h>

#include <Windows.h>

CHAR szBlacklist[64];
INT nBlacklistCount = 0;

VOID WINAPI Blacklist(CHAR cCharacter) {
    szBlacklist[nBlacklistCount] = cCharacter;
    nBlacklistCount++;
}

BOOL WINAPI IsBlacklisted(CHAR cCharacter) {
    for (INT i = 0; i < nBlacklistCount; i++)
        if (szBlacklist[i] == cCharacter)
            return TRUE;
    return FALSE;
}

VOID WINAPI ResetBlacklist() {
    nBlacklistCount = 0;
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

    CHAR szBackpack[64];

    while (!feof(pFile)) {
        fscanf_s(pFile, "%s\n", szBackpack, sizeof(szBackpack));

        INT nBackpackSize = strlen(szBackpack);
        INT nCompartmentSize = nBackpackSize / 2;
        LPSTR lpCompartment1 = &szBackpack[0], lpCompartment2 = &szBackpack[nCompartmentSize];

        for (INT i = 0; i < nCompartmentSize; i++)
            for (INT j = 0; j < nCompartmentSize; j++)
                if (lpCompartment1[i] == lpCompartment2[j] && !IsBlacklisted(lpCompartment1[i])) {
                    nSum += GetPriority(lpCompartment1[i]);
                    Blacklist(lpCompartment1[i]);
                }

        ResetBlacklist();
    }

    fclose(pFile);

    printf("Sum: %i\n", nSum);
}