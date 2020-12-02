#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>
#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_TextureLight.h"
#include "SkyBox.h"
#include "ShaderTexture.h"

void DXApp::InitDemo()
{
	pShaderTextureLight = new ShaderTextureLight(md3dDevice);
	pShaderTex = new ShaderTexture(md3dDevice);
	pShaderColLight = new ShaderColorLight(md3dDevice);
	
	
	pModel1 = new Model(md3dDevice, "../Assets/Models/Soyuz-FG.azul");
	pModel2 = new Model(md3dDevice, "../Assets/Models/ML_LP.azul");
  	pModel3 = new Model(md3dDevice, Model::PreMadedeModels::UnitSphere,0.5);
	pModel4 = new Model(md3dDevice, "../Assets/Models/wooden_watch_tower.azul");
	pModel5 = new Model(md3dDevice, "../Assets/Models/B1.azul");
	pModel6 = new Model(md3dDevice, "../Assets/Models/B2.azul");
	pModel7 = new Model(md3dDevice, "../Assets/Models/B3.azul");
	pModel8 = new Model(md3dDevice, Model::PreMadedeModels::UnitBoxRepeatedTexture, 0.2);
	//pModel8 = new Model(md3dDevice, Model::PreMadedeModels::UnitBoxSixFacesTexture, 0.2);

	/*pShaderTextureLight->SetToContext(md3dImmediateContext);
	pShaderTextureLight->SetTextureResourceAndSampler(pTex1, L"../Assets/Textures/mobilelauncher_LowRes_d.tga",
		D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);*/

	GraphObj1 = new GraphicObject_TextureLight(pTex1, pShaderTextureLight, pModel2, md3dImmediateContext);
	GraphObj1->SetTexPath(L"../Assets/Textures/mobilelauncher_LowRes_d.tga");
	GraphObj1->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj1->SetTextureResourceAndSampler(pTex1);
	

	GraphObj2 = new GraphicObject_TextureLight(pTex2, pShaderTextureLight, pModel1, md3dImmediateContext);
	GraphObj2->SetTexPath(L"../Assets/Textures/shuttel.tga");
	GraphObj2->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj2->SetTextureResourceAndSampler(pTex2);
	
	GraphObj4 = new GraphicObject_TextureLight(pTex3, pShaderTextureLight, pModel3, md3dImmediateContext,true);
	GraphObj4->SetTexPath(L"../Assets/Textures/football.tga");
	GraphObj4->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj4->SetTextureResourceAndSampler(pTex3);

	//===================================building============================================

	GraphObj5 = new GraphicObject_TextureLight(pTex4, pShaderTextureLight, pModel5, md3dImmediateContext);
	GraphObj5->SetTexPath(L"../Assets/Textures/building.tga",0);
	GraphObj5->SetColor(0.5*Colors::White, 0.5*Colors::White, Vect(1, 1, 1, 150));
	GraphObj5->SetTextureResourceAndSampler(pTex4);

	GraphObj6 = new GraphicObject_TextureLight(pTex5, pShaderTextureLight, pModel6, md3dImmediateContext);
	GraphObj6->SetTexPath(L"../Assets/Textures/ConcreteFloorsDamaged0010_6_S.tga",0);
	GraphObj6->SetTexPath(L"../Assets/Textures/1383-v3.tga",1);
	GraphObj6->SetTexPath(L"../Assets/Textures/panel.tga",2);
	GraphObj6->SetTexPath(L"../Assets/Textures/BrickSmallBrown0271_7_S.tga",3);
	GraphObj6->SetColor(0.5*Colors::White, 0.5*Colors::White, Vect(1, 1, 1, 150));
	GraphObj6->SetTextureResourceAndSampler(pTex5_0, 0);
	GraphObj6->SetTextureResourceAndSampler(pTex5_1, 1);
	GraphObj6->SetTextureResourceAndSampler(pTex5_2, 2);
	GraphObj6->SetTextureResourceAndSampler(pTex5_3, 3);


	//GraphObj6->SetColor(0.5*Colors::Purple, 0.5*Colors::White, Vect(1, 1, 1, 150),0);
	//GraphObj6->SetColor(0.5*Colors::AntiqueWhite, 0.5*Colors::White, Vect(1, 1, 1, 150),1);
	//GraphObj6->SetColor(0.5*Colors::Fuchsia, 0.5*Colors::White, Vect(1, 1, 1, 150),2);
	//GraphObj6->SetColor(0.5*Colors::NavajoWhite, 0.5*Colors::White, Vect(1, 1, 1, 150),3);
	
	GraphObj7 = new GraphicObject_TextureLight(pTex6, pShaderTextureLight, pModel7, md3dImmediateContext);
	GraphObj7->SetTexPath(L"../Assets/Textures/RooftilesMetal0006_2_S.tga",0);
	GraphObj7->SetColor(0.5*Colors::White, 0.5*Colors::White, Vect(1, 1, 1, 150));
	GraphObj7->SetTextureResourceAndSampler(pTex6);
	//===================================building============================================


	////====================================watchtowers=================================================

	GraphObj8 = new GraphicObject_TextureLight(pTex7, pShaderTextureLight, pModel4, md3dImmediateContext);
	GraphObj8->SetTexPath(L"../Assets/Textures/Wood_Tower_Col.tga");
	GraphObj8->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj8->SetTextureResourceAndSampler(pTex7);
	
	GraphObj9 = new GraphicObject_TextureLight(pTex8, pShaderTextureLight, pModel4, md3dImmediateContext);
	GraphObj9->SetTexPath(L"../Assets/Textures/Wood_Tower_Col.tga");
	GraphObj9->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj9->SetTextureResourceAndSampler(pTex8);
	
	GraphObj10 = new GraphicObject_TextureLight(pTex9, pShaderTextureLight, pModel4, md3dImmediateContext);
	GraphObj10->SetTexPath(L"../Assets/Textures/Wood_Tower_Col.tga");
	GraphObj10->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj10->SetTextureResourceAndSampler(pTex9);
	
	GraphObj11 = new GraphicObject_TextureLight(pTex10, pShaderTextureLight, pModel4, md3dImmediateContext);
	GraphObj11->SetTexPath(L"../Assets/Textures/Wood_Tower_Col.tga");
	GraphObj11->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));
	GraphObj11->SetTextureResourceAndSampler(pTex10);
	
	
	//======================================box and testing=========================================
	GraphObj3 = new GraphicObject_ColorLight(pShaderColLight, pModel8, md3dImmediateContext,
		Colors::Firebrick, Colors::Firebrick, 5 * Vect(1, 0, 0, 150));
	//
	//GraphObj12 = new GraphicObject_TextureLight(pTex11, pShaderTextureLight, pModel8, md3dImmediateContext, true);
	//// GraphObj12->SetTexPath(L"../Assets/Textures/CrateFace.tga");
	////GraphObj12->SetTexPath(L"../Assets/Textures/CubeFaces.tga");
	//GraphObj12->SetColor(Colors::White, Colors::White, Vect(1, 1, 1, 150));


	// Initialize the world matrix

	//misc
	mWorld1 = Matrix(ROT_Y, -1.5708)*Matrix(TRANS, 0, -10, 0);
	GraphObj1->SetWorld(mWorld1);
	GraphObj2->SetWorld(Matrix(TRANS,0,-71,16));
	GraphObj3->SetWorld(Matrix(TRANS, 35, 8, 10));
	GraphObj4->SetWorld(Matrix(TRANS, 35, 0.5, 13)*Matrix(TRANS, -5, 0, 0));

	//for spolights
	pos2 = Vect(40, 150, 40);
	mWorld2 = Matrix(TRANS, pos2);//Matrix(IDENTITY);


	////building
	GraphObj5->SetWorld(Matrix(TRANS, 30, 3, 15));
	GraphObj6->SetWorld(Matrix(TRANS, 30, 3, 15));
	GraphObj7->SetWorld(Matrix(TRANS, 30, 3, 15));
			

	//Watchtowers
	GraphObj8->SetWorld(Matrix(ROT_X, -1.5708)*Matrix(TRANS, 40, 5, 40));
	GraphObj9->SetWorld(Matrix(ROT_X, -1.5708)*Matrix(TRANS, 40, 0, 0));
	GraphObj10->SetWorld(Matrix(ROT_X, -1.5708)*Matrix(TRANS, 0, 2, 40));
	GraphObj11->SetWorld(Matrix(ROT_X, -1.5708)*Matrix(TRANS, 0, -2, 0));

	//GraphObj12->SetWorld(Matrix(TRANS, 30, 8, 10));
	/****************************************/
	//skybox model creation

	pSkyBox = new SkyBox(md3dDevice, 10000);
	pShaderTextureLight->SetTextureResourceAndSampler(pTex11, L"../Assets/Textures/skybox2(2).tga"
		, D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);

	
	/****************************************/
	//terrain model creation
	
	float Tscale = 5;
	float THeight = Tscale * 0.25f;

	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/HMTest.tga", Tscale, THeight, 0, 64, 64);
	
	TerrainWorld = Matrix(SCALE, 1, 1, 1) * Matrix(TRANS, 600, -5, 600);

	pShaderTextureLight->SetTextureResourceAndSampler(pTex12, L"../Assets/Textures/ground.tga"
		, D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);

	///****************************************/
	
		// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 20000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(0, 3, -5));

	/////////TESTING///////////////


	/////////TESTING///////////////

	// Initialize gimmicky mouse control values
	mTheta = .5;
	mPhi = 3.1415f / 8;
	mRadius = 6;

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mWorld2 *= Matrix(ROT_Y, .05f);  // Simple slow rotation about y axis

	pos2 = mWorld2.get(MatrixRowType::ROW_3);

	float camSpeed = 0.1f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.04f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// --- Render Object #1;
	
	//misc

	//pShaderTextureLight->SetToContext(pTex1);
	GraphObj1->pShader->SetToContext(pTex1);
	GraphObj1->Render(mCam, pos2);
	//

	GraphObj2->pShader->SetToContext(pTex2);
	GraphObj2->Render(mCam, pos2);

	
	//box
	GraphObj3->Render(mCam, pos2);	

	//football 
	GraphObj4->pShader->SetToContext(pTex3);
	GraphObj4->Render(mCam, pos2);

	
	//////building //setting diffrent textures for diffrent meshes
	GraphObj5->pShader->SetToContext(pTex4);
	GraphObj5->Render(mCam, pos2);

	GraphObj6->pShader->SetToContext(pTex5_0);
	GraphObj6->Render_Mesh(mCam, pos2, md3dImmediateContext, 0);

	GraphObj6->pShader->SetToContext(pTex5_1);
	GraphObj6->Render_Mesh(mCam, pos2, md3dImmediateContext, 1);


	GraphObj6->pShader->SetToContext(pTex5_2);
	GraphObj6->Render_Mesh(mCam, pos2, md3dImmediateContext, 2);

	GraphObj6->pShader->SetToContext(pTex5_3);
	GraphObj6->Render_Mesh(mCam, pos2, md3dImmediateContext, 3);

	GraphObj7->pShader->SetToContext(pTex6);
	GraphObj7->Render_Mesh(mCam, pos2, md3dImmediateContext,0);
	GraphObj7->Render_Mesh(mCam, pos2, md3dImmediateContext,1);


	//
	//////watchtowers
	GraphObj8->pShader->SetToContext(pTex7);
	GraphObj8->Render(mCam, pos2);
	GraphObj9->pShader->SetToContext(pTex8);
	GraphObj9->Render(mCam, pos2);
	GraphObj10->pShader->SetToContext(pTex9);
	GraphObj10->Render(mCam, pos2);
	GraphObj11->pShader->SetToContext(pTex10);
	GraphObj11->Render(mCam, pos2);
	//
	////GraphObj12->Render(mCam, pos2);

	//
	//
	////=====================================================SkyBox ===============================================================//
	pShaderTextureLight->SetToContext(pTex11);

	pShaderTextureLight->SendWorldAndMaterial(Matrix(IDENTITY), Vect(1, 1, 1), Vect(1, 1, 1), Vect(0, 0, 0, 0));
	//
	pSkyBox->Render(md3dImmediateContext);
	//
	//

	////===================================================Terrain ===============================================================//
	pShaderTextureLight->SetToContext(pTex12);

	pShaderTextureLight->SendWorldAndMaterial(TerrainWorld, Vect(0.3, 0.3, 0.3), Vect(0.3, 0.3, 0.3), Vect(1, 1, 1, 100));

	//// --- Render plane;
	pTerrain->Render(md3dImmediateContext);  
	//
	////=====================================================fog=====================================================//
	//
	//pShaderTextureLight->SendFogProperties(15, 100, 1.5*Vect(0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f));
	//
	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	WCHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pModel1;
	delete pModel2;
	delete pModel3;
	delete pModel4;
	delete pModel5;
	delete pModel6;
	delete pModel7;
	delete pModel8;

	//delete pShaderCol;
	delete pShaderTextureLight;
	delete pShaderColLight;
	delete pShaderTex;
	//
	delete pSkyBox;
	delete pTerrain;

	
	delete GraphObj1;
	delete GraphObj2;
	delete GraphObj3;
	delete GraphObj4;
	delete GraphObj5;
	delete GraphObj6;
	delete GraphObj7;
	delete GraphObj8;
	delete GraphObj9;
	delete GraphObj10;
	delete GraphObj11;
	//delete GraphObj12;

	delete pTex1;
	delete pTex2;
	delete pTex3;
	delete pTex4;
	delete pTex5_0;
	delete pTex5_1;
	delete pTex5_2;
	delete pTex5_3;
	delete pTex6;
	delete pTex7;
	delete pTex8;
	delete pTex9;
	delete pTex10;
	delete pTex11;
	delete pTex12;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	//rd.FillMode = D3D11_FILL_WIREFRAME;  // Also: 
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		MousePos[x] = static_cast<float>(xval);
		MousePos[y] = static_cast<float>(yval);
	}
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	// Gimmicky mouse control
	if (btnState & MK_LBUTTON)
	{
		float dx = 0.01f*(MousePos[x] - xval);
		float dy = 0.01f*(MousePos[y] - yval);

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi -= dy;

		static float verticalMax = MATH_PI2 - 0.2f;

		if (mPhi > verticalMax)
			mPhi = verticalMax;
		else if (mPhi < -verticalMax)
			mPhi = -verticalMax;

		// Build the view matrix using gimmicky trick
		Vect target = Vect(0, 0, 0, 0);
		Vect up = Vect(0, 1, 0, 0);
		Vect pos = Vect(0, 0, -mRadius) * Matrix(ROT_Y, mTheta) * Matrix(ROT_X, mPhi);
		mCam.setOrientAndPosition(up, target, pos);
	}

	MousePos[x] = static_cast<float>(xval);
	MousePos[y] = static_cast<float>(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	if (delta > 0)
	{
		mRadius -= 1;
	}
	else
	{
		mRadius += 1;
	}
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}