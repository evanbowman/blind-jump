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
        bash packageScriptDebian.sh $(EXECUTABLE) BlindJump

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
./backgroundHandler.o: /usr/include/stdint.h /usr/include/features.h
./backgroundHandler.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./backgroundHandler.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./backgroundHandler.o: /usr/include/bits/wchar.h treasureChest.hpp
./backgroundHandler.o: detailParent.hpp framework/framework.hpp
./backgroundHandler.o: framework/utilities.hpp inputController.hpp
./backgroundHandler.o: shutdownSignal.hpp spriteSheet.hpp rng.hpp powerup.hpp
./backgroundHandler.o: detailController.hpp resourceHandler.hpp
./backgroundHandler.o: ResourcePath.hpp tileController.hpp
./backgroundHandler.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./backgroundHandler.o: /usr/include/bits/types.h
./backgroundHandler.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./backgroundHandler.o: /usr/include/_G_config.h /usr/include/wchar.h
./backgroundHandler.o: /usr/include/bits/stdio_lim.h
./backgroundHandler.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./backgroundHandler.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./backgroundHandler.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./backgroundHandler.o: dasherShot.hpp turretShot.hpp RenderType.hpp
./backgroundHandler.o: enemyShot.hpp math.hpp shotPuff.hpp Item.hpp scoot.hpp
./backgroundHandler.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp util.hpp
./backgroundHandler.o: alias.hpp coordinate.hpp userInterface.hpp colors.hpp
./backgroundHandler.o: generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./backgroundHandler.o: lampLight.hpp IntroDoor.hpp rock.hpp
./backgroundHandler.o: soundController.hpp
./mappingFunctions.o: tileController.hpp wall.hpp /usr/include/stdint.h
./mappingFunctions.o: /usr/include/features.h /usr/include/stdc-predef.h
./mappingFunctions.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./mappingFunctions.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./mappingFunctions.o: enemyController.hpp resourceHandler.hpp
./mappingFunctions.o: ResourcePath.hpp turret.hpp /usr/include/stdio.h
./mappingFunctions.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./mappingFunctions.o: /usr/include/libio.h /usr/include/_G_config.h
./mappingFunctions.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./mappingFunctions.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./mappingFunctions.o: framework/framework.hpp framework/utilities.hpp
./mappingFunctions.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./mappingFunctions.o: rng.hpp smallExplosion.hpp easingTemplates.hpp
./mappingFunctions.o: FireExplosion.hpp bulletType1.hpp dasherShot.hpp
./mappingFunctions.o: turretShot.hpp RenderType.hpp enemyShot.hpp math.hpp
./mappingFunctions.o: shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./mappingFunctions.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./mappingFunctions.o: camera.hpp player.hpp playerAnimationFunctions.hpp
./mappingFunctions.o: playerCollisionFunctions.hpp treasureChest.hpp
./mappingFunctions.o: detailParent.hpp inputController.hpp shutdownSignal.hpp
./mappingFunctions.o: powerup.hpp detailController.hpp userInterface.hpp
./mappingFunctions.o: colors.hpp generalDetail.hpp damagedRobot.hpp
./mappingFunctions.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./mappingFunctions.o: soundController.hpp mappingFunctions.hpp
./enemyPlacementFn.o: /usr/include/stdio.h /usr/include/features.h
./enemyPlacementFn.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./enemyPlacementFn.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./enemyPlacementFn.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./enemyPlacementFn.o: /usr/include/libio.h /usr/include/_G_config.h
./enemyPlacementFn.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./enemyPlacementFn.o: /usr/include/bits/sys_errlist.h enemyPlacementFn.hpp
./enemyPlacementFn.o: game.hpp backgroundHandler.hpp camera.hpp player.hpp
./enemyPlacementFn.o: playerAnimationFunctions.hpp
./enemyPlacementFn.o: playerCollisionFunctions.hpp wall.hpp
./enemyPlacementFn.o: /usr/include/stdint.h /usr/include/bits/wchar.h
./enemyPlacementFn.o: treasureChest.hpp detailParent.hpp
./enemyPlacementFn.o: framework/framework.hpp framework/utilities.hpp
./enemyPlacementFn.o: inputController.hpp shutdownSignal.hpp spriteSheet.hpp
./enemyPlacementFn.o: rng.hpp powerup.hpp detailController.hpp
./enemyPlacementFn.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./enemyPlacementFn.o: enemyController.hpp turret.hpp effectsController.hpp
./enemyPlacementFn.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./enemyPlacementFn.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./enemyPlacementFn.o: dasherShot.hpp turretShot.hpp RenderType.hpp
./enemyPlacementFn.o: enemyShot.hpp math.hpp shotPuff.hpp Item.hpp scoot.hpp
./enemyPlacementFn.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp util.hpp
./enemyPlacementFn.o: alias.hpp coordinate.hpp userInterface.hpp colors.hpp
./enemyPlacementFn.o: generalDetail.hpp damagedRobot.hpp Teleporter.hpp
./enemyPlacementFn.o: lampLight.hpp IntroDoor.hpp rock.hpp
./enemyPlacementFn.o: soundController.hpp framework/option.hpp
./soundController.o: soundController.hpp resourceHandler.hpp ResourcePath.hpp
./resourceHandler.o: resourceHandler.hpp ResourcePath.hpp
./inputController.o: inputController.hpp shutdownSignal.hpp
./enemyController.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./enemyController.o: turret.hpp /usr/include/stdio.h /usr/include/features.h
./enemyController.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./enemyController.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./enemyController.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./enemyController.o: /usr/include/libio.h /usr/include/_G_config.h
./enemyController.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./enemyController.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./enemyController.o: framework/framework.hpp framework/utilities.hpp
./enemyController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./enemyController.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./enemyController.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./enemyController.o: RenderType.hpp enemyShot.hpp math.hpp shotPuff.hpp
./enemyController.o: Item.hpp scoot.hpp wall.hpp /usr/include/stdint.h
./enemyController.o: /usr/include/bits/wchar.h enemy.hpp dasher.hpp
./enemyController.o: critter.hpp aStar.hpp util.hpp alias.hpp
./enemyController.o: tileController.hpp coordinate.hpp camera.hpp player.hpp
./enemyController.o: playerAnimationFunctions.hpp
./enemyController.o: playerCollisionFunctions.hpp treasureChest.hpp
./enemyController.o: detailParent.hpp inputController.hpp shutdownSignal.hpp
./enemyController.o: powerup.hpp detailController.hpp userInterface.hpp
./enemyController.o: colors.hpp generalDetail.hpp damagedRobot.hpp
./enemyController.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./enemyController.o: soundController.hpp game.hpp backgroundHandler.hpp
./enemyController.o: framework/option.hpp
./tileController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./tileController.o: /usr/include/features.h /usr/include/stdc-predef.h
./tileController.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./tileController.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./tileController.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./tileController.o: turret.hpp /usr/include/stdio.h /usr/include/bits/types.h
./tileController.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./tileController.o: /usr/include/_G_config.h /usr/include/wchar.h
./tileController.o: /usr/include/bits/stdio_lim.h
./tileController.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./tileController.o: framework/framework.hpp framework/utilities.hpp
./tileController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./tileController.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./tileController.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./tileController.o: RenderType.hpp enemyShot.hpp math.hpp shotPuff.hpp
./tileController.o: Item.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./tileController.o: aStar.hpp util.hpp alias.hpp coordinate.hpp camera.hpp
./tileController.o: player.hpp playerAnimationFunctions.hpp
./tileController.o: playerCollisionFunctions.hpp treasureChest.hpp
./tileController.o: detailParent.hpp inputController.hpp shutdownSignal.hpp
./tileController.o: powerup.hpp detailController.hpp userInterface.hpp
./tileController.o: colors.hpp generalDetail.hpp damagedRobot.hpp
./tileController.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./tileController.o: soundController.hpp mappingFunctions.hpp
./tileController.o: initMapVectors.hpp drawPixels.hpp
./smallExplosion.o: smallExplosion.hpp spriteSheet.hpp Effect.hpp
./smallExplosion.o: framework/framework.hpp framework/utilities.hpp
./smallExplosion.o: easingTemplates.hpp
./shutdownSignal.o: shutdownSignal.hpp
./initMapVectors.o: initMapVectors.hpp wall.hpp /usr/include/stdint.h
./initMapVectors.o: /usr/include/features.h /usr/include/stdc-predef.h
./initMapVectors.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./initMapVectors.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./initMapVectors.o: coordinate.hpp tileController.hpp enemyController.hpp
./initMapVectors.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./initMapVectors.o: /usr/include/stdio.h /usr/include/bits/types.h
./initMapVectors.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./initMapVectors.o: /usr/include/_G_config.h /usr/include/wchar.h
./initMapVectors.o: /usr/include/bits/stdio_lim.h
./initMapVectors.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./initMapVectors.o: framework/framework.hpp framework/utilities.hpp
./initMapVectors.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./initMapVectors.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./initMapVectors.o: bulletType1.hpp dasherShot.hpp turretShot.hpp
./initMapVectors.o: RenderType.hpp enemyShot.hpp math.hpp shotPuff.hpp
./initMapVectors.o: Item.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./initMapVectors.o: aStar.hpp util.hpp alias.hpp camera.hpp player.hpp
./initMapVectors.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./initMapVectors.o: treasureChest.hpp detailParent.hpp inputController.hpp
./initMapVectors.o: shutdownSignal.hpp powerup.hpp detailController.hpp
./initMapVectors.o: userInterface.hpp colors.hpp generalDetail.hpp
./initMapVectors.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp
./initMapVectors.o: IntroDoor.hpp rock.hpp soundController.hpp
./userInterface.o: userInterface.hpp effectsController.hpp
./userInterface.o: framework/framework.hpp framework/utilities.hpp
./userInterface.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./userInterface.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./userInterface.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./userInterface.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./userInterface.o: math.hpp shotPuff.hpp Item.hpp inputController.hpp
./userInterface.o: shutdownSignal.hpp powerup.hpp colors.hpp player.hpp
./userInterface.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./userInterface.o: wall.hpp /usr/include/stdint.h /usr/include/features.h
./userInterface.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./userInterface.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./userInterface.o: /usr/include/bits/wchar.h treasureChest.hpp
./userInterface.o: detailParent.hpp detailController.hpp tileController.hpp
./userInterface.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./userInterface.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./userInterface.o: /usr/include/libio.h /usr/include/_G_config.h
./userInterface.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./userInterface.o: /usr/include/bits/sys_errlist.h scoot.hpp enemy.hpp
./userInterface.o: dasher.hpp critter.hpp aStar.hpp util.hpp alias.hpp
./userInterface.o: coordinate.hpp camera.hpp generalDetail.hpp
./userInterface.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp
./userInterface.o: IntroDoor.hpp rock.hpp soundController.hpp
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
./Teleporter.o: Teleporter.hpp detailParent.hpp framework/framework.hpp
./Teleporter.o: framework/utilities.hpp effectsController.hpp
./Teleporter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./Teleporter.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./Teleporter.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./Teleporter.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./Teleporter.o: math.hpp shotPuff.hpp Item.hpp
./dasherShot.o: dasherShot.hpp spriteSheet.hpp Effect.hpp
./dasherShot.o: framework/framework.hpp framework/utilities.hpp rng.hpp
./dasherShot.o: easingTemplates.hpp
./lampLight.o: lampLight.hpp detailParent.hpp framework/framework.hpp
./lampLight.o: framework/utilities.hpp
./IntroDoor.o: IntroDoor.hpp detailParent.hpp framework/framework.hpp
./IntroDoor.o: framework/utilities.hpp effectsController.hpp
./IntroDoor.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./IntroDoor.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./IntroDoor.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./IntroDoor.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./IntroDoor.o: math.hpp shotPuff.hpp Item.hpp
./enemyShot.o: enemyShot.hpp spriteSheet.hpp Effect.hpp
./enemyShot.o: framework/framework.hpp framework/utilities.hpp math.hpp
./enemyShot.o: rng.hpp
./shotPuff.o: shotPuff.hpp spriteSheet.hpp Effect.hpp framework/framework.hpp
./shotPuff.o: framework/utilities.hpp
./critter.o: critter.hpp enemy.hpp wall.hpp /usr/include/stdint.h
./critter.o: /usr/include/features.h /usr/include/stdc-predef.h
./critter.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./critter.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./critter.o: effectsController.hpp framework/framework.hpp
./critter.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./critter.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./critter.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./critter.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./critter.o: enemyShot.hpp math.hpp shotPuff.hpp Item.hpp aStar.hpp
./critter.o: tileController.hpp enemyController.hpp turret.hpp
./critter.o: /usr/include/stdio.h /usr/include/bits/types.h
./critter.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./critter.o: /usr/include/_G_config.h /usr/include/wchar.h
./critter.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./critter.o: scoot.hpp dasher.hpp util.hpp alias.hpp coordinate.hpp
./critter.o: camera.hpp player.hpp playerAnimationFunctions.hpp
./critter.o: playerCollisionFunctions.hpp treasureChest.hpp detailParent.hpp
./critter.o: inputController.hpp shutdownSignal.hpp powerup.hpp
./critter.o: detailController.hpp userInterface.hpp colors.hpp
./critter.o: generalDetail.hpp damagedRobot.hpp Teleporter.hpp lampLight.hpp
./critter.o: IntroDoor.hpp rock.hpp soundController.hpp /usr/include/math.h
./critter.o: /usr/include/bits/math-vector.h
./critter.o: /usr/include/bits/libm-simd-decl-stubs.h
./critter.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
./critter.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
./critter.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
./critter.o: /usr/include/bits/mathcalls.h
./turret.o: turret.hpp /usr/include/stdio.h /usr/include/features.h
./turret.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./turret.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./turret.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./turret.o: /usr/include/libio.h /usr/include/_G_config.h
./turret.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./turret.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./turret.o: framework/framework.hpp framework/utilities.hpp
./turret.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./turret.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./turret.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./turret.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./turret.o: math.hpp shotPuff.hpp Item.hpp angleFunction.hpp
./player.o: player.hpp playerAnimationFunctions.hpp
./player.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
./player.o: /usr/include/features.h /usr/include/stdc-predef.h
./player.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./player.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./player.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./player.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./player.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./player.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./player.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./player.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./player.o: /usr/include/libio.h /usr/include/_G_config.h
./player.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./player.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./player.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./player.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./player.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./player.o: math.hpp shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./player.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./player.o: camera.hpp userInterface.hpp colors.hpp generalDetail.hpp
./player.o: damagedRobot.hpp Teleporter.hpp lampLight.hpp IntroDoor.hpp
./player.o: rock.hpp soundController.hpp game.hpp backgroundHandler.hpp
./player.o: framework/option.hpp
./dasher.o: dasher.hpp effectsController.hpp framework/framework.hpp
./dasher.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./dasher.o: Effect.hpp rng.hpp resourceHandler.hpp ResourcePath.hpp
./dasher.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./dasher.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./dasher.o: enemyShot.hpp math.hpp shotPuff.hpp Item.hpp enemy.hpp wall.hpp
./dasher.o: /usr/include/stdint.h /usr/include/features.h
./dasher.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./dasher.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./dasher.o: /usr/include/bits/wchar.h angleFunction.hpp
./camera.o: camera.hpp player.hpp playerAnimationFunctions.hpp
./camera.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
./camera.o: /usr/include/features.h /usr/include/stdc-predef.h
./camera.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./camera.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./camera.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./camera.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./camera.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./camera.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./camera.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./camera.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./camera.o: /usr/include/libio.h /usr/include/_G_config.h
./camera.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
./camera.o: /usr/include/bits/sys_errlist.h effectsController.hpp
./camera.o: turretFlashEffect.hpp Effect.hpp smallExplosion.hpp
./camera.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./camera.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./camera.o: math.hpp shotPuff.hpp Item.hpp scoot.hpp enemy.hpp dasher.hpp
./camera.o: critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./camera.o: userInterface.hpp colors.hpp generalDetail.hpp damagedRobot.hpp
./camera.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./camera.o: soundController.hpp
./scoot.o: scoot.hpp wall.hpp /usr/include/stdint.h /usr/include/features.h
./scoot.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./scoot.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./scoot.o: /usr/include/bits/wchar.h effectsController.hpp
./scoot.o: framework/framework.hpp framework/utilities.hpp
./scoot.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./scoot.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./scoot.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./scoot.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./scoot.o: math.hpp shotPuff.hpp Item.hpp enemy.hpp angleFunction.hpp
./enemy.o: enemy.hpp wall.hpp /usr/include/stdint.h /usr/include/features.h
./enemy.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./enemy.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./enemy.o: /usr/include/bits/wchar.h effectsController.hpp
./enemy.o: framework/framework.hpp framework/utilities.hpp
./enemy.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./enemy.o: resourceHandler.hpp ResourcePath.hpp smallExplosion.hpp
./enemy.o: easingTemplates.hpp FireExplosion.hpp bulletType1.hpp
./enemy.o: dasherShot.hpp turretShot.hpp RenderType.hpp enemyShot.hpp
./enemy.o: math.hpp shotPuff.hpp Item.hpp
./aStar.o: aStar.hpp /usr/include/stdint.h /usr/include/features.h
./aStar.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./aStar.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./aStar.o: /usr/include/bits/wchar.h
./wall.o: wall.hpp /usr/include/stdint.h /usr/include/features.h
./wall.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./wall.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./wall.o: /usr/include/bits/wchar.h
./util.o: util.hpp alias.hpp RenderType.hpp
./rock.o: rock.hpp detailParent.hpp framework/framework.hpp
./rock.o: framework/utilities.hpp spriteSheet.hpp rng.hpp
./main.o: framework/smartThread.hpp backgroundHandler.hpp camera.hpp
./main.o: player.hpp playerAnimationFunctions.hpp
./main.o: playerCollisionFunctions.hpp wall.hpp /usr/include/stdint.h
./main.o: /usr/include/features.h /usr/include/stdc-predef.h
./main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./main.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
./main.o: treasureChest.hpp detailParent.hpp framework/framework.hpp
./main.o: framework/utilities.hpp inputController.hpp shutdownSignal.hpp
./main.o: spriteSheet.hpp rng.hpp powerup.hpp detailController.hpp
./main.o: resourceHandler.hpp ResourcePath.hpp tileController.hpp
./main.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
./main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./main.o: effectsController.hpp turretFlashEffect.hpp Effect.hpp
./main.o: smallExplosion.hpp easingTemplates.hpp FireExplosion.hpp
./main.o: bulletType1.hpp dasherShot.hpp turretShot.hpp RenderType.hpp
./main.o: enemyShot.hpp math.hpp shotPuff.hpp Item.hpp scoot.hpp enemy.hpp
./main.o: dasher.hpp critter.hpp aStar.hpp util.hpp alias.hpp coordinate.hpp
./main.o: userInterface.hpp colors.hpp generalDetail.hpp damagedRobot.hpp
./main.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./main.o: soundController.hpp aspectScaling.hpp game.hpp framework/option.hpp
./Item.o: Item.hpp spriteSheet.hpp Effect.hpp framework/framework.hpp
./Item.o: framework/utilities.hpp
./game.o: mappingFunctions.hpp tileController.hpp wall.hpp
./game.o: /usr/include/stdint.h /usr/include/features.h
./game.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
./game.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
./game.o: /usr/include/bits/wchar.h enemyController.hpp resourceHandler.hpp
./game.o: ResourcePath.hpp turret.hpp /usr/include/stdio.h
./game.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./game.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
./game.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./game.o: effectsController.hpp framework/framework.hpp
./game.o: framework/utilities.hpp turretFlashEffect.hpp spriteSheet.hpp
./game.o: Effect.hpp rng.hpp smallExplosion.hpp easingTemplates.hpp
./game.o: FireExplosion.hpp bulletType1.hpp dasherShot.hpp turretShot.hpp
./game.o: RenderType.hpp enemyShot.hpp math.hpp shotPuff.hpp Item.hpp
./game.o: scoot.hpp enemy.hpp dasher.hpp critter.hpp aStar.hpp util.hpp
./game.o: alias.hpp coordinate.hpp camera.hpp player.hpp
./game.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./game.o: treasureChest.hpp detailParent.hpp inputController.hpp
./game.o: shutdownSignal.hpp powerup.hpp detailController.hpp
./game.o: userInterface.hpp colors.hpp generalDetail.hpp damagedRobot.hpp
./game.o: Teleporter.hpp lampLight.hpp IntroDoor.hpp rock.hpp
./game.o: soundController.hpp enemyPlacementFn.hpp initMapVectors.hpp
./game.o: pillarPlacement.h lightingMap.h game.hpp backgroundHandler.hpp
./game.o: framework/option.hpp /usr/include/math.h
./game.o: /usr/include/bits/math-vector.h
./game.o: /usr/include/bits/libm-simd-decl-stubs.h
./game.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
./game.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
./game.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
./game.o: /usr/include/bits/mathcalls.h
./rng.o: rng.hpp
