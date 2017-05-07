#include "General\XML\XMLParser.h"
#include "UI\CanvasButton.h"

bool XMLParser::Parse(std::string pPath)
{
	XMLError error = m_Doc_.LoadFile(pPath.c_str());

	if (error != XML_SUCCESS)
		return false;
	m_Root_ = m_Doc_.FirstChild();

	return true;
}

std::vector<XMLElement*> XMLParser::GetElements(std::string filter)
{

	std::vector<XMLElement*> temp;
	for (XMLElement* e = m_Root_->FirstChildElement(filter.c_str()); e != NULL; e = e->NextSiblingElement(filter.c_str()))
	{
		temp.push_back(e);
	}

	return temp;
}


Scene * XMLParser::LoadScene()
{
	Scene * _Scene = new Scene("");

	XMLElement * sceneElem = m_Doc_.FirstChildElement("scene");
	XMLElement * sceneContent = sceneElem->FirstChildElement("scenecontent");
	XMLElement * gObject = sceneContent->FirstChildElement("GameObject");
	while (gObject != nullptr)
	{

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

glm::vec3 XMLParser::GenerateVec3(XMLElement * element)
{

	XMLElement * child = element->FirstChildElement();
	float x = 0, y = 0, z = 0;
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "x"))
		{
			child->QueryFloatText(&x);
		}
		if (checkStrings(childName, "y"))
		{
			child->QueryFloatText(&y);
		}
		if (checkStrings(childName, "z"))
		{
			child->QueryFloatText(&z);
		}

		child = child->NextSiblingElement();
	}

	return glm::vec3(x, y, z);

}

glm::vec4 XMLParser::GenerateVec4(XMLElement * element)
{

	XMLElement * child = element->FirstChildElement();
	float x = 0, y = 0, z = 0, w = 0;
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "x"))
		{
			child->QueryFloatText(&x);
		}
		if (checkStrings(childName, "y"))
		{
			child->QueryFloatText(&y);
		}
		if (checkStrings(childName, "z"))
		{
			child->QueryFloatText(&z);
		}
		if (checkStrings(childName, "w"))
		{
			child->QueryFloatText(&w);
		}

		child = child->NextSiblingElement();
	}

	return glm::vec4(x, y, z, w);

}


void XMLParser::ProcessComponent(Scene * pScene, XMLElement * pElement, int pIndex)
{
	const char* componentName = pElement->Name();
	const char* tag = pElement->Attribute("tag");

	//Setup the Transform Component
	if (checkStrings(componentName, "TransformComponent"))
	{
		TransformComponent * tc = pScene->getGameObjects()->at(pIndex).GetComponentByType<TransformComponent>();
		tc->setTag(tag);
		XMLElement * child = pElement->FirstChildElement();
		while (child != nullptr)
		{
			const char* childName = child->Name();
			if (checkStrings(childName, "position")) {
				tc->setPosition( GenerateVec3(child));
			}

			if (checkStrings(childName, "rotation")) {
				tc->setRotation( GenerateVec3(child));
			}
			if (checkStrings(childName, "scale")) {
				tc->setScale( GenerateVec3(child));
			}

			child = child->NextSiblingElement();

		}	
	}

	//Setup the Render Component
	if (checkStrings(componentName, "RenderComponent"))
	{

		RenderComponent * rc = new RenderComponent(&pScene->getGameObjects()->at(pIndex), std::string("default"));
		rc->setTag(tag);
		XMLElement * child = pElement->FirstChildElement();
		while (child != nullptr)
		{
			const char* childName = child->Name();
			if (checkStrings(childName, "Model")) {
				std::string temp = AssetPath + child->GetText();
				GLchar* path = (GLchar*)temp.c_str();
				Model model = loader.LoadModel(path);

				rc->AttachModel(model);
			}
			if (checkStrings(childName, "CullBack")) {
				if (child->BoolText() == true)
					rc->toggleBackCulling(true);
				else
					rc->toggleBackCulling(false);
			}

			child = child->NextSiblingElement();

		}


		pScene->getGameObjects()->at(pIndex).registerComponent(rc);
		rc->setParent(&pScene->getGameObjects()->at(pIndex));

	}
		
	if (checkStrings(componentName, "FirstPersonCameraComponent"))
	{


		XMLElement * child = pElement->FirstChildElement();
		glm::vec3 position;
		bool main = false;

		const char* name = pElement->Attribute("name");

		while (child != nullptr)
		{
			const char* childName = child->Name();

			if (checkStrings(childName, "position"))
			{
				position = GenerateVec3(child);
			}
			if (checkStrings(childName, "main")) {

				child->QueryBoolText(&main);

			}
			child = child->NextSiblingElement();
		}
		FirstPersonCameraComponent * camera = new FirstPersonCameraComponent(&pScene->getGameObjects()->at(pIndex), std::string(name), position);
		camera->setTag(tag);
		pScene->getGameObjects()->at(pIndex).registerComponent(camera);
		camera->setParent(&pScene->getGameObjects()->at(pIndex));

		if (main)
			pScene->attachMainCameraComponent(pScene->getGameObjects()->at(pIndex).GetComponentByType<FirstPersonCameraComponent>());

	}
	if (checkStrings(componentName, "Script"))
	{
		XMLElement * child = pElement->FirstChildElement();
		std::string path;
		std::string name;
		while (child != nullptr)
		{
			const char* childName = child->Name();
			
			if (checkStrings(childName, "path")) {
				std::string temp = AssetPath + child->GetText();
				path = temp;
			}
			if (checkStrings(childName, "name")) {
				name = child->GetText();
			}

			child = child->NextSiblingElement();
		}
		Script * s1 = new Script(path, name);
		pScene->getGameObjects()->at(pIndex).registerComponent(s1);
		s1->setParent(&pScene->getGameObjects()->at(pIndex));
	}
	if (checkStrings(componentName, "BoxCollider")) {
		XMLElement * child = pElement->FirstChildElement();
		bool isTrigger = false;

		while (child != nullptr)
		{
			const char* childName = child->Name();
			if (checkStrings(childName, "trigger")) {
				child->QueryBoolText(&isTrigger);
			}

			child = child->NextSiblingElement();

		}

		BoxCollider * bc = new BoxCollider(&pScene->getGameObjects()->at(pIndex), isTrigger);
		pScene->getGameObjects()->at(pIndex).registerComponent(bc);
		bc->setParent(&pScene->getGameObjects()->at(pIndex));
	}
	if (checkStrings(componentName, "RigidBody")) {
		XMLElement * child = pElement->FirstChildElement();

		RigidBody * rb = new RigidBody();
		bool isGrounded = false;
		float gravity = 1.0f;
		while (child != nullptr)
		{
			const char* childName = child->Name();
			if (checkStrings(childName, "acceleration")) {
				rb->SetAcc(GenerateVec3(child));
			}
			if (checkStrings(childName, "grounded")) {
				child->QueryBoolText(&isGrounded);

			}
			if (checkStrings(childName, "gravity")) {
				child->QueryFloatText(&gravity);

			}

			child = child->NextSiblingElement();

		}
		rb->SetGravScale(gravity);
		rb->setGrounded(isGrounded);
		pScene->getGameObjects()->at(pIndex).registerComponent(rb);
		rb->setParent(&pScene->getGameObjects()->at(pIndex));
	}

	//Create the GUI here.
	if (checkStrings(componentName, "canvas"))
	{
		ProcessCanvas(pScene, pElement, pIndex);
	}


}

//Process the GUI and create a canvas component for the overlay.
void XMLParser::ProcessCanvas(Scene * pScene, XMLElement * pElement, int pIndex)
{
	const char* componentName = pElement->Name();

	const char* type = pElement->Attribute("type");
	CanvasComponent * canvas = new CanvasComponent(&pScene->getGameObjects()->at(pIndex));
	XMLElement * child = pElement->FirstChildElement();
	while (child != nullptr)
	{
		const char* childName = child->Name();
		if (checkStrings(childName, "rect")) {


			const char* shader = "gui_plain";

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
			const char* shader = "text_shader";

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
			
			const char* shader = "gui_plain";

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

