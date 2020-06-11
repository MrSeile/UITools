#include "InteractiveGraph.h"

namespace ui {
	InteractiveGraph::InteractiveGraph(const std::string& id)
		: Graph(id)
		, m_zoom(2)
		, m_center(0, 0)
		, m_view(-m_zoom, m_zoom)
		, m_mousePressed(false)
		, m_aspect(1)
	{
	}

	void InteractiveGraph::UpdateView()
	{
		SetRange(ui::Vec2f(m_center.x, m_center.x) + m_view * m_aspect, ui::Vec2f(m_center.y, m_center.y) + m_view);
	}

	void InteractiveGraph::Update(const sf::RenderWindow& window)
	{
		ui::Vec2f windowSize = (ui::Vec2f)window.getSize();

		m_aspect = windowSize.x / windowSize.y;

		if (m_mousePressed)
		{
			ui::Vec2f mousePos = MapCoordsToPos((ui::Vec2f)sf::Mouse::getPosition(window));
			ui::Vec2f delta = MapCoordsToPos(m_startPos) - mousePos;
			m_center += delta;

			m_startPos = (ui::Vec2f)sf::Mouse::getPosition(window);
		}

		UpdateView();
	}

	void InteractiveGraph::CheckInput(const sf::RenderWindow& window, ui::Event& e)
	{
		if (e.type == sf::Event::MouseWheelMoved)
		{
			switch (e.mouseWheel.delta)
			{
			case 1:
				m_zoom /= 1.2f;
				break;

			case -1:
				m_zoom *= 1.2f;
				break;

			default:
				break;
			}

			m_view = { -m_zoom, m_zoom };

			// Zoom where the mouse is
			ui::Vec2f iMousePos = MapCoordsToPos((ui::Vec2f)sf::Mouse::getPosition(window));

			UpdateView();

			ui::Vec2f fMousePos = MapCoordsToPos((ui::Vec2f)sf::Mouse::getPosition(window));

			ui::Vec2f delta = fMousePos - iMousePos;

			m_center -= delta;
		}

		if (e.type == sf::Event::MouseButtonPressed && e.key.code == sf::Mouse::Left && !e.handled)
		{
			m_mousePressed = true;
			m_startPos = (ui::Vec2f)sf::Mouse::getPosition(window);
		}

		if (e.type == sf::Event::MouseButtonReleased && e.key.code == sf::Mouse::Left)
		{
			m_mousePressed = false;
		}
	}

	void InteractiveGraph::SetCenter(const ui::Vec2f& center)
	{
		m_center = center;

		UpdateView();
	}

}