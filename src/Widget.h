#pragma once

#include "Button.h"
#include "Slider.h"
#include "Sprite.h"
#include "Text.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Graph.h"
#include "InteractiveGraph.h"
#include "ToggleButton.h"
#include "Event.h"

namespace ui
{
	class Widget
	{
	private:
		std::vector<ui::UIObject*> m_objects;

	public:
		Widget();
		~Widget();


		void Update(const sf::RenderWindow& window);
		void CheckInput(const sf::RenderWindow& window, ui::Event& e);
		void Draw(sf::RenderWindow& window);
		void BeginPlay();
		void Clear();

		void AddObject(ui::UIObject* newObject);

		const std::vector<ui::UIObject*>& GetObjects();

		template<typename T>
		T* Get(const std::string& id);

		ui::UIObject* GetUIObject(const std::string& id);
	};

	template<typename T>
	inline T * Widget::Get(const std::string& id)
	{
		for (ui::UIObject* x : m_objects)
		{
			auto y = dynamic_cast<T*>(x);
			if (!y)
				continue;

			if (y->id == id)
				return y;
		}
		return nullptr;
	}
}