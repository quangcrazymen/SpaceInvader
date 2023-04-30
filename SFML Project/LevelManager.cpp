#include "LevelManager.h"
#include "PlayModeObjectLoader.h"
#include <iostream>

void LevelManager::
loadGameObjectsForPlayMode(string screenToLoad)
{
	m_GameObjects.clear();
	string levelToLoad = WORLD_FOLDER + SLASH + screenToLoad;

	PlayModeObjectLoader pmol;
	pmol.loadGameObjectsForPlayMode(
		levelToLoad, m_GameObjects);

	runStartPhase();
}

void LevelManager::
loadGameObjectsForEditorMode(string screenToLoad)
{
	m_GameObjects.clear();
	string levelToLoad = WORLD_FOLDER + SLASH + screenToLoad;

	// share these function with play mode?
	PlayModeObjectLoader pmol;
	pmol.loadGameObjectsForPlayMode(
		levelToLoad, m_GameObjects);

	runStartPhase();
}

vector<GameObject>& LevelManager::getGameObjects()
{
	return m_GameObjects;
}

void LevelManager::runStartPhase()
{
	for (auto &it: m_GameObjects)
	{
		it.start(this);
	}

	activateAllGameObjects();
}

void LevelManager::activateAllGameObjects()
{
	for (auto &it : m_GameObjects)
	{
		it.setActive();
	}
}