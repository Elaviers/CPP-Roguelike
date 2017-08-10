#pragma once
#include "UIElement.h"

#include <vector>

namespace GUI {
	class UIContainer : public UIElement
	{
	protected:
		std::vector<UIElement*> _elements;
	public:
		UIContainer(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		virtual ~UIContainer();

		void addElement(UIElement& element, const bool recalc = true) { _elements.push_back(&element); element.setParent(this, recalc); };
		void addElement(UIElement* elementp, const bool recalc = true) { _elements.push_back(elementp); elementp->setParent(this, recalc); };
		std::vector<UIElement*>* getChildren() { return &_elements; };
		void deleteChildren();
		void removeElement(UIElement* element);
		
		void render(Shader *shader) override;
		bool click() override;
		bool isOverlapping(const int x, const int y) override;//returns true if any of the children of this root overlap with the point given
		void calculate() override;
	};
}
