#include "Scripting/Script.h"

// --- Static variables

int Script::idNum = 0;

// --- Constructor

Script::Script(std::string scriptName, std::string path) : id("obj_" + std::to_string(idNum + 1))
{	
	// Load script from file
	_file.eval_file(path);
	_file.eval("auto " + id + " = " + scriptName + "();");

	// Register base class
	_file.add(chaiscript::base_class<Component, Script>());

	// Create obj
	obj = std::make_shared<chaiscript::Boxed_Value>(_file.eval(id));

	// Register component functions
	chai_Start = _file.eval<std::function<void(chaiscript::Boxed_Value&)>>("Start");
	chai_Update = _file.eval<std::function<void(chaiscript::Boxed_Value&, double)>>("Update");
	chai_LateUpdate = _file.eval<std::function<void(chaiscript::Boxed_Value&, double)>>("LateUpdate");
	chai_Destroy = _file.eval<std::function<void(chaiscript::Boxed_Value&)>>("Destroy");
}

// --- Destructor

Script::~Script() {}

// --- Methods

void Script::Start()
{
	chai_Start(*obj);
}

void Script::Update(double dt)
{
	chai_Update(*obj, dt);
}

void Script::LateUpdate(double dt)
{
	chai_LateUpdate(*obj, dt);
}

void Script::Destroy()
{
	chai_Destroy(*obj);
}