cbuffer Frame :register(b0)
{
	float2 maxFrame;
	float2 curFrame;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

// SV -> System Value
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// �ĸ���ۿ� �׸� ����
// 1�����Ӵ� ȣ�� Ƚ�� : 1280 x 720 ��ŭ ȣ��
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	spriteUV.x = input.uv.x / maxFrame.x + curFrame.x / maxFrame.x;
	spriteUV.y = input.uv.y / maxFrame.y + curFrame.y / maxFrame.y;

	return map.Sample(samp, spriteUV);
}