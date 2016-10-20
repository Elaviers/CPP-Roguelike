#version 130

in vec2 fragPosition;
in vec4 fragColour;
in vec2 fragUV;

out vec4 colour;

uniform float time;
uniform sampler2D sTexture;

void main() {
	
	colour = fragColour * vec4(	fragColour.r * (fragPosition.x + sin(time) * .5 + .5) * cos(fragPosition.x * 3.1415 + time) * .5 + .5,
					fragColour.g * (fragPosition.y + sin(1+time*2) * .5 + .5) * cos(fragPosition.y * 1.5707 + time) * .5 + .5,
					fragColour.b * (fragPosition.x + cos(2+time*4) * .5 + .5) * sin(((fragPosition.x + fragPosition.y)/2) * 8 + time) * .5 + .5,
					1);
}