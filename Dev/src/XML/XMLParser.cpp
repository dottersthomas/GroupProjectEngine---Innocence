#include "XML\XMLParser.h"
#include "Rendering\GUI\CanvasButton.h"
#include "Components\RobotAnimationComponent.h"
#include "Components\DistanceComponent.h"

XMLParser::XMLParser() {

}

bool XMLParser::Parse(std::string pPath) {

	XMLError error = m_Doc_.LoadFile(pPath.c_str());

	if (error != XML_SUCCESS)
		return false;
	m_Root_ = m_Doc_.FirstChild();

	return true;
}

std::vector<XMLElement*> XMLParser::GetElements(std::string filter) {

	std::vector<XMLElement*> temp;
	for (XMLElement* e = m_Root_->FirstChildElement(filter.c_str()); e != NULL; e = e->NextSiblingElement(filter.c_str()))
	{
		
		temp.push_back(e);
	}

	return temp;
}


Scene * XMLParser::LoadScene() {
	Scene * _Scene = new Scene("");
	
	XMLElement * sceneElem = m_Doc_.FirstChildElement("scene");

	XMLElement * gObject = sceneElem->FirstChildElement("GameObject");
	while (gObject != nullptr) {

		const char* objName = gObject->Attribute("name");
		GameObject object(objName);

		int index = _Scene->AddGameObject(object);
		TransformComponent * tc = _Scene->getGameObjects()->at(index).GetComponentByType<TransformComponent>();
		tc->setParent(&_Scene->getGameObjects()->at(index));
		XMLElement * child = gObject->FirstChildElement();

		while (child != nullptr)
		{

			std::cout << child->Name() << std::endl;

			ProcessComponent(_Scene, child, index);
			child = child->NextSiblingElement();
		}


		std::cout << gObject->Name() << std::endl;
		gObject = gObject->NextSiblingElement("GameObject");
	}

	return _Scene;

}

glm::vec3 XMLParser::GenerateVec3(XMLElement * element) {

	XMLElement * child = element->FirstChildElement();
	float x = 0, y = 0, z = 0;
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "x")) {
			child->QueryFloatText(&x);
		}
		if (checkStrings(childName, "y")) {
			child->QueryFloatText(&y);
		}
		if (checkStrings(childName, "z")) {
			child->QueryFloatText(&z);
		}

		child = child->NextSiblingElement();
	}

	return glm::vec3(x, y, z);

}

glm::vec4 XMLParser::GenerateVec4(XMLElement * element) {

	XMLElement * child = element->FirstChildElement();
	float x = 0, y = 0, z = 0, w = 0;
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "x")) {
			child->QueryFloatText(&x);
		}
		if (checkStrings(childName, "y")) {
			child->QueryFloatText(&y);
		}
		if (checkStrings(childName, "z")) {
			child->QueryFloatText(&z);
		}
		if (checkStrings(childName, "w")) {
			child->QueryFloatText(&w);
		}

		child = child->NextSiblingElement();
	}

	return glm::vec4(x, y, z, w);

}


void XMLParser::ProcessComponent(Scene * pScene, XMLElement * pElement, int pIndex) {
	const char* componentName = pElement->Name();

	//Setup the Transform Component
	if (checkStrings(componentName, "position")) {
		TransformComponent * tc = pScene->getGameObjects()->at(pIndex).GetComponentByType<TransformComponent>();
	
		tc->setPosition(GenerateVec3(pElement));
	}

	//Setup the Animation Component
	if (checkStrings(componentName, "animate")) {

		RobotAnimationComponent * r = new RobotAnimationComponent(&pScene->getGameObjects()->at(pIndex));

		pScene->getGameObjects()->at(pIndex).registerComponent(r);
		r->setParent(&pScene->getGameObjects()->at(pIndex));
	}

	//Setup the Render Component
	if (checkStrings(componentName, "mesh")) {

		MeshFactory factory;


		const char* shader = pElement->Attribute("shader");
		const char* name = pElement->Attribute("name");

		int type = 0;

		pElement->QueryIntAttribute("type", &type);

	
		RenderComponent * render;
		if (pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RenderComponent>()) {
			render = pScene->getGameObjects()->at(pIndex).GetComponentByType<RenderComponent>();
		}
		else {
			render = new RenderComponent(&pScene->getGameObjects()->at(pIndex), std::string(shader), type);
		}
		XMLElement * child = pElement->FirstChildElement();

		glm::vec3 position, rotation, scale, pivot = glm::vec3(0.0f,0.0f,0.0f);
		glm::vec4 colour = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
		const char* path;
		const char* texturePath;
		while (child != nullptr)
		{
			const char* childName = child->Name();
			if (checkStrings(childName, "path")) {
				path = child->GetText();
			}
			if (checkStrings(childName, "pivot")) {
				pivot = GenerateVec3(child);
			}
			if (checkStrings(childName, "position")) {
				position = GenerateVec3(child);
			}
			if (checkStrings(childName, "rotation")) {
				rotation = GenerateVec3(child);
			}
			if (checkStrings(childName, "scale")) {
				scale = GenerateVec3(child);
			}
			if (checkStrings(childName, "texture")) {
				texturePath = child->GetText();
				ResourceManager::getInstance()->loadTexture(texturePath, GL_FALSE, texturePath);

			}
			if (checkStrings(childName, "colour")) {
				colour = GenerateVec4(child);
			}
			child = child->NextSiblingElement();
		}

		Mesh * mesh;

		if(path != nullptr){
			if(type == 1)
				mesh = factory.create(path, position, rotation, scale , texturePath);
			else
				mesh = factory.create(path, position, rotation, scale, colour);

		}

		mesh->setPivotPoint(pivot);
		mesh->setColour(colour);

		if (checkStrings(name ,"RobotArmRight")) {
			if (pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RobotAnimationComponent>()) {
				pScene->getGameObjects()->at(pIndex).GetComponentByType<RobotAnimationComponent>()->attachRightArm(mesh);
			}
		}
		if (checkStrings(name, "RobotArmLeft")) {
			if (pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RobotAnimationComponent>()) {
				pScene->getGameObjects()->at(pIndex).GetComponentByType<RobotAnimationComponent>()->attachLeftArm(mesh);
			}
		}
		if (checkStrings(name, "RobotLegLeft")) {
			if (pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RobotAnimationComponent>()) {
				pScene->getGameObjects()->at(pIndex).GetComponentByType<RobotAnimationComponent>()->attachLeftLeg(mesh);
			}
		}
		if (checkStrings(name, "RobotLegRight")) {
			if (pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RobotAnimationComponent>()) {
				pScene->getGameObjects()->at(pIndex).GetComponentByType<RobotAnimationComponent>()->attachRightLeg(mesh);
			}
		}
		render->AttachMesh(mesh);
		
		if (!pScene->getGameObjects()->at(pIndex).CheckComponentTypeExists<RenderComponent>()) {
			pScene->getGameObjects()->at(pIndex).registerComponent(render);
			render->setParent(&pScene->getGameObjects()->at(pIndex));
		}
	}

	//Setup the Interaction Component.
	if (checkStrings(componentName, "interaction")) {
		float distance = 0.0;
		pElement->QueryFloatText(&distance);

		TransformComponent * tc;

		//Search for a unique component.

		for (int i = 0; i < pScene->getGameObjects()->size(); i++) {
			if (pScene->getGameObjects()->at(i).CheckComponentTypeExists<PlayerKeyboardControlComponent>())
				tc = pScene->getGameObjects()->at(i).GetComponentByType<TransformComponent>();
		}


		DistanceComponent * dc = new DistanceComponent(&pScene->getGameObjects()->at(pIndex), tc, distance);

		pScene->getGameObjects()->at(pIndex).registerComponent(dc);
		dc->setParent(&pScene->getGameObjects()->at(pIndex));
	}
	if (checkStrings(componentName, "firstpersoncamera")) {

		
		XMLElement * child = pElement->FirstChildElement();
		glm::vec3 position;
		bool main = false;

		const char* name = pElement->Attribute("name");

		pElement->QueryBoolAttribute("main", &main);

		

		while (child != nullptr)
		{
			const char* childName = child->Name();

			if (checkStrings(childName, "position")) {
				position = GenerateVec3(child);
			}
			child = child->NextSiblingElement();
		}
		FirstPersonCameraComponent * camera = new FirstPersonCameraComponent(&pScene->getGameObjects()->at(pIndex), std::string(name), position);
		pScene->getGameObjects()->at(pIndex).registerComponent(camera);
		camera->setParent(&pScene->getGameObjects()->at(pIndex));

		if(main)
			pScene->attachMainCameraComponent(pScene->getGameObjects()->at(pIndex).GetComponentByType<FirstPersonCameraComponent>());

	}

	if (checkStrings(componentName, "thirdpersoncamera")) {
		XMLElement * child = pElement->FirstChildElement();
		glm::vec3 position;
		bool main = true;

		const char* name = pElement->Attribute("name");

		pElement->QueryBoolAttribute("main", &main);

		float distance = 10.0f;


		//TODO add distance modifiers to constructor.
		ThirdPersonCameraComponent * camera;

		while (child != nullptr)
		{
			const char* childName = child->Name();

			if (checkStrings(childName, "position")) {
				position = GenerateVec3(child);
			}

			if (checkStrings(childName, "distance")) {
				child->QueryFloatText(&distance);
			}
			child = child->NextSiblingElement();
		}


		camera = new ThirdPersonCameraComponent(&pScene->getGameObjects()->at(pIndex), std::string(name), distance);

		pScene->getGameObjects()->at(pIndex).registerComponent(camera);
		camera->setParent(&pScene->getGameObjects()->at(pIndex));

		if (main)
			pScene->attachMainCameraComponent(pScene->getGameObjects()->at(pIndex).GetComponentByType<ThirdPersonCameraComponent>());
	}

	//Setup the movement Component
	if (checkStrings(componentName, "playermovementcontroller")) {
		PlayerKeyboardControlComponent * movement = new PlayerKeyboardControlComponent(&pScene->getGameObjects()->at(pIndex));
		pScene->getGameObjects()->at(pIndex).registerComponent(movement);
		movement->setParent(&pScene->getGameObjects()->at(pIndex));

	}

	//Create the GUI here.
	if (checkStrings(componentName, "canvas")) {
		ProcessCanvas(pScene, pElement, pIndex);
	}


}

//Process the GUI and create a canvas component for the overlay.
void XMLParser::ProcessCanvas(Scene * pScene, XMLElement * pElement, int pIndex) {
	const char* componentName = pElement->Name();

	const char* type = pElement->Attribute("type");
	CanvasComponent * canvas = new CanvasComponent(&pScene->getGameObjects()->at(pIndex));
	XMLElement * child = pElement->FirstChildElement();
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "rect")) {


			const char* shader = child->Attribute("shader");

			glm::vec4 colour = glm::vec4(1.0, 1.0, 1.0, 1.0);
			glm::vec2 pos, size;
			XMLElement * rectChild = child->FirstChildElement();
			CanvasRect * rect;
			while (rectChild != nullptr)
			{
				const char* rectChildName = rectChild->Name();
				if (checkStrings(rectChildName, "colour")) {
					
					colour = GenerateVec4(rectChild);
				
				}

				if (checkStrings(rectChildName, "position")) {

					pos = glm::vec2(GenerateVec3(rectChild).x, GenerateVec3(rectChild).y);

				}

				if (checkStrings(rectChildName, "scale")) {

					size = glm::vec2(GenerateVec3(rectChild).x, GenerateVec3(rectChild).y);

				}

				rectChild = rectChild->NextSiblingElement();
			}

			rect = new CanvasRect(nullptr, colour);
			rect->SetShader(shader);
			rect->setPosition(pos);
			rect->setScale(size);

			canvas->AddElement(rect);

			//canvas->AddElement(new Text2D("text", "abcdefghijklmnopqrstuvwxyz , 1234567890 - + _ = @#~;:?><\\"));
		}

		if (checkStrings(childName, "text")) {
			const char* shader = child->Attribute("shader");

			glm::vec4 colour = glm::vec4(1.0, 1.0, 1.0, 1.0);
			glm::vec2 pos, size;
			std::string textContent;
			bool usesID = false;
			XMLElement * textChild = child->FirstChildElement();
			while (textChild != nullptr)
			{
				const char* textChildName = textChild->Name();

				if (checkStrings(textChildName, "content")) {
					textContent = textChild->GetText();
				}

				if (checkStrings(textChildName, "contentidentifier")) {
					textContent = textChild->GetText();
					usesID = true;
				}
				if (checkStrings(textChildName, "colour")) {

					colour = GenerateVec4(textChild);

				}

				if (checkStrings(textChildName, "position")) {

					pos = glm::vec2(GenerateVec3(textChild).x, GenerateVec3(textChild).y);

				}

				if (checkStrings(textChildName, "scale")) {

					size = glm::vec2(GenerateVec3(textChild).x, GenerateVec3(textChild).y);

				}

				textChild = textChild->NextSiblingElement();
			}
			Text2D * text = new Text2D(shader, textContent);
			text->SetShader(shader);
			text->setPosition(pos);
			text->setUsesID(usesID);
			text->setScale(size);
			text->setColour(colour);

			canvas->AddElement(text);
		}

		if (checkStrings(childName, "button")) {
			
			const char* shader = child->Attribute("shader");

			glm::vec4 colour = glm::vec4(1.0, 1.0, 1.0, 1.0), hoverColour;
			glm::vec2 pos, size;
			std::string textContent;
			std::string onclick;
			XMLElement * buttonChild = child->FirstChildElement();
			while (buttonChild != nullptr)
			{
				const char* buttonChildName = buttonChild->Name();

				if (checkStrings(buttonChildName, "content")) {
					textContent = buttonChild->GetText();
				}
				
				if (checkStrings(buttonChildName, "onclick")) {
					onclick = buttonChild->GetText();
				}
				if (checkStrings(buttonChildName, "colour")) {

					colour = GenerateVec4(buttonChild);

				}

				if (checkStrings(buttonChildName, "colourHover")) {

					hoverColour = GenerateVec4(buttonChild);

				}

				if (checkStrings(buttonChildName, "position")) {

					pos = glm::vec2(GenerateVec3(buttonChild).x, GenerateVec3(buttonChild).y);

				}

				if (checkStrings(buttonChildName, "scale")) {

					size = glm::vec2(GenerateVec3(buttonChild).x, GenerateVec3(buttonChild).y);

				}

				buttonChild = buttonChild->NextSiblingElement();
			}
			Text2D * text = new Text2D("text", textContent);
			text->SetShader("text");
			text->setPosition(glm::vec2(pos.x, pos.y + (size.y / 2) - 16));
			//text->setScale(size);
			text->setColour(glm::vec4(1.0,1.0,1.0,1.0));
			CanvasButton * button = new CanvasButton(nullptr, colour);
			button->SetShader(shader);
			button->setPosition(pos);
			button->setScale(size);
			button->setHoverColour(hoverColour);
			button->setOnClickListener(ResourceManager::getInstance()->getButtonFunctions(onclick));


			canvas->AddElement(button);
			canvas->AddElement(text);
		
		
		}

		child = child->NextSiblingElement();
	}


	pScene->getGameObjects()->at(pIndex).registerComponent(canvas);
	canvas->setParent(&pScene->getGameObjects()->at(pIndex));

	if (checkStrings(type, "menu")) {
		Proxy::getInstance()->setUIFocus(true);
		Proxy::getInstance()->requestCursorDrawChange(true);
	}
	else {
		Proxy::getInstance()->setUIFocus(false);
		Proxy::getInstance()->requestCursorDrawChange(false);
	}
}

