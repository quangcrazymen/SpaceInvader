#include "AnimationGraphicsComponent.h"
#include "BitmapStore.h"
#include <iostream>
void AnimationGraphicsComponent::initializeGraphics(
	string bitmapName,
	Vector2f objectSize)
{
	BitmapStore::addBitmap("graphics/BlueExplosionSprite.png");
	Texture &texture = BitmapStore::getBitmap("graphics/BlueExplosionSprite.png");
		
	// push the all the animation frame into the array
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			sf::IntRect rectSourceSprite(j * 128, i * 128, 128, 128);
			sf::Sprite sprite(texture, rectSourceSprite);
			m_Sprite[index].setTexture(texture);
			m_Sprite[index].setTextureRect(rectSourceSprite);
			auto textureSize = m_Sprite[index].getTexture()->getSize();
			m_Sprite[index].setScale(float(objectSize.x) / textureSize.x,
				float(objectSize.y) / textureSize.y);
			index++;
		}
	}

	// Set fps for animation

	//sf::Texture texture;
	//texture.loadFromFile("images/dragonFrames.png");

	//sf::IntRect rectSourceSprite(0, 0, 128, 128);
	//sf::Sprite sprite(texture, rectSourceSprite);
}

void AnimationGraphicsComponent::draw(RenderWindow& window,shared_ptr<TransformComponent> t){
#ifdef debuggingOnConsole 		
	//cout << "In Collision debug mode"
	//	<< endl;
	// draw hitbox
	auto pos = IntRect(m_RCC->getColliderRectF());
	RectangleShape hitbox;
	hitbox.setOutlineColor(Color::Red);
	hitbox.setSize(Vector2f(pos.width, pos.height));
	hitbox.setPosition(pos.left, pos.top);
	window.draw(hitbox);
#endif

	// Draw the animation down here

	// CRASH HERE AGAIN
	if (m_CurrentFrame > 14) { 
		// make update component instead
		//m_Switch->setInactive();
		m_CurrentFrame = 0; 
	}

	window.draw(m_Sprite[m_CurrentFrame]);
	if (m_Clock.getElapsedTime().asSeconds() > 0.20f ) {
		m_CurrentFrame++;	
		m_Clock.restart();
	}

	m_Sprite[m_CurrentFrame].setPosition(t->getLocation());
	//m_Sprite[m_CurrentFrame].setRotation(t->getRotation());
}
