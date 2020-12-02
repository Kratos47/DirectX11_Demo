// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTextureLight.h"
#include "GraphicObject_TextureLight.h"
#include "GraphicObject_TextureLight.h"
#include"ShaderType.h"
#include"ShaderTexture.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class ShaderTexture;
class ShaderTextureLight;
class GraphicObject_Texture;
class GraphicObject_ColorLight;
class GraphicObject_TextureLight;
class SkyBox;
class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	/*FlatPlane* pPlane;
	Matrix planeMat;
	Matrix planeMat2;*/
	Vect pos2;

	Model* pModel1;
	
	Matrix mWorld1;	
	
	Model* pModel2;
	
	Matrix mWorld2;
	
	Model* pModel3;
	
	Matrix mWorld3;
	
	Model* pModel4;
	
	Matrix mWorld4;
	
	Model* pModel5;
	
	Matrix mWorld5;
	
	Model* pModel6;
	
	Matrix mWorld6;
	
	Model* pModel7;
	
	Matrix mWorld7;
	
	Model* pModel8;
	
	Matrix mWorld8;

	SkyBox* pSkyBox;

	TerrainModel* pTerrain;
	Matrix TerrainWorld;

	//ShaderColor*			pShaderCol;
	ShaderTexture*			pShaderTex;
	ShaderColorLight* pShaderColLight;
	
	ShaderTextureLight* pShaderTextureLight;

	//GraphicObject_Color*	GraphObj1;
	//GraphicObject_Color*	GraphObj2;
	
	//GraphicObject_ColorLight*	GraphObj1;
	//GraphicObject_ColorLight*	GraphObj2;

	//GraphicObject_Texture*	GraphObj1;
	//GraphicObject_Texture*	GraphObj2;
	
	GraphicObject_TextureLight*	GraphObj1;
	GraphicObject_TextureLight*	GraphObj2;
	GraphicObject_TextureLight*	GraphObj4;
	
	//building
	GraphicObject_TextureLight*	GraphObj5;
	GraphicObject_TextureLight*	GraphObj6;
	GraphicObject_TextureLight*	GraphObj7;

	//watchtowers
	GraphicObject_TextureLight*	GraphObj8;
	GraphicObject_TextureLight*	GraphObj9;
	GraphicObject_TextureLight*	GraphObj10;
	GraphicObject_TextureLight*	GraphObj11;

	GraphicObject_ColorLight*	GraphObj3;
	GraphicObject_TextureLight*	GraphObj12;
	
	Vect rot;

	  Texture*				pTex1;
	  Texture*				pTex2;
	  Texture*				pTex3;
	  Texture*				pTex4;
	  Texture*				pTex5;
	  Texture*				pTex5_0;
	  Texture*				pTex5_1;
	  Texture*				pTex5_2;
	  Texture*				pTex5_3;
	  Texture*				pTex6;
	  Texture*				pTex7;
	  Texture*				pTex8;
	  Texture*				pTex9;
	  Texture*				pTex10;
	  Texture*				pTex11;
	  Texture*				pTex12;

	// gimmicky mouse control
	Vect MousePos;		
	float mTheta;
	float mPhi;
	float mRadius;
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp