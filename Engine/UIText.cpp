#include "UIText.h"

#include "RenderType.h"
#include "ResourceManager.h"

using namespace GUI;

void UIText::setFont(const std::string& path) {
	_font = ResourceManager::getFontRef(path);
}

void UIText::render(Shader *shader) {
	if (!_font->loaded) {
		std::printf("Warning:attempted to render UIText without a loaded font!\n");
		return;
	}

	if (shader && shader->Channel == RenderTypes::FONT)
		_font->drawString(text, _min.x * cameraScale.x, _min.y * cameraScale.y,
		(text.length() * cameraScale.y * getHeight() > cameraScale.x * getWidth()) ? (int)((cameraScale.x * getWidth()) / text.length()) : (int)(cameraScale.y * getHeight()),
			_colour.vec4(), *shader);
}
