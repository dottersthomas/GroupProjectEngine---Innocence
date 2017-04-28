-- Test class for defining a standard script within lua

Test = 
{
	Start = function()
		t = gameObject:getComponent("TransformComponent") -- Can be shortened to gameObject.transform
		print(t.position)
	end,
	
	Update = function()
		
	end,
	
	LateUpdate = function()
		
	end,
	
	Destroy = function()
		
	end,
}