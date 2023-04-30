#pragma once
#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "StandardGraphicsComponent.h"
#include "ScreenManagerRemoteControl.h"
class EditorInputHandler :
	public InputHandler
{
private:
	shared_ptr<PlayerUpdateComponent> m_PUC;
	shared_ptr<TransformComponent> m_PTC;
	shared_ptr<GraphicsComponent> m_PGC;
public:

	void initialize();

	void handleKeyPressed(Event& event,
		RenderWindow& window) override;

	void handleKeyReleased(Event& event,
		RenderWindow& window) override;

	void handleLeftClick(std::string& buttonInteractedWith, RenderWindow& window);

	void handleInput(RenderWindow& window, Event& event) override;
};
