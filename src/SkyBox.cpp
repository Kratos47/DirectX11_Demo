#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"
SkyBox::SkyBox(ID3D11Device * dev, float len)
{
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];




	//Setting up faces

	// Back
	int vind = 0;
	int tind = 0;
	
	pVerts[vind].set(0.5f*len, 0.5f*len, 0.5f*len, 0.50, 0.34);
	pVerts[vind + 1].set(-0.5f*len, 0.5f*len, 0.5f*len, 0.75, 0.34);
	pVerts[vind + 2].set(-0.5f*len, -0.5f*len, 0.5f*len, 0.75, 0.66);
	pVerts[vind + 3].set(0.5f*len, -0.5f*len, 0.5f*len, 0.50, 0.66);
	
	pTriList[tind].set(vind, vind + 2, vind + 1);	
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// front
	vind += 4;
	tind += 2;
	
	pVerts[vind].set(0.5f*len, 0.5f*len, -0.5f*len, 0.25, 0.34);
	pVerts[vind + 1].set(-0.5f*len, 0.5f*len, -0.5f*len, 0, 0.34);
	pVerts[vind + 2].set(-0.5f*len, -0.5f*len, -0.5f*len, 0, 0.66);
	pVerts[vind + 3].set(0.5f*len, -0.5f*len, -0.5f*len, 0.25, 0.66);
	
	pTriList[tind].set(vind, vind + 1, vind + 3);
	pTriList[tind + 1].set(vind+1, vind + 2, vind+3);
	

	// right
	vind += 4;
	tind += 2;
	
	pVerts[vind].set(0.5f*len, 0.5f*len, -0.5f*len, 0.25, 0.34);
	pVerts[vind + 1].set(0.5f*len, 0.5f*len, 0.5f*len, 0.50, 0.34);
	pVerts[vind + 2].set(0.5f*len, -0.5f*len, 0.5f*len, 0.50, 0.66);
	pVerts[vind + 3].set(0.5f*len, -0.5f*len, -0.5f*len, 0.25, 0.66);
	
	
	pTriList[tind].set(vind, vind + 2, vind + 1);	
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// left
	vind += 4;
	tind += 2;
	
	pVerts[vind].set(-0.5f*len, 0.5f*len, 0.5f*len, 0.75, 0.34);
	pVerts[vind + 1].set(-0.5f*len, 0.5f*len, -0.5f*len, 1, 0.34);
	pVerts[vind + 2].set(-0.5f*len, -0.5f*len, -0.5f*len, 1, 0.66);
	pVerts[vind + 3].set(-0.5f*len, -0.5f*len, 0.5f*len, 0.75, 0.66);
	
	
	pTriList[tind].set(vind, vind + 2, vind + 1);	
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Top
	vind += 4;
	tind += 2;
	
	pVerts[vind].set(0.5f*len, 0.5f*len, -0.5f*len, 0.499, 0);
	pVerts[vind + 1].set(-0.5f*len, 0.5f*len, -0.5f*len, 0.2505, 0);
	pVerts[vind + 2].set(-0.5f*len, 0.5f*len, 0.5f*len, 0.2505, 0.34);
	pVerts[vind + 3].set(0.5f*len, 0.5f*len, 0.5f*len, 0.499, 0.34);
	
	pTriList[tind].set(vind, vind + 2, vind + 1);
	
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Bottom
	vind += 4;
	tind += 2;
	
	pVerts[vind].set(0.5f*len, -0.5f*len, 0.5f*len, 0.4995, 0.66);
	pVerts[vind + 1].set(-0.5f*len, -0.5f*len, 0.5f*len, 0.499, 1);
	pVerts[vind + 2].set(-0.5f*len, -0.5f*len, -0.5f*len, 0.251, 1);
	pVerts[vind + 3].set(0.5f*len, -0.5f*len, -0.5f*len, 0.251, 0.66);
	
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);


	pSkyBox = new Model(dev, pVerts, nverts, pTriList, ntri);
}

SkyBox::~SkyBox()
{
	delete pSkyBox;
}
void SkyBox::Render(ID3D11DeviceContext * context)
{
	pSkyBox->SetToContext(context);
	pSkyBox->Render(context);
}
