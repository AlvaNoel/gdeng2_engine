#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "SimpleMath.h"
#include "StringUtils.h"

using namespace DirectX;

#include <json/json.h>
#include <json/value.h>

typedef std::fstream FileReader;
SceneReader::SceneReader(std::string _directory)
{
	this->directory = _directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::ReadFromFile()
{
	std::string fileDir = this->directory;
	std::cout << fileDir << std::endl;
	if (this->directory.find(".level") != std::string::npos) {
		fileDir = this->directory;
	}

	FileReader sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	/*int index = 0;
	std::string readLine;

	std::string objectName;
	PrimitiveType objectType;
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;
	SimpleMath::Vector3 scale;

	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) {
			std::vector stringSplit = StringUtils::split(readLine, ' ');
			objectType = (PrimitiveType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 2) {
			std::vector stringSplit = StringUtils::split(readLine, ' ');
			position = SimpleMath::Vector3(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) {
			std::vector stringSplit = StringUtils::split(readLine, ' ');
			rotation = SimpleMath::Vector3(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) {
			std::vector stringSplit = StringUtils::split(readLine, ' ');
			scale = SimpleMath::Vector3(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 5) {
			std::vector stringSplit = StringUtils::split(readLine, ' ');
			bool hasPhysics = (bool)std::stoi(stringSplit[1]);

			GameObjectManager::Get()->CreateObjectFromFile(objectName, objectType, position, rotation, scale, hasPhysics);
			index = 0;
		}
	}*/

	Json::Value root;

	sceneFile >> root;

	//std::string objectName;
	PrimitiveType objectType;
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;
	SimpleMath::Vector3 scale;
	bool hasPhysics;

	auto array = root["objectsToInstantiate"];

	//for (auto const& id : array.getMemberNames())
	//{
	//	hasPhysics = (bool)array[id]["hasPhysics"].asInt();
	//	//objectName = root[id]["name"].asString();
	//	position =	{ array.get(id,array)["position"][0]["x"].asFloat(), array[id]["position"][0]["y"].asFloat(), array[id]["position"][0]["z"].asFloat()};
	//	rotation =	{ array[id]["rotation"][0]["x"].asFloat(), array[id]["rotation"][0]["y"].asFloat(), array[id]["rotation"][0]["z"].asFloat() };
	//	scale =	{ array[id]["scale"][0]["x"].asFloat(), array[id]["scale"][0]["y"].asFloat(), array[id]["scale"][0]["z"].asFloat() };
	//	objectType = (PrimitiveType)array[id]["type"].asInt();

	//	GameObjectManager::Get()->CreateObjectFromFile(objectType, position, rotation, scale, hasPhysics);
	//}

	for(int i = 0; i < array.size(); i++)
	{
		hasPhysics = (bool)array[i]["hasPhysics"].asInt();
		position = { array[i]["position"]["x"].asFloat(), array[i]["position"]["y"].asFloat(), array[i]["position"]["z"].asFloat() };
		rotation = { array[i]["rotation"]["x"].asFloat(), array[i]["rotation"]["y"].asFloat(), array[i]["rotation"]["z"].asFloat() };
		scale = { array[i]["scale"]["x"].asFloat(), array[i]["scale"]["y"].asFloat(), array[i]["scale"]["z"].asFloat() };
		objectType = (PrimitiveType)array[i]["type"].asInt();

		GameObjectManager::Get()->CreateObjectFromFile(objectType, position, rotation, scale, hasPhysics);
	}

	sceneFile.close();
}
