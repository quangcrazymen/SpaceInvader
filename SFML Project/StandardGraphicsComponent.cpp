//#define debuggingOnConsole
#include "StandardGraphicsComponent.h"
#include "BitmapStore.h"

void StandardGraphicsComponent::initializeGraphics(
	string bitmapName,
	Vector2f objectSize)
{
	BitmapStore::addBitmap("graphics/" + bitmapName + ".png");
	m_Sprite.setTexture(BitmapStore::getBitmap(
		"graphics/" + bitmapName + ".png"));

	auto textureSize = m_Sprite.getTexture()->getSize();
	m_Sprite.setScale(float(objectSize.x) / textureSize.x,
		float(objectSize.y) / textureSize.y);
	// Nostalgic filter
	//m_Sprite.setColor(sf::Color(0, 255, 0));
}

void StandardGraphicsComponent::draw(
	RenderWindow& window,
	shared_ptr<TransformComponent> t)
{

#ifdef debuggingOnConsole 		
	//cout << "In Collision debug mode"
	//	<< endl;
	// draw hitbox
	auto pos = IntRect(m_RCC->getColliderRectF());
	RectangleShape hitbox;
	hitbox.setOutlineColor(Color::Red);
	hitbox.setSize(Vector2f(pos.width,pos.height));
	hitbox.setPosition(pos.left,pos.top);
	window.draw(hitbox);
#endif

	m_Sprite.setPosition(t->getLocation());
	m_Sprite.setRotation(t->getRotation());
	window.draw(m_Sprite);
}