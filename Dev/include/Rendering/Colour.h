#ifndef _RENDERING_COLOUR_H_
#define _RENDERING_COLOUR_H_

#include <glm\glm.hpp>
#include <iostream>

struct Colour {

	Colour(){ }
	Colour(glm::vec3 pColour, std::string pType) {
		M_Colour = pColour;
		M_Type = pType;
	}

	std::string M_Type;

	glm::vec3 M_Colour;


};

#endif