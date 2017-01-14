#version 330

struct LightStruct
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
};

struct MaterialStruct
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	float Shininess;
};

uniform LightStruct Light;
uniform MaterialStruct Material;
uniform sampler2D Texture;

in vec3 ex_N;
in vec3 ex_V;
in vec3 ex_L;
in vec2 ex_TexCoord;

out vec4 out_Colour;
 
void main()
{
	vec4 AmbientI = Light.Ambient * Material.Ambient;

	vec4 DiffuseI = Light.Diffuse * Material.Diffuse;

	DiffuseI = DiffuseI * max( dot( normalize( ex_N ), normalize( ex_L ) ), 0 );

	vec3 R = normalize( reflect( normalize( -ex_L ), normalize( ex_N ) ) );

	vec4 SpecularI = Light.Specular * Material.Specular;

	SpecularI = SpecularI * pow( max( dot( R, ex_V ), 0 ), Material.Shininess );

	out_Colour = ( AmbientI + DiffuseI + SpecularI ) * texture( Texture, ex_TexCoord );
}
