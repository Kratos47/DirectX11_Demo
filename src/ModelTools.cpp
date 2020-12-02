#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"
#include <math.h>

/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	 //Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

}
// Creates the unit Pyramid centered at the origin
void ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 50;
	pVerts = new StandardVertex[nverts];
	ntri = 60;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(0.0f, 1.0f, 0.0f, 0.5, 0, 0, 0, -1);
	pVerts[1].set(-1.0f, -1.0f, -1.0f, 1, 1, 0, 0, -1);
	pVerts[2].set(+1.0f, -1.0f, -1.0f, 0, 1, 0, 0, -1);

	pVerts[3].set(0.0f, 1.0f, 0.0f, 0.5, 0, 0, 0, 1);
	pVerts[4].set(-1.0f, -1.0f, +1.0f, 0, 1, 0, 0, 1);
	pVerts[5].set(+1.0f, -1.0f, +1.0f, 1, 1, 0, 0, 1);

	pVerts[6].set(0.0f, 1.0f, 0.0f, 0.5, 0, 1, 0, 0);
	pVerts[7].set(+1.0f, -1.0f, -1.0f, 1, 1, 1, 0, 0);
	pVerts[8].set(+1.0f, -1.0f, +1.0f, 0, 1, 1, 0, 0);

	pVerts[9].set(0.0f, 1.0f, 0.0f, 0.5, 0, -1, 0, 0);
	pVerts[10].set(-1.0f, -1.0f, -1.0f, 0, 1, -1, 0, 0);
	pVerts[11].set(-1.0f, -1.0f, +1.0f, 1, 1, -1, 0, 0);

	pVerts[12].set(-1.0f, -1.0f, -1.0f, 0, 0, 0, -1, 0);
	pVerts[13].set(+1.0f, -1.0f, +1.0f, 1, 1, 0, -1, 0);
	pVerts[14].set(+1.0f, -1.0f, -1.0f, 0, 1, 0, -1, 0);

	pVerts[15].set(-1.0f, -1.0f, -1.0f, 0, 0, 0, -1, 0);
	pVerts[16].set(-1.0f, -1.0f, +1.0f, 1, 0, 0, -1, 0);
	pVerts[17].set(+1.0f, -1.0f, +1.0f, 1, 1, 0, -1, 0);


	// back face
	pTriList[0].set(0, 2, 1);
	// front face
	pTriList[1].set(3, 4, 5);
	// left face
	pTriList[2].set(6, 8, 7);
	// right face
	pTriList[3].set(9, 10, 11);
	// bottom faces
	pTriList[4].set(12, 14, 13);
	pTriList[5].set(15, 17, 16);

}

void ModelTools::CreateUnitSphere(float radius, int vslice, int hslice, StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri)
{
	nverts = ((hslice - 2) * vslice) + 2;
	ntri = ((hslice - 3)*(vslice) * 2) + (vslice * 2);

	float r = radius;

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	//creating verts
	pVerts = new StandardVertex[nverts];
	Vect currVertPos = Vect(0.0f, 0.0f, r);

	//north pole
	pVerts[0].set(0.0f, 0.0f, -r);
	pVerts[0].normal = Vect(0, 0, -r);

	//middle stuff
	for (int i = 0; i < hslice - 2; ++i)
	{
		spherePitch = (i + 1) * (3.14f / (hslice - 1));
		Matrix Rotationx = Matrix(ROT_X, spherePitch);
		for (int j = 0; j < vslice; ++j)
		{
			sphereYaw = j * (6.28f / (vslice));
			Matrix Rotationz = Matrix(ROT_Z, sphereYaw);
			currVertPos = Vect(0.0f, 0.0f, -r)* Rotationx * Rotationz;
			currVertPos.getNorm();
			
			pVerts[i*vslice + j + 1].set(currVertPos.X(), currVertPos.Y(), currVertPos.Z());
			pVerts[i*vslice + j + 1].normal = currVertPos;

			pVerts[i*vslice + j + 1].u = (float)asin(currVertPos.getNorm().X() / MATH_PI) + r;
			pVerts[i*vslice + j + 1].v = (float)asin(currVertPos.getNorm().Y() / MATH_PI) + r;
		}
	}	

	//south pole
	pVerts[nverts - 1].set(0.0f, 0.0f, r);
	pVerts[nverts - 1].normal = Vect(0, 0, r);

	
	//setting verts
	pTriList = new TriangleByIndex[ntri * 3];
	int k = 0;

	//north pole
	for (int l = 0; l < vslice - 1; ++l)
	{
		pTriList[k].set(0, l + 2, l + 1);
		k++;
	}
	pTriList[k].set(0, 1, vslice);
	k++;

	//middle stuff
	for (int i = 0; i < hslice - 3; ++i)
	{
		for (int j = 0; j < vslice - 1; ++j)
		{
			pTriList[k].set(i * vslice + j + 1,
				i * vslice + j + 2,
				(i + 1)*vslice + j + 1);
			pTriList[k + 1].set((i + 1)*vslice + j + 1,
				i * vslice + j + 2,
				(i + 1)*vslice + j + 2);

			k += 2;
		}

		pTriList[k].set((i*vslice) + vslice,
			(i*vslice) + 1,
			((i + 1)*vslice) + vslice);

		pTriList[k + 1].set(((i + 1)*vslice) + vslice,
			(i*vslice) + 1,
			((i + 1)*vslice) + 1);

		k += 2;
	}

	//south pole

	for (int l = 0; l < vslice - 1; ++l)
	{
		pTriList[k].set(nverts - 1,
			(nverts - 1) - (l + 2),
			(nverts - 1) - (l + 1));
		k++;
	}
	pTriList[k].set(nverts - 1,
		(nverts - 2),
		(nverts - 1) - vslice);
}


void ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex *& pVerts, int & nverts, TriangleByIndex *& pTriList, int & ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Back
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.50, 0.375, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.50, 0.625, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0.75, 0.625, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0.75, 0.375, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// front
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.25, 0.375, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.25, 0.625, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 0.625, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 0.375, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5, 0.625, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25, 0.625, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25, 0.875, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5, 0.875, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5, 0.375, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5, 0.125, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25, 0.125, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.25, 0.625, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.25, 0.375, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.5, 0.375, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.5, 0.625, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 0.75, 0.375, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0.75, 0.625, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 0.625, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 0.375, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

