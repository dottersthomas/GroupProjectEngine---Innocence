function math.clamp(low, n, high) return math.min(math.max(n, low), high) end

function table.size(t) -- Only works when the table is a list not a dictionary
	local count = 0
	for k,v in pairs(t) do
		count = count + 1
	end
	return count
end

function table.invert(t)
  local it = { }
  for k, v in pairs(t) do it[v] = k end
  return it
end

function table.contains(table, element)
  for k, value in pairs(table) do
    if value == element then
      return true
    end
  end
  return false
end