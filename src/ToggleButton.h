#pragma once

#include "Global.h"
#include "UIObject.h"
#include "Interactuable.h"

namespace ui
{
	class ToggleButton : public ui::UIObject, public ui::Interactuable
	{
	private:
		std::function<void(ui::UIObject* self, bool pressed)> m_clickFunction;

		bool m_hasClickFuncion = false;
		bool m_able = true;
		bool m_pressed = false;

	public:
		// Constructor
		ToggleButton(const std::string& id);

		// Generals
		void CheckInput(const sf::RenderWindow& window, ui::Event& e) override;
		void Update(const sf::RenderWindow& window) override;
		void Draw(sf::RenderWindow& window) override;

		// Set
		void SetClickFunction(const std::function<void(ui::UIObject* self, bool pressed)>& function);
		void SetAble(bool able);
		void SetPressed(bool pressed, bool update = true);

		// Get
		bool GetAble();
		std::function<void(ToggleButton* self , bool pressed)> GetClickEvent();
		ui::Vec2f GetPosition();

		// Variables
		sf::Text text;
		sf::RectangleShape shape;
	};

}