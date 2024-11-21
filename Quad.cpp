#include "Quad.h"
#include "wrl/client.h"
#include "string"

Quad::Quad(float x, float y, float z) : m_vb(nullptr), m_cb(nullptr), m_vs(nullptr), m_ps(nullptr) //m_samplerState(nullptr), m_texture(nullptr)
{
    position1[0] = x;
    position1[1] = y;
    position1[2] = z;

}

Quad::~Quad()   
{
}

void Quad::init(ID3D11Device* device)
{

    // Define quad vertices with two positions and two colors
    vertex2D quadVertices[] = {
        { -0.6f + position1[0], -0.85f + position1[1], 0.0f +  position1[2],   -0.12f + position1[0], -0.11f + position1[1], 0.0f + position1[2], 0,-1,0,  0,1,0},  // Bottom-left
        { -0.85f + position1[0],  0.45f + position1[1],  0.0f +  position1[2], -0.10f + position1[0], 0.80f + position1[1], 0.0f + position1[2],   1,1,0,  1,1,0},  // Top-left
        {  1.0f + position1[0], -0.25f + position1[1],  0.0f +  position1[2], 0.30f + position1[0], -0.73f + position1[1], 0.0f + position1[2],  0,0,1,  1,0,0},  // Bottom-right
        {  0.0f + position1[0],  0.0f + position1[1],  0.0f +  position1[2], 0.88f + position1[0], 0.77f + position1[1], 0.0f + position1[2],    1,0,0,  0,0,1 }   // Top-right
    };

    // Load shaders
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    // Create vertex buffer for the quad
    m_vb = graphEngine->createVertexBuffer();

    // Compile and set vertex shader
    graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &shader_size);
    m_vs = graphEngine->createVertexShader(shader_byte_code, shader_size);
    m_vb->load(quadVertices, sizeof(vertex2D), ARRAYSIZE(quadVertices), shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();

    // Compile and set pixel shader
    graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &shader_size);
    m_ps = graphEngine->createPixelShader(shader_byte_code, shader_size);
    graphEngine->releaseCompiledShader();


    /*
    //load the texture
    HRESULT hr = DirectX::CreateWICTextureFromFile(
        graphEngine->getD3DDevice(), // Use the method to get the device
        textureFilePath.c_str(),
        nullptr, // Create the texture resource
        &m_texture);

    if (FAILED(hr)) {
        // Handle the texture loading error here
        return;
    }

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Create the sampler state
    hr = GraphicsEngine::getInstance()->getD3DDevice()->CreateSamplerState(&sampDesc, &m_samplerState);
    if (FAILED(hr)) {
        // Handle error
        return;
    }*/

}

void Quad::render(float m_delta_time)
{
    GraphicsEngine* graphEngine = GraphicsEngine::getInstance();
    DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

    /*
    if (m_cb != nullptr) {
        m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);


        GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
        GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
    }

    */

     // Bind the sampler state
    //deviceContext->getContext()->PSSetSamplers(0, 1, &m_samplerState);

    /*
    // Check if m_texture is valid
    if (m_texture) {
        deviceContext->getContext()->PSSetShaderResources(0, 1, &m_texture);
    } else {
        // Handle error: Texture is not initialized
        return;
    }
    */
     // Set the vertex and pixel shaders
    deviceContext->setVertexShader(m_vs);
    deviceContext->setPixelShader(m_ps);

    // Set the vertex buffer and draw
    deviceContext->setVertexBuffer(m_vb);
    deviceContext->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

bool Quad::release()
{
    if (m_vb) m_vb->release();
    if (m_cb) m_cb->release();
    if (m_vs) m_vs->release();
    if (m_ps) m_ps->release();
    delete this;
    return true;
}





// Initialize constant buffer
    //m_cb = graphEngine->createConstantBuffer();
    //m_constant.m_angle = 0;
    //m_cb->load(&m_constant, sizeof(constant));

// Update constant buffer with rotation angle
//m_constant.m_angle = angle;
//m_cb->update(deviceContext, &m_constant);


// Set the constant buffer
  //deviceContext->setConstantBuffer(m_vs, m_cb);
  //deviceContext->setConstantBuffer(m_ps, m_cb);