#include <stdio.h>
#include <string.h>

#include <Windows.h>

VOID WINAPI Blacklist(LPSTR lpBlacklist, LPINT lpBlacklistCount, CHAR cCharacter) {
    lpBlacklist[*lpBlacklistCount] = cCharacter;
    (*lpBlacklistCount)++;
}

BOOL WINAPI IsBlacklisted(LPSTR lpBlacklist, LPINT lpBlacklistCount, CHAR cCharacter) {
    for (INT i = 0; i < *lpBlacklistCount; i++)
        if (lpBlacklist[i] == cCharacter)
            return TRUE;
    return FALSE;
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

        CHAR szBlacklist[64];
        INT nBlacklistCount = 0;

        for (INT i = 0; i < nCompartmentSize; i++)
            for (INT j = 0; j < nCompartmentSize; j++)
                if (lpCompartment1[i] == lpCompartment2[j] && !IsBlacklisted(szBlacklist, &nBlacklistCount, lpCompartment1[i])) {
                    nSum += GetPriority(lpCompartment1[i]);
                    Blacklist(szBlacklist, &nBlacklistCount, lpCompartment1[i]);
                }
    }

    printf("Sum: %i\n", nSum);
}