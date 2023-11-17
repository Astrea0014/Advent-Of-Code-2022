#include <stdio.h>

#include <Windows.h>

VOID WINAPI Push(LPSTR lpString, CHAR cCharacter) {
    INT nStrLen = lstrlenA(lpString);
    lpString[nStrLen] = cCharacter;
    lpString[nStrLen + 1] = '\0';
}

VOID WINAPI Move(LPSTR lpFrom, LPSTR lpTo, INT nCount) {
    INT nFromLen = lstrlenA(lpFrom), nToLen = lstrlenA(lpTo);
    for (INT i = 0; i < nCount; i++) {
        lpTo[nToLen + i] = lpFrom[nFromLen - nCount + i];
    }

    lpTo[nToLen + nCount] = '\0';
    lpFrom[nFromLen - nCount] = '\0';
}

int main() {
    FILE* pFile;
    fopen_s(&pFile, "input.txt", "r");

    // Read every layer of crates until the line with numbers is encountered.

    CHAR szLayers[16][64];
    INT nLayerCount;

    for (nLayerCount = 0; nLayerCount < 16; nLayerCount++) {
        fscanf_s(pFile, "%[^\n]\n", szLayers[nLayerCount], (UINT)sizeof(szLayers[nLayerCount]));
        if (szLayers[nLayerCount][0] == '1') goto _count;
    }

    return -1;

_count:;

    // Count the number of piles.

    INT nPileCount = 0;
    BOOL bFound = FALSE;

    for (INT i = 0; i < strlen(szLayers[nLayerCount]); i++)
        if (szLayers[nLayerCount][i] != ' ' && !bFound) {
            nPileCount++;
            bFound = TRUE;
        }
        else bFound = FALSE;

    // Allocate memory for piles.

    LPSTR* ppPiles = (LPSTR*)malloc(nPileCount * sizeof(LPSTR));

    for (INT i = 0; i < nPileCount; i++) {
        ppPiles[i] = (LPSTR)malloc(64);
        ppPiles[i][0] = '\0';
    }

    // Convert layers into piles.

    for (INT i = nLayerCount - 1; i >= 0; i--)
        for (INT j = 0; j < nPileCount; j++)
            if (szLayers[i][1 + j * 4] != ' ')
                Push(ppPiles[j], szLayers[i][1 + j * 4]);

    // Read and execute instructions.

    INT nMoveCount = 0, nMoveFrom = 0, nMoveTo = 0;

    while (!feof(pFile)) {
        fscanf_s(pFile, "move %i from %i to %i\n", &nMoveCount, &nMoveFrom, &nMoveTo);
        Move(ppPiles[nMoveFrom - 1], ppPiles[nMoveTo - 1], nMoveCount);
    }

    // Print top most character in every pile in order.

    for (INT i = 0; i < nPileCount; i++)
        putc(ppPiles[i][lstrlenA(ppPiles[i]) - 1], stdout);
    putc('\n', stdout);

    // Free memory from piles.

    for (INT i = 0; i < nPileCount; i++)
        free(ppPiles[i]);

    free(ppPiles);

    // Close file handle.

    fclose(pFile);

    return 0;
}