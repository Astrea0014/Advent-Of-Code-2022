#include <stdio.h>
#include <stdlib.h>

#undef UNICODE
#include <Windows.h>

int qsort_s_callback(const void* pElem1, const void* pElem2, void* pContext) {
  if (*(const int*)pElem1 < *(const int*)pElem2)
    return -1;
  else if (*(const int*)pElem1 > *(const int*)pElem2)
    return 1;
  else return 0;
}

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
  INT sznMaxTotal[3] = { 0, 0, 0 };
  INT nTotal = 0;
  INT nCurrent = 0;

  for (int i = 0; i < dwFileSize; i++) {
    if (lpFileContents[i] == '\n') {
      if (i + 1 != dwFileSize && lpFileContents[i + 1] == '\n') {

        if (nTotal > sznMaxTotal[0]) {
          sznMaxTotal[0] = nTotal;
          qsort_s(sznMaxTotal, 3, sizeof(int), qsort_s_callback, NULL);
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