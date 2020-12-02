// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTextureLight.h"
#include "Camera.h"
#include"ShaderType.h"
class GraphicObject_TextureLight: public GraphicObject_Base

{
friend class ShaderTextureLight;

public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetTexPath(const LPCWSTR path, int meshnum);
	void SetTexPath(const LPCWSTR path);
	void SetColor(const Vect ambcol, const Vect diffcol, const Vect speccol);
	void SetColor(const Vect ambcol, const Vect diffcol, const Vect speccol, int meshnum);
	void SetWorld(const Matrix m);
	void SetTextureResourceAndSampler(Texture *& tex);
	void SetTextureResourceAndSampler(Texture*& tex, unsigned int meshnum);
	virtual void Render(Camera Cam, Vect spotlightpos);
	virtual void Render_Mesh(Camera Cam, Vect spotlightpos, ID3D11DeviceContext * md3dImmediateContext, unsigned int meshnum = 0);
	bool   isPremade;

	GraphicObject_TextureLight(Texture*& tex, ShaderTextureLight *& shader, Model * mod, ID3D11DeviceContext * md3dImmediateContext = 0,float ispremade = false);

	ID3D11DeviceContext*            md3dIC;
	ShaderTextureLight*				pShader;
private:
	ShaderType*                     ptype;
	Vect							Color;
	Matrix							World;
	//ID3D11DeviceContext*            md3dIC;
	Vect                            eyepos;
	Vect                            ac;
	Vect                            dc;
	Vect                            sc;

	Vect*							MeshColoramb;
	Vect*							MeshColordiff;
	Vect*							MeshColorspec;
	
	Vect							MeshColoramb_premade;
	Vect							MeshColordiff_premade;
	Vect							MeshColorspec_premade;

	Texture*                        Tex;
	LPCWSTR*                        MeshTexpath;
	LPCWSTR							MeshTexpathpremade;

	unsigned int                    Meshcount;
};

#endif _GraphicObject_Color
