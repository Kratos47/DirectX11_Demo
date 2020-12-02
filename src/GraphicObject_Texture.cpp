#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture*	shader, Texture* pTexin,  Model* mod, ID3D11DeviceContext* md3dImmediateContext)
{
	SetModel(mod );
	pShader = shader;
	md3dIC = md3dImmediateContext;
	pTex = pTexin;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshTexpath = new LPCWSTR[n];
	for (int i = 0; i < n; i++)
		MeshTexpath[i] = L"../Assets/Textures/brick.tga"; // default texture
	
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	
	
}

void GraphicObject_Texture::SetTexPath(const LPCWSTR& path, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshTexpath[meshnum] = path;
}
void GraphicObject_Texture::SetTexPath(const LPCWSTR& path)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshTexpath[i] = path;
}


void GraphicObject_Texture::SetWorld(const Matrix& m)
{ 
	World = m;
}

void GraphicObject_Texture::Render(Camera Cam, Vect spotlightpos)
{
	pShader->SetToContext(md3dIC);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pTex, MeshTexpath[i], D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);
		pShader->SendWorld(World);
		pModel->SetToContext(pShader->GetContext());
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}