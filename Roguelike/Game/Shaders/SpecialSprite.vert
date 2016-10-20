#version 450

layout (location = 0)in vec2 vertPosition;
layout (location = 1)in vec4 vertColour;
layout (location = 2)in vec2 vertUV;

out vec2 fragPosition;
out vec4 fragColour;
out vec2 fragUV;

uniform mat4 p;
uniform mat4 transform;

void main() {
	gl_Position = (p * transform * vec4(vertPosition.xy,0,1));
	
	fragPosition = vertPosition;
	fragColour = vertColour;
	fragUV = vec2(vertUV.x,1-vertUV.y);
}