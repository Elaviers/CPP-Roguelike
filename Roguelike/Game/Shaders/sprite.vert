#version 450

layout (location = 0)in vec2 vertPosition;
layout (location = 1)in vec4 vertColour;
layout (location = 2)in vec2 vertUV;

out vec2 fragPosition;
out vec4 fragColour;
out vec2 fragUV;

uniform mat4 projection;
uniform mat4 transform;
uniform vec2 UVOffset;

void main() {
	gl_Position = (projection * transform * vec4(vertPosition.xy,1,1));
	
	fragPosition = vertPosition;
	fragColour = vertColour;
	
	fragUV = vec2(vertUV.x+UVOffset.x,1-(vertUV.y+UVOffset.y));
}