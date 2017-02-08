#ifndef _COMPONENT_VECTOR_WRAPPER_H_
#define _COMPONENT_VECTOR_WRAPPER_H_

#include "Component.h"
#include <vector>

class Component;


struct ComponentVectorWrapper {

	typedef std::vector<Component*> t_Components_Vector_;

	typedef t_Components_Vector_::iterator t_Component_Iter;
	typedef t_Components_Vector_::const_iterator t_Component_Const_Iter;
};

#endif