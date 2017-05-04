-- Test class for defining a standard script within lua

require("InputTable")

Test = 
{
	Start = function()
		t = gameObject:getComponents("TransformComponent")
		print(t[1].position)
		r = gameObject:getComponent("TransformComponent")
		print(r.position)
		
		y = Timer()
		y:start()
	end,
	
	Update = function(dt)
		--f = gameObject:getComponentsByTag("TransformComponent", "Dodo")
		--print(f[1])
		
		if Input.wasKeyPressed(Key.SPACE) then
			y:pause()
		end
		
		print(y:currentTime())
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}