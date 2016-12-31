local stack = require("stack")

local mapgen = {}

local createMatrix = function(x, y, init)
   local matrix = {}
   for i = 1, x do
      matrix[i] = {}
      for j = 1, y do
	 matrix[i][j] = init(i, j)
      end
   end
   return matrix
end

local condense = function(map, temp, rep, recurse)
   for i = 2, #map - 1 do
      for j = 2, #map[i] - 1 do
	 local count = 0
	 for ii = i - 1, i + 1 do
	    for jj = j - 1, j + 1 do
	       if ii ~= i or jj ~= j then
		  count = count + map[ii][jj]
	       end
	    end
	 end
	 if map[i][j] == 1 then
	    if count < 2 then
	       temp[i][j] = 0
	    else
	       temp[i][j] = 1
	    end
	 else
	    if count > 5 then
	       temp[i][j] = 1
	    else
	       temp[i][j] = 0
	    end
	 end
      end
   end
   for i = 2, #map - 1 do
      for j = 2, #map[i] - 1 do
	 map[i][j] = temp[i][j]
      end
   end
   if rep > 0 then
      return recurse(map, temp, rep - 1)
   end
end

local bfs = function(map, x, y, sub)
   local s = stack:new()
   s:push({x, y})
   local target = map[x][y]
   map[x][y] = sub
   local count = 1
   local action = function(coord, xOff, yOff)
      local i, j = coord[1] + xOff, coord[2] + yOff
      if i > 1 and i < #map - 1 and j > 1 and j < #map[i] - 1 then
	 if map[i][j] == target then
	    map[i][j] = sub
	    s:push({i, j})
	    count = count + 1
	 end
      end
   end
   while not s:isEmpty() do
      local coord = s:pop()
      action(coord, -1,  0)
      action(coord,  0,  1)
      action(coord,  0, -1)
      action(coord,  1,  0)
   end
   return count
end

local replace = function(map, target, sub)
   for i = 1, #map do
      for j = 1, #map[i] do
	 if map[i][j] == target then
	    map[i][j] = sub
	 end
      end
   end
end

function mapgen.createMap(x, y, border, smoothing, minTiles)
   local count = 0
   local map
   repeat
      local sieve = function(i, j)
	 if (i > border and i < x - border and
	     j > border and j < y - border) then
	    return calc.random(2, 0)
	 else
	    return 0
	 end
      end
      map = createMatrix(x, y, sieve)
      condense(map, createMatrix(x, y, function() return 0 end), smoothing, condense)
      local randX, randY
      repeat
	 randX, randY = calc.random(x, 1), calc.random(y, 1)
      until map[randX][randY] == 1
      count = bfs(map, randX, randY, 5)
   until count >= minTiles
   replace(map, 1, 0)
   replace(map, 5, 1)
   return map
end

function mapgen.displayMap(map)
   for i = 1, #map do
      for j = 1, #map[i] do
	 if map[i][j] ~= 0 then
	    io.write("@ ")
	 else
	    io.write(". ")
	 end
      end
      io.write("\n")
   end
end

return mapgen
