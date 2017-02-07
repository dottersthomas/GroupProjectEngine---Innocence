#ifndef _INPUT_COMPONENT_H_
#define _INPUT_COMPONENT_H_

#include "Component.h"


class InputComponent : public Component {

private:


public:

	InputComponent();

	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt);

	virtual void Destroy();
	virtual void Start();


};

#endif // !_INPUT_COMPONENT_H_
