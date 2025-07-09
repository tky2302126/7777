#pragma once
//! 循環参照注意
#include "InputSystem.h"
#include "define.h"


/**
* @struct MouseInfo
* @brief マウス情報
*/
struct MouseInfo
{
	Vector2Int position;
	InputState leftButton;  // 左クリック
	InputState rightButton; // 右クリック
};

//
class Mouse
{
public:
	Mouse();
	~Mouse();

	void MouseInfoUpdate();

	MouseInfo GetMouseInfo() const { return mouseInfo; }

	// クリックしたかどうかを返すヘルパー関数
	bool IsMouseLeftButtonClicked() { return mouseInfo.leftButton == InputState::Started; }
	bool IsMouseRightButtonClicked() { return mouseInfo.rightButton == InputState::Started; }

	// マウスの座標をスクリーン座標からワールド座標に変換するヘルパー関数
	VECTOR GetMouseWorldPos() { return ConvScreenPosToWorldPos(VGet(mouseInfo.position.x, mouseInfo.position.y, 0.5f)); }

private:
	
	// @brief	    マウスの入力情報
	// @History		25/07/04 作成(h_Suzuki)
	MouseInfo mouseInfo;

	bool mouseEnable;

	bool IsMouseLeftButtonPressed() { return GetMouseInput() && MOUSE_INPUT_LEFT; }
	bool IsMouseRightButtonPressed() { return GetMouseInput() && MOUSE_INPUT_RIGHT; }

#pragma region マウス関係
public:
	void MouseEnable() { mouseEnable = true; }

	void MouseDisable() { mouseEnable = false; }
};

