#version 330

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform vec4 LightPosition;

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

out vec3 ex_N;
out vec3 ex_V;
out vec3 ex_L;
out vec2 ex_TexCoord;

void main() 
{
	vec4 VertexPosition = ViewMatrix * ModelMatrix * vec4( in_Position, 1.0 );

	ex_V = normalize( -VertexPosition ).xyz;

	mat3 NormalMatrix = mat3( ViewMatrix * ModelMatrix );

	ex_N = normalize( NormalMatrix * in_Normal );

	ex_L = normalize( LightPosition.xyz - VertexPosition.xyz );

	ex_TexCoord = in_TexCoord;

    gl_Position = ProjMatrix * VertexPosition;
}
