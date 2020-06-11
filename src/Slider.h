#pragma once

#include "Global.h"
#include "UIObject.h"
#include "Interactuable.h"

namespace ui
{
	class Slider : public ui::UIObject, public ui::Interactuable
	{
	private:
		bool m_pressed = false;
		float m_value = 0;
		float m_offset = 0;
		bool m_showValue = true;
		ui::Vec2f m_range = { 0, 255 };
		float m_step = 0.1f;

		sf::RectangleShape m_slider;
		sf::Text m_text;
		sf::RectangleShape m_body;

	public:
		Slider(const std::string& id, const sf::Font& font);

		// General
		void CheckInput(const sf::RenderWindow& window, ui::Event& e) override;
		void Update(const sf::RenderWindow& window) override;
		void Draw(sf::RenderWindow& window) override;

		// Set
		void SetValue(const float& value);
		void SetPosition(const ui::Vec2f& position);
		void SetPosition(const float& x, const float& y);
		void SetSize(const float& width, const float& heigth);
		void SetSize(const ui::Vec2f& size);
		void SetStep(const float& step);
		void SetRange(const ui::Vec2f& range);

		void ShowValue(bool show);

		// Get
		ui::Vec2f GetRange();
		sf::RectangleShape& GetBody();
		sf::RectangleShape& GetHandle();
		sf::Text& GetText();

		// Get
		float GetValue() const;
		bool IsPressed() const;
	};
}