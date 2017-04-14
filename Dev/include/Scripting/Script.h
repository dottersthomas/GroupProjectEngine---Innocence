#pragma once 

#include <chaiscript/chaiscript.hpp>
#include "Component.h"

class Script : public Component
{
public:
	static int idNum;
	const std::string id;
	std::shared_ptr<chaiscript::Boxed_Value> obj;

	explicit Script(std::string scriptName, std::string path);
	~Script();
	 
	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;
private:
	chaiscript::ChaiScript _file;

	std::function<void(chaiscript::Boxed_Value&)> chai_Start;
	std::function<void(chaiscript::Boxed_Value&, double)> chai_Update;
	std::function<void(chaiscript::Boxed_Value&, double)> chai_LateUpdate;
	std::function<void(chaiscript::Boxed_Value&)> chai_Destroy;
};