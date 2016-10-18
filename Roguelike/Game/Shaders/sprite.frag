#version 130

in vec2 fragPosition;
in vec4 fragColour;
in vec2 fragUV;

out vec4 colour;

uniform float time;
uniform sampler2D sTexture;

void main() {

	vec4 textureColour = texture(sTexture,fragUV);
	colour = textureColour * fragColour;
}