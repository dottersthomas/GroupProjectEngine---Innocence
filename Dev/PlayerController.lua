-- Test class for defining a standard script within lua

require("InputTable")

-- set speed
local moving = false -- Used to stop rotating on the spot
local speed = 5
local rot = 0

PlayerController = 
{
	Start = function()

	end,
	
	Update = function(dt)
		moving = false -- Reset variable
	
		-- Check if any of the input keys have been pressed
		if (Input.isKeyDown(Key.W, 0)) then
			moving = true
			currentPos = gameObject.transform.position -- Get current position
			calc = (speed * dt) 
			currentPos.z = currentPos.z + calc * math.cos(gameObject.transform.rotation.y) -- Modify position
			currentPos.x = currentPos.x + calc * math.sin(gameObject.transform.rotation.y)
			gameObject.transform.position = currentPos -- Set position
		elseif (Input.isKeyDown(Key.S, 0)) then
			moving = true
			currentPos = gameObject.transform.position -- Get current position
			calc = (speed * dt) 
			currentPos.z = currentPos.z - calc * math.cos(gameObject.transform.rotation.y) -- Modify position
			currentPos.x = currentPos.x - calc * math.sin(gameObject.transform.rotation.y)
			gameObject.transform.position = currentPos -- Set position
		end
		
		if (Input.isKeyDown(Key.A, 0)) then
			if (moving == false) then return end
			currentRot = gameObject.transform.rotation -- Get current rotation
			currentRot.y = currentRot.y + speed * dt -- Modify rotation
			gameObject.transform.rotation = currentRot -- Set rotation
		elseif (Input.isKeyDown(Key.D, 0)) then
			if (moving == false) then return end
			currentRot = gameObject.transform.rotation -- Get current rotation
			currentRot.y = currentRot.y - speed * dt -- Modify rotation
			gameObject.transform.rotation = currentRot -- Set rotation
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}