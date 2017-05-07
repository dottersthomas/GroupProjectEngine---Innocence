require("InputTable")

Ghost = 
{
	Start = function()
		-- Create timer
		timer = Timer()
		timer:start()
		
		-- Keep track of delay
		lastTime = 0
		delay =  math.random(5, 15)
	end,
	
	Update = function(dt)
		if (lastTime == 0) then
			lastTime = timer.time
		end
		
		if (timer.time >= lastTime + 0) then
			-- Teleport within a 25% distance of the player
			
			-- Get pos
			playerPos = WindowManager.instance.sceneManager.currentScene:getGameObject("Player").transform.position
			-- Create new pos
			local newX = math.random(playerPos.x, playerPos.x * 1.25)
			local newZ = math.random(playerPos.z, playerPos.z * 1.25)
			newPos = Vec3(newX, playerPos.y, newZ)
			-- Set new pos
			WindowManager.instance.sceneManager.currentScene:getGameObject("Player").transform.position = newPos
			
			lastTime = 0
			delay = math.random(5, 15)
			timer:reset()
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}