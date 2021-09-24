#pragma once
#include "tinyxml2.h"
#include "DigitalLogic.h"

#include <fstream>
#include <vector>

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

class LoadAndSaveWorkspace {
public:
	LoadAndSaveWorkspace();
	~LoadAndSaveWorkspace();
	void loadWorkSpace(DigitalLogic* _digitalLogic, std::string _xmlPath);
	void saveWorkSpace(std::vector<Component*> *_components, std::string _path);
	//Block counter used to keep track of the number of blocks, so the blocks can be named appropriately in XML
	int componentCounter;
	bool doesFileExist(std::string _fileName);
	void indexFiles(std::string _path);
	std::vector<std::string> getFileNames();
private:
	void addBlockFromXML(tinyxml2::XMLElement* _parsedXML, DigitalLogic* _digitalLogic);
	void saveBlock(Component* _component);
	//The temporary char where XML data is stored before being put into the XML file
	char xmlFileChar[500000];
	tinyxml2::XMLDocument xmlFile;
	std::vector<std::string> fileNames;

};