#include "UIPanel.h"

UIPanel::UIPanel(Vector2i res, int x, int y,
	float width, float height,
	const Color& color)
{
	m_UIPanel.setFillColor(color);

	// How big in pixels is the UI panel
	m_UIPanel.setSize(Vector2f(width, height));

	// How big in pixels is the view
	m_View.setSize(Vector2f(width, height));

	// Where in pixels does the center of the view focus
	// This is most relevant when drawing a portion of the game world
	// width/2, height/2 ensures it is exactly centered around the
	// RectangleShape, mUIPanel
	m_View.setCenter(width / 2, height / 2);

	// Where in the window is the view positioned?
	float viewportStartX = 1.f / (res.x / x);
	float viewportStartY = 1.f / (res.y / y);
	float viewportSizeX = 1.f / (res.x / width);
	float viewportSizeY = 1.f / (res.y / height);

	// Params from left to right
	// StartX as a fraction of 1, startY as a fraction of 1 
	// SizeX as a fraction of 1
	// SizeY as a fraction of 1
	m_View.setViewport(FloatRect(viewportStartX, viewportStartY,
		viewportSizeX, viewportSizeY));
}

vector<shared_ptr<Button>> UIPanel::getButtons()
{
	return m_Buttons;
}

void UIPanel::addButton(float x, float y,
	int width, int height,
	const Color& color,
	string label)
{
	m_Buttons.push_back(make_shared<Button>(Vector2f(x, y),
		width, height,
		color,
		label));
}

void UIPanel::draw(RenderWindow& window)
{
	window.setView(m_View);
	if (!m_Hidden) {
		window.draw(m_UIPanel);
		for (auto &it:m_Buttons)
		{
			it->draw(window);
		}
	}
}

void UIPanel::show()
{
	m_Hidden = false;
}

void UIPanel::hide()
{
	m_Hidden = true;
}