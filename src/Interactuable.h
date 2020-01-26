#pragma once

#include "Global.h"
#include "Event.h"

namespace ui {

	class Interactuable
	{
	protected:
		bool m_blockEvent = true;

	public:
		Interactuable();

		virtual void CheckInput(const sf::RenderWindow& window, ui::Event& e) = 0;
		void BlockEvent(bool block);

		~Interactuable();
	};
}
