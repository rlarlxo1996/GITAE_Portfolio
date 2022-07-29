#pragma once
class CircleCollider;

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 _position;
		Vector2 _direction[2]; // ���� ����
		float _length[2]; // ���� ����
	};

	RectCollider(const Vector2& halfSize);
	virtual ~RectCollider();

	void CreateVertices();

	virtual void Update() override;
	virtual void Render() override;

	float Top() { return GetWorldPos().y + (_halfSize.y * _transform->GetWorldScale().y); }
	float Bottom() { return GetWorldPos().y - (_halfSize.y * _transform->GetWorldScale().y); }
	float Right() { return GetWorldPos().x + (_halfSize.x * _transform->GetWorldScale().x); }
	float Left() { return GetWorldPos().x - (_halfSize.x * _transform->GetWorldScale().x); }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr< RectCollider> rect, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other, bool isObb = false) override;

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

	bool IsOBB(shared_ptr<RectCollider> rect);
	bool IsAABB(shared_ptr<RectCollider> rect);

	bool IsOBB(shared_ptr<class CircleCollider> circle);
	bool IsAABB(shared_ptr<class CircleCollider> circle);

	ObbDesc GetOBB();

private:
	Vector2 _halfSize = { 0,0 };
};

