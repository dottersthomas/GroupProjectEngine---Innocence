#ifndef _GameObject_VECTOR_WRAPPER_H_
#define _GameObject_VECTOR_WRAPPER_H_

#include "GameObject.h"

struct GameObjectVectorWrapper {
	typedef std::vector<GameObject> t_GameObject_Vector_;
	typedef t_GameObject_Vector_::iterator t_GameObject_Vector_Iterator_;
	typedef t_GameObject_Vector_::const_iterator t_GameObject_Vector_Const_Iterator_;
};

#endif