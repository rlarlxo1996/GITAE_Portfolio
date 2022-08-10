Texture2D map : register(t0);
SamplerState samp : register(s0);

// SV -> System Value
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float2 maxFrame : MAX_FRAME;
	float2 curFrame : CUR_FRAME;
};

// �ĸ���ۿ� �׸� ����
// 1�����Ӵ� ȣ�� Ƚ�� : 1280 x 720 ��ŭ ȣ��
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	spriteUV.x = input.uv.x / input.maxFrame.x + input.curFrame.x / input.maxFrame.x;
	spriteUV.y = input.uv.y / input.maxFrame.y + input.curFrame.y / input.maxFrame.y;

	return map.Sample(samp, spriteUV);
}