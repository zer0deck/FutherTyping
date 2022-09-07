#pragma once

#include "resource.h"
#include "framework.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string> 
#include <iomanip>
#include <strsafe.h>
#include <ctime>

#define STRICT
#define MAX_LOADSTRING  100
#define BUF_SIZE        255

// HUD 
#define mcBUF_SIZE      50

// �������
#define updateStats     1
#define OnMenuAction1   11
#define OnMenuAction2   3
#define OnMenuAction3   4
#define OnMenuExit      5
#define OnMenuAbout     6
#define OnMenuStatus    7
#define OnMenuStart     8
#define OnMenuPause     9
#define OnMenuStop      10
#define OnMenuLogsPrint 12

// ���������
template <typename T>
std::string intToString(T val)
{
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

// ��������� 
const int                   LOG_SIZE_BUFFER = 260;                               // ������ ������� �����
PCWSTR                      PATH = L"logs.txt";                                  // ���� � ����� �����  
const std::wstring          VERSION = L"0.03.01";                                // ������ ���������

// ���������� ����������:
HINSTANCE       hInst;                                              // ������� ���������
PAINTSTRUCT     ps;
WCHAR           szTitle[MAX_LOADSTRING];                            // ����� ������ ���������
WCHAR           szWindowClass[MAX_LOADSTRING];                      // ��� ������ �������� ����
DWORD           dwThreadId;                                         // id ������
HANDLE          hThread;                                            // ������� ������
DWORD           tExitCode;
LPDWORD         lpExitCode = 0;                                     // �������� ���
BOOLEAN         closingEventforThreads = false;                     // ���������� ���������� ��� ��������� ���� �������
BOOLEAN         isThreadRunningDebug = false;                       // ����� ��� �������� ������ �����  
POINT           lpPoint;                                            // ������� �������
UINT            sOWidth, sOHeight, sCWidth, sCHeight;
HANDLE hFile = CreateFile(
    PATH,
    GENERIC_WRITE | GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    NULL);                                                          // ���� �����
int             startTime = clock();
float           mainCounter = 0,
                wordCounter = 0;
char            mcBuffer[mcBUF_SIZE],
                mwBuffer[mcBUF_SIZE];

int             caseButtonPress;

std::string mcBufferStartInfo = "0S\0", mwBufferStartInfo = "0W\0";

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD   WINAPI      MainThread(LPVOID lpParam);                     // ������� ����� � ���������
HWND                hPlotRT;                                        // ���� � �������� �������� realtime
HWND                hCurrentDay;                                    // ���� � ����������� � ������� ������
HWND                hWnd;                                           // �������� ����
void                logTracker(HANDLE hFile, std::string logText);  // ������� ������ �����
void                mainMenu(HWND hWnd);
void                closingThread(), creationThread();
inline  LPCWSTR     boolToText(BOOLEAN isSmth);                     // ����������� BOOLEAN � LPCWSTR
inline  std::string currentDate();                                  // ���������� ������� ���� � ����� ��� ����� � ������� %Y_%m_%d_%H:%M
inline  std::string kbType(int kbT);                                // ���������� �������� ���� ����������
inline  void        stopLogging(HANDLE hFile);                      // �������� ����� ����� � ���������� �����������