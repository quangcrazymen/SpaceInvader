#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "GameOverUIPanel.h"
#include "WorldState.h"
#include "GameObject.h"
#include "BulletUpdateComponent.h"
#include "InvaderUpdateComponent.h"
#include "ItemUpdateComponent.h"

class BulletSpawner;

int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;
int WorldState::LEVEL;

GameScreen::GameScreen(ScreenManagerRemoteControl* smrc,
	Vector2i res)
{
	m_GIH = make_shared<GameInputHandler>();
	auto guip = make_unique<GameUIPanel>(res);
	addPanel(move(guip), smrc, m_GIH);

	auto m_GOIH = make_shared<GameOverInputHandler>();
	auto gouip = make_unique<GameOverUIPanel>(res);
	addPanel(move(gouip), smrc, m_GOIH);

	m_ScreenManagerRemoteControl = smrc;
	float screenRatio = VideoMode::getDesktopMode().width /
		VideoMode::getDesktopMode().height;

	WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH /
		screenRatio;

	m_View.setSize(
		WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);

	m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH /
		2, WorldState::WORLD_HEIGHT / 2));

	m_BackgroundTexture.loadFromFile("graphics/background.jpg");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	auto textureSize = m_BackgroundSprite.getTexture()->getSize();
	m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x,
		float(m_View.getSize().y) / textureSize.y);
}

void GameScreen::initialise()
{
	m_GIH->initialize();
	m_PhysicsEnginePlayMode.initilize(
		m_ScreenManagerRemoteControl->
		shareGameObjectSharer());

	WorldState::NUM_INVADERS = 0;

	// Store all the bullet locations and
	// Initialize all the BulletSpawners in the invaders
	// Count the number of invaders
	// i is the random seed for the invader to shoot
	int i = 0;

	for (auto &it:m_ScreenManagerRemoteControl->getGameObjects())
	{
		// Pre-sorted in the level file (for better branch prediction)
		if (it.getTag() == "bullet")
		{
			m_BulletObjectLocations.push_back(i);
		}
		if (it.getTag() == "explosion") {
			m_ExplosionObjectLocations.push_back(i);
		}
		if (it.getTag() == "item") {
			m_ItemObjectLocations.push_back(i);
			static_pointer_cast<ItemUpdateComponent>(
				it.getFirstUpdateComponent())
				->initializeItemSpawner(
					getItemSpawner());
			
		}
		if (it.getTag() == "invader")
		{
			static_pointer_cast<InvaderUpdateComponent>(
				it.getFirstUpdateComponent())->
				initializeBulletSpawner(
					getBulletSpawner(), i);

			WorldState::NUM_INVADERS++;
		}

		++i;
	}

	m_GameOver = false;

	if (WorldState::WAVE_NUMBER == 0)
	{
		WorldState::NUM_INVADERS_AT_START =
			WorldState::NUM_INVADERS;

		WorldState::WAVE_NUMBER = 1;
		WorldState::LIVES = 3;
		WorldState::SCORE = 0;
	}
}

void GameScreen::update(float fps)
{
	Screen::update(fps);

	if (!m_GameOver)
	{
		if (m_WaitingToSpawnBulletForPlayer)
		{
			static_pointer_cast<BulletUpdateComponent>(
				m_ScreenManagerRemoteControl->
				getGameObjects()
				[m_BulletObjectLocations[m_NextBullet]].
				getFirstUpdateComponent())->
				spawnForPlayer(m_PlayerBulletSpawnLocation);

			m_WaitingToSpawnBulletForPlayer = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size())
			{
				m_NextBullet = 0;
			}
		}

		if (m_WaitingToSpawnBulletForInvader)
		{
			static_pointer_cast<BulletUpdateComponent>(
				m_ScreenManagerRemoteControl->
				getGameObjects()
				[m_BulletObjectLocations[m_NextBullet]].
				getFirstUpdateComponent())->
				spawnForInvader(m_InvaderBulletSpawnLocation);

			m_WaitingToSpawnBulletForInvader = false;
			m_NextBullet++;

			if (m_NextBullet == m_BulletObjectLocations.size())
			{
				m_NextBullet = 0;
			}
		}

		// Item spawn
		for (auto &it : m_ScreenManagerRemoteControl->
			getGameObjects())
		{
			it.update(fps);
		}

		m_PhysicsEnginePlayMode.detectCollisions(
			m_ScreenManagerRemoteControl->getGameObjects(),
			m_BulletObjectLocations,
			m_ExplosionObjectLocations,
			m_ItemObjectLocations);

		if (WorldState::NUM_INVADERS <= 0)
		{
			//if (WorldState::LEVEL > 2) WorldState::LEVEL = 0;
			WorldState::WAVE_NUMBER++;
			m_ScreenManagerRemoteControl->loadLevelInPlayMode("level0");

			//WorldState::LEVEL++;
			//// beware of go out of level
			//m_ScreenManagerRemoteControl->
			//	loadLevelInPlayMode("level"+to_string(WorldState::LEVEL));
		}

		if (WorldState::LIVES <= 0)
		{
			m_GameOver = true;
		}
	}
}

void GameScreen::draw(RenderWindow& window)
{
	// Change to this screen's view to draw
	window.setView(m_View);
	window.draw(m_BackgroundSprite);

	// Draw the GameObject instances
	for (auto &it : m_ScreenManagerRemoteControl->
		getGameObjects())
	{
		it.draw(window);
	}

	// Draw the UIPanel view(s)
	Screen::draw(window);
}


BulletSpawner* GameScreen::getBulletSpawner()
{
	return this;
}

ItemSpawner* GameScreen::getItemSpawner()
{
	return this;
}

