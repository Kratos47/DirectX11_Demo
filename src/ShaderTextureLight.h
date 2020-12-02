#ifndef _ShaderTextureLight
#define _ShaderTextureLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"
#include "DirectXTex.h"
struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTextureLight : public ShaderBase
{
public:
	ShaderTextureLight(const ShaderTextureLight&) = delete;				 // Copy constructor
	ShaderTextureLight(ShaderTextureLight&&) = default;                    // Move constructor
	ShaderTextureLight& operator=(const ShaderTextureLight&) & = default;  // Copy assignment operator
	ShaderTextureLight& operator=(ShaderTextureLight&&) & = default;       // Move assignment operator
	~ShaderTextureLight();		  							         // Destructor

	ShaderTextureLight(ID3D11Device* device);
	

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;
	void SetDirectionalLightParameters(const Vect dir[2], const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect pos[2], float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect pos[4], float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

	void SetTextureResourceAndSampler(Texture *& tex, LPCWSTR filepath, D3D11_FILTER filter, UINT isotropic_level,
	bool ComputeMip, size_t miplevel, DirectX::TEX_FILTER_FLAGS filterflags);
	void SetToContext(Texture *& tex);
	void SendFogProperties(const float& FogStart = 1000000.0f, const float&FogRange = 1000000.0f, const Vect& FogColor = Vect(1.0f, 1.0f, 1.0f));

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};



	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction[2];
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position[2];
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position[4];
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData;

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight;
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;
	struct Fog
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};
	ID3D11Buffer*  mpBufferFog;
};
#endif _ShaderTextureLight