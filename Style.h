#pragma once

#include <windows.h>
// Создается палет цветов 
// 0 - основной фон
// 1 - дополнительный фон
// 2 - акцент фона
// 3 - основной цвет
// 4 - первый акцент (близкий к основному цвету)
// 5 - второй акцент (противоположный основному цвету)
// 6 - цвет основного текста
// 7 - цвет дополнительного текста
//
const int	Palette[8][3] = { {34, 31, 46}, 
							{46, 43, 63}, 
							{77, 74, 92}, 
							{113, 32, 234}, 
							{62, 192, 234}, 
							{239, 152, 208}, 
							{255, 255, 255}, 
							{112, 110, 124} };

HBRUSH		bgBrush1 = CreateSolidBrush(RGB(Palette[0][0], Palette[0][1], Palette[0][2])),
			bgBrush2 = CreateSolidBrush(RGB(Palette[1][0], Palette[1][1], Palette[1][2])),
			bgBrush3 = CreateSolidBrush(RGB(Palette[2][0], Palette[2][1], Palette[2][2])),
			mBrush = CreateSolidBrush(RGB(Palette[3][0], Palette[3][1], Palette[3][2])),
			acBrush1 = CreateSolidBrush(RGB(Palette[4][0], Palette[4][1], Palette[4][2])),
			acBrush2 = CreateSolidBrush(RGB(Palette[5][0], Palette[5][1], Palette[5][2])),
			tBrush1 = CreateSolidBrush(RGB(Palette[6][0], Palette[6][1], Palette[6][2])),
			tBrush2 = CreateSolidBrush(RGB(Palette[7][0], Palette[7][1], Palette[7][2]));

// основные блоки
int			rgnMainCounterPos[5] = { 310, 555, 270, 365 },
			rgnAllTimeCounterPos[5] = { 570, 820, 270, 365 },
			rgnPlotRTPos[5] = { 40, 290, 90, 250 },
			rgnKBInfoPos[5] = { 310, 820, 90, 250 },
			rgnCurrentDayPos[5] = { 40, 290, 270, 610 },
			rgnPlotATPos[5] = { 310, 820, 380, 610 },
			rgnExportLogsButtonPos[5] = { 750, 820, 35, 60 },
			rgnStopButtonPos[5] = { 660, 730, 35, 60 },
			rgnStartPauseButtonPos[5] = { 570, 640, 35, 60},
			rgnRefreshButtonPos[5] = { 480, 550, 35, 60 },
			rgnExportLogsButtonPressedPos[5] = { 752, 818, 37, 58 },
			rgnStopButtonPressedPos[5] = { 662, 728, 37, 58 },
			rgnStartPauseButtonPressedPos[5] = { 572, 638, 37, 58 },
			rgnRefreshButtonPressedPos[5] = { 482, 548, 37, 58 };

const int	roundingValue = 5;

int			mainFontSize = 30,
			addFontSize = 17;

HRGN		rgnAllTimeCounter,
			rgnMainCounter,
			rgnPlotRT,
			rgnKBInfo,
			rgnCurrentDay,
			rgnPlotAT,
			rgnExportButton,
			rgnStopButton,
			rgnStartPauseButton,
			rgnRefreshButton,
			rgnExportButtonPressed,
			rgnStopButtonPressed,
			rgnStartPauseButtonPressed,
			rgnRefreshButtonPressed;
	
HFONT		hFont,
			hFontLabels;


// набор дочерних элементов

int			rMainCounterPos[5] = { 345, 415, 315, 335 },
			rMainWCounterPos[5] = { 415, 485, 315, 335 },
			rMainCounterLabelPos[5] = { 330, 480, 290, 300 },
			rAllTimeCounterPos[5] = { 615, 745, 315, 335 },
			rAllTimeCounterLabelPos[5] = { 595, 745, 290, 300 },
			rPlotRTLabelPos[5] = {60, 210, 110, 120 },
			rKBInfoLabelPos[5] = { 345, 485, 110, 120 },
			rCurrentDayLabelPos[5] = { 60, 210, 290, 300 },
	//!@!!
			rPlotPos[5] = { 40, 290, 90, 250 },
	//!@!!
			rPlotATLabelPos[5] = { 330, 480, 400, 410 };


RECT		rMainCounter = { 0, 0, 0, 0 },
			rMainWCounter = { 0, 0, 0, 0 },
			rMainCounterLabel = { 0, 0, 0, 0 },
			rAllTimeCounter = { 0, 0, 0, 0 },
			rAllTimeCounterLabel = { 0, 0, 0, 0 },
			rPlotRTLabel = { 0, 0, 0, 0 },
			rKBInfoLabel = { 0, 0, 0, 0 },
			rCurrentDayLabel = { 0, 0, 0, 0 },
			rPlotATLabel = { 0, 0, 0, 0 },
			rPlot = { rPlotPos[0], rPlotPos[2], rPlotPos[1], rPlotPos[3] };


// графические элементы
int			rMainCounterChildVertPos[5] = { 330, 332, 315, 348 },
			rAllTimeCounterChildVertPos[5] = { 595, 597, 315, 348 };

RECT		rMainCounterChildVert = { 0, 0, 0, 0 },
			rAllTimeCounterChildVert = { 0, 0, 0, 0 };


// иконки
HICON		hPlayPauseIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 0, 0, LR_LOADTRANSPARENT),
			hRefreshIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 0, 0, LR_LOADTRANSPARENT);
			/*hStopIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 0, 0, LR_LOADTRANSPARENT);*/

void		countObjects() {
		rgnAllTimeCounter = CreateRoundRectRgn(rgnAllTimeCounterPos[0], rgnAllTimeCounterPos[2], rgnAllTimeCounterPos[1], rgnAllTimeCounterPos[3], roundingValue, roundingValue);
		rgnMainCounter = CreateRoundRectRgn(rgnMainCounterPos[0], rgnMainCounterPos[2], rgnMainCounterPos[1], rgnMainCounterPos[3], roundingValue, roundingValue);
		rgnPlotRT = CreateRoundRectRgn(rgnPlotRTPos[0], rgnPlotRTPos[2], rgnPlotRTPos[1], rgnPlotRTPos[3], roundingValue, roundingValue);
		rgnKBInfo = CreateRoundRectRgn(rgnKBInfoPos[0], rgnKBInfoPos[2], rgnKBInfoPos[1], rgnKBInfoPos[3], roundingValue, roundingValue);
		rgnCurrentDay = CreateRoundRectRgn(rgnCurrentDayPos[0], rgnCurrentDayPos[2], rgnCurrentDayPos[1], rgnCurrentDayPos[3], roundingValue, roundingValue);
		rgnPlotAT = CreateRoundRectRgn(rgnPlotATPos[0], rgnPlotATPos[2], rgnPlotATPos[1], rgnPlotATPos[3], roundingValue, roundingValue);
		rgnExportButton = CreateRoundRectRgn(rgnExportLogsButtonPos[0], rgnExportLogsButtonPos[2], rgnExportLogsButtonPos[1], rgnExportLogsButtonPos[3], roundingValue, roundingValue);
		rgnStopButton = CreateRoundRectRgn(rgnStopButtonPos[0], rgnStopButtonPos[2], rgnStopButtonPos[1], rgnStopButtonPos[3], roundingValue, roundingValue);
		rgnStartPauseButton = CreateRoundRectRgn(rgnStartPauseButtonPos[0], rgnStartPauseButtonPos[2], rgnStartPauseButtonPos[1], rgnStartPauseButtonPos[3], roundingValue, roundingValue);
		rgnRefreshButton = CreateRoundRectRgn(rgnRefreshButtonPos[0], rgnRefreshButtonPos[2], rgnRefreshButtonPos[1], rgnRefreshButtonPos[3], roundingValue, roundingValue);
		rgnExportButtonPressed = CreateRoundRectRgn(rgnExportLogsButtonPressedPos[0], rgnExportLogsButtonPressedPos[2], rgnExportLogsButtonPressedPos[1], rgnExportLogsButtonPressedPos[3], roundingValue, roundingValue);
		rgnStopButtonPressed = CreateRoundRectRgn(rgnStopButtonPressedPos[0], rgnStopButtonPressedPos[2], rgnStopButtonPressedPos[1], rgnStopButtonPressedPos[3], roundingValue, roundingValue);
		rgnStartPauseButtonPressed = CreateRoundRectRgn(rgnStartPauseButtonPressedPos[0], rgnStartPauseButtonPressedPos[2], rgnStartPauseButtonPressedPos[1], rgnStartPauseButtonPressedPos[3], roundingValue, roundingValue);
		rgnRefreshButtonPressed = CreateRoundRectRgn(rgnRefreshButtonPressedPos[0], rgnRefreshButtonPressedPos[2], rgnRefreshButtonPressedPos[1], rgnRefreshButtonPressedPos[3], roundingValue, roundingValue);
		rMainCounter = { rMainCounterPos[0], rMainCounterPos[2], rMainCounterPos[1], rMainCounterPos[3] };
		rMainWCounter = { rMainWCounterPos[0], rMainWCounterPos[2], rMainWCounterPos[1], rMainWCounterPos[3] };
		rMainCounterLabel = { rMainCounterLabelPos[0], rMainCounterLabelPos[2], rMainCounterLabelPos[1], rMainCounterLabelPos[3] };
		rAllTimeCounter = { rAllTimeCounterPos[0], rAllTimeCounterPos[2], rAllTimeCounterPos[1], rAllTimeCounterPos[3] };
		rAllTimeCounterLabel = { rAllTimeCounterLabelPos[0], rAllTimeCounterLabelPos[2], rAllTimeCounterLabelPos[1], rAllTimeCounterLabelPos[3] };
		rPlotRTLabel = { rPlotRTLabelPos[0], rPlotRTLabelPos[2], rPlotRTLabelPos[1], rPlotRTLabelPos[3] };
		rKBInfoLabel = { rKBInfoLabelPos[0], rKBInfoLabelPos[2], rKBInfoLabelPos[1], rKBInfoLabelPos[3] };
		rCurrentDayLabel = { rCurrentDayLabelPos[0], rCurrentDayLabelPos[2], rCurrentDayLabelPos[1], rCurrentDayLabelPos[3] };
		rPlotATLabel = { rPlotATLabelPos[0], rPlotATLabelPos[2], rPlotATLabelPos[1], rPlotATLabelPos[3] };
		rMainCounterChildVert = { rMainCounterChildVertPos[0], rMainCounterChildVertPos[2], rMainCounterChildVertPos[1], rMainCounterChildVertPos[3] };
		rAllTimeCounterChildVert = { rAllTimeCounterChildVertPos[0], rAllTimeCounterChildVertPos[2], rAllTimeCounterChildVertPos[1], rAllTimeCounterChildVertPos[3] };
		hFont = CreateFontA(mainFontSize, 0, 0, 0, FW_BOLD,
			FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Abel"),
		hFontLabels = CreateFontA(addFontSize, 0, 0, 0, FW_BOLD,
				FALSE, FALSE, FALSE, DEFAULT_CHARSET,
				OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				FIXED_PITCH | FF_DONTCARE, "Ebrima");
}
