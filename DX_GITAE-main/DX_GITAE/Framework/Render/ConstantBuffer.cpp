#include "framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
: _data(data)
, _dataSize(dataSize)
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    // D3D11_USAGE_DEFALUT // GPU������ �а� ���� ����
    // D3D11_USAGE_IMMUTABLE // GPU������ �б⸸ ����
    // D3D11_USAGE_DYNAMIC // CPU���� ���� ����, GPU���� �б�
    // D3D11_USAGE_STAGING // GPU���� CPU�� �̵�(�б⸸ ����)
    bd.ByteWidth = dataSize;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

    DEVICE->CreateBuffer(&bd, nullptr, _buffer.GetAddressOf());
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Update()
{
    DEVICE_CONTEXT->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);
    memcpy(_subResource.pData, _data, _dataSize);
    DEVICE_CONTEXT->Unmap(_buffer.Get(), 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
    DEVICE_CONTEXT->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
    Update();
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    DEVICE_CONTEXT->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
    Update();
}
