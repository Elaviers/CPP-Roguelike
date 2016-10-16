#version 130

in vec2 vertPosition;
in vec4 vertColour;
in vec2 vertUV;

out vec2 fragPosition;
out vec4 fragColour;
out vec2 fragUV;

uniform mat4 p;

void main() {
	gl_Position = (p * vec4(vertPosition.x,vertPosition.y,0,1));
	
	fragPosition = vertPosition;
	fragColour = vertColour;
	fragUV = vec2(vertUV.x,1-vertUV.y);
}