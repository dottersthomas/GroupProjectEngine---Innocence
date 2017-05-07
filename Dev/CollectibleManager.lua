local counterMax = 5
local counter = 0

CollectibleManager = 
{
	addCounter = function()
		counter = counter + 1
	end,

	getCounter = function()
		return counter
	end,

	Start = function()
		goal = 5 -- Total number of objects to collect
	end,
	
	Update = function(dt)
		-- Check if game is over
		if (counter == counterMax) then
			-- Game Over
			
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}