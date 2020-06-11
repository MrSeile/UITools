#include "ToggleButton.h"

namespace ui {

	ToggleButton::ToggleButton(const std::string& id)
		: UIObject(id)
	{
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(10);

		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color::Black);
	}

	void ToggleButton::CheckInput(const sf::RenderWindow& window, ui::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		{

			if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && m_able && m_hasClickFuncion && !e.handled)
			{
				m_pressed = m_pressed ? false : true;

				if (m_blockEvent)
					e.handled = true;

				m_clickFunction(this, m_pressed);
			}
		}
	}

	void ToggleButton::Update(const sf::RenderWindow& window)
	{
		text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f),
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 1.f));

		if (m_hasCustomUpdateFunction)
		{
			m_updateFunction(this);
		}
	}

	void ToggleButton::SetClickFunction(const std::function<void(UIObject * self, bool pressed)>& function)
	{
		m_hasClickFuncion = true;
		m_clickFunction = function;
	}

	bool ToggleButton::GetAble()
	{
		return m_able;
	}

	void ToggleButton::SetAble(bool able)
	{
		m_able = able;
		text.setFillColor(able ? sf::Color(0, 0, 0) : sf::Color(200, 200, 200));
	}

	void ToggleButton::SetPressed(bool pressed, bool update)
	{
		m_pressed = pressed;
		if (update && m_hasClickFuncion)
			m_clickFunction(this, m_pressed);
	}

	ui::Vec2f ToggleButton::GetPosition()
	{
		return shape.getPosition();
	}

	std::function<void(ToggleButton* self, bool pressed)> ToggleButton::GetClickEvent()
	{
		return m_clickFunction;
	}


	void ToggleButton::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
		window.draw(text);
	}

}