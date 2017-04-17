#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_


#include <tinyxml2.h>

#include <iostream>
#include <vector>
#include "General\Scene.h"

#include "UI\Text2D.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Components\FirstPersonCameraComponent.h"
#include "Rendering\Components\ThirdPersonCameraComponent.h"
#include "Rendering\Components\RenderComponent.h"


using namespace tinyxml2;

class XMLParser {


private:
	//The Document to be loaded.
	XMLDocument m_Doc_;
	XMLNode * m_Root_;
public:

	XMLParser();
	//Parse the file.
	bool Parse(std::string pPath);

	std::vector<XMLElement*> GetElements(std::string filter);

	//Load the scene after its been parsed.
	Scene * LoadScene();

	//Process Components and Canvas elements separately.
	void ProcessComponent(Scene * pScene, XMLElement * pElement, int pIndex);
	void ProcessCanvas(Scene * pScene, XMLElement * pElement, int pIndex);


	glm::vec3 GenerateVec3(XMLElement * element);
	glm::vec4 GenerateVec4(XMLElement * element);

	//Compare Const char strings.
	bool checkStrings(const char* s1, const char* s2) {
		if (std::strcmp(s1, s2) == 0)
			return true;
		else
			return false;
	}
};




#endif