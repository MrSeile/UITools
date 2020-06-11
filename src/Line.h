#pragma once

#include "Global.h"
#include "UIObject.h"

namespace ui {

	class Line : public ui::UIObject
	{
	private:
		float m_width;
		ui::Vec2f m_iPos;
		ui::Vec2f m_fPos;

		sf::RectangleShape shape;

		void Reset();

	public:
		Line(const std::string& id, const ui::Vec2f& iPos, const ui::Vec2f& fPos);

		void Draw(sf::RenderWindow& window) override;
		void SetWidth(const float& width);
		void SetColor(const sf::Color& color);

		void SetOutlineThickness(const float& width);
		void SetOutlineColor(const sf::Color& color);

		void SetStartPos(const ui::Vec2f& pos);
		ui::Vec2f GetStartPos();

		void SetEndPos(const ui::Vec2f& pos);
		ui::Vec2f GetEndPos();

		~Line();
	};
}
