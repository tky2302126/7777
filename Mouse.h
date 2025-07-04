#pragma once
//! 循環参照注意
#include "InputSystem.h"

/**
* @struct Vector2Int
* @brief 2次元座標を管理する構造体
*/
struct Vector2Int
{
	int x;
	int y;

	bool operator== (const Vector2Int& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Vector2Int& other) const { return !(*this == other); }
};

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

