local counterMax = 5
local counter = 0

CollectableManager = 
{
	addCounter = function()
		counter = counter + 1
	end,

	getCounter = function()
		return counter
	end,
}