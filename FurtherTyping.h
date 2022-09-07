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

// Команды
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

// Прототипы
template <typename T>
std::string intToString(T val)
{
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

// Константы 
const int                   LOG_SIZE_BUFFER = 260;                               // размер буффера логов
PCWSTR                      PATH = L"logs.txt";                                  // путь к файлу логов  
const std::wstring          VERSION = L"0.03.01";                                // версия программы

// Глобальные переменные:
HINSTANCE       hInst;                                              // текущий экземпляр
PAINTSTRUCT     ps;
WCHAR           szTitle[MAX_LOADSTRING];                            // Текст строки заголовка
WCHAR           szWindowClass[MAX_LOADSTRING];                      // имя класса главного окна
DWORD           dwThreadId;                                         // id потока
HANDLE          hThread;                                            // хэндлер потока
DWORD           tExitCode;
LPDWORD         lpExitCode = 0;                                     // выходной код
BOOLEAN         closingEventforThreads = false;                     // глобальная переменная для остановки всех потоков
BOOLEAN         isThreadRunningDebug = false;                       // дебаг для проверки работы треда  
POINT           lpPoint;                                            // позиция курсора
UINT            sOWidth, sOHeight, sCWidth, sCHeight;
HANDLE hFile = CreateFile(
    PATH,
    GENERIC_WRITE | GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    NULL);                                                          // файл логов
int             startTime = clock();
float           mainCounter = 0,
                wordCounter = 0;
char            mcBuffer[mcBUF_SIZE],
                mwBuffer[mcBUF_SIZE];

int             caseButtonPress;

std::string mcBufferStartInfo = "0S\0", mwBufferStartInfo = "0W\0";

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
DWORD   WINAPI      MainThread(LPVOID lpParam);                     // главный поток с листнером
HWND                hPlotRT;                                        // окно с графиком скорости realtime
HWND                hCurrentDay;                                    // окно с информацией о текущем сеансе
HWND                hWnd;                                           // основное окно
void                logTracker(HANDLE hFile, std::string logText);  // функция записи логов
void                mainMenu(HWND hWnd);
void                closingThread(), creationThread();
inline  LPCWSTR     boolToText(BOOLEAN isSmth);                     // преобразует BOOLEAN в LPCWSTR
inline  std::string currentDate();                                  // возвращает текущую дату и время для логов в формате %Y_%m_%d_%H:%M
inline  std::string kbType(int kbT);                                // возвращает описание типа клавиатуры
inline  void        stopLogging(HANDLE hFile);                      // закрытие файла логов и завершение логирования