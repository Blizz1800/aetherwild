#pragma once

namespace Game
{
	class Vector2
	{
	private:

	public:
		float x, y;
		Vector2() : x(0), y(0) {};
		Vector2(float v) : x(v), y(v) {};
		Vector2(float x, float y) : x(x), y(y) {};

		Vector2 operator+(Vector2 v);
		Vector2 operator-(Vector2 v);
	};
}
