#pragma once
#include "Component.h"
#include "GraphicsComponent.h"
#include "RectColliderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <string>

class Component;

class StandardGraphicsComponent : public GraphicsComponent {
private:
	sf::Sprite m_Sprite;
	const string m_SpecificType = "standard";
	shared_ptr<RectColliderComponent> m_RCC;
	shared_ptr<TransformComponent> m_TC;
public:

	/****************************************************
	*****************************************************
	From Component interface base class
	*****************************************************
	*****************************************************/

	string Component::getSpecificType() {
		return m_SpecificType;
	}

	void Component::start(
		GameObjectSharer* gos, GameObject* self) {
		m_TC = static_pointer_cast<TransformComponent>(self->
			getComponentByTypeAndSpecificType(
				"transform", "transform"));
		m_RCC = static_pointer_cast<RectColliderComponent>(
			self->getComponentByTypeAndSpecificType(
				"collider", "rect"
			)
		);
	}

	/****************************************************
	*****************************************************
	From GraphicsComponent
	*****************************************************
	*****************************************************/

	void draw(
		RenderWindow& window,
		shared_ptr<TransformComponent> t) override;

	void initializeGraphics(
		string bitmapName,
		Vector2f objectSize) override;

};