-- Test class for defining a standard script within lua

require("Util")

RandomFile =
{
	addFile = function(path)
		files[#files+1] = path
	end,

	removeFile = function(path)
		-- Invert table to find id
		it = table.invert(files)
		files[it[path]] = nil
	end,
	
	getRandom = function()
		-- Get random number (only first value is inclusive)
		local index = math.random(1, #files)
		return index
	end,
	
	Start = function()
		files = {}
	end,
	
	Update = function(dt)
		f = RandomFile.getRandom()
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}