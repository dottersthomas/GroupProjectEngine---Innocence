require("TriggerStatus")

Collectible = 
{
	Start = function()

	end,
	
	Update = function(dt)
		collider = gameObject:getComponent("BoxCollider")
		if (collider.triggerStatus == Trigger.ENTER) then
			print "HELLO"
			-- Collision, Pick up object
			WindowManager.instance.sceneManager.currentScene:removeGameObject(gameObject)
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}