#
#  makefile for Blind Jump game
#  Evan Bowman 2016
# 

CC = clang++
override CPPFLAGS += -flto -O2 -std=c++14 -Wall -Werror
LDFLAGS = -flto -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime
EXECUTABLE = BlindJump
SOURCES = $(shell find . -name "*.cpp" | awk '{print length, $$0;}' | sort -nr | cut -d ' ' -f 2-) # Hey it looks nice though
OBJECTS = $(SOURCES:.cpp=.o)
DEBUGFLAGS = # Specify them when calling make

all: $(OBJECTS) ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS)

ResourcePath.o: ResourcePath.hpp
	$(CC) ResourcePath.mm -c -o ResourcePath.o

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o

macOS: all packageScriptMac.sh
	bash packageScriptMac.sh $(EXECUTABLE) BlindJump

depend:
	makedepend -- $(CPPFLAGS) -- $(SOURCES)

# DO NOT DELETE

./playerCollisionFunctions.o: playerCollisionFunctions.hpp wall.hpp
./playerCollisionFunctions.o: /usr/include/stdint.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_int8_t.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_int16_t.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_int32_t.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_int64_t.h
./playerCollisionFunctions.o: /usr/include/_types/_uint8_t.h
./playerCollisionFunctions.o: /usr/include/_types/_uint16_t.h
./playerCollisionFunctions.o: /usr/include/_types/_uint32_t.h
./playerCollisionFunctions.o: /usr/include/_types/_uint64_t.h
./playerCollisionFunctions.o: /usr/include/sys/_types.h
./playerCollisionFunctions.o: /usr/include/sys/cdefs.h
./playerCollisionFunctions.o: /usr/include/sys/_symbol_aliasing.h
./playerCollisionFunctions.o: /usr/include/sys/_posix_availability.h
./playerCollisionFunctions.o: /usr/include/machine/_types.h
./playerCollisionFunctions.o: /usr/include/i386/_types.h
./playerCollisionFunctions.o: /usr/include/sys/_pthread/_pthread_types.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_intptr_t.h
./playerCollisionFunctions.o: /usr/include/sys/_types/_uintptr_t.h
./playerCollisionFunctions.o: /usr/include/_types/_intmax_t.h
./playerCollisionFunctions.o: /usr/include/_types/_uintmax_t.h
./playerCollisionFunctions.o: treasureChest.hpp detailParent.hpp
./playerCollisionFunctions.o: Framework/framework.hpp Framework/utilities.hpp
./playerCollisionFunctions.o: inputController.hpp spriteSheet.hpp rng.hpp
./enemyCreationFunctions.o: enemyCreationFunctions.hpp /usr/include/stdio.h
./enemyCreationFunctions.o: /usr/include/sys/cdefs.h
./enemyCreationFunctions.o: /usr/include/sys/_symbol_aliasing.h
./enemyCreationFunctions.o: /usr/include/sys/_posix_availability.h
./enemyCreationFunctions.o: /usr/include/Availability.h
./enemyCreationFunctions.o: /usr/include/AvailabilityInternal.h
./enemyCreationFunctions.o: /usr/include/_types.h /usr/include/sys/_types.h
./enemyCreationFunctions.o: /usr/include/machine/_types.h
./enemyCreationFunctions.o: /usr/include/i386/_types.h
./enemyCreationFunctions.o: /usr/include/sys/_pthread/_pthread_types.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_va_list.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_size_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_null.h
./enemyCreationFunctions.o: /usr/include/sys/stdio.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_off_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_ssize_t.h
./enemyCreationFunctions.o: /usr/include/secure/_stdio.h
./enemyCreationFunctions.o: /usr/include/secure/_common.h enemyController.hpp
./enemyCreationFunctions.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./enemyCreationFunctions.o: fontController.hpp effectsController.hpp
./enemyCreationFunctions.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./enemyCreationFunctions.o: Framework/framework.hpp Framework/utilities.hpp
./enemyCreationFunctions.o: rng.hpp bulletType1.hpp shotPuff.hpp
./enemyCreationFunctions.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./enemyCreationFunctions.o: spritesheet.hpp ResourceHandler.hpp
./enemyCreationFunctions.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./enemyCreationFunctions.o: turretShot.hpp scoot.hpp wall.hpp
./enemyCreationFunctions.o: /usr/include/stdint.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_int8_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_int16_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_int32_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_int64_t.h
./enemyCreationFunctions.o: /usr/include/_types/_uint8_t.h
./enemyCreationFunctions.o: /usr/include/_types/_uint16_t.h
./enemyCreationFunctions.o: /usr/include/_types/_uint32_t.h
./enemyCreationFunctions.o: /usr/include/_types/_uint64_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_intptr_t.h
./enemyCreationFunctions.o: /usr/include/sys/_types/_uintptr_t.h
./enemyCreationFunctions.o: /usr/include/_types/_intmax_t.h
./enemyCreationFunctions.o: /usr/include/_types/_uintmax_t.h enemy.hpp
./enemyCreationFunctions.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./screenShakeController.o: screenShakeController.hpp player.hpp
./screenShakeController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./screenShakeController.o: /usr/include/sys/_types/_int8_t.h
./screenShakeController.o: /usr/include/sys/_types/_int16_t.h
./screenShakeController.o: /usr/include/sys/_types/_int32_t.h
./screenShakeController.o: /usr/include/sys/_types/_int64_t.h
./screenShakeController.o: /usr/include/_types/_uint8_t.h
./screenShakeController.o: /usr/include/_types/_uint16_t.h
./screenShakeController.o: /usr/include/_types/_uint32_t.h
./screenShakeController.o: /usr/include/_types/_uint64_t.h
./screenShakeController.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./screenShakeController.o: /usr/include/sys/_symbol_aliasing.h
./screenShakeController.o: /usr/include/sys/_posix_availability.h
./screenShakeController.o: /usr/include/machine/_types.h
./screenShakeController.o: /usr/include/i386/_types.h
./screenShakeController.o: /usr/include/sys/_pthread/_pthread_types.h
./screenShakeController.o: /usr/include/sys/_types/_intptr_t.h
./screenShakeController.o: /usr/include/sys/_types/_uintptr_t.h
./screenShakeController.o: /usr/include/_types/_intmax_t.h
./screenShakeController.o: /usr/include/_types/_uintmax_t.h
./screenShakeController.o: enemyController.hpp resourceHandler.hpp
./screenShakeController.o: ResourcePath.hpp turret.hpp /usr/include/stdio.h
./screenShakeController.o: /usr/include/Availability.h
./screenShakeController.o: /usr/include/AvailabilityInternal.h
./screenShakeController.o: /usr/include/_types.h
./screenShakeController.o: /usr/include/sys/_types/_va_list.h
./screenShakeController.o: /usr/include/sys/_types/_size_t.h
./screenShakeController.o: /usr/include/sys/_types/_null.h
./screenShakeController.o: /usr/include/sys/stdio.h
./screenShakeController.o: /usr/include/sys/_types/_off_t.h
./screenShakeController.o: /usr/include/sys/_types/_ssize_t.h
./screenShakeController.o: /usr/include/secure/_stdio.h
./screenShakeController.o: /usr/include/secure/_common.h fontController.hpp
./screenShakeController.o: effectsController.hpp turretFlashEffect.hpp
./screenShakeController.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./screenShakeController.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./screenShakeController.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./screenShakeController.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp
./screenShakeController.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./screenShakeController.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp
./screenShakeController.o: critter.hpp aStar.hpp coordinate.hpp
./screenShakeController.o: detailController.hpp Teleporter.hpp
./screenShakeController.o: detailParent.hpp treasureChest.hpp
./screenShakeController.o: inputController.hpp generalDetail.hpp
./screenShakeController.o: lampLight.hpp userInterface.hpp
./screenShakeController.o: easingTemplates.hpp damagedRobot.hpp rock.hpp
./screenShakeController.o: IntroDoor.hpp soundController.hpp
./turretFlashEffect.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./turretFlashEffect.o: Framework/framework.hpp Framework/utilities.hpp
./turretFlashEffect.o: rng.hpp
./backgroundHandler.o: backgroundHandler.hpp ResourcePath.hpp
./mappingFunctions.o: tileController.hpp wall.hpp /usr/include/stdint.h
./mappingFunctions.o: /usr/include/sys/_types/_int8_t.h
./mappingFunctions.o: /usr/include/sys/_types/_int16_t.h
./mappingFunctions.o: /usr/include/sys/_types/_int32_t.h
./mappingFunctions.o: /usr/include/sys/_types/_int64_t.h
./mappingFunctions.o: /usr/include/_types/_uint8_t.h
./mappingFunctions.o: /usr/include/_types/_uint16_t.h
./mappingFunctions.o: /usr/include/_types/_uint32_t.h
./mappingFunctions.o: /usr/include/_types/_uint64_t.h
./mappingFunctions.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./mappingFunctions.o: /usr/include/sys/_symbol_aliasing.h
./mappingFunctions.o: /usr/include/sys/_posix_availability.h
./mappingFunctions.o: /usr/include/machine/_types.h
./mappingFunctions.o: /usr/include/i386/_types.h
./mappingFunctions.o: /usr/include/sys/_pthread/_pthread_types.h
./mappingFunctions.o: /usr/include/sys/_types/_intptr_t.h
./mappingFunctions.o: /usr/include/sys/_types/_uintptr_t.h
./mappingFunctions.o: /usr/include/_types/_intmax_t.h
./mappingFunctions.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./mappingFunctions.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./mappingFunctions.o: /usr/include/stdio.h /usr/include/Availability.h
./mappingFunctions.o: /usr/include/AvailabilityInternal.h
./mappingFunctions.o: /usr/include/_types.h
./mappingFunctions.o: /usr/include/sys/_types/_va_list.h
./mappingFunctions.o: /usr/include/sys/_types/_size_t.h
./mappingFunctions.o: /usr/include/sys/_types/_null.h
./mappingFunctions.o: /usr/include/sys/stdio.h
./mappingFunctions.o: /usr/include/sys/_types/_off_t.h
./mappingFunctions.o: /usr/include/sys/_types/_ssize_t.h
./mappingFunctions.o: /usr/include/secure/_stdio.h
./mappingFunctions.o: /usr/include/secure/_common.h fontController.hpp
./mappingFunctions.o: effectsController.hpp turretFlashEffect.hpp
./mappingFunctions.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./mappingFunctions.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./mappingFunctions.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./mappingFunctions.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp
./mappingFunctions.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./mappingFunctions.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp
./mappingFunctions.o: critter.hpp aStar.hpp coordinate.hpp
./mappingFunctions.o: mappingFunctions.hpp
./enemyPlacementFn.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
./enemyPlacementFn.o: /usr/include/sys/_symbol_aliasing.h
./enemyPlacementFn.o: /usr/include/sys/_posix_availability.h
./enemyPlacementFn.o: /usr/include/Availability.h
./enemyPlacementFn.o: /usr/include/AvailabilityInternal.h
./enemyPlacementFn.o: /usr/include/_types.h /usr/include/sys/_types.h
./enemyPlacementFn.o: /usr/include/machine/_types.h
./enemyPlacementFn.o: /usr/include/i386/_types.h
./enemyPlacementFn.o: /usr/include/sys/_pthread/_pthread_types.h
./enemyPlacementFn.o: /usr/include/sys/_types/_va_list.h
./enemyPlacementFn.o: /usr/include/sys/_types/_size_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_null.h
./enemyPlacementFn.o: /usr/include/sys/stdio.h
./enemyPlacementFn.o: /usr/include/sys/_types/_off_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_ssize_t.h
./enemyPlacementFn.o: /usr/include/secure/_stdio.h
./enemyPlacementFn.o: /usr/include/secure/_common.h enemyPlacementFn.hpp
./enemyPlacementFn.o: scene.hpp player.hpp tileController.hpp wall.hpp
./enemyPlacementFn.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_int16_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_int32_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_int64_t.h
./enemyPlacementFn.o: /usr/include/_types/_uint8_t.h
./enemyPlacementFn.o: /usr/include/_types/_uint16_t.h
./enemyPlacementFn.o: /usr/include/_types/_uint32_t.h
./enemyPlacementFn.o: /usr/include/_types/_uint64_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_intptr_t.h
./enemyPlacementFn.o: /usr/include/sys/_types/_uintptr_t.h
./enemyPlacementFn.o: /usr/include/_types/_intmax_t.h
./enemyPlacementFn.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./enemyPlacementFn.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./enemyPlacementFn.o: fontController.hpp effectsController.hpp
./enemyPlacementFn.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./enemyPlacementFn.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./enemyPlacementFn.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./enemyPlacementFn.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./enemyPlacementFn.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp
./enemyPlacementFn.o: dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp
./enemyPlacementFn.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./enemyPlacementFn.o: detailController.hpp Teleporter.hpp detailParent.hpp
./enemyPlacementFn.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./enemyPlacementFn.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./enemyPlacementFn.o: damagedRobot.hpp rock.hpp IntroDoor.hpp
./enemyPlacementFn.o: soundController.hpp backgroundHandler.hpp
./enemyPlacementFn.o: screenShakeController.hpp enemyCreationFunctions.hpp
./soundController.o: soundController.hpp ResourcePath.hpp
./resourceHandler.o: resourceHandler.hpp ResourcePath.hpp
./inputController.o: inputController.hpp
./enemyController.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./enemyController.o: turret.hpp /usr/include/stdio.h /usr/include/sys/cdefs.h
./enemyController.o: /usr/include/sys/_symbol_aliasing.h
./enemyController.o: /usr/include/sys/_posix_availability.h
./enemyController.o: /usr/include/Availability.h
./enemyController.o: /usr/include/AvailabilityInternal.h
./enemyController.o: /usr/include/_types.h /usr/include/sys/_types.h
./enemyController.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./enemyController.o: /usr/include/sys/_pthread/_pthread_types.h
./enemyController.o: /usr/include/sys/_types/_va_list.h
./enemyController.o: /usr/include/sys/_types/_size_t.h
./enemyController.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./enemyController.o: /usr/include/sys/_types/_off_t.h
./enemyController.o: /usr/include/sys/_types/_ssize_t.h
./enemyController.o: /usr/include/secure/_stdio.h
./enemyController.o: /usr/include/secure/_common.h fontController.hpp
./enemyController.o: effectsController.hpp turretFlashEffect.hpp
./enemyController.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./enemyController.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./enemyController.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./enemyController.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp
./enemyController.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./enemyController.o: turretShot.hpp scoot.hpp wall.hpp /usr/include/stdint.h
./enemyController.o: /usr/include/sys/_types/_int8_t.h
./enemyController.o: /usr/include/sys/_types/_int16_t.h
./enemyController.o: /usr/include/sys/_types/_int32_t.h
./enemyController.o: /usr/include/sys/_types/_int64_t.h
./enemyController.o: /usr/include/_types/_uint8_t.h
./enemyController.o: /usr/include/_types/_uint16_t.h
./enemyController.o: /usr/include/_types/_uint32_t.h
./enemyController.o: /usr/include/_types/_uint64_t.h
./enemyController.o: /usr/include/sys/_types/_intptr_t.h
./enemyController.o: /usr/include/sys/_types/_uintptr_t.h
./enemyController.o: /usr/include/_types/_intmax_t.h
./enemyController.o: /usr/include/_types/_uintmax_t.h enemy.hpp dasher.hpp
./enemyController.o: critter.hpp aStar.hpp tileController.hpp coordinate.hpp
./enemyController.o: detailController.hpp Teleporter.hpp detailParent.hpp
./enemyController.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./enemyController.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./enemyController.o: damagedRobot.hpp rock.hpp IntroDoor.hpp
./enemyController.o: screenShakeController.hpp player.hpp soundController.hpp
./tileController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./tileController.o: /usr/include/sys/_types/_int8_t.h
./tileController.o: /usr/include/sys/_types/_int16_t.h
./tileController.o: /usr/include/sys/_types/_int32_t.h
./tileController.o: /usr/include/sys/_types/_int64_t.h
./tileController.o: /usr/include/_types/_uint8_t.h
./tileController.o: /usr/include/_types/_uint16_t.h
./tileController.o: /usr/include/_types/_uint32_t.h
./tileController.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./tileController.o: /usr/include/sys/cdefs.h
./tileController.o: /usr/include/sys/_symbol_aliasing.h
./tileController.o: /usr/include/sys/_posix_availability.h
./tileController.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./tileController.o: /usr/include/sys/_pthread/_pthread_types.h
./tileController.o: /usr/include/sys/_types/_intptr_t.h
./tileController.o: /usr/include/sys/_types/_uintptr_t.h
./tileController.o: /usr/include/_types/_intmax_t.h
./tileController.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./tileController.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./tileController.o: /usr/include/stdio.h /usr/include/Availability.h
./tileController.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./tileController.o: /usr/include/sys/_types/_va_list.h
./tileController.o: /usr/include/sys/_types/_size_t.h
./tileController.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./tileController.o: /usr/include/sys/_types/_off_t.h
./tileController.o: /usr/include/sys/_types/_ssize_t.h
./tileController.o: /usr/include/secure/_stdio.h
./tileController.o: /usr/include/secure/_common.h fontController.hpp
./tileController.o: effectsController.hpp turretFlashEffect.hpp
./tileController.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./tileController.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./tileController.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./tileController.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp
./tileController.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./tileController.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./tileController.o: aStar.hpp coordinate.hpp mappingFunctions.hpp
./tileController.o: initMapVectors.hpp drawPixels.hpp
./smallExplosion.o: smallExplosion.hpp spriteSheet.hpp Effect.hpp
./smallExplosion.o: Framework/framework.hpp Framework/utilities.hpp
./initMapVectors.o: initMapVectors.hpp wall.hpp /usr/include/stdint.h
./initMapVectors.o: /usr/include/sys/_types/_int8_t.h
./initMapVectors.o: /usr/include/sys/_types/_int16_t.h
./initMapVectors.o: /usr/include/sys/_types/_int32_t.h
./initMapVectors.o: /usr/include/sys/_types/_int64_t.h
./initMapVectors.o: /usr/include/_types/_uint8_t.h
./initMapVectors.o: /usr/include/_types/_uint16_t.h
./initMapVectors.o: /usr/include/_types/_uint32_t.h
./initMapVectors.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./initMapVectors.o: /usr/include/sys/cdefs.h
./initMapVectors.o: /usr/include/sys/_symbol_aliasing.h
./initMapVectors.o: /usr/include/sys/_posix_availability.h
./initMapVectors.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./initMapVectors.o: /usr/include/sys/_pthread/_pthread_types.h
./initMapVectors.o: /usr/include/sys/_types/_intptr_t.h
./initMapVectors.o: /usr/include/sys/_types/_uintptr_t.h
./initMapVectors.o: /usr/include/_types/_intmax_t.h
./initMapVectors.o: /usr/include/_types/_uintmax_t.h coordinate.hpp
./initMapVectors.o: tileController.hpp enemyController.hpp
./initMapVectors.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./initMapVectors.o: /usr/include/stdio.h /usr/include/Availability.h
./initMapVectors.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./initMapVectors.o: /usr/include/sys/_types/_va_list.h
./initMapVectors.o: /usr/include/sys/_types/_size_t.h
./initMapVectors.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./initMapVectors.o: /usr/include/sys/_types/_off_t.h
./initMapVectors.o: /usr/include/sys/_types/_ssize_t.h
./initMapVectors.o: /usr/include/secure/_stdio.h
./initMapVectors.o: /usr/include/secure/_common.h fontController.hpp
./initMapVectors.o: effectsController.hpp turretFlashEffect.hpp
./initMapVectors.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./initMapVectors.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./initMapVectors.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./initMapVectors.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp
./initMapVectors.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./initMapVectors.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./initMapVectors.o: aStar.hpp
./fontController.o: fontController.hpp resourceHandler.hpp ResourcePath.hpp
./userInterface.o: userInterface.hpp fontController.hpp resourceHandler.hpp
./userInterface.o: ResourcePath.hpp effectsController.hpp
./userInterface.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./userInterface.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./userInterface.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./userInterface.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./userInterface.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp
./userInterface.o: dasherShot.hpp turretShot.hpp inputController.hpp
./userInterface.o: easingTemplates.hpp player.hpp tileController.hpp wall.hpp
./userInterface.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./userInterface.o: /usr/include/sys/_types/_int16_t.h
./userInterface.o: /usr/include/sys/_types/_int32_t.h
./userInterface.o: /usr/include/sys/_types/_int64_t.h
./userInterface.o: /usr/include/_types/_uint8_t.h
./userInterface.o: /usr/include/_types/_uint16_t.h
./userInterface.o: /usr/include/_types/_uint32_t.h
./userInterface.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./userInterface.o: /usr/include/sys/cdefs.h
./userInterface.o: /usr/include/sys/_symbol_aliasing.h
./userInterface.o: /usr/include/sys/_posix_availability.h
./userInterface.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./userInterface.o: /usr/include/sys/_pthread/_pthread_types.h
./userInterface.o: /usr/include/sys/_types/_intptr_t.h
./userInterface.o: /usr/include/sys/_types/_uintptr_t.h
./userInterface.o: /usr/include/_types/_intmax_t.h
./userInterface.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./userInterface.o: turret.hpp /usr/include/stdio.h
./userInterface.o: /usr/include/Availability.h
./userInterface.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./userInterface.o: /usr/include/sys/_types/_va_list.h
./userInterface.o: /usr/include/sys/_types/_size_t.h
./userInterface.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./userInterface.o: /usr/include/sys/_types/_off_t.h
./userInterface.o: /usr/include/sys/_types/_ssize_t.h
./userInterface.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
./userInterface.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./userInterface.o: coordinate.hpp detailController.hpp Teleporter.hpp
./userInterface.o: detailParent.hpp treasureChest.hpp generalDetail.hpp
./userInterface.o: lampLight.hpp damagedRobot.hpp rock.hpp IntroDoor.hpp
./userInterface.o: soundController.hpp
./treasureChest.o: treasureChest.hpp detailParent.hpp Framework/framework.hpp
./treasureChest.o: Framework/utilities.hpp inputController.hpp
./treasureChest.o: spriteSheet.hpp rng.hpp
./generalDetail.o: generalDetail.hpp detailParent.hpp Framework/framework.hpp
./generalDetail.o: Framework/utilities.hpp
./FireExplosion.o: FireExplosion.hpp spriteSheet.hpp Effect.hpp
./FireExplosion.o: Framework/framework.hpp Framework/utilities.hpp
./damagedRobot.o: damagedRobot.hpp detailParent.hpp Framework/framework.hpp
./damagedRobot.o: Framework/utilities.hpp spriteSheet.hpp rng.hpp
./enemyParent.o: enemyParent.hpp wall.hpp /usr/include/stdint.h
./enemyParent.o: /usr/include/sys/_types/_int8_t.h
./enemyParent.o: /usr/include/sys/_types/_int16_t.h
./enemyParent.o: /usr/include/sys/_types/_int32_t.h
./enemyParent.o: /usr/include/sys/_types/_int64_t.h
./enemyParent.o: /usr/include/_types/_uint8_t.h
./enemyParent.o: /usr/include/_types/_uint16_t.h
./enemyParent.o: /usr/include/_types/_uint32_t.h
./enemyParent.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./enemyParent.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./enemyParent.o: /usr/include/sys/_posix_availability.h
./enemyParent.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./enemyParent.o: /usr/include/sys/_pthread/_pthread_types.h
./enemyParent.o: /usr/include/sys/_types/_intptr_t.h
./enemyParent.o: /usr/include/sys/_types/_uintptr_t.h
./enemyParent.o: /usr/include/_types/_intmax_t.h
./enemyParent.o: /usr/include/_types/_uintmax_t.h /usr/include/math.h
./enemyParent.o: /usr/include/Availability.h
./enemyParent.o: /usr/include/AvailabilityInternal.h
./bulletType1.o: bulletType1.hpp spriteSheet.hpp Effect.hpp
./bulletType1.o: Framework/framework.hpp Framework/utilities.hpp
./turretShot.o: turretShot.hpp spritesheet.hpp Effect.hpp
./turretShot.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./dasherShot.o: dasherShot.hpp spriteSheet.hpp Effect.hpp
./dasherShot.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./Teleporter.o: Teleporter.hpp detailParent.hpp Framework/framework.hpp
./Teleporter.o: Framework/utilities.hpp effectsController.hpp
./Teleporter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./Teleporter.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./Teleporter.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./Teleporter.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp
./Teleporter.o: dasherShot.hpp turretShot.hpp
./lampLight.o: lampLight.hpp detailParent.hpp Framework/framework.hpp
./lampLight.o: Framework/utilities.hpp
./enemyShot.o: enemyShot.hpp spriteSheet.hpp Effect.hpp
./enemyShot.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./dashSmoke.o: dashSmoke.hpp
./IntroDoor.o: IntroDoor.hpp detailParent.hpp Framework/framework.hpp
./IntroDoor.o: Framework/utilities.hpp effectsController.hpp
./IntroDoor.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./IntroDoor.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./IntroDoor.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./IntroDoor.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp
./IntroDoor.o: dasherShot.hpp turretShot.hpp screenShakeController.hpp
./IntroDoor.o: player.hpp tileController.hpp wall.hpp /usr/include/stdint.h
./IntroDoor.o: /usr/include/sys/_types/_int8_t.h
./IntroDoor.o: /usr/include/sys/_types/_int16_t.h
./IntroDoor.o: /usr/include/sys/_types/_int32_t.h
./IntroDoor.o: /usr/include/sys/_types/_int64_t.h
./IntroDoor.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
./IntroDoor.o: /usr/include/_types/_uint32_t.h
./IntroDoor.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./IntroDoor.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./IntroDoor.o: /usr/include/sys/_posix_availability.h
./IntroDoor.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./IntroDoor.o: /usr/include/sys/_pthread/_pthread_types.h
./IntroDoor.o: /usr/include/sys/_types/_intptr_t.h
./IntroDoor.o: /usr/include/sys/_types/_uintptr_t.h
./IntroDoor.o: /usr/include/_types/_intmax_t.h
./IntroDoor.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./IntroDoor.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./IntroDoor.o: /usr/include/stdio.h /usr/include/Availability.h
./IntroDoor.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./IntroDoor.o: /usr/include/sys/_types/_va_list.h
./IntroDoor.o: /usr/include/sys/_types/_size_t.h
./IntroDoor.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./IntroDoor.o: /usr/include/sys/_types/_off_t.h
./IntroDoor.o: /usr/include/sys/_types/_ssize_t.h
./IntroDoor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
./IntroDoor.o: fontController.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./IntroDoor.o: aStar.hpp coordinate.hpp detailController.hpp Teleporter.hpp
./IntroDoor.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./IntroDoor.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./IntroDoor.o: damagedRobot.hpp rock.hpp soundController.hpp
./shotPuff.o: shotPuff.hpp spriteSheet.hpp Effect.hpp Framework/framework.hpp
./shotPuff.o: Framework/utilities.hpp
./critter.o: critter.hpp enemy.hpp wall.hpp /usr/include/stdint.h
./critter.o: /usr/include/sys/_types/_int8_t.h
./critter.o: /usr/include/sys/_types/_int16_t.h
./critter.o: /usr/include/sys/_types/_int32_t.h
./critter.o: /usr/include/sys/_types/_int64_t.h
./critter.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
./critter.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
./critter.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./critter.o: /usr/include/sys/_symbol_aliasing.h
./critter.o: /usr/include/sys/_posix_availability.h
./critter.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./critter.o: /usr/include/sys/_pthread/_pthread_types.h
./critter.o: /usr/include/sys/_types/_intptr_t.h
./critter.o: /usr/include/sys/_types/_uintptr_t.h
./critter.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./critter.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./critter.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./critter.o: rng.hpp bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./critter.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./critter.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./critter.o: turretShot.hpp aStar.hpp tileController.hpp enemyController.hpp
./critter.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./critter.o: /usr/include/stdio.h /usr/include/Availability.h
./critter.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./critter.o: /usr/include/sys/_types/_va_list.h
./critter.o: /usr/include/sys/_types/_size_t.h
./critter.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./critter.o: /usr/include/sys/_types/_off_t.h
./critter.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./critter.o: /usr/include/secure/_common.h fontController.hpp scoot.hpp
./critter.o: dasher.hpp coordinate.hpp /usr/include/math.h
./Powerup.o: Powerup.hpp spritesheet.hpp Effect.hpp Framework/framework.hpp
./Powerup.o: Framework/utilities.hpp
./turret.o: turret.hpp /usr/include/stdio.h /usr/include/sys/cdefs.h
./turret.o: /usr/include/sys/_symbol_aliasing.h
./turret.o: /usr/include/sys/_posix_availability.h
./turret.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
./turret.o: /usr/include/_types.h /usr/include/sys/_types.h
./turret.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./turret.o: /usr/include/sys/_pthread/_pthread_types.h
./turret.o: /usr/include/sys/_types/_va_list.h
./turret.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./turret.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./turret.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./turret.o: /usr/include/secure/_common.h fontController.hpp
./turret.o: resourceHandler.hpp ResourcePath.hpp effectsController.hpp
./turret.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./turret.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./turret.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./turret.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp RenderType.hpp
./turret.o: enemyShot.hpp dasherShot.hpp turretShot.hpp angleFunction.hpp
./player.o: player.hpp tileController.hpp wall.hpp /usr/include/stdint.h
./player.o: /usr/include/sys/_types/_int8_t.h
./player.o: /usr/include/sys/_types/_int16_t.h
./player.o: /usr/include/sys/_types/_int32_t.h
./player.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./player.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./player.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./player.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./player.o: /usr/include/sys/_posix_availability.h
./player.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./player.o: /usr/include/sys/_pthread/_pthread_types.h
./player.o: /usr/include/sys/_types/_intptr_t.h
./player.o: /usr/include/sys/_types/_uintptr_t.h
./player.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./player.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./player.o: turret.hpp /usr/include/stdio.h /usr/include/Availability.h
./player.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./player.o: /usr/include/sys/_types/_va_list.h
./player.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./player.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./player.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./player.o: /usr/include/secure/_common.h fontController.hpp
./player.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./player.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./player.o: rng.hpp bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./player.o: smallExplosion.hpp Powerup.hpp spritesheet.hpp
./player.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./player.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./player.o: aStar.hpp coordinate.hpp detailController.hpp Teleporter.hpp
./player.o: detailParent.hpp treasureChest.hpp inputController.hpp
./player.o: generalDetail.hpp lampLight.hpp userInterface.hpp
./player.o: easingTemplates.hpp damagedRobot.hpp rock.hpp IntroDoor.hpp
./player.o: soundController.hpp playerAnimationFunctions.hpp
./player.o: playerCollisionFunctions.hpp scene.hpp backgroundHandler.hpp
./player.o: screenShakeController.hpp
./dasher.o: dasher.hpp effectsController.hpp turretFlashEffect.hpp
./dasher.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./dasher.o: Framework/utilities.hpp rng.hpp bulletType1.hpp shotPuff.hpp
./dasher.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp spritesheet.hpp
./dasher.o: ResourceHandler.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./dasher.o: turretShot.hpp enemy.hpp wall.hpp /usr/include/stdint.h
./dasher.o: /usr/include/sys/_types/_int8_t.h
./dasher.o: /usr/include/sys/_types/_int16_t.h
./dasher.o: /usr/include/sys/_types/_int32_t.h
./dasher.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./dasher.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./dasher.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./dasher.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./dasher.o: /usr/include/sys/_posix_availability.h
./dasher.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./dasher.o: /usr/include/sys/_pthread/_pthread_types.h
./dasher.o: /usr/include/sys/_types/_intptr_t.h
./dasher.o: /usr/include/sys/_types/_uintptr_t.h
./dasher.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./dasher.o: resourceHandler.hpp ResourcePath.hpp angleFunction.hpp
./Effect.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./scoot.o: scoot.hpp wall.hpp /usr/include/stdint.h
./scoot.o: /usr/include/sys/_types/_int8_t.h
./scoot.o: /usr/include/sys/_types/_int16_t.h
./scoot.o: /usr/include/sys/_types/_int32_t.h
./scoot.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./scoot.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./scoot.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./scoot.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./scoot.o: /usr/include/sys/_posix_availability.h
./scoot.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./scoot.o: /usr/include/sys/_pthread/_pthread_types.h
./scoot.o: /usr/include/sys/_types/_intptr_t.h
./scoot.o: /usr/include/sys/_types/_uintptr_t.h
./scoot.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./scoot.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./scoot.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./scoot.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./scoot.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp RenderType.hpp
./scoot.o: enemyShot.hpp dasherShot.hpp turretShot.hpp enemy.hpp
./scoot.o: resourceHandler.hpp ResourcePath.hpp angleFunction.hpp
./scene.o: mappingFunctions.hpp tileController.hpp wall.hpp
./scene.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./scene.o: /usr/include/sys/_types/_int16_t.h
./scene.o: /usr/include/sys/_types/_int32_t.h
./scene.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./scene.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./scene.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./scene.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./scene.o: /usr/include/sys/_posix_availability.h
./scene.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./scene.o: /usr/include/sys/_pthread/_pthread_types.h
./scene.o: /usr/include/sys/_types/_intptr_t.h
./scene.o: /usr/include/sys/_types/_uintptr_t.h
./scene.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./scene.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./scene.o: turret.hpp /usr/include/stdio.h /usr/include/Availability.h
./scene.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./scene.o: /usr/include/sys/_types/_va_list.h
./scene.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./scene.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./scene.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./scene.o: /usr/include/secure/_common.h fontController.hpp
./scene.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./scene.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./scene.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./scene.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp RenderType.hpp
./scene.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp
./scene.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp initMapVectors.hpp
./scene.o: enemyPlacementFn.hpp lightingMap.h pillarPlacement.h
./scene.o: /usr/include/math.h enemyCreationFunctions.hpp scene.hpp
./scene.o: player.hpp detailController.hpp Teleporter.hpp detailParent.hpp
./scene.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./scene.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./scene.o: damagedRobot.hpp rock.hpp IntroDoor.hpp soundController.hpp
./scene.o: backgroundHandler.hpp screenShakeController.hpp
./enemy.o: enemy.hpp wall.hpp /usr/include/stdint.h
./enemy.o: /usr/include/sys/_types/_int8_t.h
./enemy.o: /usr/include/sys/_types/_int16_t.h
./enemy.o: /usr/include/sys/_types/_int32_t.h
./enemy.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./enemy.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./enemy.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./enemy.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./enemy.o: /usr/include/sys/_posix_availability.h
./enemy.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./enemy.o: /usr/include/sys/_pthread/_pthread_types.h
./enemy.o: /usr/include/sys/_types/_intptr_t.h
./enemy.o: /usr/include/sys/_types/_uintptr_t.h
./enemy.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./enemy.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./enemy.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./enemy.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./enemy.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp RenderType.hpp
./enemy.o: enemyShot.hpp dasherShot.hpp turretShot.hpp
./aStar.o: aStar.hpp
./wall.o: wall.hpp /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./wall.o: /usr/include/sys/_types/_int16_t.h
./wall.o: /usr/include/sys/_types/_int32_t.h
./wall.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./wall.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./wall.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./wall.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./wall.o: /usr/include/sys/_posix_availability.h
./wall.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./wall.o: /usr/include/sys/_pthread/_pthread_types.h
./wall.o: /usr/include/sys/_types/_intptr_t.h
./wall.o: /usr/include/sys/_types/_uintptr_t.h
./wall.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./rock.o: rock.hpp detailParent.hpp Framework/framework.hpp
./rock.o: Framework/utilities.hpp spriteSheet.hpp rng.hpp
./main.o: player.hpp tileController.hpp wall.hpp /usr/include/stdint.h
./main.o: /usr/include/sys/_types/_int8_t.h
./main.o: /usr/include/sys/_types/_int16_t.h
./main.o: /usr/include/sys/_types/_int32_t.h
./main.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./main.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./main.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./main.o: /usr/include/sys/_posix_availability.h
./main.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./main.o: /usr/include/sys/_pthread/_pthread_types.h
./main.o: /usr/include/sys/_types/_intptr_t.h
./main.o: /usr/include/sys/_types/_uintptr_t.h
./main.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./main.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp turret.hpp
./main.o: /usr/include/stdio.h /usr/include/Availability.h
./main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./main.o: /usr/include/sys/_types/_va_list.h
./main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./main.o: /usr/include/secure/_common.h fontController.hpp
./main.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./main.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./main.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./main.o: Powerup.hpp spritesheet.hpp ResourceHandler.hpp RenderType.hpp
./main.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp
./main.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./main.o: detailController.hpp Teleporter.hpp detailParent.hpp
./main.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./main.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./main.o: damagedRobot.hpp rock.hpp IntroDoor.hpp soundController.hpp
./main.o: backgroundHandler.hpp scene.hpp screenShakeController.hpp
