#pragma once
#include <string>
#include <glm\glm.hpp>
struct Textbox {
	bool infocus;
	std::string text;
	glm::vec2 position;
	glm::vec2 size;
};