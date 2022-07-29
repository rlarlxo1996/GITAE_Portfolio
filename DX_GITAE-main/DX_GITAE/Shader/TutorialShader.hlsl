Texture2D map : register(t0);
SamplerState samp : register(s0);

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

// SV -> System Value
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV : System Value
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = input.pos;
	output.uv = input.uv;

	return output;
}

// 후면버퍼에 그릴 내용
// 1프레임당 호출 횟수 : 1280 x 720 만큼 호출
float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp,input.uv);
}