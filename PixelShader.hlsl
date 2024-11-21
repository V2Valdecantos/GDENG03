struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(lerp(input.color, input.color, (float) ((sin((float) (m_time / (float) 500.0f)) + 1.0f) / 2.0f)), 1.0f);
}

//float3 color : COLOR;
//float3 color1 : COLOR1;

/*cbuffer constant : register(b0)
{
    float m_angle;
};*/

// return float4(lerp(input.color, input.color1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);

 // Blend texture color with input vertex color (example: 50% blend)
    //float3 blendedColor = lerp(input.color, textureColor.rgb, 0.5); // 0.5 means equal blending

//return float4(input.color, 1.0f);