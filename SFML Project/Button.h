#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
private:
	RectangleShape m_Button;
	Text m_ButtonText;
	Font m_Font;

public:
	std::string m_Text;
	FloatRect m_Collider;

	Button(Vector2f position,
		float width, float height,
		const Color& color,
		std::string text);

	void draw(RenderWindow& window);
};