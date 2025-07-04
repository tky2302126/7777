#include "Mouse.h"

Mouse::Mouse()
{
	mouseEnable = false;
}

Mouse::~Mouse()
{
}

void Mouse::MouseInfoUpdate()
{
	if(!mouseEnable)
	{
		mouseInfo.position = { -1, -1 };
		mouseInfo.leftButton = InputState::Waiting;
		mouseInfo.rightButton = InputState::Waiting;
		return;
	}

	GetMousePoint(&mouseInfo.position.x, &mouseInfo.position.y);

#pragma region 左クリック
	auto&  LeftButton = mouseInfo.leftButton;
	if((LeftButton == InputState::Waiting || LeftButton == InputState::Canceled) && IsMouseLeftButtonPressed())
	{
		LeftButton = InputState::Started;
	}
	else if(LeftButton == InputState::Started && IsMouseLeftButtonPressed())
	{
		LeftButton = InputState::Performed;
	}
	else if((LeftButton == InputState::Performed || LeftButton == InputState::Started) && !IsMouseLeftButtonPressed())
	{
		LeftButton = InputState::Canceled;
	}
	else if(LeftButton == InputState::Canceled && ! IsMouseLeftButtonPressed())
	{
		LeftButton = InputState::Waiting;
	}
#pragma endregion

#pragma region 右クリック
	auto& RightButton = mouseInfo.rightButton;
	if ((RightButton == InputState::Waiting || RightButton == InputState::Canceled) && IsMouseRightButtonPressed())
	{
		RightButton = InputState::Started;
	}
	else if (RightButton == InputState::Started && IsMouseRightButtonPressed())
	{
		RightButton = InputState::Performed;
	}
	else if ((RightButton == InputState::Performed || RightButton == InputState::Started) && !IsMouseRightButtonPressed())
	{
		RightButton = InputState::Canceled;
	}
	else if (RightButton == InputState::Canceled && !IsMouseRightButtonPressed())
	{
		RightButton = InputState::Waiting;
	}
#pragma endregion

}
