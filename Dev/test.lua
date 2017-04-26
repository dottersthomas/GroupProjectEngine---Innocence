-- Test class for defining a standard script within lua

s = Sound("test.mp3")
gameObject:addComponent(s)

Test = 
{
	Start = function()
		print(s.parent.name)
	end,
	
	Update = function()
		
	end,
	
	LateUpdate = function()
		
	end,
	
	Destroy = function()
		
	end,
}