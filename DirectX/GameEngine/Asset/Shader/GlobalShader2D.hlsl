
#include "Share.hlsli"

struct VS_INPUT_COLOR2D
{
    // POSITION 만 적으면 뒤에 0이 생략되어 POSITION0번으로 인식된다.
    float3 Pos : POSITION0;
    float4 Color : COLOR0;
};

struct VS_OUTPUT_COLOR2D
{
    // SV_ 가 붙은 레지스터는 VS에서 값을 넣어주는 용도이며 다른곳에서 이 값을
    // 가져와서 사용하면 안된다.
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_OUTPUT_COLOR2D Color2DVS(VS_INPUT_COLOR2D input)
{
    VS_OUTPUT_COLOR2D output = (VS_OUTPUT_COLOR2D) 0;
    
    // x, y, z 에는 input.Pos의 x, y, z 가 들어가고 w에는 1.f이 들어간다.
    output.Pos = float4(input.Pos, 1.f);
    output.Color = input.Color;

    return output;
}

struct PS_OUTPUT_COLOR
{
    // 0번 백버퍼에 색상을 출력한다.
    float4 Color : SV_TARGET;
};

PS_OUTPUT_COLOR Color2DPS(VS_OUTPUT_COLOR2D input)
{
    PS_OUTPUT_COLOR output = (PS_OUTPUT_COLOR) 0;
    
    output.Color = input.Color;
    
    return output;
}
