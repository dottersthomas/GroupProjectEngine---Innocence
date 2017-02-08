#ifndef _GUI_MESH_VECTOR_WRAPPER_H_
#define _GUI_MESH_VECTOR_WRAPPER_H_

#include "GUIMesh.h"
#include <vector>


struct GUIMeshVectorWrapper {

	typedef std::vector<GUIMesh*> t_GUI_Mesh_Vector_;

	typedef t_GUI_Mesh_Vector_::iterator t_GUI_Mesh_Iter;
	typedef t_GUI_Mesh_Vector_::const_iterator t_GUI_Mesh_Const_Iter;
};

#endif