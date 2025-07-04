// @author : h_suzuki
// @date : 2025-07-03
// @history : 2025-07-03 update : SceneResultの仮実装

#pragma once
#include "SceneBase.h"
#include "MovieManager.h"
#include "UIManager.h"

class SceneResult : public SceneBase
{
public:
	SceneResult();
	~SceneResult();

	void LoadComplete() override;

	void AsyncAwake() override;

	void KeyInputCallback(InputAction::CallBackContext _c) override;

	void Update() override;

	void LateUpdate() override;

private:


};

