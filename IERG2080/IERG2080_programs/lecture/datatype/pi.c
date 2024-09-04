#include <stdio.h>
#include <stdlib.h> // mblen
#include <locale.h> // setlocale _wsetlocale
#include <wchar.h>  // mbrlen wprintf

int main()
{
    // code page: set locale
    setlocale(LC_ALL, "en_US.utf8");

    // multibyte
    // define and assign
    char *mbstr = "π", *mbutf = "\u03C0";

    // property: count lenth
    mblen(NULL, 0);
    printf("length of π: %d\n", mblen(mbstr, 10));

    mblen(NULL, 0);
    printf("length of \ucf80: %d\n", mblen(mbutf, 10));
    

    mbstate_t mbs;
    mbrlen(NULL, 0, &mbs);
    printf("length of π in mbrlen: %zu\n", mbrlen(mbstr, 10, &mbs));

    // wide char
    wchar_t wch = L'π';
    wchar_t *wstr = L"明天好龟";

    wprintf(L"wide char string 明天好龟 is %ls\n", wstr);
    printf("wide char string is %ls\n", wstr);



    return 0;
}