#pragma once

class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0);
	~VertexBuffer();
	
	void CreateBuffer(void* data);

	void IASetVertexBuffer(int slot);

private:
	void Update();

	Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _stride = 0;
	UINT _count = 0;
	UINT _offset = 0;
};

