#
# makefile for Blind Jump game
# Evan Bowman 2016
# Style guidelines:
#  - Object dependencies in ABC order
#

CC = clang++
CFLAGS = -O2 -std=c++11 -Wall -Weffc++ -Werror
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXENAME = Blind_Jump
OBJECTS = aStar.o backgroundHandler.o bulletType1.o critter.o damagedRobot.o dasher.o dasherShot.o dashSmoke.o detailController.o detailParent.o drawPixels.o effectsController.o enemyController.o enemyCreationFunctions.o enemyParent.o enemyPlacementFn.o enemyShot.o energyBeam.o explosion32effect.o FireExplosion.o fontController.o generalDetail.o gameMap.o GradientCircle.o gun.o healthEffect.o heavyBot.o initLoot.o initMapVectors.o inputController.o IntroDoor.o lampLight.o main.o mappingFunctions.o player.o playerCollisionFunctions.o Powerup.o ResourcePath.o rock.o scoot.o screenShakeController.o shotPuff.o smallExplosion.o soundController.o Teleporter.o teleporterSmoke.o terminal.o tileController.o treasureChest.o turret.o turretFlashEffect.o turretShot.o ui_bubble.o userInterface.o wall.o wallinpath.o worldDetailsController.o
RSP = resourcePath.hpp resourcePath.cpp

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $(EXENAME)

aStar.o: aStar.hpp aStar.cpp
	$(CC) aStar.cpp $(CFLAGS) -c -o aStar.o

backgroundHandler.o: backgroundHandler.hpp backgroundHandler.cpp $(RSP)
	$(CC) backgroundHandler.cpp $(CFLAGS) -c -o backgroundHandler.o

bulletType1.o: bulletType1.cpp bulletType1.hpp
	$(CC) bulletType1.cpp $(CFLAGS) -c -o bulletType1.o

critter.o: critter.cpp critter.hpp tileController.hpp
	$(CC) critter.cpp $(CFLAGS) -c -o critter.o

damagedRobot.o: damagedRobot.cpp damagedRobot.hpp
	$(CC) damagedRobot.cpp $(CFLAGS) -c -o damagedRobot.o

dasher.o: dasher.cpp dasher.hpp angleFunction.hpp wallinpath.hpp
	$(CC) dasher.cpp $(CFLAGS) -c -o dasher.o

dasherShot.o: dasherShot.hpp
	$(CC) dasherShot.cpp $(CFLAGS) -c -o dasherShot.o

dashSmoke.o: dashSmoke.hpp dashSmoke.cpp
	$(CC) dashSmoke.cpp $(CFLAGS) -c -o dashSmoke.o

detailController.o: detailController.hpp detailController.cpp $(RSP)
	$(CC) detailController.cpp $(CFLAGS) -c -o detailController.o

detailParent.o: detailParent.hpp detailParent.cpp
	$(CC) detailParent.cpp $(CFLAGS) -c -o detailParent.o

drawPixels.o: drawPixels.hpp drawPixels.cpp
	$(CC) drawPixels.cpp $(CFLAGS) -c -o drawPixels.o

effectsController.o: effectsController.cpp effectsController.hpp screenShakeController.hpp
	$(CC) effectsController.cpp $(CFLAGS) -c -o effectsController.o

enemyController.o: enemyController.hpp enemyController.cpp $(RSP) wall.hpp tileController.hpp detailController.hpp screenShakeController.hpp
	$(CC) enemyController.cpp $(CFLAGS) -c -o enemyController.o

enemyCreationFunctions.o: enemyCreationFunctions.hpp enemyCreationFunctions.cpp turret.hpp scoot.hpp dasher.hpp
	$(CC) enemyCreationFunctions.cpp $(CFLAGS) -c -o enemyCreationFunctions.o

enemyParent.o: enemyParent.hpp enemyParent.cpp
	$(CC) enemyParent.cpp $(CFLAGS) -c -o enemyParent.o

enemyPlacementFn.o: enemyPlacementFn.hpp enemyPlacementFn.cpp gameMap.hpp enemyCreationFunctions.hpp
	$(CC) enemyPlacementFn.cpp $(CFLAGS) -c -o enemyPlacementFn.o

enemyShot.o: enemyShot.hpp enemyShot.cpp
	$(CC) enemyShot.cpp $(CFLAGS) -c -o enemyShot.o

energyBeam.o: energyBeam.cpp energyBeam.hpp
	$(CC) energyBeam.cpp $(CFLAGS) -c -o energyBeam.o

explosion32effect.o: explosion32effect.cpp explosion32effect.hpp
	$(CC) explosion32effect.cpp $(CFLAGS) -c -o explosion32effect.o

FireExplosion.o: FireExplosion.hpp FireExplosion.cpp
	$(CC) FireExplosion.cpp $(CFLAGS) -c -o FireExplosion.o

fontController.o: fontController.cpp fontController.hpp
	$(CC) fontController.cpp $(CFLAGS) -c -o fontController.o

gameMap.o: gameMap.cpp gameMap.hpp mappingFunctions.hpp initMapVectors.hpp $(RSP) enemyPlacementFn.hpp lightingMap.h pillarPlacement.h enemyCreationFunctions.hpp
	$(CC) gameMap.cpp $(CFLAGS) -c -o gameMap.o

generalDetail.o: generalDetail.hpp generalDetail.cpp
	$(CC) generalDetail.cpp $(CFLAGS) -c -o generalDetail.o

GradientCircle.o: GradientCircle.cpp GradientCircle.hpp
	$(CC) GradientCircle.cpp $(CFLAGS) -c -o GradientCircle.o

gun.o: gun.cpp gun.hpp $(RSP) bulletType1.hpp
	$(CC) gun.cpp $(CFLAGS) -c -o gun.o

healthEffect.o: healthEffect.cpp healthEffect.hpp
	$(CC) healthEffect.cpp $(CFLAGS) -c -o healthEffect.o

heavyBot.o: heavyBot.hpp heavyBot.cpp tileController.hpp
	$(CC) heavyBot.cpp $(CFLAGS) -c -o heavyBot.o

initLoot.o: initLoot.hpp initLoot.cpp
	$(CC) initLoot.cpp $(CFLAGS) -c -o initLoot.o

initMapVectors.o: initMapVectors.hpp initMapVectors.cpp
	$(CC) initMapVectors.cpp $(CFLAGS) -c -o initMapVectors.o

inputController.o: inputController.hpp inputController.cpp
	$(CC) inputController.cpp $(CFLAGS) -c -o inputController.o

IntroDoor.o: IntroDoor.cpp IntroDoor.hpp screenShakeController.hpp
	$(CC) IntroDoor.cpp $(CFLAGS) -c -o IntroDoor.o

lampLight.o: lampLight.cpp lampLight.hpp
	$(CC) lampLight.cpp $(CFLAGS) -c -o lampLight.o

main.o: player.hpp backgroundHandler.hpp gameMap.hpp $(RSP) inputController.hpp
	$(CC) main.cpp $(CFLAGS) -c -o main.o

mappingFunctions.o: mappingFunctions.hpp mappingFunctions.cpp tileController.hpp bossLevels.h
	$(CC) mappingFunctions.cpp $(CFLAGS) -c -o mappingFunctions.o

player.o: player.hpp player.cpp $(RSP) playerAnimationFunctions.hpp playerCollisionFunctions.hpp wall.hpp
	$(CC) player.cpp $(CFLAGS) -c -o player.o

playerCollisionFunctions.o: playerCollisionFunctions.hpp playerCollisionFunctions.cpp
	$(CC) playerCollisionFunctions.cpp $(CFLAGS) -c -o playerCollisionFunctions.o

Powerup.o: Powerup.hpp Powerup.cpp
	$(CC) Powerup.cpp $(CFLAGS) -c -o Powerup.o

ResourcePath.o: ResourcePath.cpp ResourcePath.hpp
	$(CC) ResourcePath.cpp $(CFLAGS) -c -o ResourcePath.o

rock.o: rock.hpp rock.cpp
	$(CC) rock.cpp $(CFLAGS) -c -o rock.o

scoot.o: scoot.cpp scoot.hpp angleFunction.hpp
	$(CC) scoot.cpp $(CFLAGS) -c -o scoot.o

screenShakeController.o: screenShakeController.cpp screenShakeController.hpp
	$(CC) screenShakeController.cpp $(CFLAGS) -c -o screenShakeController.o

shotPuff.o: shotPuff.cpp shotPuff.hpp
	$(CC) shotPuff.cpp $(CFLAGS) -c -o shotPuff.o

smallExplosion.o: smallExplosion.cpp smallExplosion.hpp
	$(CC) smallExplosion.cpp $(CFLAGS) -c -o smallExplosion.o

soundController.o: soundController.cpp soundController.hpp $(RSP)
	$(CC) soundController.cpp $(CFLAGS) -c -o soundController.o

Teleporter.o: Teleporter.hpp Teleporter.cpp
	$(CC) Teleporter.cpp $(CFLAGS) -c -o teleporter.o

teleporterSmoke.o: teleporterSmoke.cpp teleporterSmoke.hpp
	$(CC) teleporterSmoke.cpp $(CFLAGS) -c -o teleporterSmoke.o

terminal.o: terminal.cpp terminal.hpp
	$(CC) terminal.cpp $(CFLAGS) -c -o terminal.o

tileController.o: tileController.cpp tileController.hpp $(RSP) mappingFunctions.hpp turret.hpp initMapVectors.hpp drawPixels.hpp
	$(CC) tileController.cpp $(CFLAGS) -c -o tileController.o

treasureChest.o: treasureChest.cpp treasureChest.hpp
	$(CC) treasureChest.cpp $(CFLAGS) -c -o treasureChest.o

turret.o: turret.cpp turret.hpp angleFunction.hpp
	$(CC) turret.cpp $(CFLAGS) -c -o turret.o

turretFlashEffect.o: turretFlashEffect.cpp turretFlashEffect.hpp
	$(CC) turretFlashEffect.cpp $(CFLAGS) -c -o turretFlashEffect.o

turretShot.o: turretShot.cpp turretShot.hpp
	$(CC) turretShot.cpp $(CFLAGS) -c -o turretShot.o

ui_bubble.o: ui_bubble.cpp ui_bubble.hpp
	$(CC) ui_bubble.cpp $(CFLAGS) -c -o ui_bubble.o

userInterface.o: userInterface.cpp userInterface.hpp $(RSP) player.hpp
	$(CC) userInterface.cpp $(CFLAGS) -c -o userInterface.o

wall.o: wall.cpp wall.hpp
	$(CC) wall.cpp $(CFLAGS) -c -o wall.o

wallinpath.o: wallinpath.cpp wallinpath.hpp
	$(CC) wallinpath.cpp $(CFLAGS) -c -o wallinpath.o

worldDetailsController.o: worldDetailsController.cpp worldDetailsController.hpp
	$(CC) worldDetailsController.cpp $(CFLAGS) -c -o worldDetailsController.o

clean:
	rm *.o

