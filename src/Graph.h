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
	};

	class Graph : public ui::UIObject
	{
	private:
		sf::Vector2f m_pos;
		sf::Vector2f m_size;
		sf::Vector2f m_xRange;
		sf::Vector2f m_yRange;
		sf::Color m_backColor;
		sf::Color m_axisColor;
		float m_axisWidth;
		float m_gridWidth;

		std::function<float(const float& x)> m_function;

		std::vector<std::pair<std::vector<sf::Vector2f>, PlotDef>> m_plots;
		std::vector<std::pair<std::pair<sf::Vector2f, sf::Vector2f>, ArrowDef>> m_arrows;

		sf::Vector2f CalculateAxisStep();

	public:
		Graph(const std::string& id);


		void SetPosition(const sf::Vector2f& pos);
		void SetSize(const sf::Vector2f& size);
		void SetRange(const sf::Vector2f& xRange, const sf::Vector2f& yRange);
		void SetBackgrowndColor(const sf::Color& color);
		void SetAxisColor(const sf::Color& color);
		void SetAxisWidth(const float& width);

		sf::Vector2f MapPosToCoords(const sf::Vector2f& pos);
		sf::Vector2f MapCoordsToPos(const sf::Vector2f& coords);

		void ClearAll();
		void ClearArrows();
		void ClearPlots();

		//void Recalculate();
		void Plot(const std::vector<sf::Vector2f>& data, const PlotDef& props = PlotDef());
		void Arrow(const sf::Vector2f& pos, const sf::Vector2f& size, const ArrowDef& props = ArrowDef());
		
		void Draw(sf::RenderWindow& window) override;

		~Graph();
	};

}