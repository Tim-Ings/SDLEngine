#pragma once
class BaseScene
{
public:
	~BaseScene() { OnFinal(); }
	virtual void OnInit() { }
	virtual void OnFinal() { }
	virtual void OnDraw() { }
	virtual void OnUpdate(const float& deltaTime) { }
};

