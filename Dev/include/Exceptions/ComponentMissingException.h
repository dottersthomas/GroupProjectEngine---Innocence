#ifndef _COMPONENT_MISSING_EXCEPTION_H_
#define _COMPONENT_MISSING_EXCEPTION_H_

#include <exception>
#include <intrin.h>

using namespace std;

//Called if a Component is missing.
struct ComponentMissingException : public exception {

	virtual const char* what() const throw()
	{
		return "Component Not Found";
	}
};



#endif
