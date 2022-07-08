#pragma warning(disable: 4996)

#include <DxLib.h>
#include "Define.h"
#include "Looper.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(TRUE);	// Execution even when the window is inactive
	ChangeWindowMode(TRUE);	// Set to window mode
	SetWindowSizeChangeEnableFlag(TRUE); // Allow window size to be freely resizable
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(700, 600, 32);
	DxLib_Init(); // DX library initialization process
	
	SetDrawScreen(DX_SCREEN_BACK); //Set the drawing destination to the back screen

	Looper* loop = new Looper();

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!loop->loop()) {
			break;
		}
	}
	
	DxLib_End(); // DX library Exit process
	return 0;
}