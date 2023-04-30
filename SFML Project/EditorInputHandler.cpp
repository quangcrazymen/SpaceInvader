#include "EditorInputHandler.h"
#include "GameScreen.h"
#include "SoundEngine.h"
#include <iostream>


void EditorInputHandler::initialize()
{
	m_PUC = static_pointer_cast<PlayerUpdateComponent>
		(getPointerToScreenManagerRemoteControl()
			->shareGameObjectSharer()
			.findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType(
				"update", "player"));

	m_PTC = getPointerToScreenManagerRemoteControl()->
		shareGameObjectSharer().findFirstObjectWithTag(
			"Player").getTransformComponent();

	m_PGC = make_shared<StandardGraphicsComponent>();
}

void EditorInputHandler::handleInput(RenderWindow& window, Event& event) {
	if (event.type == Event::MouseButtonReleased)
	{
		std::cout << Vector2f(Mouse::getPosition()).x << " " << Vector2f(Mouse::getPosition()).y << std::endl;
		shared_ptr<TransformComponent> test = make_shared<TransformComponent>(200, 300, Vector2f(1000,1000));
		m_PGC = static_pointer_cast<StandardGraphicsComponent>(m_PGC);
		m_PGC->initializeGraphics("player", Vector2f(0.0, 0.0));
		m_PGC->enabled();
		m_PGC->enableComponent();
		GameObject temp;
		temp.addComponent(m_PGC);
		cout<<getPointerToScreenManagerRemoteControl()->getGameObjects().size();
		temp.setActive();
	
		getPointerToScreenManagerRemoteControl()->getGameObjects().push_back(temp);
		//temp.start(gos,)
	}
	//shared_ptr<TransformComponent> test = static_pointer_cast<TransformComponent>(
	//	getPointerToScreenManagerRemoteControl()->shareGameObjectSharer().
	//)
}

void EditorInputHandler::handleLeftClick(
	std::string& buttonInteractedWith, RenderWindow& window)
{
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();

		getPointerToScreenManagerRemoteControl()
			->loadLevelInPlayMode("level0");
	}
}

void EditorInputHandler::handleKeyPressed(
	Event& event, RenderWindow& window)
{
	// Handle key presses
	if (event.key.code == Keyboard::Escape)
	{
		//SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}

	if (event.key.code == Keyboard::Left)
	{
		m_PUC->moveLeft();
	}

	if (event.key.code == Keyboard::Right)
	{
		m_PUC->moveRight();
	}

	if (event.key.code == Keyboard::Up)
	{
		m_PUC->moveUp();
	}

	if (event.key.code == Keyboard::Down)
	{
		m_PUC->moveDown();
	}
}

void EditorInputHandler::handleKeyReleased(
	Event& event, RenderWindow& window)
{
	if (event.key.code == Keyboard::Left)
	{
		m_PUC->stopLeft();
	}

	else if (event.key.code == Keyboard::Right)
	{
		m_PUC->stopRight();
	}

	else if (event.key.code == Keyboard::Up)
	{
		m_PUC->stopUp();
	}

	else if (event.key.code == Keyboard::Down)
	{
		m_PUC->stopDown();
	}

	else if (event.key.code == Keyboard::Space)
	{
		// Shoot a bullet
		//SoundEngine::playShoot();
		Vector2f spawnLocation;
		spawnLocation.x = m_PTC->getLocation().x +
			m_PTC->getSize().x / 2;

		spawnLocation.y = m_PTC->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->
			spawnBullet(spawnLocation, true);
	}
}
