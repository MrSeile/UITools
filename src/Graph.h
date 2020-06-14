#pragma once

#include "UIObject.h"
#include "Interactuable.h"

namespace ui {

	struct ArrowDef
	{
		float width = 5;
		sf::Color color = sf::Color::Black;
	};

	struct PlotDef
	{
		float width = 2;
		sf::Color color = sf::Color::Black;
		bool cyclic = false;
	};

	class Graph : public ui::UIObject
	{
	private:
		ui::Vec2f m_pos;
		ui::Vec2f m_size;
		ui::Vec2f m_xRange;
		ui::Vec2f m_yRange;
		sf::Color m_backColor;
		sf::Color m_axisColor;
		float m_axisWidth;
		float m_gridWidth;

		std::function<float(const float& x)> m_function;

		std::vector<std::pair<std::vector<ui::Vec2f>, PlotDef>> m_plots;
		std::vector<std::pair<std::pair<ui::Vec2f, ui::Vec2f>, ArrowDef>> m_arrows;

		ui::Vec2f CalculateAxisStep();

	public:
		Graph(const std::string& id);


		void SetPosition(const ui::Vec2f& pos);
		void SetSize(const ui::Vec2f& size);
		void SetRange(const ui::Vec2f& xRange, const ui::Vec2f& yRange);
		void SetBackgrowndColor(const sf::Color& color);
		void SetAxisColor(const sf::Color& color);
		void SetAxisWidth(const float& width);

		ui::Vec2f MapPosToCoords(const ui::Vec2f& pos);
		ui::Vec2f MapCoordsToPos(const ui::Vec2f& coords);

		void ClearAll();
		void ClearArrows();
		void ClearPlots();

		ui::Vec2f GetPosition();
		ui::Vec2f GetRange();
		ui::Vec2f GetSize();

		void Fit(const float& margin = 0.05f);

		//void Recalculate();
		void Plot(const std::vector<ui::Vec2f>& data, const PlotDef& props = PlotDef());
		void Arrow(const ui::Vec2f& pos, const ui::Vec2f& size, const ArrowDef& props = ArrowDef());
		
		void Draw(sf::RenderWindow& window) override;

		~Graph();
	};

}