#include <DxLib.h>
#include <map>
#include <vector>
#include <random>
#include <stack>
#include <memory>

#include "Define.h"
#include "AbstractMethod.h"
#include "AreaDivisionMethod.h"

using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetAlwaysRunFlag(TRUE);						// Execute even if window is inactive
	ChangeWindowMode(TRUE);						// Set to WindowMode
	SetWindowSizeChangeEnableFlag(TRUE);		// Allow the window size to be freely resizable
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(Define::WIN_W, Define::WIN_H, 32);
	DxLib_Init();								// DX library initialization process

	SetDrawScreen(DX_SCREEN_BACK); // Set the drawing destination to the back screen


	std::stack<std::shared_ptr<AbstractMethod>> method;

	/*
	* Push the method to be executed onto the stack
	*/
	method.push(make_shared<AreaDivisionMethod>());



	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		if (!method.size()) break;

		method.top()->draw();

		WaitKey();

		method.pop();
		method.push(make_shared<AreaDivisionMethod>());
	}

	DxLib_End(); // DX library exit process
	return 0;
}