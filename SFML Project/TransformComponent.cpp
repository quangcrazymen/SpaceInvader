#include "TransformComponent.h"

TransformComponent::TransformComponent(
	float width, float height, Vector2f location, float angle)
{
	m_Height = height;
	m_Width = width;
	m_Location = location;
	m_Angle = angle;
}

Vector2f& TransformComponent::getLocation()
{
	return m_Location;
}

Vector2f TransformComponent::getSize()
{
	return Vector2f(m_Width, m_Height);
}

float& TransformComponent::getRotation()
{
	return m_Angle;
}

