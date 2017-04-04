#include "Shader.h"

const char* Shader::Presets::SPRITE_VERT = R"(
		#version 450
		layout(location = 0)in vec2 vertPosition;
		layout(location = 1)in vec4 vertColour;
		layout(location = 2)in vec2 vertUV;
		out vec2 fragPosition;
		out vec4 fragColour;
		out vec2 fragUV;
		uniform mat4 projection;
		void main() {
			gl_Position = (projection * vec4(vertPosition.xy, 1, 1));
			fragPosition = vertPosition;
			fragColour = vertColour;
			fragUV = vec2(vertUV.x, 1 - vertUV.y);
		})";

const char* Shader::Presets::TRANSFORMED_SPRITE_VERT = R"(
		#version 450
		layout(location = 0)in vec2 vertPosition;
		layout(location = 1)in vec4 vertColour;
		layout(location = 2)in vec2 vertUV;
		out vec2 fragPosition;
		out vec4 fragColour;
		out vec2 fragUV;
		uniform mat4 projection;
		uniform mat4 transform;
		uniform vec2 UVOffset;
		void main() {
			gl_Position = (projection * transform * vec4(vertPosition.xy, 1, 1));
			fragPosition = vertPosition;
			fragColour = vertColour;
			fragUV = vec2(vertUV.x + UVOffset.x, 1 - (vertUV.y + UVOffset.y));
		})";

const char* Shader::Presets::SPRITE_FRAG = R"(
		#version 130
		in vec2 fragPosition;
		in vec4 fragColour;
		in vec2 fragUV;
		out vec4 colour;
		uniform float time;
		uniform sampler2D sTexture;
		void main() {
			vec4 textureColour = texture(sTexture, fragUV);
			colour = textureColour * fragColour;
		})";

const char* Shader::Presets::LINE_VERT = R"(
		#version 130
		in vec2 vertPosition;
		in vec4 vertColour;
		out vec4 fragColour;
		uniform mat4 projection;
		void main() {
			gl_Position = projection * vec4(vertPosition.xy,0,1);
			fragColour = vertColour;
		}
	)";
const char* Shader::Presets::LINE_FRAG = R"(
		#version 130
		in vec4 fragColour;
		out vec4 colour;
		void main() {
			colour = fragColour;
		}
	)";

const char* Shader::Presets::FONT_VERT = R"(
		#version 450

		layout (location = 0)in vec2 vertPosition;
		layout (location = 1)in vec2 vertUV;

		out vec2 fragUV;

		uniform mat4 projection;

		void main() {
			gl_Position = (projection * vec4(vertPosition.xy,1,1));
			fragUV = vec2(vertUV.x,1-vertUV.y);
	})";

const char* Shader::Presets::FONT_FRAG = R"(
		#version 450

		in vec2 fragUV;

		out vec4 colour;

		uniform sampler2D sTexture;
		uniform vec4 TextColour;

		void main() {
			vec4 textureColour = vec4(1,1,1,texture(sTexture,fragUV).r);
			colour = TextColour * textureColour;
})";
