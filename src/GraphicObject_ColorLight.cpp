#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "DXApp.h"

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod, ID3D11DeviceContext* md3dImmediateContext,
	const Vect& ambcol, const Vect& diffcol, const Vect& speccol)
{
	SetModel(mod );
	md3dIC = md3dImmediateContext;
	pShader = shader;
	ac = ambcol;
	dc = diffcol;
	sc = speccol;
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{

}

void GraphicObject_ColorLight::SetWorld(const Matrix& m)
{ 
	World = m;
}


void GraphicObject_ColorLight::Render(Camera Cam, Vect spotlightpos)
{
	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(),
		.1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(5, 10, 0), 100, .2 * Vect(0, 1, 0),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShader->SetSpotLightParameters(spotlightpos, 4000, .5 * Vect(1, 0, 0),
		-spotlightpos.getNorm(), 100,
		.2 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 450));
	
	pShader->SetToContext(md3dIC);

	Cam.getPos(eyepos);
	pShader->SendLightParameters(eyepos);

	pShader->SendWorldAndMaterial(World/**Matrix(TRANS, 0, 2*cosf( mTimer.TotalTime()), 0)*/, ac, dc, sc);
	
	pModel->SetToContext(md3dIC);
	pModel->Render(md3dIC);

	pShader->SendCamMatrices(Cam.getViewMatrix(), Cam.getProjMatrix());
}