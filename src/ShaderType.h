// GraphicObject
// Andre Berthiaume, July 2016

#ifndef _ShaderType
#define _ShaderType

#include "Matrix.h"
#include "Camera.h"
#include "Texture.h"
#include "ShaderTextureLight.h"
#include "ShaderColorLight.h"
class Model;
class ShaderMeshData;
struct ID3D11DeviceContext;
class ShaderBase;

class ShaderType : public Align16 
{
public:
	ShaderType(const ShaderType&) = delete;				   // Copy constructor
	ShaderType(ShaderType&&) = default;                    // Move constructor
	ShaderType& operator=(const ShaderType&) & = default;  // Copy assignment operator
	ShaderType& operator=(ShaderType&&) & = default;       // Move assignment operator
	~ShaderType() = default;		  							   // Destructor
	ShaderType() = default;

	ShaderTextureLight* stl;
	ShaderColorLight* scl;
};
#endif _ShaderType