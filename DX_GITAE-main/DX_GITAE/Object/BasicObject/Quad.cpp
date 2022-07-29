#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(wstring file, wstring vs, wstring ps)
{
    // Texture Setting
    _texture= Texture::Add(file);
    _size = _texture->GetSize();

    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(VertexUV), _vertices.size());
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());

    _vertexShader = ADD_VS(vs);
    _pixelShader = ADD_PS(ps);

    _transform = make_shared<Transform>();

}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->UpdateWorld();
}

void Quad::Render()
{
    _transform->SetBuffer(0);

    _texture->Set(0);

    _vertexBuffer->IASetVertexBuffer(0);
    _indexBuffer->IASetIndexBuffer();

    IASetPT();

    _vertexShader->Set();
    _pixelShader->Set();

    DEVICE_CONTEXT->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::CreateVertices()
{
    Vector2 halfSize = _size * 0.5f;

    _vertices.reserve(4);

    // ���� ��
    _vertices.emplace_back(-halfSize.x, halfSize.y, 0, 0);
    // ������ ��
    _vertices.emplace_back(halfSize.x, halfSize.y, 1, 0);
    // ������ �Ʒ�
    _vertices.emplace_back(halfSize.x, -halfSize.y, 1, 1);
    // ���� �Ʒ�
    _vertices.emplace_back(-halfSize.x, -halfSize.y, 0, 1);

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);
}
