// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"
#include "Camera.h"
class GraphicObject_ColorLight : public GraphicObject_Base
{
friend class ShaderColor;

public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;  // Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;       // Move assignment operator
	~GraphicObject_ColorLight();		  											 // Destructor

	GraphicObject_ColorLight() = delete;

	void SetWorld(const Matrix& m);
	virtual void Render(Camera Cam, Vect spotlightpos) override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod, ID3D11DeviceContext* md3dImmediateContext,
		const Vect& ambcol, const Vect& diffcol, const Vect& speccol);

private:
	ShaderColorLight*				pShader;
	Vect							Color;
	Matrix							World;
	ID3D11DeviceContext*            md3dIC;
	Vect                            eyepos;
	Vect                            ac;
	Vect                            dc;
	Vect                            sc;
};

#endif _GraphicObject_Color
