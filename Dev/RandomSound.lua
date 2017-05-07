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
	
	playRandomSound = function()
		local i = RandomSound.getRandom()
		
		while (i == lastIndex) do
			i = RandomSound.getRandom()
		end
		
		lastIndex = i
		currentSound = Sound(files[i], false)
		currentSound:play()
	end,
	
	Start = function()	
		-- Timer
		timer = Timer()
		
		-- Seed random
		math.randomseed(os.time())
		
		-- Keep track of last file played
		lastIndex = 0
		
		files = {}
		RandomSound.addFile("Assets/Audio/Creepy - Little (Find Doll).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Little (Find You).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Little (Hide).mp3")
		RandomSound.addFile("Assets/Audio/Creepy - Ring.mp3")
		RandomSound.addFile("Assets/Audio/Crying Ghost Sound.mp3")
		RandomSound.addFile("Assets/Audio/Snapping - Branches.mp3")
		
		RandomSound:playRandomSound()
		
		-- Keep track of delay
		lastTime = 0
		delay =  math.random(5, 20)
	end,
	
	Update = function(dt)
		if (currentSound.playing == false) then
		
			if (lastTime == 0) then
				lastTime = timer.time
			end
			
			if (timer.time >= lastTime + delay) then
				lastTime = 0
				delay = math.random(5, 20)
				timer:reset()
				RandomSound.playRandomSound()
			end
			
		end
	end,
	
	LateUpdate = function(dt)
		
	end,
	
	Destroy = function()
		
	end
}