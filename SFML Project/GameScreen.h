#pragma once
#include "Screen.h"
#include "GameInputHandler.h"
#include "GameOverInputHandler.h"
#include "BulletSpawner.h"
#include "PhysicsEnginePlayMode.h"
#include "ItemSpawner.h"

class GameScreen : public Screen, public BulletSpawner, public ItemSpawner
{
private:
	ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
	shared_ptr<GameInputHandler> m_GIH;
	PhysicsEnginePlayMode m_PhysicsEnginePlayMode;

	int m_NumberInvadersInWorldFile = 0;

	vector<int> m_BulletObjectLocations;
	int m_NextBullet = 0;
	bool m_WaitingToSpawnBulletForPlayer = false;
	bool m_WaitingToSpawnBulletForInvader = false;
	Vector2f m_PlayerBulletSpawnLocation;
	Vector2f m_ItemSpawnLocation;
	Vector2f m_InvaderBulletSpawnLocation;
	Clock m_BulletClock;
	Clock m_ItemClock;
	// Explosion?
	vector<int> m_ExplosionObjectLocations;

	// Items
	vector<int> m_ItemObjectLocations;

	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;
public:
	static bool m_GameOver;

	GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
	void initialise() override;
	void virtual update(float fps);
	void virtual draw(RenderWindow& window);

	BulletSpawner* getBulletSpawner();
	ItemSpawner* getItemSpawner();

	/****************************************************
	*****************************************************
	From ItemSpawner interface
	*****************************************************
	*****************************************************/
	void spawnItem(Vector2f spawnLocation) {
		Time elapsedTime = m_ItemClock.getElapsedTime();
		// FIRE RATE
		if (elapsedTime.asMilliseconds() > 50) {
			m_ItemSpawnLocation.x = spawnLocation.x;
			m_ItemSpawnLocation.y = spawnLocation.y;
			m_ItemClock.restart();
		}

	}


	/****************************************************
	*****************************************************
	From BulletSpawner interface
	*****************************************************
	*****************************************************/

	void BulletSpawner::spawnBullet(Vector2f spawnLocation, bool forPlayer)
	{
		if (forPlayer)
		{
			Time elapsedTime = m_BulletClock.getElapsedTime();
			// FIRE RATE
			if (elapsedTime.asMilliseconds() > 500) {
				m_PlayerBulletSpawnLocation.x = spawnLocation.x;
				m_PlayerBulletSpawnLocation.y = spawnLocation.y;
				m_WaitingToSpawnBulletForPlayer = true;
				m_BulletClock.restart();
			}
		}
		else
		{
			m_InvaderBulletSpawnLocation.x = spawnLocation.x;
			m_InvaderBulletSpawnLocation.y = spawnLocation.y;
			m_WaitingToSpawnBulletForInvader = true;
		}
	}
};
