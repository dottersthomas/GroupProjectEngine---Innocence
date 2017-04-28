-- Test class for defining a standard script within lua

Test = 
{
	Start = function()
		t = gameObject:getComponents("TransformComponent")
		print(t[1].position)
		r = gameObject:getComponent("TransformComponent")
		print(r.position)
	end,
	
	Update = function()
		
	end,
	
	LateUpdate = function()
		
	end,
	
	Destroy = function()
		
	end
}