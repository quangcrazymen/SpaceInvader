// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Random.h"

void Random::Init()
{
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed)
{
	sGenerator.seed(seed);
}

float Random::GetFloat()
{
	return GetFloatRange(0.0f, 1.0f);
}

float Random::GetFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(sGenerator);
}

int Random::GetIntRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGenerator);
}

my_Vector2 Random::GetVector(const my_Vector2& min, const my_Vector2& max)
{
	my_Vector2 r = my_Vector2(GetFloat(), GetFloat());
	return min + (max - min) * r;
}

my_Vector3 Random::GetVector(const my_Vector3& min, const my_Vector3& max)
{
	my_Vector3 r = my_Vector3(GetFloat(), GetFloat(), GetFloat());
	return min + (max - min) * r;
}

std::mt19937 Random::sGenerator;
