#include "Line.h"

namespace ui {

	void Line::Reset()
	{
		ui::Vec2f delta = m_fPos - m_iPos;

		float size = delta.Length();

		shape.setSize({ size, m_width });
		shape.setOrigin(0, shape.getSize().y / 2.f);
		shape.setPosition(m_iPos);

		float r = delta.Angle();

		shape.setRotation(r);
	}

	Line::Line(const std::string& id, const ui::Vec2f& iPos, const ui::Vec2f& fPos)
		: UIObject(id)
		, m_width(3)
		, m_iPos(iPos)
		, m_fPos(fPos)
	{
		shape.setFillColor(sf::Color::Black);

		Reset();
	}

	void Line::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void Line::SetWidth(const float& width)
	{
		m_width = width;

		Reset();
	}

	void Line::SetColor(const sf::Color& color)
	{
		shape.setFillColor(color);
	}

	void Line::SetOutlineThickness(const float& width)
	{
		shape.setOutlineThickness(width);
	}

	void Line::SetOutlineColor(const sf::Color& color)
	{
		shape.setOutlineColor(color);
	}

	void Line::SetStartPos(const ui::Vec2f& pos)
	{
		m_iPos = pos;
		Reset();
	}

	ui::Vec2f Line::GetStartPos()
	{
		return m_iPos;
	}

	void Line::SetEndPos(const ui::Vec2f& pos)
	{
		m_fPos = pos;
		Reset();
	}

	ui::Vec2f Line::GetEndPos()
	{
		return m_fPos;
	}

	Line::~Line()
	{
	}

}