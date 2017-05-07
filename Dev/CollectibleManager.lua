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
}