#include "Rendering\ResourceManager.h"

#include "Rendering\MeshFactory.h"

ResourceManager * ResourceManager::s_instance = 0;

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		std::string details = "#version 330 core \n #define POINT_LIGHTS " + std::to_string(pointLights) + " \n";
		vertexCode = vShaderStream.str();
		fragmentCode = details + fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	// 2. Now create shader GameObject from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);
	return shader;
}


Texture ResourceManager::loadTexture(const GLchar *filePath, GLboolean alpha, std::string name) {
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}


	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(filePath, "rb");

	if (!file) { printf("Image could not be opened\n"); }


	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);


	// Now generate texture
	texture = Texture(width, height, data);
	// And finally free image data

	//Everything is in memory now, the file can be closed
	fclose(file);

	Textures[name] = texture;
	return Textures[name];
}

Texture ResourceManager::loadTextureSOIL(const GLchar *filePath, GLboolean alpha, std::string name) {
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	int width, height;
	unsigned char * data;
	if (alpha)
		data = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGBA);
	else
		data = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);


	texture = Texture(width, height, data);

	SOIL_free_image_data(data);


	Textures[name] = texture;
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

bool ResourceManager::useShader(std::string pId) {

	//Try to find the shader, and if so, use it, otherwise return false to prevent error.
	auto iter = Shaders.find(pId);
	if (iter != Shaders.end())
	{
		// key 2 exists, do something with iter->second (the value)
		iter->second.Use();
		m_currentShaderIdentifier_ = pId;
		return true;
	}
	return false;
}

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

RawMesh * ResourceManager::RegisterMesh(std::string pPath, RawMesh pMesh) {
	MeshFactory factory;
	
	Meshes[pPath] = pMesh;
	//Mesh * meshPointer = &Meshes[pPath];

	return &Meshes[pPath];
}

RawMesh ResourceManager::GetRawMesh(std::string pPath) {
	return Meshes[pPath];
}


void ResourceManager::setupTextCharacters(std::string pFont) {


	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen("Textures/font.bmp", "rb");

	if (!file) { printf("Image could not be opened\n"); }


	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);


	fclose(file);



	// Disable byte-alignment restriction
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte i = 0; i < 128; i++)
	{

		GLubyte c = i;
		if (c == 'A') {
			std::cout << "W" << std::endl;
		}

		int y = c / 16;

		
		int x = 0;

		if (c >= 97) {
			while ((y * 16) + x < c) {
				x++;
			}
		}
		else if (c < 97 && c > 16 && (c % 16) == 0) {
			y--;
			x = 15;
		}
		else {
			while ((y * 16) + x < c -1) {
				x++;
			}
		}
		y = 7 - y;

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 512);
		

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		char *subimg = (char*)data + ((x * 32) + (y * 32)* 512) * 3;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_BGR, GL_UNSIGNED_BYTE, subimg);		// Set texture options


		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use

		
		Character character = {
			x,y,32,32, texture
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}


bool ResourceManager::checkMeshExists(std::string pPath) {
	auto iter = Meshes.find(pPath);
	if (iter != Meshes.end())
	{

		if (iter->first == pPath) {
			return true;
		}
	}
	return false;
}



