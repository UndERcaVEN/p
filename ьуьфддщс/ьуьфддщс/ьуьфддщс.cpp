#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include "atlstr.h"

#import "../exLibs/MessageGUI.tlb"

using namespace std;
using namespace MessageGUI;

#define BUF_SIZE 256

#pragma region Конвертация переменных

wchar_t* charToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

_bstr_t charToBStr(char* charArray)
{
    return _bstr_t(charArray);
}

char* LPCTSTRToChar(LPCTSTR str)
{
    CStringA sB(str);
    const char* pszC = sB;
    return const_cast<char*>(pszC);
}

#pragma endregion

#pragma region Разделение памяти

#pragma region Объявление переменных

HANDLE hMapFile;
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");
#pragma endregion

/// <summary>
/// Маппинг памяти
/// </summary>
/// <returns> буфер, с содержимым выделенной области памяти </returns>
LPCTSTR MapMemory()
{
    LPCTSTR pBuf;
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        throw new exception("couldn't create file mapping");
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        throw new exception("couldn't map view of file");
    }

    return pBuf;
}
#pragma endregion

int _tmain()
{
    CoInitialize(NULL);

    BSTR username = NULL;
    BSTR msg;

    IMessageGUIPtr guiObject(__uuidof(Initializer));

    guiObject->Initialize();

   

    auto pBuf = MapMemory();
    auto emptypBuf = LPCTSTRToChar(pBuf);
    
    while (true)
    {
        if (LPCTSTRToChar(pBuf) != emptypBuf)
        {
            guiObject->DisplayMessage(SysAllocString(pBuf));
            CopyMemory((PVOID)pBuf, charToLPCWSTR(emptypBuf), BUF_SIZE);
        }

        guiObject->get_message(&msg);
        if (msg == NULL)
            continue;

        guiObject->ClearMessage();
        CopyMemory((PVOID)pBuf, msg, SysStringByteLen(msg));
    }

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

    return 0;
}