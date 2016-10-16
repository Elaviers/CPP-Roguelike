#version 130

in vec2 vertPosition;
in vec4 vertColour;
in vec2 vertUV;

out vec2 fragPosition;
out vec4 fragColour;
out vec2 fragUV;

void main() {
	gl_Position.xy = vertPosition;
	gl_Position.z = 0;
	gl_Position.w = 1;
	
	fragPosition = vertPosition;
	fragColour = vertColour;
	fragUV = vec2(vertUV.x,1-vertUV.y);
}