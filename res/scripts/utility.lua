utility = {}

function utility.setLayerFixedStretched(id, lib, width, height)
   local viewportW, viewportH = camera.getViewportSize()
   lib.setFixedEnabled(id, true)
   lib.setScale(id, viewportW * 0.72 / width, viewportH * 0.72 / height)
end

return utility
