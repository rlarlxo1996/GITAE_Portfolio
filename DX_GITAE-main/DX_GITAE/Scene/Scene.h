#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PreRender() {}
	virtual void PostRender() {}

private:
};

