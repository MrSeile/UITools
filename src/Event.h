#pragma once
#include "UIObject.h"

namespace ui {
	class Event : public sf::Event
	{
	public:
		bool handled = false;
	};
}


