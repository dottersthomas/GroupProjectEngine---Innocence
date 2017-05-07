-- Test class for defining a standard script within lua

require("InputTable")

-- set speed
local moving = false -- Used to stop rotating on the spot
local speed = 150
local rot = 0


Test = 
{
	Start = function()
		r = gameObject:getComponent("RigidBody").acceleration
		justJump = false
		sprinting = false
		nightvision = false
		energy = 100
		power = 1000
		lastkey = 0
	end,
	
	Update = function(dt)
		print("x")
		print(gameObject.transform.position.x)
		print("z")
		print(gameObject.transform.position.z)
		r.y = 0
		r.x = 0
		r.z = 0
		moving = false -- Reset variable
		if (sprinting == true) then
		if( energy > 0) then
		speed = 300
		energy = energy - 1
		end
		end
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
			if(justJump == false) then
			
			print("lol")
			r.y = 3000
			gameObject:getComponent("RigidBody").grounded = false
			justJump = true
			end
		
			--print(r.y)
		end

		if(Input.isKeyDown(Key.SPACE,0) == false) then
		if(gameObject:getComponent("RigidBody").grounded) then
		justJump = false
		end
		end
		if(Input.isKeyDown(Key.LEFT_SHIFT,0)) then

		sprinting = true
		end
		if(Input.isKeyDown(Key.LEFT_SHIFT,0) == false) then

		sprinting = false
		if(energy < 100)then
		energy = energy + 1
		
		end
		end
		

		 if(Input.isKeyDown(Key.F, 0))then
		 lastkey = 1
		
		 end
		 if(Input.isKeyDown(Key.F, 0) == false)then
		 if(lastkey == 1) then
		 nightvision = not nightvision
		 end
		 lastkey = 0
		
		 end
		if(power < 0) then
		nightvision = false
		end
		 	if(nightvision) then
		 		WindowManager.instance.sceneManager.currentScene:togglePostProcess(1);
				power = power - 1
				end
		 	if(nightvision == false) then
		 
		 		WindowManager.instance.sceneManager.currentScene:togglePostProcess(0);
		 	end
		
		--print(r.x)
		--print(r.y)
		--print(r.z)
		gameObject:getComponent("RigidBody").acceleration = r
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}