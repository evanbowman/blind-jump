#
#  makefile for Blind Jump game
#  Evan Bowman 2016
# 

CC = clang++
CPPFLAGS = -O2 -std=c++14 -Wall -Werror
LDFLAGS = -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime
EXECUTABLE = BlindJump
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS) ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS)

ResourcePath.o: ResourcePath.hpp
	$(CC) ResourcePath.mm -c -o ResourcePath.o

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o

MacOS: all packageScriptMac.sh
	bash packageScriptMac.sh $(EXECUTABLE) BlindJump

depend:
	makedepend -- $(CPPFLAGS) -- $(SOURCES)

# DO NOT DELETE

./aStar.o: aStar.hpp
./backgroundHandler.o: backgroundHandler.hpp ResourcePath.hpp
./bulletType1.o: bulletType1.hpp spriteSheet.hpp
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
./critter.o: Effect.hpp bulletType1.hpp shotPuff.hpp turretShot.hpp
./critter.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./critter.o: dasherShot.hpp fontController.hpp resourceHandler.hpp
./critter.o: ResourcePath.hpp dashSmoke.hpp FireExplosion.hpp
./critter.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp
./critter.o: RenderType.hpp aStar.hpp tileController.hpp enemyController.hpp
./critter.o: turret.hpp /usr/include/stdio.h /usr/include/Availability.h
./critter.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./critter.o: /usr/include/sys/_types/_va_list.h
./critter.o: /usr/include/sys/_types/_size_t.h
./critter.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./critter.o: /usr/include/sys/_types/_off_t.h
./critter.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./critter.o: /usr/include/secure/_common.h scoot.hpp dasher.hpp
./critter.o: coordinate.hpp /usr/include/math.h
./damagedRobot.o: damagedRobot.hpp detailParent.hpp spriteSheet.hpp
./dasher.o: dasher.hpp effectsController.hpp turretFlashEffect.hpp
./dasher.o: spriteSheet.hpp Effect.hpp bulletType1.hpp shotPuff.hpp
./dasher.o: turretShot.hpp spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./dasher.o: hitBox.hpp dasherShot.hpp fontController.hpp resourceHandler.hpp
./dasher.o: ResourcePath.hpp dashSmoke.hpp FireExplosion.hpp
./dasher.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp RenderType.hpp
./dasher.o: enemy.hpp wall.hpp /usr/include/stdint.h
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
./dasher.o: angleFunction.hpp
./dasherShot.o: dasherShot.hpp spriteSheet.hpp
./dashSmoke.o: dashSmoke.hpp
./detailController.o: detailController.hpp Teleporter.hpp detailParent.hpp
./detailController.o: effectsController.hpp turretFlashEffect.hpp
./detailController.o: spriteSheet.hpp Effect.hpp bulletType1.hpp shotPuff.hpp
./detailController.o: turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./detailController.o: enemyShot.hpp hitBox.hpp dasherShot.hpp
./detailController.o: fontController.hpp resourceHandler.hpp ResourcePath.hpp
./detailController.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./detailController.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp
./detailController.o: treasureChest.hpp inputController.hpp
./detailController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./detailController.o: /usr/include/sys/_types/_int8_t.h
./detailController.o: /usr/include/sys/_types/_int16_t.h
./detailController.o: /usr/include/sys/_types/_int32_t.h
./detailController.o: /usr/include/sys/_types/_int64_t.h
./detailController.o: /usr/include/_types/_uint8_t.h
./detailController.o: /usr/include/_types/_uint16_t.h
./detailController.o: /usr/include/_types/_uint32_t.h
./detailController.o: /usr/include/_types/_uint64_t.h
./detailController.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./detailController.o: /usr/include/sys/_symbol_aliasing.h
./detailController.o: /usr/include/sys/_posix_availability.h
./detailController.o: /usr/include/machine/_types.h
./detailController.o: /usr/include/i386/_types.h
./detailController.o: /usr/include/sys/_pthread/_pthread_types.h
./detailController.o: /usr/include/sys/_types/_intptr_t.h
./detailController.o: /usr/include/sys/_types/_uintptr_t.h
./detailController.o: /usr/include/_types/_intmax_t.h
./detailController.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./detailController.o: turret.hpp /usr/include/stdio.h
./detailController.o: /usr/include/Availability.h
./detailController.o: /usr/include/AvailabilityInternal.h
./detailController.o: /usr/include/_types.h
./detailController.o: /usr/include/sys/_types/_va_list.h
./detailController.o: /usr/include/sys/_types/_size_t.h
./detailController.o: /usr/include/sys/_types/_null.h
./detailController.o: /usr/include/sys/stdio.h
./detailController.o: /usr/include/sys/_types/_off_t.h
./detailController.o: /usr/include/sys/_types/_ssize_t.h
./detailController.o: /usr/include/secure/_stdio.h
./detailController.o: /usr/include/secure/_common.h scoot.hpp enemy.hpp
./detailController.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./detailController.o: generalDetail.hpp lampLight.hpp userInterface.hpp
./detailController.o: damagedRobot.hpp rock.hpp IntroDoor.hpp player.hpp
./detailController.o: soundController.hpp gameMap.hpp backgroundHandler.hpp
./detailController.o: screenShakeController.hpp initLoot.hpp
./detailParent.o: detailParent.hpp
./Effect.o: Effect.hpp
./effectsController.o: effectsController.hpp turretFlashEffect.hpp
./effectsController.o: spriteSheet.hpp Effect.hpp bulletType1.hpp
./effectsController.o: shotPuff.hpp turretShot.hpp spritesheet.hpp
./effectsController.o: teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./effectsController.o: dasherShot.hpp fontController.hpp resourceHandler.hpp
./effectsController.o: ResourcePath.hpp dashSmoke.hpp FireExplosion.hpp
./effectsController.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp
./effectsController.o: RenderType.hpp screenShakeController.hpp player.hpp
./effectsController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./effectsController.o: /usr/include/sys/_types/_int8_t.h
./effectsController.o: /usr/include/sys/_types/_int16_t.h
./effectsController.o: /usr/include/sys/_types/_int32_t.h
./effectsController.o: /usr/include/sys/_types/_int64_t.h
./effectsController.o: /usr/include/_types/_uint8_t.h
./effectsController.o: /usr/include/_types/_uint16_t.h
./effectsController.o: /usr/include/_types/_uint32_t.h
./effectsController.o: /usr/include/_types/_uint64_t.h
./effectsController.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./effectsController.o: /usr/include/sys/_symbol_aliasing.h
./effectsController.o: /usr/include/sys/_posix_availability.h
./effectsController.o: /usr/include/machine/_types.h
./effectsController.o: /usr/include/i386/_types.h
./effectsController.o: /usr/include/sys/_pthread/_pthread_types.h
./effectsController.o: /usr/include/sys/_types/_intptr_t.h
./effectsController.o: /usr/include/sys/_types/_uintptr_t.h
./effectsController.o: /usr/include/_types/_intmax_t.h
./effectsController.o: /usr/include/_types/_uintmax_t.h enemyController.hpp
./effectsController.o: turret.hpp /usr/include/stdio.h
./effectsController.o: /usr/include/Availability.h
./effectsController.o: /usr/include/AvailabilityInternal.h
./effectsController.o: /usr/include/_types.h
./effectsController.o: /usr/include/sys/_types/_va_list.h
./effectsController.o: /usr/include/sys/_types/_size_t.h
./effectsController.o: /usr/include/sys/_types/_null.h
./effectsController.o: /usr/include/sys/stdio.h
./effectsController.o: /usr/include/sys/_types/_off_t.h
./effectsController.o: /usr/include/sys/_types/_ssize_t.h
./effectsController.o: /usr/include/secure/_stdio.h
./effectsController.o: /usr/include/secure/_common.h scoot.hpp enemy.hpp
./effectsController.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./effectsController.o: detailController.hpp Teleporter.hpp detailParent.hpp
./effectsController.o: treasureChest.hpp inputController.hpp
./effectsController.o: generalDetail.hpp lampLight.hpp userInterface.hpp
./effectsController.o: damagedRobot.hpp rock.hpp IntroDoor.hpp
./effectsController.o: soundController.hpp
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
./enemy.o: Effect.hpp bulletType1.hpp shotPuff.hpp turretShot.hpp
./enemy.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./enemy.o: dasherShot.hpp fontController.hpp resourceHandler.hpp
./enemy.o: ResourcePath.hpp dashSmoke.hpp FireExplosion.hpp
./enemy.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp RenderType.hpp
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
./enemyController.o: /usr/include/secure/_common.h effectsController.hpp
./enemyController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./enemyController.o: bulletType1.hpp shotPuff.hpp turretShot.hpp
./enemyController.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./enemyController.o: hitBox.hpp dasherShot.hpp fontController.hpp
./enemyController.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./enemyController.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp scoot.hpp
./enemyController.o: wall.hpp /usr/include/stdint.h
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
./enemyController.o: lampLight.hpp userInterface.hpp damagedRobot.hpp
./enemyController.o: rock.hpp IntroDoor.hpp screenShakeController.hpp
./enemyController.o: player.hpp soundController.hpp
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
./enemyCreationFunctions.o: effectsController.hpp turretFlashEffect.hpp
./enemyCreationFunctions.o: spriteSheet.hpp Effect.hpp bulletType1.hpp
./enemyCreationFunctions.o: shotPuff.hpp turretShot.hpp spritesheet.hpp
./enemyCreationFunctions.o: teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./enemyCreationFunctions.o: dasherShot.hpp fontController.hpp dashSmoke.hpp
./enemyCreationFunctions.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./enemyCreationFunctions.o: ResourceHandler.hpp RenderType.hpp scoot.hpp
./enemyCreationFunctions.o: wall.hpp /usr/include/stdint.h
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
./enemyPlacementFn.o: gameMap.hpp player.hpp tileController.hpp wall.hpp
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
./enemyPlacementFn.o: effectsController.hpp turretFlashEffect.hpp
./enemyPlacementFn.o: spriteSheet.hpp Effect.hpp bulletType1.hpp shotPuff.hpp
./enemyPlacementFn.o: turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./enemyPlacementFn.o: enemyShot.hpp hitBox.hpp dasherShot.hpp
./enemyPlacementFn.o: fontController.hpp dashSmoke.hpp FireExplosion.hpp
./enemyPlacementFn.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp
./enemyPlacementFn.o: RenderType.hpp scoot.hpp enemy.hpp dasher.hpp
./enemyPlacementFn.o: critter.hpp aStar.hpp coordinate.hpp
./enemyPlacementFn.o: detailController.hpp Teleporter.hpp detailParent.hpp
./enemyPlacementFn.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./enemyPlacementFn.o: lampLight.hpp userInterface.hpp damagedRobot.hpp
./enemyPlacementFn.o: rock.hpp IntroDoor.hpp soundController.hpp
./enemyPlacementFn.o: backgroundHandler.hpp screenShakeController.hpp
./enemyPlacementFn.o: initLoot.hpp enemyCreationFunctions.hpp
./enemyShot.o: enemyShot.hpp spriteSheet.hpp hitBox.hpp
./FireExplosion.o: FireExplosion.hpp spriteSheet.hpp Effect.hpp
./fontController.o: fontController.hpp resourceHandler.hpp ResourcePath.hpp
./gameMap.o: mappingFunctions.hpp tileController.hpp wall.hpp
./gameMap.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./gameMap.o: /usr/include/sys/_types/_int16_t.h
./gameMap.o: /usr/include/sys/_types/_int32_t.h
./gameMap.o: /usr/include/sys/_types/_int64_t.h
./gameMap.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
./gameMap.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
./gameMap.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./gameMap.o: /usr/include/sys/_symbol_aliasing.h
./gameMap.o: /usr/include/sys/_posix_availability.h
./gameMap.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./gameMap.o: /usr/include/sys/_pthread/_pthread_types.h
./gameMap.o: /usr/include/sys/_types/_intptr_t.h
./gameMap.o: /usr/include/sys/_types/_uintptr_t.h
./gameMap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./gameMap.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./gameMap.o: turret.hpp /usr/include/stdio.h /usr/include/Availability.h
./gameMap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./gameMap.o: /usr/include/sys/_types/_va_list.h
./gameMap.o: /usr/include/sys/_types/_size_t.h
./gameMap.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./gameMap.o: /usr/include/sys/_types/_off_t.h
./gameMap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./gameMap.o: /usr/include/secure/_common.h effectsController.hpp
./gameMap.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp bulletType1.hpp
./gameMap.o: shotPuff.hpp turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./gameMap.o: enemyShot.hpp hitBox.hpp dasherShot.hpp fontController.hpp
./gameMap.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./gameMap.o: ResourceHandler.hpp RenderType.hpp scoot.hpp enemy.hpp
./gameMap.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./gameMap.o: initMapVectors.hpp enemyPlacementFn.hpp lightingMap.h
./gameMap.o: pillarPlacement.h /usr/include/math.h enemyCreationFunctions.hpp
./gameMap.o: gameMap.hpp player.hpp detailController.hpp Teleporter.hpp
./gameMap.o: detailParent.hpp treasureChest.hpp inputController.hpp
./gameMap.o: generalDetail.hpp lampLight.hpp userInterface.hpp
./gameMap.o: damagedRobot.hpp rock.hpp IntroDoor.hpp soundController.hpp
./gameMap.o: backgroundHandler.hpp screenShakeController.hpp initLoot.hpp
./generalDetail.o: generalDetail.hpp detailParent.hpp
./initLoot.o: initLoot.hpp
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
./initMapVectors.o: /usr/include/secure/_common.h effectsController.hpp
./initMapVectors.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./initMapVectors.o: bulletType1.hpp shotPuff.hpp turretShot.hpp
./initMapVectors.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./initMapVectors.o: hitBox.hpp dasherShot.hpp fontController.hpp
./initMapVectors.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./initMapVectors.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp scoot.hpp
./initMapVectors.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp
./inputController.o: inputController.hpp
./IntroDoor.o: IntroDoor.hpp detailParent.hpp effectsController.hpp
./IntroDoor.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./IntroDoor.o: bulletType1.hpp shotPuff.hpp turretShot.hpp spritesheet.hpp
./IntroDoor.o: teleporterSmoke.hpp enemyShot.hpp hitBox.hpp dasherShot.hpp
./IntroDoor.o: fontController.hpp resourceHandler.hpp ResourcePath.hpp
./IntroDoor.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./IntroDoor.o: ResourceHandler.hpp RenderType.hpp screenShakeController.hpp
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
./IntroDoor.o: turret.hpp /usr/include/stdio.h /usr/include/Availability.h
./IntroDoor.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./IntroDoor.o: /usr/include/sys/_types/_va_list.h
./IntroDoor.o: /usr/include/sys/_types/_size_t.h
./IntroDoor.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./IntroDoor.o: /usr/include/sys/_types/_off_t.h
./IntroDoor.o: /usr/include/sys/_types/_ssize_t.h
./IntroDoor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
./IntroDoor.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./IntroDoor.o: coordinate.hpp detailController.hpp Teleporter.hpp
./IntroDoor.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./IntroDoor.o: lampLight.hpp userInterface.hpp damagedRobot.hpp rock.hpp
./IntroDoor.o: soundController.hpp
./lampLight.o: lampLight.hpp detailParent.hpp
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
./main.o: /usr/include/secure/_common.h effectsController.hpp
./main.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp bulletType1.hpp
./main.o: shotPuff.hpp turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./main.o: enemyShot.hpp hitBox.hpp dasherShot.hpp fontController.hpp
./main.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./main.o: ResourceHandler.hpp RenderType.hpp scoot.hpp enemy.hpp dasher.hpp
./main.o: critter.hpp aStar.hpp coordinate.hpp detailController.hpp
./main.o: Teleporter.hpp detailParent.hpp treasureChest.hpp
./main.o: inputController.hpp generalDetail.hpp lampLight.hpp
./main.o: userInterface.hpp damagedRobot.hpp rock.hpp IntroDoor.hpp
./main.o: soundController.hpp backgroundHandler.hpp gameMap.hpp
./main.o: screenShakeController.hpp initLoot.hpp
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
./mappingFunctions.o: /usr/include/secure/_common.h effectsController.hpp
./mappingFunctions.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./mappingFunctions.o: bulletType1.hpp shotPuff.hpp turretShot.hpp
./mappingFunctions.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./mappingFunctions.o: hitBox.hpp dasherShot.hpp fontController.hpp
./mappingFunctions.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./mappingFunctions.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp
./mappingFunctions.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./mappingFunctions.o: coordinate.hpp mappingFunctions.hpp
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
./player.o: /usr/include/secure/_common.h effectsController.hpp
./player.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp bulletType1.hpp
./player.o: shotPuff.hpp turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./player.o: enemyShot.hpp hitBox.hpp dasherShot.hpp fontController.hpp
./player.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./player.o: ResourceHandler.hpp RenderType.hpp scoot.hpp enemy.hpp dasher.hpp
./player.o: critter.hpp aStar.hpp coordinate.hpp detailController.hpp
./player.o: Teleporter.hpp detailParent.hpp treasureChest.hpp
./player.o: inputController.hpp generalDetail.hpp lampLight.hpp
./player.o: userInterface.hpp damagedRobot.hpp rock.hpp IntroDoor.hpp
./player.o: soundController.hpp playerAnimationFunctions.hpp
./player.o: playerCollisionFunctions.hpp gameMap.hpp backgroundHandler.hpp
./player.o: screenShakeController.hpp initLoot.hpp
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
./playerCollisionFunctions.o: inputController.hpp spriteSheet.hpp
./Powerup.o: Powerup.hpp spritesheet.hpp
./resourceHandler.o: resourceHandler.hpp ResourcePath.hpp
./rock.o: rock.hpp detailParent.hpp spriteSheet.hpp
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
./scoot.o: Effect.hpp bulletType1.hpp shotPuff.hpp turretShot.hpp
./scoot.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./scoot.o: dasherShot.hpp fontController.hpp resourceHandler.hpp
./scoot.o: ResourcePath.hpp dashSmoke.hpp FireExplosion.hpp
./scoot.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp RenderType.hpp
./scoot.o: enemy.hpp angleFunction.hpp
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
./screenShakeController.o: /usr/include/secure/_common.h
./screenShakeController.o: effectsController.hpp turretFlashEffect.hpp
./screenShakeController.o: spriteSheet.hpp Effect.hpp bulletType1.hpp
./screenShakeController.o: shotPuff.hpp turretShot.hpp spritesheet.hpp
./screenShakeController.o: teleporterSmoke.hpp enemyShot.hpp hitBox.hpp
./screenShakeController.o: dasherShot.hpp fontController.hpp dashSmoke.hpp
./screenShakeController.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./screenShakeController.o: ResourceHandler.hpp RenderType.hpp scoot.hpp
./screenShakeController.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp
./screenShakeController.o: coordinate.hpp detailController.hpp Teleporter.hpp
./screenShakeController.o: detailParent.hpp treasureChest.hpp
./screenShakeController.o: inputController.hpp generalDetail.hpp
./screenShakeController.o: lampLight.hpp userInterface.hpp damagedRobot.hpp
./screenShakeController.o: rock.hpp IntroDoor.hpp soundController.hpp
./shotPuff.o: shotPuff.hpp spriteSheet.hpp Effect.hpp
./smallExplosion.o: smallExplosion.hpp spriteSheet.hpp Effect.hpp
./soundController.o: soundController.hpp ResourcePath.hpp
./Teleporter.o: Teleporter.hpp detailParent.hpp effectsController.hpp
./Teleporter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./Teleporter.o: bulletType1.hpp shotPuff.hpp turretShot.hpp spritesheet.hpp
./Teleporter.o: teleporterSmoke.hpp enemyShot.hpp hitBox.hpp dasherShot.hpp
./Teleporter.o: fontController.hpp resourceHandler.hpp ResourcePath.hpp
./Teleporter.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./Teleporter.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp
./teleporterSmoke.o: teleporterSmoke.hpp spriteSheet.hpp Effect.hpp
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
./tileController.o: /usr/include/secure/_common.h effectsController.hpp
./tileController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./tileController.o: bulletType1.hpp shotPuff.hpp turretShot.hpp
./tileController.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./tileController.o: hitBox.hpp dasherShot.hpp fontController.hpp
./tileController.o: dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp
./tileController.o: Powerup.hpp ResourceHandler.hpp RenderType.hpp scoot.hpp
./tileController.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./tileController.o: mappingFunctions.hpp initMapVectors.hpp drawPixels.hpp
./treasureChest.o: treasureChest.hpp detailParent.hpp inputController.hpp
./treasureChest.o: spriteSheet.hpp
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
./turret.o: /usr/include/secure/_common.h effectsController.hpp
./turret.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp bulletType1.hpp
./turret.o: shotPuff.hpp turretShot.hpp spritesheet.hpp teleporterSmoke.hpp
./turret.o: enemyShot.hpp hitBox.hpp dasherShot.hpp fontController.hpp
./turret.o: resourceHandler.hpp ResourcePath.hpp dashSmoke.hpp
./turret.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./turret.o: ResourceHandler.hpp RenderType.hpp angleFunction.hpp
./turretFlashEffect.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./turretShot.o: turretShot.hpp spritesheet.hpp
./userInterface.o: userInterface.hpp fontController.hpp resourceHandler.hpp
./userInterface.o: ResourcePath.hpp effectsController.hpp
./userInterface.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./userInterface.o: bulletType1.hpp shotPuff.hpp turretShot.hpp
./userInterface.o: spritesheet.hpp teleporterSmoke.hpp enemyShot.hpp
./userInterface.o: hitBox.hpp dasherShot.hpp dashSmoke.hpp FireExplosion.hpp
./userInterface.o: smallExplosion.hpp Powerup.hpp ResourceHandler.hpp
./userInterface.o: RenderType.hpp inputController.hpp player.hpp
./userInterface.o: tileController.hpp wall.hpp /usr/include/stdint.h
./userInterface.o: /usr/include/sys/_types/_int8_t.h
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
