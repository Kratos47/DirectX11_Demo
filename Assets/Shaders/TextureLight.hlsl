#pragma pack_matrix( row_major )

// Material properties
struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;  // Hack: w holds the specular power
};

// Light properties
struct PhongADS
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};

// Basic Phong Illumination computation
void PhongModel(
	Material mat,
	PhongADS lightint,
	float3 L,
	float3 normal,
	float3 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// every light source adds to the ambient light total
	ambient = mat.Ambient * lightint.Ambient;

	float diffuseFactor = dot(L, normal);

	// Diffuse and specular contribution only if not facing away from light source
	if (diffuseFactor > 0.0f)
	{
		diffuse = diffuseFactor * mat.Diffuse * lightint.Diffuse;

		float3 r = reflect(-L, normal);		// Compute the reflected ray of light
		float spec_val = max(dot(r, DirToEye.xyz), 0);
		float specFactor = pow(spec_val, mat.Specular.w);
		spec = specFactor * mat.Specular * lightint.Specular;
	}
	else
	{
		diffuse = float4(0, 0, 0, 0);
		spec = float4(0, 0, 0, 0);
	}
}

// Directional Light Data
struct DirectionalLight
{
	PhongADS LightInt;
	float4 Direction[2];
};

// Point Light data
struct PointLight
{
	PhongADS LightInt;
	float4 Position[2];
	float4 Attenuation;
	float Range;
};

// Spot light data
struct SpotLight
{
	PhongADS LightInt;
	float4 Position[4];
	float4 Attenuation;
	float4 Direction;
	float SpotExp;
	float Range;
};

Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);

//  Constant Buffers
cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

cbuffer LightParameters : register (b1)
{
	DirectionalLight DirLight;
	PointLight PntLight;
	SpotLight SpLight;
	float4 EyePosWorld;
};

cbuffer InstanceData : register(b2)
{
	float4x4 World;
	float4x4 WorldInv;
	Material Mater;
};

cbuffer Fog : register(b3)
{
	float FogStart;
	float FogRange;
	float4 FogColor;
};

// Directional Light Computation
void ComputeDirectionalLight(
	Material mat,
	DirectionalLight DirLit,
	float3 direction,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the initial ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute ligth in the model-space 
	// For directional light, the source is infinitely far, so translation have no effect
	float3 L = normalize(mul(direction, (float3x3)WorldInv));
	PhongModel(mat, DirLit.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);
}


// Point Light Computation
void ComputePointLight(
	Material mat,
	PointLight PLight,
	float4 position,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute the model-space position
	float3 litPosMS = mul(position , WorldInv).xyz;
	float3 L = litPosMS - posms.xyz;

	// Early out if out of range
	float d = length(L);
	if (d > PLight.Range)
		return;

	L /= d;	// normalize 

	PhongModel(mat, PLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	// Now we attenuate based on range
	float att = 1 / dot(PLight.Attenuation.xyz, float3(1, d, d*d));
	// Ambient not attenuated
	diffuse *= att;
	spec *= att;
}

// Spot Light Computation
void ComputeSpotLight(
	Material mat,
	SpotLight SptLight,
	float4 position,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// ****** Same calculations as Point Light  ****

	// we compute the model-space position
	float3 litPosMS = mul(position, WorldInv).xyz;
	float3 L = litPosMS - posms.xyz;

	float d = length(L);
	if (d > SptLight.Range)
		return;

	L /= d;  // normalize 

	PhongModel(mat, SptLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	// Now we attenuate based on range
	float att = 1 / dot(SptLight.Attenuation.xyz, float3(1, d, d*d));

	// Ambient not attenuated
	diffuse *= att;
	spec *= att;

	// *****************************************

	// now we compute the spotlight factor
	float4 msLitDir = SptLight.Direction;
	msLitDir.w = 0; // making sure we have a vector and not a point
	msLitDir = normalize(mul(msLitDir, WorldInv));
	float spot = pow(max(dot(-L, msLitDir.xyz), 0), SptLight.SpotExp);

	ambient *= spot;
	diffuse *= spot;
	spec *= spot;
}

void CalculateFog(float4 msEyePos, float4 MSPos, out float FogPercent)
{
	/****************************************************/
	// Fog Demo
	
	// These three values should be passed-in using cbuffers
	//float FogStart = 5;	// anything closer than this value will have no fog
	float fogStart = FogStart;
	float fogRange = FogRange;	// fog contribution increases linearly until full fog at dist = FogStart + Range
	//float4 FogColor = float4(.2,.2,.2, 1); // grey
	//float4 fogColor = float4(0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f); // MidnightBlue
	//float4 fogColor = FogColor;
	if (fogStart <= 0 && fogRange <= 0)
	{
		fogStart = 30000.0f;
		fogRange = 30000.0f;
	}
	// Compute fog density as function of distance to eye
	float distToEye = length(msEyePos - MSPos);
	FogPercent = saturate((distToEye - fogStart) / fogRange);  // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx

	// blend litcolor with fog level
	// C_src = FogColor
	// C_dst = litColor
	// C = C_src * fogPercent + C_dst * (1 - fogPercent)
}
// ******* Shader operations

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float2 Tex : TEXCOORD;
	float4 Norm : NORMAL;

};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD, float4 nor : NORMAL)
{
	VS_OUTPUT output;
	output.PosMS = Pos;  // We pass along the raw model space position 
	output.Norm = nor;	 // and the face normal

	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Tex = Tex;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	// Compute light values in model-space
	float4 msEyePos = mul(EyePosWorld, WorldInv);
	float4 msDirToEye = normalize(msEyePos - input.PosMS);

	float4 ambient = float4(0, 0, 0, 0);
	float4 diffuse = float4(0, 0, 0, 0);
	float4 spec = float4(0, 0, 0, 0);

	float4 A, D, S;

	for (int i = 0; i < 2; i++)
	{
		ComputeDirectionalLight(Mater, DirLight, DirLight.Direction[i].xyz, normalize(input.Norm), msDirToEye, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;

	}
	for (int i = 0; i < 2; i++)
	{
		ComputePointLight(Mater, PntLight, PntLight.Position[i], input.PosMS, normalize(input.Norm), msDirToEye, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;

	}

	for (int i = 0; i < 4; i++)
	{
		ComputeSpotLight(Mater, SpLight, SpLight.Position[i],input.PosMS, normalize(input.Norm), msDirToEye, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;
	}
	float4 litColor = ambient + diffuse + spec;

	float FogPercent;
	
	//functioin to calculate Fog
	CalculateFog(msEyePos, input.PosMS, FogPercent);
	FogPercent += FogPercent;

	litColor = lerp(litColor, FogColor, FogPercent);				// See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509618(v=vs.85).aspx
	/****************************************************/
	return litColor * mainTexture.Sample(aSampler, input.Tex);
}
