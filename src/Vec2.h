#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace ui {

	template<typename T>
	class Vec2 : public sf::Vector2<T>
	{
	public:
		T& min;
		T& max;

		Vec2()
			: sf::Vector2<T>()
			, min(this->x)
			, max(this->y)
		{
		}

		Vec2(T X, T Y)
			: sf::Vector2<T>(X, Y)
			, min(this->x)
			, max(this->y)
		{
		}

		template<typename U>
		Vec2(const Vec2<U>& vector)
			: sf::Vector2<T>(vector)
			, min(this->x)
			, max(this->y)
		{
		}

		template<typename U>
		Vec2(const sf::Vector2<U>& vector)
			: sf::Vector2<T>(vector)
			, min(this->x)
			, max(this->y)
		{
		}

		Vec2(const sf::Vector2<T>& vector)
			: sf::Vector2<T>(vector)
			, min(this->x)
			, max(this->y)
		{
		}


		T Length() const
		{
			return sqrt(this->x * this->x + this->y * this->y);
		}

		T Angle() const
		{
			return (atan2(this->y, this->x) * (T)180) / (T)M_PI;
		}

		Vec2& operator =(const Vec2& vec)
		{
			sf::Vector2<T>::operator =(vec);
			return *this;
		}
	};


	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	template <typename T>
	inline Vec2<T> operator -(const Vec2<T>& right)
	{
		return Vec2<T>(-right.x, -right.y);
	}

	template <typename T>
	inline Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right)
	{
		left.x += right.x;
		left.y += right.y;

		return left;
	}

	template <typename T>
	inline Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;

		return left;
	}

	template <typename T>
	inline Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right)
	{
		return Vec2<T>(left.x + right.x, left.y + right.y);
	}

	template <typename T>
	inline Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right)
	{
		return Vec2<T>(left.x - right.x, left.y - right.y);
	}

	template <typename T>
	inline Vec2<T> operator *(const Vec2<T>& left, T right)
	{
		return Vec2<T>(left.x * right, left.y * right);
	}


	template <typename T>
	inline Vec2<T> operator *(T left, const Vec2<T>& right)
	{
		return Vec2<T>(right.x * left, right.y * left);
	}

	template <typename T>
	inline Vec2<T>& operator *=(Vec2<T>& left, T right)
	{
		left.x *= right;
		left.y *= right;

		return left;
	}

	template <typename T>
	inline Vec2<T> operator /(const Vec2<T>& left, T right)
	{
		return Vec2<T>(left.x / right, left.y / right);
	}

	template <typename T>
	inline Vec2<T>& operator /=(Vec2<T>& left, T right)
	{
		left.x /= right;
		left.y /= right;

		return left;
	}

	template <typename T>
	inline bool operator ==(const Vec2<T>& left, const Vec2<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}


	////////////////////////////////////////////////////////////
	template <typename T>
	inline bool operator !=(const Vec2<T>& left, const Vec2<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y);
	}

}