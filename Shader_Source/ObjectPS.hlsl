#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


//���� Ÿ������
float4 main(VSOut In) : SV_TARGET
{
    //return In.Color;
    float4 color = (float4) 0.f;
    color = albedoTexture.Sample(pointSampler, In.UV);
    
    //������ UV��ǥ�� �ؽ��� �����ؼ� ����
    color *= ObjectColor;
    
 
    float4 lightColor = float4(1.f, 1.f, 1.f, 1.0f);
    
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    color *= lightColor;
    
    if (color.a <= 0.0f)
        discard;
    
    
    return color;
}