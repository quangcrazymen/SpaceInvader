#pragma once
#include "GraphicsComponent.h"
#include "TransformComponent.h"
#include "RectColliderComponent.h"
#include "GameObject.h"
#include "Component.h"

class AnimationGraphicsComponent :
    public GraphicsComponent
{
private:
	// pre-store the static array of animation
	sf::Sprite m_Sprite[16];
	const string m_SpecificType = "animation";
	//shared_ptr<RectColliderComponent> m_RCC;
	shared_ptr<TransformComponent> m_TC;
	int m_CurrentFrame = 0;
	//float m_FPS = 0;
	sf::Clock m_Clock;
	// 
	GameObject* m_Switch;
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
		//m_RCC = static_pointer_cast<RectColliderComponent>(
		//	self->getComponentByTypeAndSpecificType(
		//		"collider", "rect"
		//	)
		//);
		m_Switch = self;
	}


	/****************************************************
	*****************************************************
	From GraphicsComponent
	*****************************************************
	*****************************************************/

	void initializeGraphics(
		string bitmapName,
		Vector2f objectSize) override;

	void draw(
		RenderWindow& window,
		shared_ptr<TransformComponent> t) override;
};

