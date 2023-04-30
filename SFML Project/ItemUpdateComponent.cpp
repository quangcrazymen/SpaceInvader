#include "ItemUpdateComponent.h"
#include "WorldState.h"
#include "Random.h"
void ItemUpdateComponent::deSpawn(){
	m_IsSpawned = false;
}
void ItemUpdateComponent::spawnRandomly(Vector2f spawnPosition) {
	m_IsSpawned = true;
	m_TC->getLocation() = spawnPosition;
	// Update the collider
	m_RCC->setOrMoveCollider(m_TC->getLocation().x,
		m_TC->getLocation().y,
		m_TC->getSize().x, m_TC->getSize().y);

}

void ItemUpdateComponent::update(float fps) {
	m_IsSpawned = true;
	if (m_IsSpawned) {
		m_TC->getLocation().y += m_Speed * fps;

	}
	if (m_TC->getLocation().y > WorldState::WORLD_HEIGHT)
	{
		// send this offscreen like in physic engine
		m_TC->getLocation() = Vector2f(-20.0, -20.0);
		deSpawn();
	}
	m_TimeSinceLastDrop += fps;
	if (m_TimeSinceLastDrop > m_TimeBetweenDrops) {
		//my_Vector2 spawnLocation = Random::GetVector(my_Vector2(2, 3), my_Vector2(4, 5));
		Vector2f spawnLoc(Random::GetFloatRange(5,20), Random::GetFloatRange(5, 20));
		//m_ItemSpawner->spawnItem(spawnLoc);
		spawnRandomly(spawnLoc);

		m_TimeSinceLastDrop = 0;
	}


}

void ItemUpdateComponent::initializeItemSpawner(ItemSpawner* itemSpawner) {
	m_ItemSpawner = itemSpawner;
	m_TimeBetweenDrops = Random::GetIntRange(3, 5);
}


