#include "EditorUIPanel.h"

EditorUIPanel::EditorUIPanel(Vector2i res) :
	UIPanel(res,
		(res.x / 10) * 2, // Start 2/10 accross
		res.y / 3, // 1/3 of the resolution from the top
		(res.x / 10) * 7, // as wide as 6/10 of the resolution
		res.y / 3, // and as tall as 1/3 of the resolution
		Color(255, 255, 255, 50)) // r, g, b,a
{
	m_ButtonWidth = res.x / 20;
	m_ButtonHeight = res.y / 20;
	m_ButtonPadding = res.x / 100;

	m_Text.setFillColor(sf::Color(0, 255, 0, 255));
	m_Text.setString("EDITOR MODE");

	//https://www.dafont.com/roboto.font
	m_Font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_Text.setFont(m_Font);

	m_Text.setPosition(Vector2f(m_ButtonPadding,
		m_ButtonHeight + (m_ButtonPadding * 2)));

	m_Text.setCharacterSize(160);

	initializeButtons();

}

void EditorUIPanel::initializeButtons() {
	addButton(m_ButtonPadding,
		m_ButtonPadding,
		m_ButtonWidth,
		m_ButtonHeight,
		Color(0, 255, 0),
		"Play");

}

void EditorUIPanel::draw(RenderWindow& window)
{
	show();
	UIPanel::draw(window);
	window.draw(m_Text);
}
