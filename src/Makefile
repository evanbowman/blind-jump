#
#  makefile for Blind Jump game
#  Evan Bowman 2016
# 

CC = g++
override CPPFLAGS += -O2 -flto -std=c++14 -Wall -Wextra -pedantic -Werror
LDFLAGS_MAC = -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime -flto
LDFLAGS_LINUX = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lpthread -lX11 -flto
LDFLAGS_WINDOWS = 
EXECUTABLE = BlindJump
SOURCES = $(shell find . -name "*.cpp" | awk '{print length, $$0;}' | sort -nr | cut -d ' ' -f 2-) # Hey it looks nice though
OBJECTS = $(SOURCES:.cpp=.o)

all:
	@echo Specify a platform to build for, options:
	@echo make macOS
	@echo make Linux CPPFLAGS=-DLINUX

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

macOS: $(OBJECTS) packageScriptMac.sh ResourcePath.mm ResourcePath.hpp
	$(CC) ResourcePath.mm -c -o ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS_MAC)
	bash packageScriptMac.sh $(EXECUTABLE) BlindJump

Linux: $(OBJECTS) ResourcePath.hpp ResourcePath.cxx
	$(CC) -c ResourcePath.cxx -o ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS_LINUX)

Windows: $(OBJECTS)
	$(CC) -c ResourcePath.cxx -o ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS_WINDOWS)

clean:
	rm *.o

analyze:
	rm ../test/cppcheck_results.txt
	cppcheck --enable=warning --enable=performance --enable=information . > ../test/cppcheck_results.txt

depend:
	makedepend -- $(CPPFLAGS) -- $(SOURCES)

# DO NOT DELETE

./turretFlashEffect.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./turretFlashEffect.o: framework/framework.hpp framework/utilities.hpp
./turretFlashEffect.o: rng.hpp
./backgroundHandler.o: backgroundHandler.hpp camera.hpp player.hpp
./backgroundHandler.o: playerAnimationFunctions.hpp
./backgroundHandler.o: playerCollisionFunctions.hpp wall.hpp
./backgroundHandler.o: /usr/include/stdint.h
./backgroundHandler.o: /usr/include/sys/_types/_int8_t.h
./backgroundHandler.o: /usr/include/sys/_types/_int16_t.h
./backgroundHandler.o: /usr/include/sys/_types/_int32_t.h
./backgroundHandler.o: /usr/include/sys/_types/_int64_t.h
./backgroundHandler.o: /usr/include/_types/_uint8_t.h
./backgroundHandler.o: /usr/include/_types/_uint16_t.h
./backgroundHandler.o: /usr/include/_types/_uint32_t.h
./backgroundHandler.o: /usr/include/_types/_uint64_t.h
./backgroundHandler.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
./backgroundHandler.o: /usr/include/sys/_symbol_aliasing.h
./backgroundHandler.o: /usr/include/sys/_posix_availability.h
./backgroundHandler.o: /usr/include/machine/_types.h
./backgroundHandler.o: /usr/include/i386/_types.h
./backgroundHandler.o: /usr/include/sys/_pthread/_pthread_types.h
./backgroundHandler.o: /usr/include/sys/_types/_intptr_t.h
./backgroundHandler.o: /usr/include/sys/_types/_uintptr_t.h
./backgroundHandler.o: /usr/include/_types/_intmax_t.h
./backgroundHandler.o: /usr/include/_types/_uintmax_t.h treasureChest.hpp
./backgroundHandler.o: detailParent.hpp framework/framework.hpp
./backgroundHandler.o: framework/utilities.hpp inputController.hpp
./backgroundHandler.o: shutdownSignal.hpp spriteSheet.hpp rng.hpp powerup.hpp
./backgroundHandler.o: detailController.hpp resourceHandler.hpp
./backgroundHandler.o: ResourcePath.hpp tileController.hpp
./backgroundHandler.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./backgroundHandler.o: /usr/include/Availability.h
./backgroundHandler.o: /usr/include/AvailabilityInternal.h
./backgroundHandler.o: /usr/include/_types.h
./backgroundHandler.o: /usr/include/sys/_types/_va_list.h
./backgroundHandler.o: /usr/include/sys/_types/_size_t.h
./backgroundHandler.o: /usr/include/sys/_types/_null.h
./backgroundHandler.o: /usr/include/sys/stdio.h
./backgroundHandler.o: /usr/include/sys/_types/_off_t.h
./backgroundHandler.o: /usr/include/sys/_types/_ssize_t.h
./backgroundHandler.o: /usr/include/secure/_stdio.h
./backgroundHandler.o: /usr/include/secure/_common.h effectsController.hpp
./backgroundHandler.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./backgroundHandler.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./backgroundHandler.o: dasherShot.hpp turretShot.hpp RenderType.hpp
./backgroundHandler.o: enemyShot.hpp shotPuff.hpp Item.hpp scoot.hpp
./backgroundHandler.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp util.hpp
./backgroundHandler.o: alias.hpp coordinate.hpp userInterface.hpp colors.hpp
./backgroundHandler.o: generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./backgroundHandler.o: lampLight.hpp IntroDoor.hpp rock.hpp
./backgroundHandler.o: soundController.hpp math.hpp
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
./mappingFunctions.o: framework/framework.hpp framework/utilities.hpp
./mappingFunctions.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./mappingFunctions.o: rng.hpp smallExplosion.hpp easingTemplates.hpp
./mappingFunctions.o: FireExplosion.hpp bulletType1.hpp dasherShot.hpp
./mappingFunctions.o: turretShot.hpp RenderType.hpp enemyShot.hpp
./mappingFunctions.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./mappingFunctions.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./mappingFunctions.o: camera.hpp player.hpp playerAnimationFunctions.hpp
./mappingFunctions.o: playerCollisionFunctions.hpp treasureChest.hpp
./mappingFunctions.o: detailParent.hpp inputController.hpp shutdownSignal.hpp
./mappingFunctions.o: powerup.hpp detailController.hpp userInterface.hpp
./mappingFunctions.o: colors.hpp generalDetail.hpp damagedRobot.hpp
./mappingFunctions.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./mappingFunctions.o: soundController.hpp math.hpp mappingFunctions.hpp
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
./enemyPlacementFn.o: game.hpp backgroundHandler.hpp camera.hpp player.hpp
./enemyPlacementFn.o: playerAnimationFunctions.hpp
./enemyPlacementFn.o: playerCollisionFunctions.hpp wall.hpp
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
./enemyPlacementFn.o: /usr/include/_types/_uintmax_t.h treasureChest.hpp
./enemyPlacementFn.o: detailParent.hpp framework/framework.hpp
./enemyPlacementFn.o: framework/utilities.hpp inputController.hpp
./enemyPlacementFn.o: shutdownSignal.hpp spriteSheet.hpp rng.hpp powerup.hpp
./enemyPlacementFn.o: detailController.hpp resourceHandler.hpp
./enemyPlacementFn.o: ResourcePath.hpp tileController.hpp enemyController.hpp
./enemyPlacementFn.o: turret.hpp effectsController.hpp turretFlashEffect.hpp
./enemyPlacementFn.o: Effect.hpp smallExplosion.hpp easingTemplates.hpp
./enemyPlacementFn.o: FireExplosion.hpp bulletType1.hpp dasherShot.hpp
./enemyPlacementFn.o: turretShot.hpp RenderType.hpp enemyShot.hpp
./enemyPlacementFn.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./enemyPlacementFn.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./enemyPlacementFn.o: userInterface.hpp colors.hpp generalDetail.hpp
./enemyPlacementFn.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp
./enemyPlacementFn.o: IntroDoor.hpp rock.hpp soundController.hpp math.hpp
./enemyPlacementFn.o: framework/option.hpp
./soundController.o: soundController.hpp resourceHandler.hpp ResourcePath.hpp
./resourceHandler.o: resourceHandler.hpp ResourcePath.hpp
./inputController.o: inputController.hpp shutdownSignal.hpp
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
./enemyController.o: framework/framework.hpp framework/utilities.hpp
./enemyController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./enemyController.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./enemyController.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./enemyController.o: RenderType.hpp enemyShot.hpp shotPuff.hpp Item.hpp
./enemyController.o: scoot.hpp wall.hpp /usr/include/stdint.h
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
./enemyController.o: critter.hpp aStar.hpp util.hpp alias.hpp
./enemyController.o: tileController.hpp coordinate.hpp camera.hpp player.hpp
./enemyController.o: playerAnimationFunctions.hpp
./enemyController.o: playerCollisionFunctions.hpp treasureChest.hpp
./enemyController.o: detailParent.hpp inputController.hpp shutdownSignal.hpp
./enemyController.o: powerup.hpp detailController.hpp userInterface.hpp
./enemyController.o: colors.hpp generalDetail.hpp damagedRobot.hpp
./enemyController.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./enemyController.o: soundController.hpp math.hpp game.hpp
./enemyController.o: backgroundHandler.hpp framework/option.hpp
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
./tileController.o: framework/framework.hpp framework/utilities.hpp
./tileController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./tileController.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./tileController.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./tileController.o: RenderType.hpp enemyShot.hpp shotPuff.hpp Item.hpp
./tileController.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./tileController.o: util.hpp alias.hpp coordinate.hpp camera.hpp player.hpp
./tileController.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./tileController.o: treasureChest.hpp detailParent.hpp inputController.hpp
./tileController.o: shutdownSignal.hpp powerup.hpp detailController.hpp
./tileController.o: userInterface.hpp colors.hpp generalDetail.hpp
./tileController.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp
./tileController.o: IntroDoor.hpp rock.hpp soundController.hpp math.hpp
./tileController.o: mappingFunctions.hpp initMapVectors.hpp drawPixels.hpp
./smallExplosion.o: smallExplosion.hpp spriteSheet.hpp Effect.hpp
./smallExplosion.o: framework/framework.hpp framework/utilities.hpp
./smallExplosion.o: easingTemplates.hpp
./shutdownSignal.o: shutdownSignal.hpp
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
./initMapVectors.o: framework/framework.hpp framework/utilities.hpp
./initMapVectors.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./initMapVectors.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./initMapVectors.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./initMapVectors.o: RenderType.hpp enemyShot.hpp shotPuff.hpp Item.hpp
./initMapVectors.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./initMapVectors.o: util.hpp alias.hpp camera.hpp player.hpp
./initMapVectors.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./initMapVectors.o: treasureChest.hpp detailParent.hpp inputController.hpp
./initMapVectors.o: shutdownSignal.hpp powerup.hpp detailController.hpp
./initMapVectors.o: userInterface.hpp colors.hpp generalDetail.hpp
./initMapVectors.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp
./initMapVectors.o: IntroDoor.hpp rock.hpp soundController.hpp math.hpp
./userInterface.o: userInterface.hpp effectsController.hpp
./userInterface.o: framework/framework.hpp framework/utilities.hpp
./userInterface.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./userInterface.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./userInterface.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./userInterface.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./userInterface.o: shotPuff.hpp Item.hpp inputController.hpp
./userInterface.o: shutdownSignal.hpp powerup.hpp colors.hpp player.hpp
./userInterface.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./userInterface.o: wall.hpp /usr/include/stdint.h
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
./userInterface.o: /usr/include/_types/_uintmax_t.h treasureChest.hpp
./userInterface.o: detailParent.hpp detailController.hpp tileController.hpp
./userInterface.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./userInterface.o: /usr/include/Availability.h
./userInterface.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./userInterface.o: /usr/include/sys/_types/_va_list.h
./userInterface.o: /usr/include/sys/_types/_size_t.h
./userInterface.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./userInterface.o: /usr/include/sys/_types/_off_t.h
./userInterface.o: /usr/include/sys/_types/_ssize_t.h
./userInterface.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
./userInterface.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp
./userInterface.o: util.hpp alias.hpp coordinate.hpp camera.hpp math.hpp
./userInterface.o: generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./userInterface.o: lampLight.hpp IntroDoor.hpp rock.hpp soundController.hpp
./treasureChest.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./treasureChest.o: framework/utilities.hpp inputController.hpp
./treasureChest.o: shutdownSignal.hpp spriteSheet.hpp rng.hpp powerup.hpp
./generalDetail.o: generalDetail.hpp detailParent.hpp framework/framework.hpp
./generalDetail.o: framework/utilities.hpp
./FireExplosion.o: FireExplosion.hpp spriteSheet.hpp Effect.hpp
./FireExplosion.o: framework/framework.hpp framework/utilities.hpp
./FireExplosion.o: easingTemplates.hpp
./damagedRobot.o: damagedRobot.hpp detailParent.hpp framework/framework.hpp
./damagedRobot.o: framework/utilities.hpp spriteSheet.hpp rng.hpp
./bulletType1.o: bulletType1.hpp spriteSheet.hpp Effect.hpp
./bulletType1.o: framework/framework.hpp framework/utilities.hpp
./turretShot.o: turretShot.hpp spriteSheet.hpp Effect.hpp
./turretShot.o: framework/framework.hpp framework/utilities.hpp rng.hpp
./dasherShot.o: dasherShot.hpp spriteSheet.hpp Effect.hpp
./dasherShot.o: framework/framework.hpp framework/utilities.hpp rng.hpp
./dasherShot.o: easingTemplates.hpp
./Teleporter.o: Teleporter.hpp detailParent.hpp framework/framework.hpp
./Teleporter.o: framework/utilities.hpp effectsController.hpp
./Teleporter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./Teleporter.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./Teleporter.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./Teleporter.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./Teleporter.o: shotPuff.hpp Item.hpp
./lampLight.o: lampLight.hpp detailParent.hpp framework/framework.hpp
./lampLight.o: framework/utilities.hpp
./enemyShot.o: enemyShot.hpp spriteSheet.hpp Effect.hpp
./enemyShot.o: framework/framework.hpp framework/utilities.hpp rng.hpp
./IntroDoor.o: IntroDoor.hpp detailParent.hpp framework/framework.hpp
./IntroDoor.o: framework/utilities.hpp effectsController.hpp
./IntroDoor.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./IntroDoor.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./IntroDoor.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./IntroDoor.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./IntroDoor.o: shotPuff.hpp Item.hpp
./shotPuff.o: shotPuff.hpp spriteSheet.hpp Effect.hpp framework/framework.hpp
./shotPuff.o: framework/utilities.hpp
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
./critter.o: effectsController.hpp framework/framework.hpp
./critter.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./critter.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./critter.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./critter.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./critter.o: enemyShot.hpp shotPuff.hpp Item.hpp aStar.hpp tileController.hpp
./critter.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./critter.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
./critter.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
./critter.o: /usr/include/sys/_types/_size_t.h
./critter.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
./critter.o: /usr/include/sys/_types/_off_t.h
./critter.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./critter.o: /usr/include/secure/_common.h scoot.hpp dasher.hpp util.hpp
./critter.o: alias.hpp coordinate.hpp camera.hpp player.hpp
./critter.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./critter.o: treasureChest.hpp detailParent.hpp inputController.hpp
./critter.o: shutdownSignal.hpp powerup.hpp detailController.hpp
./critter.o: userInterface.hpp colors.hpp generalDetail.hpp damagedRobot.hpp
./critter.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./critter.o: soundController.hpp math.hpp /usr/include/math.h
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
./turret.o: framework/framework.hpp framework/utilities.hpp
./turret.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./turret.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./turret.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./turret.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./turret.o: shotPuff.hpp Item.hpp angleFunction.hpp
./player.o: player.hpp playerAnimationFunctions.hpp
./player.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
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
./player.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./player.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./player.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./player.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./player.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./player.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
./player.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
./player.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./player.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./player.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./player.o: /usr/include/secure/_common.h effectsController.hpp
./player.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./player.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./player.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./player.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./player.o: aStar.hpp util.hpp alias.hpp coordinate.hpp camera.hpp math.hpp
./player.o: userInterface.hpp colors.hpp generalDetail.hpp damagedRobot.hpp
./player.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./player.o: soundController.hpp game.hpp backgroundHandler.hpp
./player.o: framework/option.hpp
./dasher.o: dasher.hpp effectsController.hpp framework/framework.hpp
./dasher.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./dasher.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./dasher.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./dasher.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./dasher.o: enemyShot.hpp shotPuff.hpp Item.hpp enemy.hpp wall.hpp
./dasher.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
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
./camera.o: camera.hpp player.hpp playerAnimationFunctions.hpp
./camera.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
./camera.o: /usr/include/sys/_types/_int8_t.h
./camera.o: /usr/include/sys/_types/_int16_t.h
./camera.o: /usr/include/sys/_types/_int32_t.h
./camera.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./camera.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./camera.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./camera.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./camera.o: /usr/include/sys/_posix_availability.h
./camera.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./camera.o: /usr/include/sys/_pthread/_pthread_types.h
./camera.o: /usr/include/sys/_types/_intptr_t.h
./camera.o: /usr/include/sys/_types/_uintptr_t.h
./camera.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./camera.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./camera.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./camera.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./camera.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./camera.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./camera.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
./camera.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
./camera.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./camera.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./camera.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./camera.o: /usr/include/secure/_common.h effectsController.hpp
./camera.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./camera.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./camera.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./camera.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./camera.o: aStar.hpp util.hpp alias.hpp coordinate.hpp userInterface.hpp
./camera.o: colors.hpp generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./camera.o: lampLight.hpp IntroDoor.hpp rock.hpp soundController.hpp math.hpp
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
./scoot.o: effectsController.hpp framework/framework.hpp
./scoot.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./scoot.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./scoot.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./scoot.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./scoot.o: enemyShot.hpp shotPuff.hpp Item.hpp enemy.hpp angleFunction.hpp
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
./enemy.o: effectsController.hpp framework/framework.hpp
./enemy.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./enemy.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./enemy.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./enemy.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./enemy.o: enemyShot.hpp shotPuff.hpp Item.hpp
./aStar.o: aStar.hpp /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./aStar.o: /usr/include/sys/_types/_int16_t.h
./aStar.o: /usr/include/sys/_types/_int32_t.h
./aStar.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./aStar.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./aStar.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./aStar.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./aStar.o: /usr/include/sys/_posix_availability.h
./aStar.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./aStar.o: /usr/include/sys/_pthread/_pthread_types.h
./aStar.o: /usr/include/sys/_types/_intptr_t.h
./aStar.o: /usr/include/sys/_types/_uintptr_t.h
./aStar.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
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
./util.o: util.hpp alias.hpp RenderType.hpp
./rock.o: rock.hpp detailParent.hpp framework/framework.hpp
./rock.o: framework/utilities.hpp spriteSheet.hpp rng.hpp
./main.o: framework/smartThread.hpp backgroundHandler.hpp camera.hpp
./main.o: player.hpp playerAnimationFunctions.hpp
./main.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
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
./main.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./main.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./main.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./main.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./main.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./main.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
./main.o: /usr/include/_types.h /usr/include/sys/_types/_va_list.h
./main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./main.o: /usr/include/secure/_common.h effectsController.hpp
./main.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./main.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./main.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./main.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./main.o: aStar.hpp util.hpp alias.hpp coordinate.hpp userInterface.hpp
./main.o: colors.hpp generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./main.o: lampLight.hpp IntroDoor.hpp rock.hpp soundController.hpp math.hpp
./main.o: aspectScaling.hpp game.hpp framework/option.hpp
./game.o: mappingFunctions.hpp tileController.hpp wall.hpp
./game.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
./game.o: /usr/include/sys/_types/_int16_t.h
./game.o: /usr/include/sys/_types/_int32_t.h
./game.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
./game.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
./game.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types.h
./game.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
./game.o: /usr/include/sys/_posix_availability.h
./game.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
./game.o: /usr/include/sys/_pthread/_pthread_types.h
./game.o: /usr/include/sys/_types/_intptr_t.h
./game.o: /usr/include/sys/_types/_uintptr_t.h
./game.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
./game.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp turret.hpp
./game.o: /usr/include/stdio.h /usr/include/Availability.h
./game.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
./game.o: /usr/include/sys/_types/_va_list.h
./game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
./game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
./game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
./game.o: /usr/include/secure/_common.h effectsController.hpp
./game.o: framework/framework.hpp framework/utilities.hpp
./game.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./game.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./game.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./game.o: enemyShot.hpp shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./game.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp camera.hpp
./game.o: player.hpp playerAnimationFunctions.hpp
./game.o: playerCollisionFunctions.hpp treasureChest.hpp detailParent.hpp
./game.o: inputController.hpp shutdownSignal.hpp powerup.hpp
./game.o: detailController.hpp userInterface.hpp colors.hpp generalDetail.hpp
./game.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp IntroDoor.hpp
./game.o: rock.hpp soundController.hpp math.hpp enemyPlacementFn.hpp
./game.o: initMapVectors.hpp pillarPlacement.h lightingMap.h game.hpp
./game.o: backgroundHandler.hpp framework/option.hpp /usr/include/math.h
./Item.o: Item.hpp spriteSheet.hpp Effect.hpp framework/framework.hpp
./Item.o: framework/utilities.hpp
./rng.o: rng.hpp
