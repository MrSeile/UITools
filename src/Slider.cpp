#include "Slider.h"

namespace ui {

	Slider::Slider(const std::string& id, const sf::Font& font)
		: UIObject(id)
	{
		m_body.setFillColor(sf::Color::White);
		m_body.setOutlineColor(sf::Color::Black);
		m_body.setOutlineThickness(1);
		m_body.setSize(ui::Vec2f(500, 20));
		m_slider.setFillColor(sf::Color::Red);
		m_slider.setSize(ui::Vec2f(10, 20));

		m_text.setFont(font);
		m_text.setFillColor(sf::Color::White);
	}

	void Slider::CheckInput(const sf::RenderWindow& window, ui::Event& e)
	{
		if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left)
		{
			if (m_slider.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && !e.handled)
			{
				if (m_blockEvent)
					e.handled = true;

				m_pressed = true;
				m_offset = (float)(sf::Mouse::getPosition(window).x - window.mapCoordsToPixel(m_slider.getPosition()).x);
			}
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.key.code == sf::Mouse::Left)
			{
				m_pressed = false;
			}
		}
	}

	void Slider::Update(const sf::RenderWindow& window)
	{
		if (m_pressed)
		{
			m_value = map((window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - m_body.getPosition().x - m_offset), 0.f, m_body.getSize().x - m_slider.getSize().x, 0.f, 1.f);

			if (m_value < 0)
			{
				m_value = 0;
			}
			else if (map(m_value, 0.f, 1.f, 0.f, m_body.getSize().x - m_slider.getSize().x) > (m_body.getSize().x) - m_slider.getSize().x)
			{
				m_value = 1;
			}

			m_value = map(snap(map(m_value, 0.f, 1.f, m_range.min, m_range.max), m_step), m_range.min, m_range.max, 0.f, 1.f);
		}

		if (m_hasCustomUpdateFunction)
		{
			m_updateFunction(this);
		}

		m_text.setCharacterSize((uint)(m_body.getSize().y + m_body.getSize().y * 0.3f));
		std::stringstream text;
		text << std::fixed << std::setprecision(3) << map(m_value, 0.f, 1.f, m_range.min, m_range.max);
		m_text.setString(text.str());
		m_text.setPosition((ui::Vec2f(m_body.getPosition().x + m_body.getSize().x + 10, m_body.getPosition().y - m_body.getSize().y * 0.3f)));

		m_slider.setSize(ui::Vec2f(m_slider.getSize().x, m_body.getSize().y));
		m_slider.setPosition(m_body.getPosition().x + map(m_value, 0.f, 1.f, 0.f, m_body.getSize().x - m_slider.getSize().x), m_body.getPosition().y);
	}

	void Slider::Draw(sf::RenderWindow& window)
	{
		if (m_showValue)
		{
			window.draw(m_text);
		}

		window.draw(m_body);
		window.draw(m_slider);
	}

	void Slider::SetValue(const float& value)
	{
		m_value = value;
	}

	void Slider::SetPosition(const ui::Vec2f& position)
	{
		m_body.setPosition(position);
	}

	void Slider::SetPosition(const float& x, const float& y)
	{
		m_body.setPosition(x, y);
	}

	void Slider::SetSize(const float& width, const float& heigth)
	{
		m_body.setSize(ui::Vec2f(width, heigth));
	}

	void Slider::SetSize(const ui::Vec2f& size)
	{
		m_body.setSize(size);
	}

	void Slider::SetStep(const float& step)
	{
		m_step = step;
	}

	void Slider::SetRange(const ui::Vec2f& range)
	{
		m_range = range;
	}

	void Slider::ShowValue(bool show)
	{
		m_showValue = show;
	}

	ui::Vec2f Slider::GetRange()
	{
		return m_range;
	}

	sf::RectangleShape& Slider::GetBody()
	{
		return m_body;
	}

	sf::RectangleShape& Slider::GetHandle()
	{
		return m_slider;
	}

	sf::Text& Slider::GetText()
	{
		return m_text;
	}

	float Slider::GetValue() const
	{
		return map(m_value, 0.f, 1.f, m_range.min, m_range.max);
	}

	bool Slider::IsPressed() const
	{
		return m_pressed;
	}

}