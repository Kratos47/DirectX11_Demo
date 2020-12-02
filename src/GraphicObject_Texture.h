// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
class GraphicObject_Texture : public GraphicObject_Base
{
friend class ShaderColor;

public:
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				 // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) & = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) & = default;       // Move assignment operator
	~GraphicObject_Texture();		  											 // Destructor

	GraphicObject_Texture() = delete;

	void SetTexPath(const LPCWSTR& path, int meshnum);
	void SetTexPath(const LPCWSTR& path);
	void SetWorld(const Matrix& m);
	virtual void Render(Camera Cam, Vect spotlightpos) override;

	GraphicObject_Texture(ShaderTexture* shader, Texture* pTex , Model* mod, ID3D11DeviceContext* md3dImmediateContext);

private:
	ShaderTexture*					pShader;
	ID3D11DeviceContext*            md3dIC;
	Matrix							World;
	Texture*				        pTex;
	LPCWSTR*						MeshTexpath;

};

#endif _GraphicObject_Color
