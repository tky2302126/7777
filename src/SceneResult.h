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

