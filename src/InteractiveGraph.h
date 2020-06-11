#pragma once

#include "Graph.h"

namespace ui {

	class InteractiveGraph : public Graph, public Interactuable
	{
	private:
		ui::Vec2f m_startPos;
		float m_zoom;
		ui::Vec2f m_center;
		ui::Vec2f m_view;
		bool m_mousePressed;
		float m_aspect;

		void UpdateView();

	public:
		InteractiveGraph(const std::string& id);

		void Update(const sf::RenderWindow& window) override;
		void CheckInput(const sf::RenderWindow& window, ui::Event& e) override;

		void SetCenter(const ui::Vec2f& center);
	};

}