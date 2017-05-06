Rig = 
{
	Start = function()
		r = gameObject:getComponent("RigidBody").acceleration
		r.z = 10
		gameObject:getComponent("RigidBody").acceleration = r
	end,
	
	Update = function(dt)
		r.z = 10
		gameObject:getComponent("RigidBody").acceleration = r
		print(r.acceleration.z)
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}