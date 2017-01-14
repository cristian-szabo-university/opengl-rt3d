#version 330

uniform mat4 ProjMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

in vec3 in_Position;
in vec2 in_TexCoord;

out vec2 ex_TexCoord;

void main()
{
	ex_TexCoord = in_TexCoord;
	
	gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4( in_Position, 1.0 );
}
