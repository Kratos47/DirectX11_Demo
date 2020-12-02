#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>
#include "DXApp.h"

GraphicObject_TextureLight::GraphicObject_TextureLight(Texture*& tex, ShaderTextureLight *& shader, Model * mod, ID3D11DeviceContext * md3dImmediateContext, float ispremade)
{
	SetModel(mod);
	md3dIC = md3dImmediateContext;
	pShader = shader;
	Tex = tex;


	if (ispremade == 1)
	{
		this->isPremade = true;
		MeshColoramb = new Vect(0, 0, 0);
		MeshColordiff = new Vect(0, 0, 0);
		MeshColorspec = new Vect(0, 0, 0);
		MeshTexpathpremade = L"../Assets/Textures/brick.tga"; // default texture

	}
	else
	{
		Meshcount = mod->GetMeshCount();

		MeshColoramb = new Vect[Meshcount];
		MeshColordiff = new Vect[Meshcount];
		MeshColorspec = new Vect[Meshcount];
		MeshTexpath = new LPCWSTR[Meshcount];

		for (unsigned int i = 0; i < Meshcount; i++)
		{
			MeshColoramb[i] = Vect(0, 0, 0);
			MeshColordiff[i] = Vect(0, 0, 0);
			MeshColorspec[i] = Vect(0, 0, 0);
			MeshTexpath[i] = L"../Assets/Textures/brick.tga"; // default texture
		}
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{

}
void GraphicObject_TextureLight::SetTexPath(const LPCWSTR path, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshTexpath[meshnum] = path;
}

void GraphicObject_TextureLight::SetTexPath(const LPCWSTR path)
{
	if (isPremade == true)
	{
		MeshTexpathpremade = path;
	}
	else
	{
		MeshTexpath[0] = path;
	}
}

void GraphicObject_TextureLight::SetColor(const Vect ambcol, const Vect diffcol, const Vect speccol)
{
	if (isPremade == true)
	{
		MeshColoramb_premade = ambcol;
		MeshColordiff_premade = diffcol;
		MeshColorspec_premade = speccol;
	}
	else
	{
		for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		{
			MeshColoramb[i] = ambcol;
			MeshColordiff[i] = diffcol;
			MeshColorspec[i] = speccol;
		}
	}
}

void GraphicObject_TextureLight::SetColor(const Vect ambcol, const Vect diffcol, const Vect speccol, int meshnum)
{
	if (isPremade == true)
	{
		MeshColoramb_premade = ambcol;
		MeshColordiff_premade = diffcol;
		MeshColorspec_premade = speccol;
	}
	else
	{
		assert(pModel->ValidMeshNum(meshnum));
		MeshColoramb[meshnum] = ambcol;
		MeshColordiff[meshnum] = diffcol;
		MeshColorspec[meshnum] = speccol;
	}
}


void GraphicObject_TextureLight::SetWorld(const Matrix m)
{
	World = m;
}
void GraphicObject_TextureLight::SetTextureResourceAndSampler(Texture*& tex)
{
	pShader->SetToContext(md3dIC);

	if (isPremade == true)
	{
		pShader->SetTextureResourceAndSampler(tex, MeshTexpathpremade, D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);
	}
	else
	{
		pShader->SetTextureResourceAndSampler(tex, MeshTexpath[0], D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);

	}
}

void GraphicObject_TextureLight::SetTextureResourceAndSampler(Texture*& tex, unsigned int meshnum)
{
	pShader->SetToContext(md3dIC);

	pShader->SetTextureResourceAndSampler(tex, MeshTexpath[meshnum], D3D11_FILTER_ANISOTROPIC, 8, true, 0, DirectX::TEX_FILTER_LINEAR);
}




void GraphicObject_TextureLight::Render(Camera Cam, Vect spotlightpos)
{

	Vect dL[2] = { Vect(1, 1, 1).getNorm(),Vect(-1, -1, -1).getNorm() };

	pShader->SetDirectionalLightParameters(dL,
		.3 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));


	Vect PL[2] = { Vect(0,10,20),Vect(32,10,20) };

	pShader->SetPointLightParameters(PL, 25, .2 * Vect(0, 1, 0),
		Vect(1, 1, 1), 1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShader->SetToContext(md3dIC);

	Vect SL[4] = { Vect(40, 20, 40),Vect(40, 20, 0),Vect(0, 20, 40),Vect(0, 20, 0) };

	pShader->SetSpotLightParameters(SL, 100, .5 * Vect(1, 1, 1),
		-spotlightpos.getNorm(), 100,
		4 * Vect(1, 1, 1), 4 * Vect(1, 1, 1), 4 * Vect(1, 1, 1, 150));



	Cam.getPos(eyepos);
	pShader->SendLightParameters(eyepos);
	if (isPremade == true)
	{
		pShader->SendWorldAndMaterial(World, MeshColoramb_premade, MeshColordiff_premade, MeshColorspec_premade);
		pModel->SetToContext(md3dIC);
		pModel->Render(md3dIC);
		pShader->SendCamMatrices(Cam.getViewMatrix(), Cam.getProjMatrix());
	}
	else
	{
		pShader->SendWorldAndMaterial(World, MeshColoramb[0], MeshColordiff[0], MeshColorspec[0]);
		pModel->SetToContext(md3dIC);
		pModel->RenderMesh(md3dIC, 0);
		pShader->SendCamMatrices(Cam.getViewMatrix(), Cam.getProjMatrix());
	}
}

void GraphicObject_TextureLight::Render_Mesh(Camera Cam, Vect spotlightpos, ID3D11DeviceContext * md3dIc, unsigned int meshnum)
{
	Vect dL[2] = { Vect(1, 1, 1).getNorm(),Vect(-1, -1, -1).getNorm() };

	pShader->SetDirectionalLightParameters(dL,
		.3 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));


	Vect PL[2] = { Vect(0,10,20),Vect(32,10,20) };

	pShader->SetPointLightParameters(PL, 25, .2 * Vect(0, 1, 0),
		Vect(1, 1, 1), 1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShader->SetToContext(md3dIC);

	Vect SL[4] = { Vect(40, 20, 40),Vect(40, 20, 0),Vect(0, 20, 40),Vect(0, 20, 0) };

	pShader->SetSpotLightParameters(SL, 100, .5 * Vect(1, 1, 1),
		-spotlightpos.getNorm(), 100,
		4 * Vect(1, 1, 1), 4 * Vect(1, 1, 1), 4 * Vect(1, 1, 1, 150));

	Cam.getPos(eyepos);
	pShader->SendLightParameters(eyepos);


	pShader->SendWorldAndMaterial(World, MeshColoramb[meshnum], MeshColordiff[meshnum], MeshColorspec[meshnum]);
	pModel->SetToContext(md3dIc);
	pModel->RenderMesh(md3dIC, meshnum);

	pShader->SendCamMatrices(Cam.getViewMatrix(), Cam.getProjMatrix());
}


