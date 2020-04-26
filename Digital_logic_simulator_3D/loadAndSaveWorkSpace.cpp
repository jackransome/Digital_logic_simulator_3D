#include "loadAndSaveWorkspace.h"

LoadAndSaveWorkspace::LoadAndSaveWorkspace()
{
}

LoadAndSaveWorkspace::~LoadAndSaveWorkspace()
{
}

void LoadAndSaveWorkspace::loadWorkSpace(DigitalLogic* _digitalLogic, std::string _xmlPath)
{
	if (!doesFileExist(_xmlPath)) {
		std::cout << "file " << _xmlPath << " not found" << std::endl;
		return;
	}
	//clear current workspace:
	//_digitalLogic->clearComponents();
	//loading the xml file
	xmlFile.LoadFile(("savedWorkspaces/" + _xmlPath + ".xml").c_str());
	//using tinyXML to parse the xml data to find the number of blocks saved
	tinyxml2::XMLElement* numberOfBlocks = xmlFile.FirstChildElement("NUMBEROFBLOCKS");
	for (int i = 1; i < atof((char*)(const char*)(numberOfBlocks)->GetText()) + 1; i++)
	{
		if (i == 625) {
			int y = 0;
		}
		//creating a string with the name of the next block to parse. eg: "BLOCK4"
		char integer_string[4];
		sprintf_s(integer_string, "%d", i);
		char p[10] = "B";
		strcat_s(p, integer_string);
		//using tinyXML to parse the xml in the file for this particular block
		tinyxml2::XMLElement* parsedxml = xmlFile.FirstChildElement(p);
		addBlockFromXML(parsedxml, _digitalLogic);
	}
}

void LoadAndSaveWorkspace::saveWorkSpace(std::vector<Component*> *_components, std::string _fileName)
{
	_fileName = "savedWorkspaces/" + _fileName;
	//Reseting the block counter for saving the current workspace
	componentCounter = 0;
	//A temporary char used to manipulate the xmlFileChar
	char tempChar[4000];
	std::ofstream xmlFile;
	xmlFile.open(_fileName + ".xml", std::ios::out | std::ios::trunc);
	xmlFile.close();
	xmlFile.open(_fileName + ".xml", std::ofstream::in | std::ofstream::out | std::ofstream::app);
	strcpy_s(xmlFileChar, "<?xml version=\"1.0\"?>\n");
	//ADD BLOCKS
	for (int i = 0; i < _components->size(); i++) {
		saveBlock(_components->at(i));
		componentCounter++;
	}
	//Saving the number of blocks to the file needed for loadin it
	char charNumberOfBlocks[8];
	sprintf_s(charNumberOfBlocks, "%d", _components->size());
	strcpy_s(tempChar, "<NUMBEROFBLOCKS>");
	strcat_s(xmlFileChar, tempChar);
	strcat_s(xmlFileChar, charNumberOfBlocks);
	strcpy_s(tempChar, "</NUMBEROFBLOCKS>\n");
	strcat_s(xmlFileChar, tempChar);
	//Writing to the xml file
	xmlFile << xmlFileChar;
}

void LoadAndSaveWorkspace::saveBlock(Component* _component)
{
	//creating the chars that contain the raw block data, to be inserted into the final block char with the xml tags
	char charX[8];
	sprintf_s(charX, "%d", (int)_component->position.x);
	char charY[8];
	sprintf_s(charY, "%d", (int)_component->position.y);
	char charZ[8];
	sprintf_s(charZ, "%d", (int)_component->position.z);
	char charType[8];
	sprintf_s(charType, "%d", (int)_component->type);
	char charDirection[8];
	sprintf_s(charDirection, "%d", (int)_component->direction);
	char tempChar[100];
	char integer_string[4];
	sprintf_s(integer_string, "%d", componentCounter + 1);
	char blockChar[500] = "<B";
	strcat_s(blockChar, integer_string);
	strcpy_s(tempChar, ">\n\t<x>");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, charX);
	strcpy_s(tempChar, "</x>\n\t<y>");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, charY);
	strcpy_s(tempChar, "</y>\n\t<z>");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, charZ);
	strcpy_s(tempChar, "</z>\n\t<T>");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, charType);
	strcpy_s(tempChar, "</T>\n\t<D>");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, charDirection);
	strcpy_s(tempChar, "</D>\n</B");
	strcat_s(blockChar, tempChar);
	strcat_s(blockChar, integer_string);
	strcpy_s(tempChar, "> \n");
	strcat_s(blockChar, tempChar);
	//adding the xml for this particular block to the temporary xml data that will eventually be saved to the file
	strcat_s(xmlFileChar, blockChar);
}

void LoadAndSaveWorkspace::indexFiles(std::string path)
{
	fileNames.clear();
	std::string temp;
	for (auto & p : fs::directory_iterator(path)) {
		temp = p.path().string().erase(0, path.size());
		temp.resize(temp.size() - 4);
		fileNames.push_back(temp);
	}
}
bool LoadAndSaveWorkspace::doesFileExist(std::string fileName) {
	indexFiles("savedWorkspaces/");
	for (int i = 0; i < fileNames.size(); i++) {
		if (fileName == fileNames[i]) {
			return true;
		}
	}
	return false;
}
std::vector<std::string> LoadAndSaveWorkspace::getFileNames()
{
	return fileNames;
}

void LoadAndSaveWorkspace::addBlockFromXML(tinyxml2::XMLElement* _parsedXML, DigitalLogic* _digitalLogic)
{
	//parsing the xml data and using it the create a new block which is then added to the blocks vector
	_digitalLogic->addComponent(
		(int)atof((char*)(const char*)(_parsedXML->FirstChildElement("x"))->GetText()),
		(int)atof((char*)(const char*)(_parsedXML->FirstChildElement("y"))->GetText()),
		(int)atof((char*)(const char*)(_parsedXML->FirstChildElement("z"))->GetText()),
		static_cast<componentType>((int)atof((char*)(const char*)(_parsedXML->FirstChildElement("T"))->GetText())),
		static_cast<componentDirection>((int)atof((char*)(const char*)(_parsedXML->FirstChildElement("D"))->GetText()))
	);
}