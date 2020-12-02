#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	//for now to supress warning && can be changed if needed
	ytrans = 0;

	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel


	// ** much work to add below **

	size_t rows_vert = side;
	size_t column_vert = side;

	int nverts = rows_vert * column_vert;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = (rows_vert - 1)*(column_vert - 1) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	uint8_t h_val;
	float xval = 0;
	float zval = 0;

	for (DWORD i = 0; i < column_vert; ++i)
	{
		for (DWORD j = 0; j < rows_vert; ++j)
		{
			h_val = hgtmap->pixels[TexelIndex(pixel_width, side, j, i)]; // the 'R' byte of the pixel at (2,5)

			pVerts[i*rows_vert + j].set(xval * len, h_val*maxheight, zval * len);


			xval -= 1;
		}
		xval = 0;
		zval -= 1;
	}

	//setting uv's
	float du = 1.0f / (rows_vert - 1);
	/*int texUIndex = 0;
	int texVIndex = 0;*/
	for (DWORD i = 0; i < column_vert; ++i)
	{
		for (DWORD j = 0; j < rows_vert; ++j)
		{
			pVerts[i*column_vert + j].u = j * du*RepeatU;
			pVerts[i*column_vert + j].v = i * du*RepeatV;
		}
	}

	//face normal calculation

	for (DWORD i = 1; i < column_vert - 1; ++i)
	{
		for (DWORD j = 2; j < rows_vert - 1; ++j)
		{
			Vect Side1 = pVerts[i*column_vert + j].Pos - pVerts[i*column_vert + (j - 1)].Pos;
			Vect Side2 = pVerts[i*column_vert + j].Pos - pVerts[(i - 1)*column_vert + (j - 2)].Pos;
			Vect FN1 = Side2.cross(Side1);
			FN1 = FN1.norm();

			Vect Side3 = pVerts[i*column_vert + j].Pos - pVerts[(i - 1)*column_vert + (j - 2)].Pos;
			Vect Side4 = pVerts[i*column_vert + j].Pos - pVerts[(i - 1)*column_vert + (j - 1)].Pos;
			Vect FN2 = Side4.cross(Side3);
			FN2 = FN2.norm();

			Vect Side5 = pVerts[i*column_vert + j].Pos - pVerts[(i - 1)*column_vert + (j - 1)].Pos;
			Vect Side6 = pVerts[i*column_vert + j].Pos - pVerts[i*column_vert + (j + 1)].Pos;
			Vect FN3 = Side6.cross(Side5);
			FN3 = FN3.norm();

			Vect Side7 = pVerts[i*column_vert + j].Pos - pVerts[i*column_vert + (j - 1)].Pos;
			Vect Side8 = pVerts[i*column_vert + j].Pos - pVerts[(i + 1)*column_vert + j].Pos;
			Vect FN4 = Side7.cross(Side8);
			FN4 = FN4.norm();

			Vect Side9 = pVerts[i*column_vert + j].Pos - pVerts[(i + 1)*column_vert + j].Pos;
			Vect Side10 = pVerts[i*column_vert + j].Pos - pVerts[(i + 1)*column_vert + (j + 1)].Pos;
			Vect FN5 = Side9.cross(Side10);
			FN5 = FN5.norm();

			Vect Side11 = pVerts[i*column_vert + j].Pos - pVerts[(i + 1)*column_vert + (j + 1)].Pos;
			Vect Side12 = pVerts[i*column_vert + j].Pos - pVerts[i*column_vert + (j + 1)].Pos;
			Vect FN6 = Side11.cross(Side12);
			FN6 = FN6.norm();

			//Vect N = (FN1 + FN2 + FN3 + FN4 + FN5 + FN6)*0.16;
			Vect N = (FN1 + FN2 + FN3 + FN4 + FN5 + FN6)*0.16;

			pVerts[i*column_vert + j].normal = N;
		}
	}


	//setting faces
	int k = 0;
	for (DWORD i = 0; i < rows_vert - 1; i++)
	{
		for (DWORD j = 0; j < column_vert - 1; j++)
		{
			pTriList[k].set(i * column_vert + j, (i + 1)*column_vert + j, (i + 1)*column_vert + j + 1);  //first triangle
			pTriList[k + 1].set(i * column_vert + j, (i + 1)*column_vert + j + 1, i * column_vert + j + 1);// second triangle	

			k += 2;
		}
	}


	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
}
TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

int TerrainModel::TexelIndex(size_t pixel_width, int side, int i, int j) const
{
	return pixel_width * (j*side + i);
}



void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}