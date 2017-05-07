require("TriggerStatus")
require("CollectableManager")

Collectable = 
{
	Start = function()
		
	end,
	
	Update = function(dt)
		collider = gameObject:getComponent("BoxCollider")

		if (collider.triggerStatus == Trigger.ENTER) then
			-- Add to collectible global
			CollectableManager.addCounter()
			-- Collision, Pick up object (Stop drawing)
			gameObject:getComponent("RenderComponent"):toggleDrawing(false)
			gameObject.transform.position = Vec3(0, -100, 0)
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}