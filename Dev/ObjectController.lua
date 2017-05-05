-- Test class for defining a standard script within lua

require("Input")

-- set speed
local speed = 10

ObjectController = 
{
	Start = function()

	end,
	
	Update = function(dt)
		-- Get current position 
		currentPos = gameObject.transform.position

		-- Check if any of the input keys have been pressed
		if (Input.isKeyDown(Key.W, 0)) then
			currentPos.z = currentPos.z + speed * dt
		elseif (Input.isKeyDown(Key.A, 0)) then
			currentPos.x = currentPos.x - speed * dt
		elseif (Input.isKeyDown(Key.S, 0)) then
			currentPos.z = currentPos.z - speed * dt
		elseif (Input.isKeyDown(Key.D, 0)) then
			currentPos.x = currentPos.x + speed * dt
		end
		
		-- Set the position
		gameObject.transform.position = currentPos
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}