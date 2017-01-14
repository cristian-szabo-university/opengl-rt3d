#version 330

uniform sampler2D Texture;

in vec2 ex_TexCoord;

out vec4 out_Colour;

void main()
{
	out_Colour = vec4( 0, 0, 0, texture2D( Texture, ex_TexCoord ).r );
}
