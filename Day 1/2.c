#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

BOOL WINAPI IsCRLF(LPSTR lpString) {
  if (lpString[0] == '\r' && lpString[1] == '\n') return TRUE;
  else return FALSE;
}

int qsort_callback(const void* pElem1, const void* pElem2) {
  const int x = *(const int*)pElem1;
  const int y = *(const int*)pElem2;

  return (x > y) - (x < y);
}

int main() {
  HANDLE hFile = CreateFile(
    TEXT("input.txt"),
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
  INT sznMaxTotal[3] = { 0, 0, 0 };
  INT nTotal = 0;
  INT nCurrent = 0;

  for (int i = 0; i < dwFileSize; i++) {
    if (IsCRLF(&lpFileContents[i])) {
      if (i + 4 < dwFileSize && IsCRLF(&lpFileContents[i + 2])) {
        if (nTotal > sznMaxTotal[0]) {
          sznMaxTotal[0] = nTotal;
          qsort(sznMaxTotal, sizeof(sznMaxTotal) / sizeof(sznMaxTotal[0]), sizeof(sznMaxTotal[0]), qsort_callback);
        }

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

  printf(
    "Max numbers: %i + %i + %i = %i\n",
    sznMaxTotal[0],
    sznMaxTotal[1],
    sznMaxTotal[2],
    sznMaxTotal[0] + sznMaxTotal[1] + sznMaxTotal[2]
  );
}