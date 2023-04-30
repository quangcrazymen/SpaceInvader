#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "RectColliderComponent.h"
#include "ItemSpawner.h"
#include "GameObject.h"

class ItemUpdateComponent :
    public UpdateComponent

{
public:
	void deSpawn();
	void spawnRandomly(Vector2f spawnPosition);
	void initializeItemSpawner(ItemSpawner* itemSpawner);
	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	string Component::getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(GameObjectSharer* gos, GameObject* self) {
		// Where is the player?
		m_PlayerTC = static_pointer_cast<TransformComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType(
				"transform", "transform"));

		m_PlayerRCC = static_pointer_cast<RectColliderComponent>(
			gos->findFirstObjectWithTag("Player")
			.getComponentByTypeAndSpecificType(
				"collider", "rect"));

		m_TC = static_pointer_cast<TransformComponent>(self->
			getComponentByTypeAndSpecificType(
				"transform", "transform"));

		m_RCC = static_pointer_cast<RectColliderComponent>(self->
			getComponentByTypeAndSpecificType(
				"collider", "rect"));
	}

	/****************************************************
	*****************************************************
	From UpdateComponent
	*****************************************************
	*****************************************************/

	void update(float fps) override;

private:
    const string m_SpecificType = "item";
    
    shared_ptr<TransformComponent> m_TC;
    shared_ptr<RectColliderComponent> m_RCC;
	shared_ptr < TransformComponent> m_PlayerTC;
	shared_ptr < RectColliderComponent> m_PlayerRCC;

	ItemSpawner* m_ItemSpawner;

	bool m_IsSpawned = false;

	float m_Speed = 30.0;

	float m_TimeSinceLastDrop;
	float m_TimeBetweenDrops = 5.0f;


};

