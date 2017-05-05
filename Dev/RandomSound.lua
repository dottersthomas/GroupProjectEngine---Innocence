-- Test class for defining a standard script within lua

require("Util")

RandomSound =
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
		RandomSound.addFile("Assets/Audio/Creepy - Little (Find Doll).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Little (Find You).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Little (Hide).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Ring.mp3")
		RandomSound.addFile("Assets/Audio/Crying Ghost Sound.mp3")
		RandomSound.addFile("Assets/Audio/Snapping - Branches.mp3")
		local i = RandomSound.getRandom()
		currentSound = Sound(files[i], false)
		currentSound:playLoop()
		
		local fil=io.open(files[1],"r")
		if fil~=nil then io.close(fil) print "found" else print "not found" end
	end,
	
	Update = function(dt)
		
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}