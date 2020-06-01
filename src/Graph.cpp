#include "Graph.h"
#include "Line.h"
#include <cmath>
#include "../../utility/utility.h"
#include "Global.h"

namespace ui {

	Graph::Graph(const std::string& id)
		: UIObject(id)
		, m_pos(0, 0)
		, m_size(100, 100)
		, m_backColor(sf::Color::White)
		, m_axisColor({ 10, 10, 10 })
		, m_axisWidth(2)
		, m_gridWidth(1)
	{

	}

	void Graph::SetPosition(const sf::Vector2f& pos)
	{
		m_pos = pos;
	}

	void Graph::SetSize(const sf::Vector2f& size)
	{
		m_size = size;
	}

	void Graph::SetRange(const sf::Vector2f& xRange, const sf::Vector2f& yRange)
	{
		m_xRange = xRange;
		m_yRange = yRange;
	}

	void Graph::SetBackgrowndColor(const sf::Color& color)
	{
		m_backColor = color;
	}

	void Graph::SetAxisColor(const sf::Color& color)
	{
		m_axisColor = color;
	}

	void Graph::SetAxisWidth(const float& width)
	{
		m_axisWidth = width;
	}

	sf::Vector2f Graph::MapPosToCoords(const sf::Vector2f& pos)
	{
		return
		{
			map(pos.x, m_xRange.x, m_xRange.y, 0, m_size.x),
			map(pos.y, m_yRange.x, m_yRange.y, m_size.y, 0)
		};
	}

	sf::Vector2f Graph::MapCoordsToPos(const sf::Vector2f& coords)
	{
		return
		{
			map(coords.x, 0, m_size.x, m_xRange.x, m_xRange.y),
			map(coords.y, m_size.y, 0, m_yRange.x, m_yRange.y)
		};
	}

	void Graph::ClearAll()
	{
		m_plots.clear();
		m_arrows.clear();
	}

	void Graph::ClearArrows()
	{
		m_arrows.clear();
	}

	void Graph::ClearPlots()
	{
		m_plots.clear();
	}

	void Graph::Plot(const std::vector<sf::Vector2f>& data, const PlotDef& props)
	{
		m_plots.push_back({ data, props });

		std::vector<float> x;
		std::vector<float> y;
		for (auto& p : data)
		{
			x.push_back(p.x);
			y.push_back(p.y);
		}
	}

	void Graph::Arrow(const sf::Vector2f& pos, const sf::Vector2f& size, const ArrowDef& props)
	{
		m_arrows.push_back({ { pos, size }, props });
	}

	sf::Vector2f Graph::CalculateAxisStep()
	{
		sf::Vector2f n(1, 1);
		sf::Vector2f e(1, 1);
		sf::Vector2f delta(n.x * powf(10.f, e.x), n.y * powf(10.f, e.y));
		while (true)
		{
			if (MapPosToCoords({ delta.x, 0 }).x - MapPosToCoords({ 0, 0 }).x < 100)
			{
				switch ((int)n.x)
				{
				case 1:
					n.x = 2;
					break;
				case 2:
					n.x = 5;
					break;
				case 5:
					n.x = 1;
					e.x += 1;
				}

				delta = { n.x * powf(10, e.x), n.y * powf(10, e.y) };
			}
			else if (MapPosToCoords({ delta.x, 0 }).x - MapPosToCoords({ 0, 0 }).x > 500)
			{
				switch ((int)n.x)
				{
				case 1:
					n.x = 5;
					e.x -= 1;
					break;
				case 2:
					n.x = 1;
					break;
				case 5:
					n.x = 2;
				}

				delta = { n.x * powf(10, e.x), n.y * powf(10, e.y) };
			}
			else
				break;
		}
		while (true)
		{
			if (MapPosToCoords({ 0, delta.y }).y - MapPosToCoords({ 0, 0 }).y > -100)
			{
				switch ((int)n.y)
				{
				case 1:
					n.y = 2;
					break;
				case 2:
					n.y = 5;
					break;
				case 5:
					n.y = 1;
					e.y += 1;
				}

				delta = { n.x * powf(10, e.x), n.y * powf(10, e.y) };
			}
			else if (MapPosToCoords({ 0, delta.y }).y - MapPosToCoords({ 0, 0 }).y < -500)
			{
				switch ((int)n.y)
				{
				case 1:
					n.y = 5;
					e.y -= 1;
					break;
				case 2:
					n.y = 1;
					break;
				case 5:
					n.y = 2;
				}

				delta = { n.x * powf(10, e.x), n.y * powf(10, e.y) };
			}
			else
				break;
		}

		return delta;
	}

	void Graph::Draw(sf::RenderWindow& window)
	{
		sf::RectangleShape back;
		back.setSize(m_size);
		back.setPosition(m_pos);
		back.setFillColor(m_backColor);
		window.draw(back);

		// Calculate steps
		sf::Vector2f delta = CalculateAxisStep();

		// Draw grid
		for (float x = snap(m_xRange.x, delta.x); MapPosToCoords({ x, 0 }).x < m_size.x; x += delta.x)
		{
			sf::Vector2f p0(MapPosToCoords({ x, 0 }).x, 0);
			sf::Vector2f p1(MapPosToCoords({ x, 0 }).x, m_size.y);

			ui::Line h("h", p0 + m_pos, p1 + m_pos);
			h.SetColor({ 150, 150, 150 });
			h.SetWidth(m_gridWidth);

			h.Draw(window);
		}
		for (float y = snap(m_yRange.x, delta.y); MapPosToCoords({ 0, y }).y > 0; y += delta.y)
		{
			sf::Vector2f p0(0, MapPosToCoords({ 0, y }).y);
			sf::Vector2f p1(m_size.x, MapPosToCoords({ 0, y }).y);

			ui::Line v("v", p0 + m_pos, p1 + m_pos);
			v.SetColor({ 150, 150, 150 });
			v.SetWidth(m_gridWidth);

			v.Draw(window);
		}

		// X axis
		sf::Vector2f axisX1;
		axisX1.x = 0;
		axisX1.y = MapPosToCoords({ 0, 0 }).y;

		sf::Vector2f axisX2;
		axisX2.x = m_size.x;
		axisX2.y = MapPosToCoords({ 0, 0 }).y;

		ui::Line x("x", axisX1 + m_pos, axisX2 + m_pos);
		x.SetColor(m_axisColor);
		x.SetWidth(m_axisWidth);
		x.Draw(window);

		// Y axis
		sf::Vector2f axisY1;
		axisY1.x = MapPosToCoords({ 0, 0 }).x;
		axisY1.y = 0;

		sf::Vector2f axisY2;
		axisY2.x = MapPosToCoords({ 0, 0 }).x;
		axisY2.y = m_size.y;

		ui::Line y("y", axisY1 + m_pos, axisY2 + m_pos);
		y.SetColor(m_axisColor);
		y.SetWidth(m_axisWidth);
		y.Draw(window);

		// Draw plots
		for (auto&[l, p] : m_plots)
		{
			for (uint i = 1; i < l.size(); i++)
			{
				sf::Vector2f p0 = MapPosToCoords(l[i - 1]);
				sf::Vector2f p1 = MapPosToCoords(l[i]);

				ui::Line l("l", p0 + m_pos, p1 + m_pos);
				l.SetWidth(p.width);
				l.SetColor(p.color);

				l.Draw(window);
			}
		}

		// Draw arrows
		for (auto&[a, p] : m_arrows)
		{
			auto& [pos, size] = a;

			sf::Vector2f iPos = MapPosToCoords(pos);
			sf::Vector2f fPos = MapPosToCoords(pos + size);

			sf::Vector2f delta = fPos - iPos;

			sf::RectangleShape shape;
			shape.setFillColor(p.color);

			float length = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

			shape.setSize({ length, p.width });
			shape.setOrigin(0, shape.getSize().y / 2.f);
			shape.setPosition(iPos);

			float r = (atan2f(delta.y, delta.x) * 180.f) / (float)PI;
			shape.setRotation(r);

			window.draw(shape);
		}
	}


	Graph::~Graph()
	{

	}

}