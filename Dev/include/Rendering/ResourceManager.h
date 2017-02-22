#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>

#include <iostream>
#include <sstream>
#include <fstream>

#include <functional>


#include "Shader.h"
#include "RawMesh.h"
#include "Texture.h"

//Characters for the Text map.
struct Character {
	GLfloat x, y, w, h;
	GLint textureID;
};


//The Resource manager acts as a master manager for all resources within the game, to keep all data loaded and avoid going out of scope.
class ResourceManager {

	//typedefinition for click callbacks.
	typedef std::function< void(void) > t_Click_Handler;
private:
	static ResourceManager * s_instance;

	// Private constructor, that is we do not want any actual resource manager GameObjects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile);

	std::map<std::string, Shader>    Shaders;	//All Shaders
	std::map<std::string, Texture>   Textures;	//All Textures
	std::map<std::string, RawMesh>	 Meshes;	//All Raw Mesh data
	std::map<GLchar, Character> Characters;		//All Characters
	std::map<std::string, t_Click_Handler> buttonClickFunctions;	//All The click Callbacks.
	std::map<std::string, std::string> textIdentifiers;	//All unique text id's

	std::string m_currentShaderIdentifier_;	//Current shader in use.

public:

	//Get the instance of the resource manager.
	static ResourceManager *getInstance()
	{

		if (s_instance == 0) {

			ResourceManager * temp = new ResourceManager();
			s_instance = temp;



		}
		// Instantiated on first use.
		return s_instance;
	}
	// Resource storage

	bool useShader(std::string pId);


	//Get the current shaders id.
	std::string getCurrentShaderID() {
		return m_currentShaderIdentifier_;
	}

	//Load a shader and compile it.
	Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name);
	// Retrieves a stored sader
	Shader& GetShader(std::string name);

	Texture loadTexture(const GLchar *file, GLboolean alpha, std::string name);
	Texture GetTexture(std::string name);

	//Register a mesh to prevent reloading the file.
	RawMesh * RegisterMesh(std::string pPath, RawMesh pMesh);
	RawMesh GetRawMesh(std::string pPath);

	//Get a character given its ascii data.
	Character getCharacter(GLchar pChar){
		return Characters[pChar];
	}

	//Get the text from the given key.
	std::string getText(std::string pKey) {
		return textIdentifiers[pKey];
	}

	void assignTextIdentifier(std::string pKey, std::string pValue) {
		textIdentifiers[pKey] = pValue;
	}


	void setupTextCharacters(std::string pFont);

	bool checkMeshExists(std::string pPath);

	void attachButtonFunction(std::string pID, t_Click_Handler pClick) {
		buttonClickFunctions[pID] = pClick;
	}

	//Get the click callback function.
	t_Click_Handler getButtonFunctions(std::string pFunction) {
		return buttonClickFunctions[pFunction];
	}

};



#endif // !_RESOURCE_MANAGER_H_
