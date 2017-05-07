require("InputTable")

Ghost = 
{
	Start = function()
		-- Create timer
		timer = Timer()
		timer:start()
		
		-- Keep track of delay
		lastTime = 0

		radius = 100
		delay =  0


	end,
	
	Update = function(dt)
		if (lastTime == 0) then
			lastTime = timer.time
		end
		
		if (timer.time >= lastTime + delay) then
			-- Teleport within a 25% distance of the player
			
			-- Get pos
			playerPos = WindowManager.instance.sceneManager.currentScene:getGameObject("Player").transform.position
			-- Create new pos
			angle = math.random(1,6)
			xoff = playerPos.x + radius * math.cos(angle)
			yoff = playerPos.z + radius * math.sin(angle)
			print(xoff)
			print(yoff)

			newX = math.random() * ((playerPos.x + xoff * 1.25) - (playerPos.x+xoff * 1.05)) + (playerPos.x+xoff * 1.05)
			newZ = math.random() * ((playerPos.z + yoff * 1.25) - (playerPos.z+yoff * 1.05)) + (playerPos.z+yoff * 1.05)
			--local newX = math.random(math.floor(playerPos.x)+math.floor(xoff * 1.05), math.floor(playerPos.x)+math.floor(xoff * 1.25))
		--	local newZ = math.random(math.floor(playerPos.z)+math.floor(yoff * 1.05), math.floor(playerPos.z)+math.floor(yoff * 1.25))
			newPos = Vec3(newX, playerPos.y, newZ)
			-- Set new pos
			WindowManager.instance.sceneManager.currentScene:getGameObject("Ghost").transform.position = newPos
			
			lastTime = 0
			if(radius > 0)then
			radius = radius - 10
			end
			delay = math.random(5, 15)
			timer:reset()
		end

		if(WindowManager.instance.sceneManager.currentScene.postProcessEnabled == 1) then
		
			print("Night")
			gameObject:getComponent("RenderComponent"):toggleDrawing()


		end
		
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}