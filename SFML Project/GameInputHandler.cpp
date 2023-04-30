#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"
#include "WorldState.h"

class BulletSpawner;

void GameInputHandler::initialize() 
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
}

void GameInputHandler::handleGamepad()
{
	float deadZone = 10.0f;
	float x = Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (x < deadZone && x > -deadZone)
	{
		x = 0;
	}

	if (y < deadZone && y > -deadZone)
	{
		y = 0;
	}

	m_PUC->updateShipTravelWithController(x, y);

	// Has the player pressed the B button?
	if (Joystick::isButtonPressed(0, 1))
	{
		mBButtonPressed = true;
	}

	// Has player just released the B button?
	if (!Joystick::isButtonPressed(0, 1) && mBButtonPressed)
	{
		mBButtonPressed = false;

		// Shoot a bullet
		SoundEngine::playShoot();
		Vector2f spawnLocation;
		for (int i = 0; i < 2; ++i) {
			spawnLocation.x = m_PTC->getLocation().x +
				m_PTC->getSize().x / 2;

			spawnLocation.y = m_PTC->getLocation().y;

			static_cast<GameScreen*>(getmParentScreen())->
				getBulletSpawner()->spawnBullet(spawnLocation, true);

		}
	}
}

void GameInputHandler::handleKeyPressed(
	Event& event, RenderWindow& window)
{
	// Handle key presses
	if (event.key.code == Keyboard::Escape)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}	
	// change level key for debug
	if (event.key.code == Keyboard::E)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Game");

		//if (WorldState::LEVEL == 2) {
		//	WorldState::LEVEL = 0;
		//}
		//else {
		//	WorldState::LEVEL += 1;
		//}
		WorldState::LEVEL = 1;
		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level" + to_string(WorldState::LEVEL));
	}

	if (event.key.code == Keyboard::Q)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Game");

		//if (WorldState::LEVEL == -1) {
		//	WorldState::LEVEL = 2;
		//}
		//else {
		//	WorldState::LEVEL -= 1;
		//}
		WorldState::LEVEL = 0;
		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level" + to_string(WorldState::LEVEL));


	}

	if (event.key.code == Keyboard::Num0)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Game");

		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level0");
	}

	if (event.key.code == Keyboard::Num1)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Game");

		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level1");
	}

	if (event.key.code == Keyboard::Num2)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Game");

		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level2");
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

void GameInputHandler::handleKeyReleased(
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
		SoundEngine::playShoot();
		Vector2f spawnLocation;
		// bacause getLocation return top left, so / 2 again -> devided by 4
		spawnLocation.x = m_PTC->getLocation().x + 
			m_PTC->getSize().x / 4;
		//spawnLocation.x = m_PTC->getLocation().x;

		spawnLocation.y = m_PTC->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->
			spawnBullet(spawnLocation, true);
	}
}