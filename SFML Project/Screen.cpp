#include "Screen.h"

void Screen::initialise() {}

void Screen::addPanel(unique_ptr<UIPanel> uip,
	ScreenManagerRemoteControl* smrc,
	shared_ptr<InputHandler> ih)
{
	ih->initialiseInputHandler(smrc,
		uip->getButtons(), &uip->m_View, this);
	// Use move() because otherwise 
	// the vector has a COPY which is not allowed
	m_Panels.push_back(move(uip));
	m_InputHandlers.push_back(ih);
}

void Screen::handleInput(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		for (auto &itr : m_InputHandlers)
		{
			itr->handleInput(window, event);
		}
	}
}

void Screen::update(float fps) {}

void Screen::draw(RenderWindow& window)
{
	for (auto &itr : m_Panels)
	{
		itr->draw(window);
	}
}
