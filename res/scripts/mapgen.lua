local mapgen = {}

local createMatrix = function(x, y, init)
   local matrix = {}
   for i = 1, x do
      matrix[i] = {}
      for j = 1, y do
	 matrix[i][j] = init()
      end
   end
   return matrix
end

function mapgen.createMap(x, y)
   local map = createMatrix(60, 60, function() return calc.random(2, 0) end)
   return map
end

return mapgen
