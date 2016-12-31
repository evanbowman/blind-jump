--[[
Calculates a drawable area to match
the aspect ratio of the desktop monitor.
If your aspect ratio isn't supported, simply
add an elseif condition for the ratio of your
monitor's width to height ratio.

The optimal area returned from this function
is a value nearest to 650,000 square pixels.
--]]
function getDrawableArea()
   local w, h = system.getScreenSize()
   local aspect = w / h
   if aspect == 16 / 9 then
      return 1072, 603
   elseif aspect == 16 / 10 then
      return 1024, 640
   elseif aspect == 4 / 3 then
      return 936, 702
   elseif aspect == 5 / 4 then
      return 905, 724
   elseif aspect == 9 / 16 then
      return 603 / 1072
   elseif aspect == 10 / 16 then
      return 640 / 1024
   elseif aspect == 3 / 4 then
      return 702, 936
   elseif aspect == 4 / 5 then
      return 724, 905
   else
      print("Error: your aspect ratio is unsupported!")
      print("To remedy this, add it to the file conf.lua")
      system.quit()
   end
end

--[[
Edit these values to mess with the vsync,
mouse visibility, framerate limit, etc.   
--]]
function getConf()
   local conf = {}
   local w, h = getDrawableArea()
   local conf = {
      width = w,
      height = h,
      --[[ The camera scrolls, so this is
	 required because more stuff needs to be 
	 drawn than will fit in the camera view 
	 (in order to achieve pixel perfect scrolling) ]]
      fractionVisible = 0.60
   }
   return conf
end
