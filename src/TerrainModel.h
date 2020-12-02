#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;
	Matrix WorldMat;


public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	Matrix GetWorldMat() { return WorldMat; }

	~TerrainModel();

	int TerrainModel::TexelIndex(size_t pixel_width, int side, int i, int j)const;


	void Render(ID3D11DeviceContext* context);

};



#endif _TerrainModel