#version 450

in vec2 fragUV;

out vec4 colour;

uniform sampler2D sTexture;
uniform vec4 TextColour;

void main() {
	vec4 textureColour = vec4(1,1,1,texture(sTexture,fragUV).r);
	colour = TextColour * textureColour;
}