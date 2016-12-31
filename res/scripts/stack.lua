local t_remove = table.remove

local stack = {_stack={}, _pointer = 0, _has = {}}
stack.__index = stack

function stack:new()
   return setmetatable({},stack)
end

function stack:push(item)
   if self._has[item] then return end
   self._pointer = self._pointer+1
   self._stack[self._pointer] = item
   self._has[item] = true
   return self
end

function stack:pop()
   local item = self._stack[self._pointer]
   self._pointer = self._pointer-1
   t_remove(self._stack)
   self._has[item] = nil
   return item
end

function stack:isEmpty()
   return (self._pointer == 0)
end

function stack:clear()
   self._stack = {}
   self._has = {}
   self._pointer = 0
   return self
end

return stack
