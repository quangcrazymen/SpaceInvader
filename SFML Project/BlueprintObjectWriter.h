#pragma once
#include <fstream>
#include <iostream>
#include "BlueprintObjectParser.h"
#include "ObjectTags.h"

class BlueprintObjectWriter
{
private:
	
public:
	void writeToFile() {
		//ofstream out("world/tempLevel",ios::app);
		ofstream out("world/tempLevel");
		string object = "";
		object += ObjectTags::START_OF_OBJECT + "\n";
		object += ObjectTags::NAME + "Something" +ObjectTags::NAME_END + "\n";
		object += ObjectTags::COMPONENT +"Something" +ObjectTags::COMPONENT_END + "\n";
		object += ObjectTags::COMPONENT + "Something" + ObjectTags::COMPONENT_END + "\n";
		object += ObjectTags::COMPONENT + "Something" + ObjectTags::COMPONENT_END + "\n";
		object += ObjectTags::LOCATION_X + "Something" + ObjectTags::LOCATION_X_END + "\n";
		object += ObjectTags::LOCATION_Y + "Something" + ObjectTags::LOCATION_X_END + "\n";
		object += ObjectTags::WIDTH + "Something" + ObjectTags::WIDTH_END + "\n";
		object += ObjectTags::HEIGHT + "Something" + ObjectTags::HEIGHT_END + "\n";
		object += ObjectTags::BITMAP_NAME + "Something" + ObjectTags::BITMAP_NAME_END + "\n";
		object += ObjectTags::ENCOMPASSING_RECT_COLLIDER + "Something" + ObjectTags::ENCOMPASSING_RECT_COLLIDER_END + "\n";
		object += ObjectTags::END_OF_OBJECT + "\n";

		out << object;
		out.close();
	}
};

