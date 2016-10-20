#version 450

layout (location = 0)in vec2 vertPosition;
layout (location = 1)in vec2 vertUV;

out vec2 fragUV;

uniform mat4 projection;

void main() {
	gl_Position = (projection * vec4(vertPosition.xy,1,1));
	fragUV = vec2(vertUV.x,1-vertUV.y);
}