// FurtherTyping.cpp 
//

#include "FurtherTyping.h"
#include "Style.h"

std::wstring    df = L"FurtherTyping " + VERSION + L"\n © Aleksei Grandilevskii aka zer0deck";
LPCWSTR         infoMessage = df.c_str();

inline void rsz(int posObj[5]);
// Главный поток
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    /// TODO: Разместите код здесь.
    setlocale(LC_ALL, "RUS");
    countObjects();


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FURTHERTYPING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FURTHERTYPING));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


// Регистрация класса окна
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FURTHERTYPING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = bgBrush1;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FURTHERTYPING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// создание главного окна
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, 870, 700, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


// обработчик сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
        mainMenu(hWnd);
        strcpy(mcBuffer, mcBufferStartInfo.c_str());
        strcpy(mwBuffer, mwBufferStartInfo.c_str());
        //creationThread();
        break;
        }
	
    // меню
    case WM_COMMAND:
        {
            switch (wParam) {

                case OnMenuAction1:
                    MessageBox(hWnd, TEXT("MENU 1 WAS CLICKED"), TEXT("MENU 1 WAS CLICKED"), MB_OK);
                    break;
                case OnMenuAction2:
                    MessageBox(hWnd, TEXT("MENU 2 WAS CLICKED"), TEXT("MENU 2 WAS CLICKED"), MB_OK);
                    break;
                case OnMenuAction3:
                    MessageBox(hWnd, TEXT("MENU 3 WAS CLICKED"), TEXT("MENU 3 WAS CLICKED"), MB_OK);
                    break;

                case OnMenuStart:
                    if (hThread == NULL) {
                        // Запуск потока
                        creationThread();
                        break;
                    }
                    else
                    {
                        // продолжение потока
                        ResumeThread(hThread);
                        break;
                    }
                case OnMenuPause:
                    // Приостановка потока
                    SuspendThread(hThread);
                    break;
                case OnMenuStop:

                    // Остановка потока
                    closingThread();
                    closingEventforThreads = false;
                    break;

                case OnMenuAbout:
                    MessageBox(hWnd, infoMessage, TEXT("About FurtherTyping"), MB_OK);
                    break;
                case updateStats:
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                    break;

                case OnMenuExit:
                    closingThread();
                    PostQuitMessage(0);
                    break;

                default:
                    break;
               }

            break;
        }
    case WM_LBUTTONDOWN:
        {
            GetCursorPos(&lpPoint);
            ScreenToClient(hWnd, &lpPoint);
        
		
            if (lpPoint.y >= rgnRefreshButtonPos[2] && lpPoint.y <= rgnRefreshButtonPos[3]) {
                if (lpPoint.x >= rgnStartPauseButtonPos[0] && lpPoint.x <= rgnStartPauseButtonPos[1]) {
                    caseButtonPress = OnMenuStart;
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                }
                else if (lpPoint.x >= rgnStopButtonPos[0] && lpPoint.x <= rgnStopButtonPos[1]) {
                    caseButtonPress = OnMenuStop;
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                }
                else if (lpPoint.x >= rgnExportLogsButtonPos[0] && lpPoint.x <= rgnExportLogsButtonPos[1]) {
                    caseButtonPress = OnMenuLogsPrint;
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                } 
                else if (lpPoint.x >= rgnRefreshButtonPos[0] && lpPoint.x <= rgnRefreshButtonPos[1]) {
                    caseButtonPress = updateStats;
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                }
            }
		
		    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
		    break;
        }
    case WM_LBUTTONUP:
        {
            int tCBP = caseButtonPress;
            caseButtonPress = NULL;
            switch (tCBP) {
                case OnMenuStart:
                {
                    if (hThread == NULL) {
                        // Запуск потока
                        creationThread();
                    }
                    else
                    {
                        // Приостановка потока
                        SuspendThread(hThread);
                        //// продолжение потока
                        //ResumeThread(hThread);
                    }
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                    break;
                }
                case OnMenuStop:
                {
                    // Остановка потока
                    closingThread();
                    strcpy(mcBuffer, mcBufferStartInfo.c_str());
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                    closingEventforThreads = false;
                    break;
                }
                case OnMenuLogsPrint:
                {
                    // выгрузка
                    std::string temp = intToString(lpPoint.x) + " | " + intToString(lpPoint.y);
                    strcpy(mcBuffer, temp.c_str());
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                    break;
                }
                case updateStats:
                {
                    // обновление
                    RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                    break;
                }
                default:
                {
                    break;
                }
            }
			
            break;
        }
    
    // отрисовщик
    case WM_PAINT:
        {
            HDC hdc = BeginPaint(hWnd, &ps);
			
			// рисуем блоки с фоном
            FillRgn(hdc, rgnMainCounter, bgBrush2);
            FillRgn(hdc, rgnAllTimeCounter, bgBrush2);
            FillRgn(hdc, rgnPlotRT, bgBrush2);
            FillRgn(hdc, rgnKBInfo, bgBrush2);
            FillRgn(hdc, rgnCurrentDay, bgBrush2);
            FillRgn(hdc, rgnPlotAT, bgBrush2);
            FillRgn(hdc, rgnExportButton, mBrush);
            FillRgn(hdc, rgnStopButton, mBrush);
            FillRgn(hdc, rgnStartPauseButton, mBrush);
            FillRgn(hdc, rgnRefreshButton, mBrush);
			
			// рисуем блоки для текста
            FillRect(hdc, &rMainCounter, bgBrush2);
            FillRect(hdc, &rMainWCounter, bgBrush2);
            FillRect(hdc, &rMainCounterLabel, bgBrush2);
            FillRect(hdc, &rAllTimeCounter, bgBrush2);
            FillRect(hdc, &rAllTimeCounterLabel, bgBrush2);
            FillRect(hdc, &rPlotRTLabel, bgBrush2);
            FillRect(hdc, &rKBInfoLabel, bgBrush2);
            FillRect(hdc, &rCurrentDayLabel, bgBrush2);
            FillRect(hdc, &rPlotATLabel, bgBrush2);

            // рисуем дочерние блоки
            FillRect(hdc, &rMainCounterChildVert, mBrush);
            FillRect(hdc, &rAllTimeCounterChildVert, mBrush);
            
			// нажатие кнопок
            if (caseButtonPress != NULL) {
                switch (caseButtonPress) {
                    case OnMenuStart:
                        FillRgn(hdc, rgnStartPauseButtonPressed, acBrush1);
                        break;
                    case OnMenuStop:
                        FillRgn(hdc, rgnStopButtonPressed, acBrush1);
                        break;
                    case OnMenuLogsPrint:
                        FillRgn(hdc, rgnExportButtonPressed, acBrush1);
                        break;
                    case updateStats:
                        FillRgn(hdc, rgnRefreshButtonPressed, acBrush1);
                        break;
                }
            }
			
			// иконки кнопок
            DrawIconEx(hdc, rgnStartPauseButtonPos[0], rgnStartPauseButtonPos[2], hPlayPauseIcon, rgnStartPauseButtonPos[1] - rgnStartPauseButtonPos[0], rgnStartPauseButtonPos[3] - rgnStartPauseButtonPos[2], 0, NULL, DI_NORMAL);
            DrawIconEx(hdc, rgnRefreshButtonPos[0], rgnRefreshButtonPos[2], hRefreshIcon, rgnRefreshButtonPos[1] - rgnRefreshButtonPos[0], rgnRefreshButtonPos[3] - rgnRefreshButtonPos[2], 0, NULL, DI_NORMAL);
			
			// настройки для основного текста
            SetTextColor(hdc, RGB(Palette[6][0], Palette[6][1], Palette[6][2]));
            SetBkMode(hdc, TRANSPARENT);
			
			// текст
            SelectObject(hdc, hFont);
            DrawTextA(hdc, mcBuffer, -1, &rMainCounter, DT_SINGLELINE | DT_LEFT | DT_TOP | DT_NOCLIP);
            DrawTextA(hdc, mwBuffer, -1, &rMainWCounter, DT_SINGLELINE | DT_LEFT | DT_TOP | DT_NOCLIP);
            DrawTextA(hdc, mcBuffer, -1, &rAllTimeCounter, DT_SINGLELINE | DT_LEFT | DT_TOP | DT_NOCLIP);
			
			// названия блоков
            SetTextColor(hdc, RGB(Palette[7][0], Palette[7][1], Palette[7][2]));
            SelectObject(hdc, hFontLabels);
            DrawTextA(hdc, "Main Counter", -1, &rMainCounterLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
            DrawTextA(hdc, "AT Counter", -1, &rAllTimeCounterLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
            DrawTextA(hdc, "RT Plot", -1, &rPlotRTLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
			DrawTextA(hdc, "Writing Process", -1, &rCurrentDayLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
            DrawTextA(hdc, "Keyboard Detection", -1, &rKBInfoLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
            DrawTextA(hdc, "AT Plot", -1, &rPlotATLabel, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOCLIP);
			
            EndPaint(hWnd, &ps);
            break;
        }
    case WM_SIZE:
        {
            if (sOWidth == NULL && sOHeight == NULL) {
                sOWidth = LOWORD(lParam);
                sOHeight = HIWORD(lParam);
            }
            else {
                sCWidth = LOWORD(lParam);
                sCHeight = HIWORD(lParam);
                rsz(rMainCounterPos);
                rsz(rMainCounterLabelPos);
                rsz(rAllTimeCounterPos);
                rsz(rAllTimeCounterLabelPos);
                rsz(rPlotRTLabelPos);
                rsz(rKBInfoLabelPos);
                rsz(rCurrentDayLabelPos);
                rsz(rPlotATLabelPos);
                rsz(rMainCounterChildVertPos);
                rsz(rAllTimeCounterChildVertPos);
                rsz(rgnMainCounterPos);
                rsz(rgnAllTimeCounterPos);
                rsz(rgnPlotRTPos);
                rsz(rgnKBInfoPos);
                rsz(rgnCurrentDayPos);
                rsz(rgnPlotATPos);
                rsz(rgnExportLogsButtonPos);
                rsz(rgnStopButtonPos);
                rsz(rgnStartPauseButtonPos);
                rsz(rgnRefreshButtonPos);
                rsz(rgnExportLogsButtonPressedPos);
                rsz(rgnStopButtonPressedPos);
                rsz(rgnStartPauseButtonPressedPos);
                rsz(rgnRefreshButtonPressedPos);
				mainFontSize = mainFontSize * (static_cast<double>(sCWidth) / sOWidth);
                addFontSize = addFontSize * (static_cast<double>(sCWidth) / sOWidth);
                countObjects();
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);
                sOWidth = sCWidth;
                sOHeight = sCHeight;
            }
            break;
        }
		
    // завершение
    case WM_DESTROY:
        closingThread();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// главная функция анализа
DWORD WINAPI MainThread(LPVOID lpParam)
{
    // инициализация переменных в потоке
    int firstKeyPressTime;
    bool pressed, spacePressed;
    std::string logText, currentSymSpeed, currentWordSpeed, bufSpeed, bufWSpeed;
    float length;

    // инициализация записи логов
    std::string logHelloText = "\n\n---------------------LOG_" +
        currentDate() +
        "---------------------\n\nPROGRAM STARTED SUCCESSFULLY\nKEYBOARD TYPE : 0x" +
        intToString(GetKeyboardType(0)) + "\t-\t" + kbType(GetKeyboardType(0)) + "\nNUMBER OF KEYS DETECTED:\t" + intToString(GetKeyboardType(2)) + "\n\n";
    
    logTracker(hFile, logHelloText);

    if (kbType(GetKeyboardType(0)) == "ERROR. KEYBOARD WAS NOT DETECTED.") {
        LPCWSTR logError = TEXT("PROGRAM FAILED. \n Exception error: { 0x0000001F_keyboard_not_detected } \n Please, inform author your problems.");
        MessageBox(GetActiveWindow(), logError, logError, MB_ICONERROR);
        stopLogging(hFile);
        return 1;
    }
    
    while (!closingEventforThreads) {
        firstKeyPressTime = 0;
        pressed = false, spacePressed = false;

        for (int i = 0x30; i <= 0x5A; i++)
        {
            do {
                if (GetAsyncKeyState(i)) {
                    if (!pressed) {
                        mainCounter++;
                        pressed = true;
                        if (firstKeyPressTime == 0) {
                            firstKeyPressTime = clock();
                        };
                    }
                }
                else {
                    if (pressed) {
                        startTime = clock();
                        pressed = false;
                    }
                };

            } while (pressed == true);

        };

        do {
            if ((GetAsyncKeyState(VK_SPACE) or GetAsyncKeyState(VK_RETURN)) && mainCounter != 0) {
                if (!spacePressed) {
                    wordCounter++;
                    spacePressed = true;
                };
            }
            else {
                if (spacePressed) {
                    spacePressed = false;
                }
            };

        } while (spacePressed == true);

        length = (startTime - firstKeyPressTime) / 1000;
        // обновление текущих результатов
        if (mainCounter != 0 and length != 0) {
            currentSymSpeed = intToString(float(mainCounter / length));
            currentWordSpeed = intToString(float((wordCounter * 60) / length));

            bufSpeed = currentSymSpeed + "S\0";
            bufWSpeed = currentWordSpeed + "W\0";
            strcpy(mcBuffer, bufSpeed.c_str());
            strcpy(mwBuffer, bufWSpeed.c_str());
        };
        if ((clock() - startTime) / CLK_TCK >= 10 && mainCounter != 0) {
         
            logText = "LOG_" + currentDate() + "\nANALYSIS LENGTH:\t" + intToString(length * 1000) + " ms ( " + intToString(length) + " s )\nENTERED KEYS REGISTERED:\t" +
                intToString(mainCounter) + "\nENTERED WORDS REGISTERED:\t" + intToString(wordCounter + 1) + "\nCURRENT PERIOD TYPING SPEED:\t" +
                currentSymSpeed + " symbols/s\t" + currentWordSpeed + " words/min\n";
            logTracker(hFile, logText);
            mainCounter = 0;
            wordCounter = 0;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
        };
    };


    stopLogging(hFile);
    return 0;
}

// функциональные штуки
void mainMenu(HWND hWnd) {
    HMENU rootMenu = CreateMenu();
    HMENU fileMenuSub = CreateMenu();
    HMENU processMenuSub = CreateMenu();
    

    AppendMenu(fileMenuSub, MF_STRING, OnMenuAction1, TEXT("Menu1"));
    AppendMenu(fileMenuSub, MF_STRING, OnMenuAction2, TEXT("Menu2"));
    AppendMenu(fileMenuSub, MF_STRING, OnMenuAction3, TEXT("Menu3"));
    AppendMenu(fileMenuSub, MF_SEPARATOR, NULL, NULL);
    AppendMenu(fileMenuSub, MF_STRING, OnMenuExit, TEXT("Save and exit"));
    AppendMenu(rootMenu, MF_POPUP, (UINT_PTR)fileMenuSub, TEXT("File"));

    AppendMenu(processMenuSub, MF_STRING, OnMenuStatus, TEXT("Status"));
    AppendMenu(processMenuSub, MF_STRING, OnMenuStart, TEXT("⏯ Start"));
    AppendMenu(processMenuSub, MF_STRING, OnMenuPause, TEXT("⏸ Pause"));
    AppendMenu(processMenuSub, MF_STRING, OnMenuStop, TEXT("⏹ Stop"));
    AppendMenu(rootMenu, MF_POPUP, (UINT_PTR)processMenuSub, TEXT("Process"));

    AppendMenu(rootMenu, MF_STRING, OnMenuAbout, TEXT("About"));
    AppendMenu(rootMenu, MF_STRING, OnMenuExit, TEXT("Save and exit"));

    SetMenu(hWnd, rootMenu);
    //SetMenu(hWnd, processMenu);
    //SetMenu(hWnd, aboutMenu);
}

void logTracker(HANDLE hFile, std::string logText) {
    if (hFile != INVALID_HANDLE_VALUE)
    {
        SetFilePointer(hFile, 0, NULL, FILE_END);
        DWORD bytesWritten;

        WriteFile(
            hFile,            // Handle to the file
            logText.c_str(),  // Buffer to write
            logText.length(),   // Buffer size
            &bytesWritten,    // Bytes written
            NULL);         // Overlapped
    }
    else
    {
        // Ошибка ведения файла логов
        LPCWSTR logError = TEXT("PROGRAM FAILED. \n Exception error: { 10016_logging_file_creation_error_exception } \n Please, inform author your problems.");
        MessageBox(GetActiveWindow(), logError, TEXT("PROGRAM FAILED"), MB_ICONERROR);
        stopLogging(hFile);
    };
}

void closingThread() {
    closingEventforThreads = true;
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    hThread = NULL;
}

void creationThread() {
    hThread = CreateThread(NULL, 0, MainThread, NULL, THREAD_SUSPEND_RESUME, &dwThreadId);

    if (hThread == NULL)
    {
        LPCWSTR threadError = TEXT("PROGRAM FAILED. \n Exception error: { 0x0000005_thread_creation_error } \n Please, inform author your problems.");
        MessageBox(GetActiveWindow(), threadError, TEXT("PROGRAM FAILED"), MB_ICONERROR);
        ExitProcess(3);
    }
    else {
        isThreadRunningDebug = true;
    }
}


// inline функции
inline LPCWSTR boolToText(BOOLEAN isSmth) {
    if (isSmth == TRUE) {
        return LPCWSTR(L"TRUE");
    }
    else {
        return LPCWSTR(L"FALSE");
    }
}

inline std::string currentDate() {
    time_t curtime;
    struct tm* loctime;

    char buffer[18];

    time(&curtime);
    loctime = localtime(&curtime);

    strftime(buffer, 18, "%Y_%m_%d_%H:%M", loctime);

    std::string cDate = buffer;
    return cDate;

}

inline std::string kbType(int kbT) {
    std::string kbRes;
    switch (kbT) {
    case 0x4:
        kbRes = "Enhanced 101 - or 102 - key keyboards(and compatibles)";
        break;
    case 0x7:
        kbRes = "Japanese Keyboard";
        break;
    case 0x8:
        kbRes = "Korean Keyboard";
        break;
    case 0x51:
        kbRes = "Unknown type or HID keyboard";
        break;
    default:
        kbRes = "ERROR. KEYBOARD WAS NOT DETECTED.";
        break;
    };
    return kbRes;
}

inline void stopLogging(HANDLE hFile) {
    SetFilePointer(hFile, 0, NULL, FILE_END);
    DWORD bytesWritten;

    std::string logText = "\n\n---------------------LOG_FINISHED---------------------";
    WriteFile(
        hFile,            // Handle to the file
        logText.c_str(),  // Buffer to write
        logText.length(),   // Buffer size
        &bytesWritten,    // Bytes written
        NULL);         // Overlapped
    CloseHandle(hFile);
}

inline void rsz(int posObj[]) {
        double tempDynW = static_cast<double>(sCWidth) / sOWidth;
		double tempDynH = static_cast<double>(sCHeight) / sOHeight;
        posObj[0] = posObj[0] * tempDynW;
        posObj[1] = posObj[1] * tempDynW;
        posObj[2] = posObj[2] * tempDynH;
        posObj[3] = posObj[3] * tempDynH;
}