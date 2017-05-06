ObjectCollector = 
{
	Start = function()

	end,
	
	Update = function(dt)
		print(gameObject:getComponent("BoxCollider").triggerStatus)
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}