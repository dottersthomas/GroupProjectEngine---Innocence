-- Test class for defining a standard script within lua

require("InputTable")

-- set speed
local moving = false -- Used to stop rotating on the spot
local speed = 20
local rot = 0

Test = 
{
	Start = function()
		r = gameObject:getComponent("RigidBody").acceleration
	end,
	
	Update = function(dt)
		r.y = 0
		r.x = 0
		r.z = 0
		moving = false -- Reset variable
		-- Check if any of the input keys have been pressed
		if (Input.isKeyDown(Key.W, 0)) then
		--	moving = true
		--	currentPos = gameObject.transform.position -- Get current position
		--	calc = (speed * dt) 
		--	currentPos.z = currentPos.z + calc * math.cos(gameObject.transform.rotation.y) -- Modify position
		--	currentPos.x = currentPos.x + calc * math.sin(gameObject.transform.rotation.y)
		--	gameObject.transform.position = currentPos -- Set position	
		r.z =  speed * math.cos(gameObject.transform.rotation.y) -- Modify position
		r.x =  speed * math.sin(gameObject.transform.rotation.y)
		--	r.z = speed
		end
		if (Input.isKeyDown(Key.S, 0)) then
		--	moving = true
		--	currentPos = gameObject.transform.position -- Get current position
		--	calc = (speed * dt) 
		--	currentPos.z = currentPos.z - calc * math.cos(gameObject.transform.rotation.y) -- Modify position
		--	currentPos.x = currentPos.x - calc * math.sin(gameObject.transform.rotation.y)
		--	gameObject.transform.position = currentPos -- Set position
			r.z = - speed * math.cos(gameObject.transform.rotation.y) -- Modify position
			r.x =  - speed * math.sin(gameObject.transform.rotation.y)

		end
		
		if (Input.isKeyDown(Key.A, 0)) then
			--if (moving == false) then return end
			--currentRot = gameObject.transform.rotation -- Get current rotation
			--currentRot.y = currentRot.y + speed * dt -- Modify rotation
			--gameObject.transform.rotation = currentRot -- Set rotation
			r.x =  speed * math.sin(gameObject.transform.rotation.y+1.57)
			r.z =  speed * math.cos(gameObject.transform.rotation.y+1.57)
		
		end
		if (Input.isKeyDown(Key.D, 0)) then
			--if (moving == false) then return end
			--currentRot = gameObject.transform.rotation -- Get current rotation
			--currentRot.y = currentRot.y - speed * dt -- Modify rotation
			--gameObject.transform.rotation = currentRot -- Set rotation
			r.x =  -speed * math.sin(gameObject.transform.rotation.y+1.57)
			r.z =  -speed * math.cos(gameObject.transform.rotation.y+1.57)
			
		end
	   if (Input.isKeyDown(Key.SPACE,0)) then
			r.y = 50
			
			gameObject:getComponent("RigidBody").grounded = false
			print(r.y)
		end
		print(r.x)
		print(r.y)
		print(r.z)
		gameObject:getComponent("RigidBody").acceleration = r
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}