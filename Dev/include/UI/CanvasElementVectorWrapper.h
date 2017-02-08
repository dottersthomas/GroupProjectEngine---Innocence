#ifndef _CANVAS_ELEMENT_VECTOR_WRAPPER_H_
#define _CANVAS_ELEMENT_VECTOR_WRAPPER_H_

#include "CanvasElement.h"
#include <vector>

class CanvasElement;

struct CanvasElementVectorWrapper {

	typedef std::vector<CanvasElement*> t_Canvas_Elements_Vector_;

	typedef t_Canvas_Elements_Vector_::iterator t_Canvas_Elements_Iter;
	typedef t_Canvas_Elements_Vector_::const_iterator t_Canvas_Elements_Const_Iter;
};

#endif