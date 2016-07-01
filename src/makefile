#
# makefile for Blind Jump game
# Evan Bowman 2016
# Style guidelines:
#  - Object dependencies in ABC order
#

CC = clang++
CPPFLAGS = -O2 -std=c++14 -Wall -Werror
LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -fobjc-link-runtime
EXENAME = BlindJump
OBJECTS = aStar.o backgroundHandler.o bulletType1.o critter.o damagedRobot.o dasher.o dasherShot.o dashSmoke.o detailController.o detailParent.o drawPixels.o effect.o effectsController.o enemy.o enemyController.o enemyCreationFunctions.o enemyParent.o enemyPlacementFn.o enemyShot.o FireExplosion.o fontController.o generalDetail.o gameMap.o initLoot.o initMapVectors.o inputController.o IntroDoor.o lampLight.o main.o mappingFunctions.o player.o playerCollisionFunctions.o Powerup.o ResourcePath.o rock.o scoot.o screenShakeController.o shotPuff.o smallExplosion.o soundController.o teleporter.o teleporterSmoke.o resourceHandler.o  tileController.o treasureChest.o turret.o turretFlashEffect.o turretShot.o userInterface.o wall.o
RSP = ResourcePath.hpp ResourcePath.cpp

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXENAME)

aStar.o: aStar.hpp aStar.cpp
	$(CC) aStar.cpp $(CPPFLAGS) -c -o aStar.o

backgroundHandler.o: backgroundHandler.hpp backgroundHandler.cpp $(RSP)
	$(CC) backgroundHandler.cpp $(CPPFLAGS) -c -o backgroundHandler.o

bulletType1.o: bulletType1.cpp bulletType1.hpp spriteSheet.hpp
	$(CC) bulletType1.cpp $(CPPFLAGS) -c -o bulletType1.o

critter.o: critter.cpp critter.hpp tileController.hpp enemyParent.hpp aStar.hpp spriteSheet.hpp
	$(CC) critter.cpp $(CPPFLAGS) -c -o critter.o

damagedRobot.o: damagedRobot.cpp damagedRobot.hpp detailParent.hpp spriteSheet.hpp
	$(CC) damagedRobot.cpp $(CPPFLAGS) -c -o damagedRobot.o

dasher.o: dasher.cpp dasher.hpp angleFunction.hpp  enemy.hpp effectsController.hpp
	$(CC) dasher.cpp $(CPPFLAGS) -c -o dasher.o

dasherShot.o: dasherShot.hpp spriteSheet.hpp
	$(CC) dasherShot.cpp $(CPPFLAGS) -c -o dasherShot.o

dashSmoke.o: dashSmoke.hpp dashSmoke.cpp
	$(CC) dashSmoke.cpp $(CPPFLAGS) -c -o dashSmoke.o

detailController.o: detailController.hpp detailController.cpp gameMap.hpp Teleporter.hpp treasureChest.hpp tileController.hpp coordinate.hpp generalDetail.hpp lampLight.hpp userInterface.hpp damagedRobot.hpp rock.hpp IntroDoor.hpp RenderType.hpp resourceHandler.hpp spriteSheet.hpp player.hpp
	$(CC) detailController.cpp $(CPPFLAGS) -c -o detailController.o

detailParent.o: detailParent.hpp detailParent.cpp
	$(CC) detailParent.cpp $(CPPFLAGS) -c -o detailParent.o

drawPixels.o: drawPixels.hpp drawPixels.cpp
	$(CC) drawPixels.cpp -Ofast -std=c++14 -c -o drawPixels.o

effect.o: Effect.cpp Effect.hpp
	$(CC) Effect.cpp -std=c++14 -O2 -c -o effect.o

effectsController.o: effectsController.cpp effectsController.hpp screenShakeController.hpp turretFlashEffect.hpp bulletType1.hpp shotPuff.hpp turretShot.hpp  teleporterSmoke.hpp enemyShot.hpp dasherShot.hpp fontController.hpp dashSmoke.hpp FireExplosion.hpp smallExplosion.hpp Powerup.hpp RenderType.hpp resourceHandler.hpp
	$(CC) effectsController.cpp $(CPPFLAGS) -c -o effectsController.o

enemy.o: enemy.cpp enemy.hpp effectsController.hpp
	$(CC) enemy.cpp $(CPPFLAGS) -c -o enemy.o

enemyController.o: enemyController.hpp enemyController.cpp $(RSP) wall.hpp tileController.hpp detailController.hpp screenShakeController.hpp turret.hpp effectsController.hpp scoot.hpp dasher.hpp critter.hpp RenderType.hpp
	$(CC) enemyController.cpp $(CPPFLAGS) -c -o enemyController.o

enemyCreationFunctions.o: enemyCreationFunctions.hpp enemyCreationFunctions.cpp turret.hpp scoot.hpp enemyController.hpp coordinate.hpp
	$(CC) enemyCreationFunctions.cpp $(CPPFLAGS) -c -o enemyCreationFunctions.o

enemyParent.o: enemyParent.hpp enemyParent.cpp wall.hpp
	$(CC) enemyParent.cpp $(CPPFLAGS) -c -o enemyParent.o

enemyPlacementFn.o: enemyPlacementFn.hpp enemyPlacementFn.cpp gameMap.hpp enemyCreationFunctions.hpp
	$(CC) enemyPlacementFn.cpp $(CPPFLAGS) -c -o enemyPlacementFn.o

enemyShot.o: enemyShot.hpp enemyShot.cpp
	$(CC) enemyShot.cpp $(CPPFLAGS) -c -o enemyShot.o

FireExplosion.o: FireExplosion.hpp FireExplosion.cpp spriteSheet.hpp Effect.hpp
	$(CC) FireExplosion.cpp $(CPPFLAGS) -c -o FireExplosion.o

fontController.o: fontController.cpp fontController.hpp $(RSP)
	$(CC) fontController.cpp $(CPPFLAGS) -c -o fontController.o

gameMap.o: gameMap.cpp gameMap.hpp mappingFunctions.hpp initMapVectors.hpp $(RSP) enemyPlacementFn.hpp lightingMap.h pillarPlacement.h enemyCreationFunctions.hpp backgroundHandler.hpp player.hpp effectsController.hpp detailController.hpp tileController.hpp fontController.hpp userInterface.hpp enemyController.hpp screenShakeController.hpp soundController.hpp initLoot.hpp inputController.hpp RenderType.hpp resourceHandler.hpp
	$(CC) gameMap.cpp $(CPPFLAGS) -c -o gameMap.o

generalDetail.o: generalDetail.hpp generalDetail.cpp detailParent.hpp
	$(CC) generalDetail.cpp $(CPPFLAGS) -c -o generalDetail.o

initLoot.o: initLoot.hpp initLoot.cpp
	$(CC) initLoot.cpp $(CPPFLAGS) -c -o initLoot.o

initMapVectors.o: initMapVectors.hpp initMapVectors.cpp wall.hpp coordinate.hpp tileController.hpp
	$(CC) initMapVectors.cpp $(CPPFLAGS) -c -o initMapVectors.o

inputController.o: inputController.hpp inputController.cpp
	$(CC) inputController.cpp $(CPPFLAGS) -c -o inputController.o

IntroDoor.o: IntroDoor.cpp IntroDoor.hpp screenShakeController.hpp detailController.hpp inputController.hpp
	$(CC) IntroDoor.cpp $(CPPFLAGS) -c -o IntroDoor.o

lampLight.o: lampLight.cpp lampLight.hpp detailParent.hpp
	$(CC) lampLight.cpp $(CPPFLAGS) -c -o lampLight.o

main.o: player.hpp backgroundHandler.hpp gameMap.hpp $(RSP) inputController.hpp main.cpp resourceHandler.hpp
	$(CC) main.cpp $(CPPFLAGS) -c -o main.o

mappingFunctions.o: mappingFunctions.hpp mappingFunctions.cpp tileController.hpp
	$(CC) mappingFunctions.cpp $(CPPFLAGS) -c -o mappingFunctions.o

player.o: player.hpp player.cpp playerAnimationFunctions.hpp playerCollisionFunctions.hpp wall.hpp tileController.hpp detailController.hpp soundController.hpp inputController.hpp RenderType.hpp resourceHandler.hpp spriteSheet.hpp
	$(CC) player.cpp $(CPPFLAGS) -c -o player.o

playerCollisionFunctions.o: playerCollisionFunctions.hpp playerCollisionFunctions.cpp wall.hpp treasureChest.hpp
	$(CC) playerCollisionFunctions.cpp $(CPPFLAGS) -c -o playerCollisionFunctions.o

Powerup.o: Powerup.hpp Powerup.cpp spriteSheet.hpp
	$(CC) Powerup.cpp $(CPPFLAGS) -c -o Powerup.o

ResourcePath.o: ResourcePath.mm ResourcePath.hpp
	$(CC) ResourcePath.mm -c -o ResourcePath.o

rock.o: rock.hpp rock.cpp detailParent.hpp spriteSheet.hpp
	$(CC) rock.cpp $(CPPFLAGS) -c -o rock.o

scoot.o: scoot.cpp scoot.hpp angleFunction.hpp enemy.hpp wall.hpp effectsController.hpp
	$(CC) scoot.cpp $(CPPFLAGS) -c -o scoot.o

screenShakeController.o: screenShakeController.cpp screenShakeController.hpp player.hpp
	$(CC) screenShakeController.cpp $(CPPFLAGS) -c -o screenShakeController.o

shotPuff.o: shotPuff.cpp shotPuff.hpp spriteSheet.hpp Effect.hpp
	$(CC) shotPuff.cpp $(CPPFLAGS) -c -o shotPuff.o

smallExplosion.o: smallExplosion.cpp smallExplosion.hpp spriteSheet.hpp Effect.hpp
	$(CC) smallExplosion.cpp $(CPPFLAGS) -c -o smallExplosion.o

soundController.o: soundController.cpp soundController.hpp $(RSP)
	$(CC) soundController.cpp $(CPPFLAGS) -c -o soundController.o

teleporter.o: Teleporter.hpp Teleporter.cpp detailParent.hpp spriteSheet.hpp
	$(CC) Teleporter.cpp $(CPPFLAGS) -c -o teleporter.o

teleporterSmoke.o: teleporterSmoke.cpp teleporterSmoke.hpp spriteSheet.hpp Effect.hpp
	$(CC) teleporterSmoke.cpp $(CPPFLAGS) -c -o teleporterSmoke.o

resourceHandler.o: $(RSP) resourceHandler.cpp resourceHandler.hpp textureEnum.hpp
	$(CC) resourceHandler.cpp $(CPPFLAGS) -c -o resourceHandler.o

tileController.o: tileController.cpp tileController.hpp $(RSP) mappingFunctions.hpp turret.hpp initMapVectors.hpp drawPixels.hpp wall.hpp enemyController.hpp coordinate.hpp resourceHandler.hpp
	$(CC) tileController.cpp $(CPPFLAGS) -c -o tileController.o

treasureChest.o: treasureChest.cpp treasureChest.hpp detailParent.hpp spriteSheet.hpp
	$(CC) treasureChest.cpp $(CPPFLAGS) -c -o treasureChest.o

turret.o: turret.cpp turret.hpp angleFunction.hpp turret.hpp effectsController.hpp
	$(CC) turret.cpp $(CPPFLAGS) -c -o turret.o

turretFlashEffect.o: turretFlashEffect.cpp turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
	$(CC) turretFlashEffect.cpp $(CPPFLAGS) -c -o turretFlashEffect.o

turretShot.o: turretShot.cpp turretShot.hpp spriteSheet.hpp
	$(CC) turretShot.cpp $(CPPFLAGS) -c -o turretShot.o

userInterface.o: userInterface.cpp userInterface.hpp player.hpp fontController.hpp inputController.hpp
	$(CC) userInterface.cpp $(CPPFLAGS) -c -o userInterface.o

wall.o: wall.cpp wall.hpp
	$(CC) wall.cpp $(CPPFLAGS) -c -o wall.o

clean:
	rm *.o

MacOS: all packageScriptMac.sh
	bash packageScriptMac.sh $(EXENAME) BlindJump
