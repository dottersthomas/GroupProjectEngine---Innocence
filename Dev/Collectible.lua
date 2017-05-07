require("TriggerStatus")
require("CollectibleManager")

Collectible = 
{
	Start = function()
		
	end,
	
	Update = function(dt)
		collider = gameObject:getComponent("BoxCollider")
		
		if (collider.triggerStatus == Trigger.ENTER) then
			-- Add to collectible global
			CollectibleManager.addCounter()
			-- Collision, Pick up object (Stop drawing)
			gameObject.GetComponent("RenderComponent").toggleDraw(false)
			gameObject.transform.position = Vec3(0, -100, 0)
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}