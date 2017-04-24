-- Test class for defining a standard script within lua

g = GameObject("T2")

Test2 = 
{
	Start = function()
		print(g.name)
	end
}