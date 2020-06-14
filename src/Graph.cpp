#include "Graph.h"
#include "Line.h"
#include <cmath>
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

	void Graph::SetPosition(const ui::Vec2f& pos)
	{
		m_pos = pos;
	}

	void Graph::SetSize(const ui::Vec2f& size)
	{
		m_size = size;
	}

	void Graph::SetRange(const ui::Vec2f& xRange, const ui::Vec2f& yRange)
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

	ui::Vec2f Graph::MapPosToCoords(const ui::Vec2f& pos)
	{
		return ui::Vec2f
		(
			map(pos.x, m_xRange.min, m_xRange.max, 0, m_size.x),
			map(pos.y, m_yRange.min, m_yRange.max, m_size.y, 0)
		) + m_pos;
	}

	ui::Vec2f Graph::MapCoordsToPos(const ui::Vec2f& coords)
	{
		return
		{
			map(coords.x - m_pos.x, 0, m_size.x, m_xRange.min, m_xRange.max),
			map(coords.y - m_pos.y, m_size.y, 0, m_yRange.min, m_yRange.max)
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

	void Graph::Plot(const std::vector<ui::Vec2f>& data, const PlotDef& props)
	{
		m_plots.push_back({ data, props });
	}

	void Graph::Arrow(const ui::Vec2f& pos, const ui::Vec2f& size, const ArrowDef& props)
	{
		m_arrows.push_back({ { pos, size }, props });
	}

	void Graph::Fit(const float& margin)
	{
		ui::Vec2f xRange = { INFINITY, -INFINITY };
		ui::Vec2f yRange = { INFINITY, -INFINITY };

		for (auto& [plot, prop] : m_plots)
		{
			for (const ui::Vec2f& p : plot)
			{
				xRange.min = std::min(xRange.min, p.x);
				xRange.max = std::max(xRange.max, p.x);

				yRange.min = std::min(yRange.min, p.y);
				yRange.max = std::max(yRange.max, p.y);
			}
		}

		for (auto& [arrow, prop] : m_arrows)
		{
			auto& [p, size] = arrow;

			xRange.min = std::min(xRange.min, p.x);
			xRange.max = std::max(xRange.max, p.x);

			yRange.min = std::min(yRange.min, p.y);
			yRange.max = std::max(yRange.max, p.y);
		}

		float xMargin = (xRange.max - xRange.min) * margin;
		float yMargin = (yRange.max - yRange.min) * margin;

		xRange.min -= xMargin;
		xRange.max += xMargin;

		yRange.min -= yMargin;
		yRange.max += yMargin;

		SetRange(xRange, yRange);
	}

	ui::Vec2f Graph::CalculateAxisStep()
	{
		ui::Vec2f n(1, 1);
		ui::Vec2f e(1, 1);
		float xDelta = n.x * powf(10.f, e.x);
		float yDelta = n.y * powf(10.f, e.y);
		while (true)
		{
			if (MapPosToCoords({ xDelta, 0 }).x - MapPosToCoords({ 0, 0 }).x < 100)
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

				xDelta = n.x * powf(10, e.x);
			}
			else if (MapPosToCoords({ xDelta, 0 }).x - MapPosToCoords({ 0, 0 }).x > 500)
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

				xDelta = n.x * powf(10, e.x);
			}
			else
				break;
		}
		while (true)
		{
			if (MapPosToCoords({ 0, yDelta }).y - MapPosToCoords({ 0, 0 }).y > -100)
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

				yDelta = n.y * powf(10, e.y);
			}
			else if (MapPosToCoords({ 0, yDelta }).y - MapPosToCoords({ 0, 0 }).y < -500)
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

				yDelta = n.y * powf(10, e.y);
			}
			else
				break;
		}

		return { xDelta, yDelta };
	}

	void Graph::Draw(sf::RenderWindow& window)
	{
		sf::RectangleShape back;
		back.setSize(m_size);
		back.setPosition(m_pos);
		back.setFillColor(m_backColor);
		window.draw(back);

		// Calculate steps
		ui::Vec2f delta = CalculateAxisStep();

		// Draw grid
		for (float x = snap(m_xRange.min, delta.x); x < m_xRange.max; x += delta.x)
		{
			ui::Vec2f p0 = MapPosToCoords({ x, m_yRange.min });
			ui::Vec2f p1 = MapPosToCoords({ x, m_yRange.max });

			ui::Line h("h", p0, p1);
			h.SetColor({ 150, 150, 150 });
			h.SetWidth(m_gridWidth);

			h.Draw(window);
		}
		for (float y = snap(m_yRange.min, delta.y); y < m_yRange.max; y += delta.y)
		{
			ui::Vec2f p0 = MapPosToCoords({ m_xRange.min, y });
			ui::Vec2f p1 = MapPosToCoords({ m_xRange.max, y });

			ui::Line v("v", p0, p1);
			v.SetColor({ 150, 150, 150 });
			v.SetWidth(m_gridWidth);

			v.Draw(window);
		}

		// X axis
		ui::Vec2f axisX1 = MapPosToCoords({ m_xRange.min, 0 });
		ui::Vec2f axisX2 = MapPosToCoords({ m_xRange.max, 0 });

		ui::Line x("x", axisX1, axisX2);
		x.SetColor(m_axisColor);
		x.SetWidth(m_axisWidth);
		x.Draw(window);

		// Y axis
		ui::Vec2f axisY1 = MapPosToCoords({ 0, m_yRange.min });
		ui::Vec2f axisY2 = MapPosToCoords({ 0, m_yRange.max });

		ui::Line y("y", axisY1, axisY2);
		y.SetColor(m_axisColor);
		y.SetWidth(m_axisWidth);
		y.Draw(window);

		// Draw plots
		for (auto&[plot, prop] : m_plots)
		{
			ui::Vec2f prevPos = MapPosToCoords(plot[0]);
			for (uint i = 1; i < plot.size(); i++)
			{
				ui::Vec2f newPos = MapPosToCoords(plot[i]);

				ui::Vec2f delta = newPos - prevPos;

				if (delta.Length() > 5.f)
				{
					ui::Line l("l", prevPos, newPos);
					l.SetWidth(prop.width);
					l.SetColor(prop.color);

					l.Draw(window);

					prevPos = newPos;
				}
			}

			if (prop.cyclic)
			{
				ui::Line l("l", prevPos, MapPosToCoords(plot[0]));
				l.SetWidth(prop.width);
				l.SetColor(prop.color);

				l.Draw(window);
			}
		}

		// Draw arrows
		for (auto&[arrow, prop] : m_arrows)
		{
			auto& [pos, size] = arrow;

			ui::Vec2f iPos = MapPosToCoords(pos);
			ui::Vec2f fPos = MapPosToCoords(pos + size);

			ui::Line l("l", iPos, fPos);
			l.SetWidth(prop.width);
			l.SetColor(prop.color);

			l.Draw(window);
		}
	}


	Graph::~Graph()
	{

	}

}