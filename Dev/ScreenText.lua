require("CollectableManager")

ScreenText = 
{
	Start = function()
		txt = Text2D("text_shader", "Items: 0/5")
		txt.position = Vec2(10, 10)
		txt.scale = Vec2(0.5, 0.5)
		txt.colour = Vec4(1, 1, 1, 1)
		
		canv = gameObject:getComponent("CanvasComponent"):addElement(txt)
	end,
	
	Update = function(dt)
		txt.text = "Items: " .. CollectableManager.getCounter() .. "/5"
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}