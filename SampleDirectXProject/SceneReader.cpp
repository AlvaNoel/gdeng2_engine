#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "GameObject.h"
#include "SimpleMath.h"
#include "StringUtils.h"

using namespace DirectX;

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

	int index = 0;
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
	}
}
