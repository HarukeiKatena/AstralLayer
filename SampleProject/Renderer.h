//=============================================================
// 
// レンダラーマネージャー
// 嘉手納春慶
// 2021/10/01
// 
//=============================================================
#pragma once
#include"main.h"
#include<AstralLayer.h>
#include"Math/SimpleMath.h"

#include<memory>

#pragma comment(lib,"AstralLayer.lib")

using namespace AstralLayer;
using namespace DirectX;
using namespace DirectX::SimpleMath;

struct ATL_VERTEX_3D
{
	Vector3 Position;
	Vector3 Normal;
	Color Diffuse;
	Vector2 UV;
};

class Renderer
{
private:
	ATLIDevice* m_pDevice = nullptr;
	ATLISwapChain* m_pSwapChain = nullptr;
	ATLIRenderTargetView* m_pRenderTargetView = nullptr;
	ATLICommandQueue* m_pCommandQueue = nullptr;
	ATLICommandList* m_pCommandList = nullptr;
	ATLIPipeLine* m_pPipeLine = nullptr;
	ATLIFence* m_pFence = nullptr;
	ATLIRootSignature* m_pRootSignature = nullptr;
	ATLIDepthStencilView* m_pDepthStencilView = nullptr;

	ATLICommandList* m_pClearCommandList = nullptr;
	
	ATLIResource* m_pWorldBuffer = nullptr;
	ATLIResource* m_pViewProjection = nullptr;
	ATLIResource* m_pVertexBuffer = nullptr;
	ATLIResource* m_pIndexBuffer = nullptr;
	ATLIResource* m_pTexture = nullptr;

	ATL_VIEWPORT m_Viewport{};
	ATL_RECT m_Rect{};

	unsigned int m_WorldID = 0;
	unsigned int m_ViewID = 0;
	unsigned int m_ProjectionID = 0;

public:
	void Init(HWND hwnd);
	void Update(void);
	void Draw(void);
	void Uninit(void);
};