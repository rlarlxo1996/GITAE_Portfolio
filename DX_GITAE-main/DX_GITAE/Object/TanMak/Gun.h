#pragma once
class Gun
{
public:
	Gun();
	~Gun();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	void SetPlayer(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }

private:
	shared_ptr<Quad> _quad;
};

