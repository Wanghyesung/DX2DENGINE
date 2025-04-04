#include "globals.hlsli"

struct VSIn
{
    //�ø�ƽ���� ����
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


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    
    float4 world = mul(float4(In.Pos, 1.0f), WorldMatrix);
    float4 view = mul(world, ViewMatrix);
    float4 proj = mul(view, ProjectionMatrix);

    Out.Pos = proj;
    Out.WorldPos = world.xyz;
    Out.Color = In.Color;
    Out.UV = In.UV;
    
    return Out;
}



/*
 //�������
    float4 world = mul(float4(In.Pos, 1.f), World);
    //������� * �����
    float4 view = mul(world, View);
    //����� * �������
    float4 proj = mul(view, Projection);
*/