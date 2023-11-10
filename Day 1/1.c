#include <stdio.h>
#include <stdlib.h>

#undef UNICODE
#include <Windows.h>

int main() {
  HANDLE hFile = CreateFile(
    "input.txt",
    FILE_GENERIC_READ,
    0,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL
  );

  LARGE_INTEGER li;
  GetFileSizeEx(hFile, &li);

  LPSTR lpFileContents = (LPSTR)malloc(li.QuadPart);

  DWORD dwFileSize = 0;

  ReadFile(
    hFile,
    lpFileContents,
    li.QuadPart,
    &dwFileSize,
    NULL
  );

  BOOL bNumberRead = FALSE;
  INT nMaxTotal = 0;
  INT nTotal = 0;
  INT nCurrent = 0;

  for (int i = 0; i < dwFileSize; i++) {
    if (lpFileContents[i] == '\n') {
      if (i + 1 != dwFileSize && lpFileContents[i + 1] == '\n') {
        if (nTotal > nMaxTotal)
          nMaxTotal = nTotal;
        nTotal = 0;
      }
      else
        bNumberRead = FALSE;
      continue;
    }

    if (!bNumberRead) {
      sscanf_s(&lpFileContents[i], "%i", &nCurrent);
      nTotal += nCurrent;
      bNumberRead = TRUE;
    }
  }

  free(lpFileContents);

  printf("Max: %i\n", nMaxTotal);
}