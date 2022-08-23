#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count, UINT offset)
: _stride(stride)
, _count(count)
, _offset(offset)
, _data(data)
{
    CreateBuffer(data);
}

VertexBuffer::~VertexBuffer()
{
}


void VertexBuffer::CreateBuffer(void* data)
{
    // Vertex Buffer
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;

    DEVICE->CreateBuffer(&bd, &initData, _vertexBuffer.GetAddressOf());
}

void VertexBuffer::IASetVertexBuffer(int slot)
{
    Update();
    DEVICE_CONTEXT->IASetVertexBuffers(slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
}

void VertexBuffer::Update()
{
    DEVICE_CONTEXT->Map(_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);
    memcpy(_subResource.pData, _data, static_cast<size_t>(_count * _stride));
    DEVICE_CONTEXT->Unmap(_vertexBuffer.Get(), 0);
}
