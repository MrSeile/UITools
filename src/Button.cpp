#include "Button.h"

namespace ui {

	Button::Button(const std::string& id)
		: UIObject(id)
	{
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(10);

		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color::Black);
	}

	void Button::CheckInput(const sf::RenderWindow& window, ui::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		{

			if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && m_able && m_hasClickFuncion && !e.handled)
			{
				if (m_blockEvent)
					e.handled = true;

				m_clickFunction(this);
			}
		}
	}

	void Button::Update(const sf::RenderWindow& window)
	{
		text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f),
			shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 1.f));

		if (m_hasCustomUpdateFunction)
		{
			m_updateFunction(this);
		}
	}

	void Button::SetClickFunction(const std::function<void(UIObject* self)>& function)
	{
		m_hasClickFuncion = true;
		m_clickFunction = function;
	}

	bool Button::GetAble()
	{
		return m_able;
	}

	void Button::SetAble(const bool& able)
	{
		m_able = able;
		text.setFillColor(able ? sf::Color(0, 0, 0) : sf::Color(200, 200, 200));
	}

	ui::Vec2f Button::GetPosition()
	{
		return shape.getPosition();
	}

	std::function<void(Button* self)> Button::GetClickEvent()
	{
		return m_clickFunction;
	}


	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
		window.draw(text);
	}

}