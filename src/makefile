#
#  makefile for Blind Jump game
#  Evan Bowman 2016
# 

CC = clang++
override CPPFLAGS += -O2 -std=c++14 -Wall -Werror
LDFLAGS_MAC = -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -Xlinker -rpath -Xlinker @loader_path/../Frameworks -fobjc-link-runtime
LDFLAGS_LINUX = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
EXECUTABLE = BlindJump
SOURCES = $(shell find . -name "*.cpp" | awk '{print length, $$0;}' | sort -nr | cut -d ' ' -f 2-) # Hey it looks nice though
OBJECTS = $(SOURCES:.cpp=.o)

all:
	@echo Specify a platform to build for, i.e.: make macOS or make Linux

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $@

macOS: $(OBJECTS) packageScriptMac.sh ResourcePath.mm ResourcePath.hpp
	$(CC) ResourcePath.mm -c -o ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS_MAC)
	bash packageScriptMac.sh $(EXECUTABLE) BlindJump

Linux: $(OBJECTS) ResourcePath.hpp ResourcePath.cxx
	$(CC) -c ResourcePath.cxx -o ResourcePath.o
	$(CC) $(OBJECTS) ResourcePath.o -o $(EXECUTABLE) $(LDFLAGS_LINUX)

clean:
	rm *.o

depend:
	makedepend -- $(CPPFLAGS) -- $(SOURCES)

# DO NOT DELETE

./playerCollisionFunctions.o: playerCollisionFunctions.hpp wall.hpp
./playerCollisionFunctions.o: /usr/include/stdint.h /usr/include/features.h
./playerCollisionFunctions.o: /usr/include/stdc-predef.h treasureChest.hpp
./playerCollisionFunctions.o: detailParent.hpp /usr/include/SFML/Graphics.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Config.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Clock.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Export.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Time.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Err.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/FileInputStream.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/InputStream.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/NonCopyable.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Lock.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/MemoryInputStream.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Mutex.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Sleep.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/String.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Utf.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Utf.inl
./playerCollisionFunctions.o: /usr/include/SFML/System/String.inl
./playerCollisionFunctions.o: /usr/include/SFML/System/Thread.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Thread.inl
./playerCollisionFunctions.o: /usr/include/SFML/System/ThreadLocal.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./playerCollisionFunctions.o: /usr/include/SFML/System/Vector2.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Vector2.inl
./playerCollisionFunctions.o: /usr/include/SFML/System/Vector3.hpp
./playerCollisionFunctions.o: /usr/include/SFML/System/Vector3.inl
./playerCollisionFunctions.o: /usr/include/SFML/Window/Context.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Export.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/GlResource.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/ContextSettings.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Event.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Joystick.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Keyboard.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Mouse.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Sensor.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Touch.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/VideoMode.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/Window.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/WindowHandle.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Window/WindowStyle.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/BlendMode.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Export.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/CircleShape.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Shape.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Drawable.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/RenderStates.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Transform.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Rect.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Rect.inl
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Transformable.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/VertexArray.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Vertex.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Color.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Font.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Glyph.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Texture.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Image.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/View.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Shader.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Sprite.hpp
./playerCollisionFunctions.o: /usr/include/SFML/Graphics/Text.hpp
./playerCollisionFunctions.o: Framework/framework.hpp Framework/utilities.hpp
./playerCollisionFunctions.o: inputController.hpp spriteSheet.hpp rng.hpp
./enemyCreationFunctions.o: enemyCreationFunctions.hpp /usr/include/stdio.h
./enemyCreationFunctions.o: /usr/include/features.h
./enemyCreationFunctions.o: /usr/include/stdc-predef.h /usr/include/libio.h
./enemyCreationFunctions.o: /usr/include/_G_config.h /usr/include/wchar.h
./enemyCreationFunctions.o: enemyController.hpp resourceHandler.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Config.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Clock.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Export.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Time.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Err.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/FileInputStream.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/InputStream.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/NonCopyable.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Lock.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Mutex.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Sleep.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/String.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Utf.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Utf.inl
./enemyCreationFunctions.o: /usr/include/SFML/System/String.inl
./enemyCreationFunctions.o: /usr/include/SFML/System/Thread.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Thread.inl
./enemyCreationFunctions.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemyCreationFunctions.o: /usr/include/SFML/System/Vector2.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Vector2.inl
./enemyCreationFunctions.o: /usr/include/SFML/System/Vector3.hpp
./enemyCreationFunctions.o: /usr/include/SFML/System/Vector3.inl
./enemyCreationFunctions.o: /usr/include/SFML/Window/Context.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Export.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/GlResource.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Event.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Joystick.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Keyboard.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Mouse.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Sensor.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Touch.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/VideoMode.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/Window.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Export.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Shape.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Transform.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Rect.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Rect.inl
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Color.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Font.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Texture.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Image.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/View.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Shader.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemyCreationFunctions.o: /usr/include/SFML/Graphics/Text.hpp
./enemyCreationFunctions.o: ResourcePath.hpp turret.hpp fontController.hpp
./enemyCreationFunctions.o: effectsController.hpp turretFlashEffect.hpp
./enemyCreationFunctions.o: spriteSheet.hpp Effect.hpp
./enemyCreationFunctions.o: Framework/framework.hpp Framework/utilities.hpp
./enemyCreationFunctions.o: rng.hpp bulletType1.hpp shotPuff.hpp
./enemyCreationFunctions.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp
./enemyCreationFunctions.o: RenderType.hpp enemyShot.hpp dasherShot.hpp
./enemyCreationFunctions.o: turretShot.hpp scoot.hpp wall.hpp
./enemyCreationFunctions.o: /usr/include/stdint.h enemy.hpp dasher.hpp
./enemyCreationFunctions.o: critter.hpp aStar.hpp coordinate.hpp
./screenShakeController.o: screenShakeController.hpp player.hpp
./screenShakeController.o: /usr/include/SFML/Graphics.hpp
./screenShakeController.o: /usr/include/SFML/Window.hpp
./screenShakeController.o: /usr/include/SFML/System.hpp
./screenShakeController.o: /usr/include/SFML/Config.hpp
./screenShakeController.o: /usr/include/SFML/System/Clock.hpp
./screenShakeController.o: /usr/include/SFML/System/Export.hpp
./screenShakeController.o: /usr/include/SFML/System/Time.hpp
./screenShakeController.o: /usr/include/SFML/System/Err.hpp
./screenShakeController.o: /usr/include/SFML/System/FileInputStream.hpp
./screenShakeController.o: /usr/include/SFML/System/InputStream.hpp
./screenShakeController.o: /usr/include/SFML/System/NonCopyable.hpp
./screenShakeController.o: /usr/include/SFML/System/Lock.hpp
./screenShakeController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./screenShakeController.o: /usr/include/SFML/System/Mutex.hpp
./screenShakeController.o: /usr/include/SFML/System/Sleep.hpp
./screenShakeController.o: /usr/include/SFML/System/String.hpp
./screenShakeController.o: /usr/include/SFML/System/Utf.hpp
./screenShakeController.o: /usr/include/SFML/System/Utf.inl
./screenShakeController.o: /usr/include/SFML/System/String.inl
./screenShakeController.o: /usr/include/SFML/System/Thread.hpp
./screenShakeController.o: /usr/include/SFML/System/Thread.inl
./screenShakeController.o: /usr/include/SFML/System/ThreadLocal.hpp
./screenShakeController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./screenShakeController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./screenShakeController.o: /usr/include/SFML/System/Vector2.hpp
./screenShakeController.o: /usr/include/SFML/System/Vector2.inl
./screenShakeController.o: /usr/include/SFML/System/Vector3.hpp
./screenShakeController.o: /usr/include/SFML/System/Vector3.inl
./screenShakeController.o: /usr/include/SFML/Window/Context.hpp
./screenShakeController.o: /usr/include/SFML/Window/Export.hpp
./screenShakeController.o: /usr/include/SFML/Window/GlResource.hpp
./screenShakeController.o: /usr/include/SFML/Window/ContextSettings.hpp
./screenShakeController.o: /usr/include/SFML/Window/Event.hpp
./screenShakeController.o: /usr/include/SFML/Window/Joystick.hpp
./screenShakeController.o: /usr/include/SFML/Window/Keyboard.hpp
./screenShakeController.o: /usr/include/SFML/Window/Mouse.hpp
./screenShakeController.o: /usr/include/SFML/Window/Sensor.hpp
./screenShakeController.o: /usr/include/SFML/Window/Touch.hpp
./screenShakeController.o: /usr/include/SFML/Window/VideoMode.hpp
./screenShakeController.o: /usr/include/SFML/Window/Window.hpp
./screenShakeController.o: /usr/include/SFML/Window/WindowHandle.hpp
./screenShakeController.o: /usr/include/SFML/Window/WindowStyle.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Export.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Shape.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Drawable.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Transform.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Rect.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Rect.inl
./screenShakeController.o: /usr/include/SFML/Graphics/Transformable.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Vertex.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Color.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Font.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Glyph.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Texture.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Image.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/View.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Shader.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Sprite.hpp
./screenShakeController.o: /usr/include/SFML/Graphics/Text.hpp
./screenShakeController.o: tileController.hpp wall.hpp /usr/include/stdint.h
./screenShakeController.o: /usr/include/features.h /usr/include/stdc-predef.h
./screenShakeController.o: enemyController.hpp resourceHandler.hpp
./screenShakeController.o: ResourcePath.hpp turret.hpp /usr/include/stdio.h
./screenShakeController.o: /usr/include/libio.h /usr/include/_G_config.h
./screenShakeController.o: /usr/include/wchar.h fontController.hpp
./screenShakeController.o: effectsController.hpp turretFlashEffect.hpp
./screenShakeController.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./screenShakeController.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./screenShakeController.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./screenShakeController.o: Powerup.hpp RenderType.hpp enemyShot.hpp
./screenShakeController.o: dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp
./screenShakeController.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./screenShakeController.o: detailController.hpp Teleporter.hpp
./screenShakeController.o: detailParent.hpp treasureChest.hpp
./screenShakeController.o: inputController.hpp generalDetail.hpp
./screenShakeController.o: lampLight.hpp userInterface.hpp
./screenShakeController.o: easingTemplates.hpp damagedRobot.hpp rock.hpp
./screenShakeController.o: IntroDoor.hpp soundController.hpp
./screenShakeController.o: /usr/include/SFML/Audio.hpp
./screenShakeController.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./screenShakeController.o: /usr/include/SFML/Audio/Export.hpp
./screenShakeController.o: /usr/include/SFML/Audio/Listener.hpp
./screenShakeController.o: /usr/include/SFML/Audio/Music.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundStream.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundSource.hpp
./screenShakeController.o: /usr/include/SFML/Audio/AlResource.hpp
./screenShakeController.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./screenShakeController.o: /usr/include/SFML/Audio/Sound.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./screenShakeController.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./screenShakeController.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./turretFlashEffect.o: turretFlashEffect.hpp /usr/include/SFML/Graphics.hpp
./turretFlashEffect.o: /usr/include/SFML/Window.hpp
./turretFlashEffect.o: /usr/include/SFML/System.hpp
./turretFlashEffect.o: /usr/include/SFML/Config.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Clock.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Export.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Time.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Err.hpp
./turretFlashEffect.o: /usr/include/SFML/System/FileInputStream.hpp
./turretFlashEffect.o: /usr/include/SFML/System/InputStream.hpp
./turretFlashEffect.o: /usr/include/SFML/System/NonCopyable.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Lock.hpp
./turretFlashEffect.o: /usr/include/SFML/System/MemoryInputStream.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Mutex.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Sleep.hpp
./turretFlashEffect.o: /usr/include/SFML/System/String.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Utf.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Utf.inl
./turretFlashEffect.o: /usr/include/SFML/System/String.inl
./turretFlashEffect.o: /usr/include/SFML/System/Thread.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Thread.inl
./turretFlashEffect.o: /usr/include/SFML/System/ThreadLocal.hpp
./turretFlashEffect.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./turretFlashEffect.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./turretFlashEffect.o: /usr/include/SFML/System/Vector2.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Vector2.inl
./turretFlashEffect.o: /usr/include/SFML/System/Vector3.hpp
./turretFlashEffect.o: /usr/include/SFML/System/Vector3.inl
./turretFlashEffect.o: /usr/include/SFML/Window/Context.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Export.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/GlResource.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/ContextSettings.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Event.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Joystick.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Keyboard.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Mouse.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Sensor.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Touch.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/VideoMode.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/Window.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/WindowHandle.hpp
./turretFlashEffect.o: /usr/include/SFML/Window/WindowStyle.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/BlendMode.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Export.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/CircleShape.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Shape.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Drawable.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/RenderStates.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Transform.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Rect.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Rect.inl
./turretFlashEffect.o: /usr/include/SFML/Graphics/Transformable.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/VertexArray.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Vertex.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Color.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Font.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Glyph.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Texture.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Image.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/View.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Shader.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Sprite.hpp
./turretFlashEffect.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp
./turretFlashEffect.o: Effect.hpp Framework/framework.hpp
./turretFlashEffect.o: Framework/utilities.hpp rng.hpp
./backgroundHandler.o: backgroundHandler.hpp /usr/include/SFML/Graphics.hpp
./backgroundHandler.o: /usr/include/SFML/Window.hpp
./backgroundHandler.o: /usr/include/SFML/System.hpp
./backgroundHandler.o: /usr/include/SFML/Config.hpp
./backgroundHandler.o: /usr/include/SFML/System/Clock.hpp
./backgroundHandler.o: /usr/include/SFML/System/Export.hpp
./backgroundHandler.o: /usr/include/SFML/System/Time.hpp
./backgroundHandler.o: /usr/include/SFML/System/Err.hpp
./backgroundHandler.o: /usr/include/SFML/System/FileInputStream.hpp
./backgroundHandler.o: /usr/include/SFML/System/InputStream.hpp
./backgroundHandler.o: /usr/include/SFML/System/NonCopyable.hpp
./backgroundHandler.o: /usr/include/SFML/System/Lock.hpp
./backgroundHandler.o: /usr/include/SFML/System/MemoryInputStream.hpp
./backgroundHandler.o: /usr/include/SFML/System/Mutex.hpp
./backgroundHandler.o: /usr/include/SFML/System/Sleep.hpp
./backgroundHandler.o: /usr/include/SFML/System/String.hpp
./backgroundHandler.o: /usr/include/SFML/System/Utf.hpp
./backgroundHandler.o: /usr/include/SFML/System/Utf.inl
./backgroundHandler.o: /usr/include/SFML/System/String.inl
./backgroundHandler.o: /usr/include/SFML/System/Thread.hpp
./backgroundHandler.o: /usr/include/SFML/System/Thread.inl
./backgroundHandler.o: /usr/include/SFML/System/ThreadLocal.hpp
./backgroundHandler.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./backgroundHandler.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./backgroundHandler.o: /usr/include/SFML/System/Vector2.hpp
./backgroundHandler.o: /usr/include/SFML/System/Vector2.inl
./backgroundHandler.o: /usr/include/SFML/System/Vector3.hpp
./backgroundHandler.o: /usr/include/SFML/System/Vector3.inl
./backgroundHandler.o: /usr/include/SFML/Window/Context.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Export.hpp
./backgroundHandler.o: /usr/include/SFML/Window/GlResource.hpp
./backgroundHandler.o: /usr/include/SFML/Window/ContextSettings.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Event.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Joystick.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Keyboard.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Mouse.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Sensor.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Touch.hpp
./backgroundHandler.o: /usr/include/SFML/Window/VideoMode.hpp
./backgroundHandler.o: /usr/include/SFML/Window/Window.hpp
./backgroundHandler.o: /usr/include/SFML/Window/WindowHandle.hpp
./backgroundHandler.o: /usr/include/SFML/Window/WindowStyle.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/BlendMode.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Export.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/CircleShape.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Shape.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Drawable.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/RenderStates.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Transform.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Rect.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Rect.inl
./backgroundHandler.o: /usr/include/SFML/Graphics/Transformable.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/VertexArray.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Vertex.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Color.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Font.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Glyph.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Texture.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Image.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/View.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Shader.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Sprite.hpp
./backgroundHandler.o: /usr/include/SFML/Graphics/Text.hpp ResourcePath.hpp
./mappingFunctions.o: tileController.hpp /usr/include/SFML/Graphics.hpp
./mappingFunctions.o: /usr/include/SFML/Window.hpp
./mappingFunctions.o: /usr/include/SFML/System.hpp
./mappingFunctions.o: /usr/include/SFML/Config.hpp
./mappingFunctions.o: /usr/include/SFML/System/Clock.hpp
./mappingFunctions.o: /usr/include/SFML/System/Export.hpp
./mappingFunctions.o: /usr/include/SFML/System/Time.hpp
./mappingFunctions.o: /usr/include/SFML/System/Err.hpp
./mappingFunctions.o: /usr/include/SFML/System/FileInputStream.hpp
./mappingFunctions.o: /usr/include/SFML/System/InputStream.hpp
./mappingFunctions.o: /usr/include/SFML/System/NonCopyable.hpp
./mappingFunctions.o: /usr/include/SFML/System/Lock.hpp
./mappingFunctions.o: /usr/include/SFML/System/MemoryInputStream.hpp
./mappingFunctions.o: /usr/include/SFML/System/Mutex.hpp
./mappingFunctions.o: /usr/include/SFML/System/Sleep.hpp
./mappingFunctions.o: /usr/include/SFML/System/String.hpp
./mappingFunctions.o: /usr/include/SFML/System/Utf.hpp
./mappingFunctions.o: /usr/include/SFML/System/Utf.inl
./mappingFunctions.o: /usr/include/SFML/System/String.inl
./mappingFunctions.o: /usr/include/SFML/System/Thread.hpp
./mappingFunctions.o: /usr/include/SFML/System/Thread.inl
./mappingFunctions.o: /usr/include/SFML/System/ThreadLocal.hpp
./mappingFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./mappingFunctions.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./mappingFunctions.o: /usr/include/SFML/System/Vector2.hpp
./mappingFunctions.o: /usr/include/SFML/System/Vector2.inl
./mappingFunctions.o: /usr/include/SFML/System/Vector3.hpp
./mappingFunctions.o: /usr/include/SFML/System/Vector3.inl
./mappingFunctions.o: /usr/include/SFML/Window/Context.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Export.hpp
./mappingFunctions.o: /usr/include/SFML/Window/GlResource.hpp
./mappingFunctions.o: /usr/include/SFML/Window/ContextSettings.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Event.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Joystick.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Keyboard.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Mouse.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Sensor.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Touch.hpp
./mappingFunctions.o: /usr/include/SFML/Window/VideoMode.hpp
./mappingFunctions.o: /usr/include/SFML/Window/Window.hpp
./mappingFunctions.o: /usr/include/SFML/Window/WindowHandle.hpp
./mappingFunctions.o: /usr/include/SFML/Window/WindowStyle.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/BlendMode.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Export.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/CircleShape.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Shape.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Drawable.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/RenderStates.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Transform.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Rect.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Rect.inl
./mappingFunctions.o: /usr/include/SFML/Graphics/Transformable.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/VertexArray.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Vertex.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Color.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Font.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Glyph.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Texture.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Image.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/View.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Shader.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Sprite.hpp
./mappingFunctions.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp
./mappingFunctions.o: /usr/include/stdint.h /usr/include/features.h
./mappingFunctions.o: /usr/include/stdc-predef.h enemyController.hpp
./mappingFunctions.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./mappingFunctions.o: /usr/include/stdio.h /usr/include/libio.h
./mappingFunctions.o: /usr/include/_G_config.h /usr/include/wchar.h
./mappingFunctions.o: fontController.hpp effectsController.hpp
./mappingFunctions.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./mappingFunctions.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./mappingFunctions.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./mappingFunctions.o: smallExplosion.hpp Powerup.hpp RenderType.hpp
./mappingFunctions.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp
./mappingFunctions.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp
./mappingFunctions.o: coordinate.hpp mappingFunctions.hpp
./enemyPlacementFn.o: /usr/include/stdio.h /usr/include/features.h
./enemyPlacementFn.o: /usr/include/stdc-predef.h /usr/include/libio.h
./enemyPlacementFn.o: /usr/include/_G_config.h /usr/include/wchar.h
./enemyPlacementFn.o: enemyPlacementFn.hpp scene.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window.hpp
./enemyPlacementFn.o: /usr/include/SFML/System.hpp
./enemyPlacementFn.o: /usr/include/SFML/Config.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Clock.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Export.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Time.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Err.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/FileInputStream.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/InputStream.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/NonCopyable.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Lock.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Mutex.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Sleep.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/String.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Utf.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Utf.inl
./enemyPlacementFn.o: /usr/include/SFML/System/String.inl
./enemyPlacementFn.o: /usr/include/SFML/System/Thread.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Thread.inl
./enemyPlacementFn.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemyPlacementFn.o: /usr/include/SFML/System/Vector2.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Vector2.inl
./enemyPlacementFn.o: /usr/include/SFML/System/Vector3.hpp
./enemyPlacementFn.o: /usr/include/SFML/System/Vector3.inl
./enemyPlacementFn.o: /usr/include/SFML/Window/Context.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Export.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/GlResource.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Event.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Joystick.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Keyboard.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Mouse.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Sensor.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Touch.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/VideoMode.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/Window.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemyPlacementFn.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Export.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Shape.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Transform.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Rect.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Rect.inl
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Color.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Font.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Texture.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Image.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/View.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Shader.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemyPlacementFn.o: /usr/include/SFML/Graphics/Text.hpp player.hpp
./enemyPlacementFn.o: tileController.hpp wall.hpp /usr/include/stdint.h
./enemyPlacementFn.o: enemyController.hpp resourceHandler.hpp
./enemyPlacementFn.o: ResourcePath.hpp turret.hpp fontController.hpp
./enemyPlacementFn.o: effectsController.hpp turretFlashEffect.hpp
./enemyPlacementFn.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./enemyPlacementFn.o: Framework/utilities.hpp rng.hpp bulletType1.hpp
./enemyPlacementFn.o: shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./enemyPlacementFn.o: Powerup.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./enemyPlacementFn.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp
./enemyPlacementFn.o: critter.hpp aStar.hpp coordinate.hpp
./enemyPlacementFn.o: detailController.hpp Teleporter.hpp detailParent.hpp
./enemyPlacementFn.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./enemyPlacementFn.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./enemyPlacementFn.o: damagedRobot.hpp rock.hpp IntroDoor.hpp
./enemyPlacementFn.o: soundController.hpp /usr/include/SFML/Audio.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/Export.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/Listener.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/Music.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundStream.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundSource.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/AlResource.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/Sound.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./enemyPlacementFn.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./enemyPlacementFn.o: backgroundHandler.hpp screenShakeController.hpp
./enemyPlacementFn.o: enemyCreationFunctions.hpp
./soundController.o: soundController.hpp /usr/include/SFML/Audio.hpp
./soundController.o: /usr/include/SFML/System.hpp
./soundController.o: /usr/include/SFML/Config.hpp
./soundController.o: /usr/include/SFML/System/Clock.hpp
./soundController.o: /usr/include/SFML/System/Export.hpp
./soundController.o: /usr/include/SFML/System/Time.hpp
./soundController.o: /usr/include/SFML/System/Err.hpp
./soundController.o: /usr/include/SFML/System/FileInputStream.hpp
./soundController.o: /usr/include/SFML/System/InputStream.hpp
./soundController.o: /usr/include/SFML/System/NonCopyable.hpp
./soundController.o: /usr/include/SFML/System/Lock.hpp
./soundController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./soundController.o: /usr/include/SFML/System/Mutex.hpp
./soundController.o: /usr/include/SFML/System/Sleep.hpp
./soundController.o: /usr/include/SFML/System/String.hpp
./soundController.o: /usr/include/SFML/System/Utf.hpp
./soundController.o: /usr/include/SFML/System/Utf.inl
./soundController.o: /usr/include/SFML/System/String.inl
./soundController.o: /usr/include/SFML/System/Thread.hpp
./soundController.o: /usr/include/SFML/System/Thread.inl
./soundController.o: /usr/include/SFML/System/ThreadLocal.hpp
./soundController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./soundController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./soundController.o: /usr/include/SFML/System/Vector2.hpp
./soundController.o: /usr/include/SFML/System/Vector2.inl
./soundController.o: /usr/include/SFML/System/Vector3.hpp
./soundController.o: /usr/include/SFML/System/Vector3.inl
./soundController.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./soundController.o: /usr/include/SFML/Audio/Export.hpp
./soundController.o: /usr/include/SFML/Audio/Listener.hpp
./soundController.o: /usr/include/SFML/Audio/Music.hpp
./soundController.o: /usr/include/SFML/Audio/SoundStream.hpp
./soundController.o: /usr/include/SFML/Audio/SoundSource.hpp
./soundController.o: /usr/include/SFML/Audio/AlResource.hpp
./soundController.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./soundController.o: /usr/include/SFML/Audio/Sound.hpp
./soundController.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./soundController.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./soundController.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./soundController.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./soundController.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./soundController.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./soundController.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./soundController.o: ResourcePath.hpp /usr/include/SFML/Graphics.hpp
./soundController.o: /usr/include/SFML/Window.hpp
./soundController.o: /usr/include/SFML/Window/Context.hpp
./soundController.o: /usr/include/SFML/Window/Export.hpp
./soundController.o: /usr/include/SFML/Window/GlResource.hpp
./soundController.o: /usr/include/SFML/Window/ContextSettings.hpp
./soundController.o: /usr/include/SFML/Window/Event.hpp
./soundController.o: /usr/include/SFML/Window/Joystick.hpp
./soundController.o: /usr/include/SFML/Window/Keyboard.hpp
./soundController.o: /usr/include/SFML/Window/Mouse.hpp
./soundController.o: /usr/include/SFML/Window/Sensor.hpp
./soundController.o: /usr/include/SFML/Window/Touch.hpp
./soundController.o: /usr/include/SFML/Window/VideoMode.hpp
./soundController.o: /usr/include/SFML/Window/Window.hpp
./soundController.o: /usr/include/SFML/Window/WindowHandle.hpp
./soundController.o: /usr/include/SFML/Window/WindowStyle.hpp
./soundController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./soundController.o: /usr/include/SFML/Graphics/Export.hpp
./soundController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./soundController.o: /usr/include/SFML/Graphics/Shape.hpp
./soundController.o: /usr/include/SFML/Graphics/Drawable.hpp
./soundController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./soundController.o: /usr/include/SFML/Graphics/Transform.hpp
./soundController.o: /usr/include/SFML/Graphics/Rect.hpp
./soundController.o: /usr/include/SFML/Graphics/Rect.inl
./soundController.o: /usr/include/SFML/Graphics/Transformable.hpp
./soundController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./soundController.o: /usr/include/SFML/Graphics/Vertex.hpp
./soundController.o: /usr/include/SFML/Graphics/Color.hpp
./soundController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./soundController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./soundController.o: /usr/include/SFML/Graphics/Font.hpp
./soundController.o: /usr/include/SFML/Graphics/Glyph.hpp
./soundController.o: /usr/include/SFML/Graphics/Texture.hpp
./soundController.o: /usr/include/SFML/Graphics/Image.hpp
./soundController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./soundController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./soundController.o: /usr/include/SFML/Graphics/View.hpp
./soundController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./soundController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./soundController.o: /usr/include/SFML/Graphics/Shader.hpp
./soundController.o: /usr/include/SFML/Graphics/Sprite.hpp
./soundController.o: /usr/include/SFML/Graphics/Text.hpp
./resourceHandler.o: resourceHandler.hpp /usr/include/SFML/Graphics.hpp
./resourceHandler.o: /usr/include/SFML/Window.hpp
./resourceHandler.o: /usr/include/SFML/System.hpp
./resourceHandler.o: /usr/include/SFML/Config.hpp
./resourceHandler.o: /usr/include/SFML/System/Clock.hpp
./resourceHandler.o: /usr/include/SFML/System/Export.hpp
./resourceHandler.o: /usr/include/SFML/System/Time.hpp
./resourceHandler.o: /usr/include/SFML/System/Err.hpp
./resourceHandler.o: /usr/include/SFML/System/FileInputStream.hpp
./resourceHandler.o: /usr/include/SFML/System/InputStream.hpp
./resourceHandler.o: /usr/include/SFML/System/NonCopyable.hpp
./resourceHandler.o: /usr/include/SFML/System/Lock.hpp
./resourceHandler.o: /usr/include/SFML/System/MemoryInputStream.hpp
./resourceHandler.o: /usr/include/SFML/System/Mutex.hpp
./resourceHandler.o: /usr/include/SFML/System/Sleep.hpp
./resourceHandler.o: /usr/include/SFML/System/String.hpp
./resourceHandler.o: /usr/include/SFML/System/Utf.hpp
./resourceHandler.o: /usr/include/SFML/System/Utf.inl
./resourceHandler.o: /usr/include/SFML/System/String.inl
./resourceHandler.o: /usr/include/SFML/System/Thread.hpp
./resourceHandler.o: /usr/include/SFML/System/Thread.inl
./resourceHandler.o: /usr/include/SFML/System/ThreadLocal.hpp
./resourceHandler.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./resourceHandler.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./resourceHandler.o: /usr/include/SFML/System/Vector2.hpp
./resourceHandler.o: /usr/include/SFML/System/Vector2.inl
./resourceHandler.o: /usr/include/SFML/System/Vector3.hpp
./resourceHandler.o: /usr/include/SFML/System/Vector3.inl
./resourceHandler.o: /usr/include/SFML/Window/Context.hpp
./resourceHandler.o: /usr/include/SFML/Window/Export.hpp
./resourceHandler.o: /usr/include/SFML/Window/GlResource.hpp
./resourceHandler.o: /usr/include/SFML/Window/ContextSettings.hpp
./resourceHandler.o: /usr/include/SFML/Window/Event.hpp
./resourceHandler.o: /usr/include/SFML/Window/Joystick.hpp
./resourceHandler.o: /usr/include/SFML/Window/Keyboard.hpp
./resourceHandler.o: /usr/include/SFML/Window/Mouse.hpp
./resourceHandler.o: /usr/include/SFML/Window/Sensor.hpp
./resourceHandler.o: /usr/include/SFML/Window/Touch.hpp
./resourceHandler.o: /usr/include/SFML/Window/VideoMode.hpp
./resourceHandler.o: /usr/include/SFML/Window/Window.hpp
./resourceHandler.o: /usr/include/SFML/Window/WindowHandle.hpp
./resourceHandler.o: /usr/include/SFML/Window/WindowStyle.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/BlendMode.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Export.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/CircleShape.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Shape.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Drawable.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/RenderStates.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Transform.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Rect.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Rect.inl
./resourceHandler.o: /usr/include/SFML/Graphics/Transformable.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/VertexArray.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Vertex.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Color.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Font.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Glyph.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Texture.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Image.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/View.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Shader.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Sprite.hpp
./resourceHandler.o: /usr/include/SFML/Graphics/Text.hpp ResourcePath.hpp
./inputController.o: inputController.hpp /usr/include/SFML/Graphics.hpp
./inputController.o: /usr/include/SFML/Window.hpp
./inputController.o: /usr/include/SFML/System.hpp
./inputController.o: /usr/include/SFML/Config.hpp
./inputController.o: /usr/include/SFML/System/Clock.hpp
./inputController.o: /usr/include/SFML/System/Export.hpp
./inputController.o: /usr/include/SFML/System/Time.hpp
./inputController.o: /usr/include/SFML/System/Err.hpp
./inputController.o: /usr/include/SFML/System/FileInputStream.hpp
./inputController.o: /usr/include/SFML/System/InputStream.hpp
./inputController.o: /usr/include/SFML/System/NonCopyable.hpp
./inputController.o: /usr/include/SFML/System/Lock.hpp
./inputController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./inputController.o: /usr/include/SFML/System/Mutex.hpp
./inputController.o: /usr/include/SFML/System/Sleep.hpp
./inputController.o: /usr/include/SFML/System/String.hpp
./inputController.o: /usr/include/SFML/System/Utf.hpp
./inputController.o: /usr/include/SFML/System/Utf.inl
./inputController.o: /usr/include/SFML/System/String.inl
./inputController.o: /usr/include/SFML/System/Thread.hpp
./inputController.o: /usr/include/SFML/System/Thread.inl
./inputController.o: /usr/include/SFML/System/ThreadLocal.hpp
./inputController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./inputController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./inputController.o: /usr/include/SFML/System/Vector2.hpp
./inputController.o: /usr/include/SFML/System/Vector2.inl
./inputController.o: /usr/include/SFML/System/Vector3.hpp
./inputController.o: /usr/include/SFML/System/Vector3.inl
./inputController.o: /usr/include/SFML/Window/Context.hpp
./inputController.o: /usr/include/SFML/Window/Export.hpp
./inputController.o: /usr/include/SFML/Window/GlResource.hpp
./inputController.o: /usr/include/SFML/Window/ContextSettings.hpp
./inputController.o: /usr/include/SFML/Window/Event.hpp
./inputController.o: /usr/include/SFML/Window/Joystick.hpp
./inputController.o: /usr/include/SFML/Window/Keyboard.hpp
./inputController.o: /usr/include/SFML/Window/Mouse.hpp
./inputController.o: /usr/include/SFML/Window/Sensor.hpp
./inputController.o: /usr/include/SFML/Window/Touch.hpp
./inputController.o: /usr/include/SFML/Window/VideoMode.hpp
./inputController.o: /usr/include/SFML/Window/Window.hpp
./inputController.o: /usr/include/SFML/Window/WindowHandle.hpp
./inputController.o: /usr/include/SFML/Window/WindowStyle.hpp
./inputController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./inputController.o: /usr/include/SFML/Graphics/Export.hpp
./inputController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./inputController.o: /usr/include/SFML/Graphics/Shape.hpp
./inputController.o: /usr/include/SFML/Graphics/Drawable.hpp
./inputController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./inputController.o: /usr/include/SFML/Graphics/Transform.hpp
./inputController.o: /usr/include/SFML/Graphics/Rect.hpp
./inputController.o: /usr/include/SFML/Graphics/Rect.inl
./inputController.o: /usr/include/SFML/Graphics/Transformable.hpp
./inputController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./inputController.o: /usr/include/SFML/Graphics/Vertex.hpp
./inputController.o: /usr/include/SFML/Graphics/Color.hpp
./inputController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./inputController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./inputController.o: /usr/include/SFML/Graphics/Font.hpp
./inputController.o: /usr/include/SFML/Graphics/Glyph.hpp
./inputController.o: /usr/include/SFML/Graphics/Texture.hpp
./inputController.o: /usr/include/SFML/Graphics/Image.hpp
./inputController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./inputController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./inputController.o: /usr/include/SFML/Graphics/View.hpp
./inputController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./inputController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./inputController.o: /usr/include/SFML/Graphics/Shader.hpp
./inputController.o: /usr/include/SFML/Graphics/Sprite.hpp
./inputController.o: /usr/include/SFML/Graphics/Text.hpp
./enemyController.o: enemyController.hpp resourceHandler.hpp
./enemyController.o: /usr/include/SFML/Graphics.hpp
./enemyController.o: /usr/include/SFML/Window.hpp
./enemyController.o: /usr/include/SFML/System.hpp
./enemyController.o: /usr/include/SFML/Config.hpp
./enemyController.o: /usr/include/SFML/System/Clock.hpp
./enemyController.o: /usr/include/SFML/System/Export.hpp
./enemyController.o: /usr/include/SFML/System/Time.hpp
./enemyController.o: /usr/include/SFML/System/Err.hpp
./enemyController.o: /usr/include/SFML/System/FileInputStream.hpp
./enemyController.o: /usr/include/SFML/System/InputStream.hpp
./enemyController.o: /usr/include/SFML/System/NonCopyable.hpp
./enemyController.o: /usr/include/SFML/System/Lock.hpp
./enemyController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemyController.o: /usr/include/SFML/System/Mutex.hpp
./enemyController.o: /usr/include/SFML/System/Sleep.hpp
./enemyController.o: /usr/include/SFML/System/String.hpp
./enemyController.o: /usr/include/SFML/System/Utf.hpp
./enemyController.o: /usr/include/SFML/System/Utf.inl
./enemyController.o: /usr/include/SFML/System/String.inl
./enemyController.o: /usr/include/SFML/System/Thread.hpp
./enemyController.o: /usr/include/SFML/System/Thread.inl
./enemyController.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemyController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemyController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemyController.o: /usr/include/SFML/System/Vector2.hpp
./enemyController.o: /usr/include/SFML/System/Vector2.inl
./enemyController.o: /usr/include/SFML/System/Vector3.hpp
./enemyController.o: /usr/include/SFML/System/Vector3.inl
./enemyController.o: /usr/include/SFML/Window/Context.hpp
./enemyController.o: /usr/include/SFML/Window/Export.hpp
./enemyController.o: /usr/include/SFML/Window/GlResource.hpp
./enemyController.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemyController.o: /usr/include/SFML/Window/Event.hpp
./enemyController.o: /usr/include/SFML/Window/Joystick.hpp
./enemyController.o: /usr/include/SFML/Window/Keyboard.hpp
./enemyController.o: /usr/include/SFML/Window/Mouse.hpp
./enemyController.o: /usr/include/SFML/Window/Sensor.hpp
./enemyController.o: /usr/include/SFML/Window/Touch.hpp
./enemyController.o: /usr/include/SFML/Window/VideoMode.hpp
./enemyController.o: /usr/include/SFML/Window/Window.hpp
./enemyController.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemyController.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemyController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemyController.o: /usr/include/SFML/Graphics/Export.hpp
./enemyController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemyController.o: /usr/include/SFML/Graphics/Shape.hpp
./enemyController.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemyController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemyController.o: /usr/include/SFML/Graphics/Transform.hpp
./enemyController.o: /usr/include/SFML/Graphics/Rect.hpp
./enemyController.o: /usr/include/SFML/Graphics/Rect.inl
./enemyController.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemyController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemyController.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemyController.o: /usr/include/SFML/Graphics/Color.hpp
./enemyController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemyController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemyController.o: /usr/include/SFML/Graphics/Font.hpp
./enemyController.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemyController.o: /usr/include/SFML/Graphics/Texture.hpp
./enemyController.o: /usr/include/SFML/Graphics/Image.hpp
./enemyController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemyController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemyController.o: /usr/include/SFML/Graphics/View.hpp
./enemyController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemyController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemyController.o: /usr/include/SFML/Graphics/Shader.hpp
./enemyController.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemyController.o: /usr/include/SFML/Graphics/Text.hpp ResourcePath.hpp
./enemyController.o: turret.hpp /usr/include/stdio.h /usr/include/features.h
./enemyController.o: /usr/include/stdc-predef.h /usr/include/libio.h
./enemyController.o: /usr/include/_G_config.h /usr/include/wchar.h
./enemyController.o: fontController.hpp effectsController.hpp
./enemyController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./enemyController.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./enemyController.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./enemyController.o: smallExplosion.hpp Powerup.hpp RenderType.hpp
./enemyController.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp
./enemyController.o: wall.hpp /usr/include/stdint.h enemy.hpp dasher.hpp
./enemyController.o: critter.hpp aStar.hpp tileController.hpp coordinate.hpp
./enemyController.o: detailController.hpp Teleporter.hpp detailParent.hpp
./enemyController.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./enemyController.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./enemyController.o: damagedRobot.hpp rock.hpp IntroDoor.hpp
./enemyController.o: screenShakeController.hpp player.hpp soundController.hpp
./enemyController.o: /usr/include/SFML/Audio.hpp
./enemyController.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./enemyController.o: /usr/include/SFML/Audio/Export.hpp
./enemyController.o: /usr/include/SFML/Audio/Listener.hpp
./enemyController.o: /usr/include/SFML/Audio/Music.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundStream.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundSource.hpp
./enemyController.o: /usr/include/SFML/Audio/AlResource.hpp
./enemyController.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./enemyController.o: /usr/include/SFML/Audio/Sound.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./enemyController.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./enemyController.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./tileController.o: tileController.hpp /usr/include/SFML/Graphics.hpp
./tileController.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./tileController.o: /usr/include/SFML/Config.hpp
./tileController.o: /usr/include/SFML/System/Clock.hpp
./tileController.o: /usr/include/SFML/System/Export.hpp
./tileController.o: /usr/include/SFML/System/Time.hpp
./tileController.o: /usr/include/SFML/System/Err.hpp
./tileController.o: /usr/include/SFML/System/FileInputStream.hpp
./tileController.o: /usr/include/SFML/System/InputStream.hpp
./tileController.o: /usr/include/SFML/System/NonCopyable.hpp
./tileController.o: /usr/include/SFML/System/Lock.hpp
./tileController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./tileController.o: /usr/include/SFML/System/Mutex.hpp
./tileController.o: /usr/include/SFML/System/Sleep.hpp
./tileController.o: /usr/include/SFML/System/String.hpp
./tileController.o: /usr/include/SFML/System/Utf.hpp
./tileController.o: /usr/include/SFML/System/Utf.inl
./tileController.o: /usr/include/SFML/System/String.inl
./tileController.o: /usr/include/SFML/System/Thread.hpp
./tileController.o: /usr/include/SFML/System/Thread.inl
./tileController.o: /usr/include/SFML/System/ThreadLocal.hpp
./tileController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./tileController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./tileController.o: /usr/include/SFML/System/Vector2.hpp
./tileController.o: /usr/include/SFML/System/Vector2.inl
./tileController.o: /usr/include/SFML/System/Vector3.hpp
./tileController.o: /usr/include/SFML/System/Vector3.inl
./tileController.o: /usr/include/SFML/Window/Context.hpp
./tileController.o: /usr/include/SFML/Window/Export.hpp
./tileController.o: /usr/include/SFML/Window/GlResource.hpp
./tileController.o: /usr/include/SFML/Window/ContextSettings.hpp
./tileController.o: /usr/include/SFML/Window/Event.hpp
./tileController.o: /usr/include/SFML/Window/Joystick.hpp
./tileController.o: /usr/include/SFML/Window/Keyboard.hpp
./tileController.o: /usr/include/SFML/Window/Mouse.hpp
./tileController.o: /usr/include/SFML/Window/Sensor.hpp
./tileController.o: /usr/include/SFML/Window/Touch.hpp
./tileController.o: /usr/include/SFML/Window/VideoMode.hpp
./tileController.o: /usr/include/SFML/Window/Window.hpp
./tileController.o: /usr/include/SFML/Window/WindowHandle.hpp
./tileController.o: /usr/include/SFML/Window/WindowStyle.hpp
./tileController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./tileController.o: /usr/include/SFML/Graphics/Export.hpp
./tileController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./tileController.o: /usr/include/SFML/Graphics/Shape.hpp
./tileController.o: /usr/include/SFML/Graphics/Drawable.hpp
./tileController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./tileController.o: /usr/include/SFML/Graphics/Transform.hpp
./tileController.o: /usr/include/SFML/Graphics/Rect.hpp
./tileController.o: /usr/include/SFML/Graphics/Rect.inl
./tileController.o: /usr/include/SFML/Graphics/Transformable.hpp
./tileController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./tileController.o: /usr/include/SFML/Graphics/Vertex.hpp
./tileController.o: /usr/include/SFML/Graphics/Color.hpp
./tileController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./tileController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./tileController.o: /usr/include/SFML/Graphics/Font.hpp
./tileController.o: /usr/include/SFML/Graphics/Glyph.hpp
./tileController.o: /usr/include/SFML/Graphics/Texture.hpp
./tileController.o: /usr/include/SFML/Graphics/Image.hpp
./tileController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./tileController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./tileController.o: /usr/include/SFML/Graphics/View.hpp
./tileController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./tileController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./tileController.o: /usr/include/SFML/Graphics/Shader.hpp
./tileController.o: /usr/include/SFML/Graphics/Sprite.hpp
./tileController.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp
./tileController.o: /usr/include/stdint.h /usr/include/features.h
./tileController.o: /usr/include/stdc-predef.h enemyController.hpp
./tileController.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./tileController.o: /usr/include/stdio.h /usr/include/libio.h
./tileController.o: /usr/include/_G_config.h /usr/include/wchar.h
./tileController.o: fontController.hpp effectsController.hpp
./tileController.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./tileController.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./tileController.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./tileController.o: smallExplosion.hpp Powerup.hpp RenderType.hpp
./tileController.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp
./tileController.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./tileController.o: mappingFunctions.hpp initMapVectors.hpp drawPixels.hpp
./smallExplosion.o: smallExplosion.hpp /usr/include/SFML/Graphics.hpp
./smallExplosion.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./smallExplosion.o: /usr/include/SFML/Config.hpp
./smallExplosion.o: /usr/include/SFML/System/Clock.hpp
./smallExplosion.o: /usr/include/SFML/System/Export.hpp
./smallExplosion.o: /usr/include/SFML/System/Time.hpp
./smallExplosion.o: /usr/include/SFML/System/Err.hpp
./smallExplosion.o: /usr/include/SFML/System/FileInputStream.hpp
./smallExplosion.o: /usr/include/SFML/System/InputStream.hpp
./smallExplosion.o: /usr/include/SFML/System/NonCopyable.hpp
./smallExplosion.o: /usr/include/SFML/System/Lock.hpp
./smallExplosion.o: /usr/include/SFML/System/MemoryInputStream.hpp
./smallExplosion.o: /usr/include/SFML/System/Mutex.hpp
./smallExplosion.o: /usr/include/SFML/System/Sleep.hpp
./smallExplosion.o: /usr/include/SFML/System/String.hpp
./smallExplosion.o: /usr/include/SFML/System/Utf.hpp
./smallExplosion.o: /usr/include/SFML/System/Utf.inl
./smallExplosion.o: /usr/include/SFML/System/String.inl
./smallExplosion.o: /usr/include/SFML/System/Thread.hpp
./smallExplosion.o: /usr/include/SFML/System/Thread.inl
./smallExplosion.o: /usr/include/SFML/System/ThreadLocal.hpp
./smallExplosion.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./smallExplosion.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./smallExplosion.o: /usr/include/SFML/System/Vector2.hpp
./smallExplosion.o: /usr/include/SFML/System/Vector2.inl
./smallExplosion.o: /usr/include/SFML/System/Vector3.hpp
./smallExplosion.o: /usr/include/SFML/System/Vector3.inl
./smallExplosion.o: /usr/include/SFML/Window/Context.hpp
./smallExplosion.o: /usr/include/SFML/Window/Export.hpp
./smallExplosion.o: /usr/include/SFML/Window/GlResource.hpp
./smallExplosion.o: /usr/include/SFML/Window/ContextSettings.hpp
./smallExplosion.o: /usr/include/SFML/Window/Event.hpp
./smallExplosion.o: /usr/include/SFML/Window/Joystick.hpp
./smallExplosion.o: /usr/include/SFML/Window/Keyboard.hpp
./smallExplosion.o: /usr/include/SFML/Window/Mouse.hpp
./smallExplosion.o: /usr/include/SFML/Window/Sensor.hpp
./smallExplosion.o: /usr/include/SFML/Window/Touch.hpp
./smallExplosion.o: /usr/include/SFML/Window/VideoMode.hpp
./smallExplosion.o: /usr/include/SFML/Window/Window.hpp
./smallExplosion.o: /usr/include/SFML/Window/WindowHandle.hpp
./smallExplosion.o: /usr/include/SFML/Window/WindowStyle.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/BlendMode.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Export.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/CircleShape.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Shape.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Drawable.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/RenderStates.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Transform.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Rect.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Rect.inl
./smallExplosion.o: /usr/include/SFML/Graphics/Transformable.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/VertexArray.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Vertex.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Color.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Font.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Glyph.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Texture.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Image.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/View.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Shader.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Sprite.hpp
./smallExplosion.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp
./smallExplosion.o: Effect.hpp Framework/framework.hpp
./smallExplosion.o: Framework/utilities.hpp
./initMapVectors.o: initMapVectors.hpp /usr/include/SFML/Graphics.hpp
./initMapVectors.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./initMapVectors.o: /usr/include/SFML/Config.hpp
./initMapVectors.o: /usr/include/SFML/System/Clock.hpp
./initMapVectors.o: /usr/include/SFML/System/Export.hpp
./initMapVectors.o: /usr/include/SFML/System/Time.hpp
./initMapVectors.o: /usr/include/SFML/System/Err.hpp
./initMapVectors.o: /usr/include/SFML/System/FileInputStream.hpp
./initMapVectors.o: /usr/include/SFML/System/InputStream.hpp
./initMapVectors.o: /usr/include/SFML/System/NonCopyable.hpp
./initMapVectors.o: /usr/include/SFML/System/Lock.hpp
./initMapVectors.o: /usr/include/SFML/System/MemoryInputStream.hpp
./initMapVectors.o: /usr/include/SFML/System/Mutex.hpp
./initMapVectors.o: /usr/include/SFML/System/Sleep.hpp
./initMapVectors.o: /usr/include/SFML/System/String.hpp
./initMapVectors.o: /usr/include/SFML/System/Utf.hpp
./initMapVectors.o: /usr/include/SFML/System/Utf.inl
./initMapVectors.o: /usr/include/SFML/System/String.inl
./initMapVectors.o: /usr/include/SFML/System/Thread.hpp
./initMapVectors.o: /usr/include/SFML/System/Thread.inl
./initMapVectors.o: /usr/include/SFML/System/ThreadLocal.hpp
./initMapVectors.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./initMapVectors.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./initMapVectors.o: /usr/include/SFML/System/Vector2.hpp
./initMapVectors.o: /usr/include/SFML/System/Vector2.inl
./initMapVectors.o: /usr/include/SFML/System/Vector3.hpp
./initMapVectors.o: /usr/include/SFML/System/Vector3.inl
./initMapVectors.o: /usr/include/SFML/Window/Context.hpp
./initMapVectors.o: /usr/include/SFML/Window/Export.hpp
./initMapVectors.o: /usr/include/SFML/Window/GlResource.hpp
./initMapVectors.o: /usr/include/SFML/Window/ContextSettings.hpp
./initMapVectors.o: /usr/include/SFML/Window/Event.hpp
./initMapVectors.o: /usr/include/SFML/Window/Joystick.hpp
./initMapVectors.o: /usr/include/SFML/Window/Keyboard.hpp
./initMapVectors.o: /usr/include/SFML/Window/Mouse.hpp
./initMapVectors.o: /usr/include/SFML/Window/Sensor.hpp
./initMapVectors.o: /usr/include/SFML/Window/Touch.hpp
./initMapVectors.o: /usr/include/SFML/Window/VideoMode.hpp
./initMapVectors.o: /usr/include/SFML/Window/Window.hpp
./initMapVectors.o: /usr/include/SFML/Window/WindowHandle.hpp
./initMapVectors.o: /usr/include/SFML/Window/WindowStyle.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/BlendMode.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Export.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/CircleShape.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Shape.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Drawable.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/RenderStates.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Transform.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Rect.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Rect.inl
./initMapVectors.o: /usr/include/SFML/Graphics/Transformable.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/VertexArray.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Vertex.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Color.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Font.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Glyph.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Texture.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Image.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/View.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Shader.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Sprite.hpp
./initMapVectors.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp
./initMapVectors.o: /usr/include/stdint.h /usr/include/features.h
./initMapVectors.o: /usr/include/stdc-predef.h coordinate.hpp
./initMapVectors.o: tileController.hpp enemyController.hpp
./initMapVectors.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./initMapVectors.o: /usr/include/stdio.h /usr/include/libio.h
./initMapVectors.o: /usr/include/_G_config.h /usr/include/wchar.h
./initMapVectors.o: fontController.hpp effectsController.hpp
./initMapVectors.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./initMapVectors.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./initMapVectors.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./initMapVectors.o: smallExplosion.hpp Powerup.hpp RenderType.hpp
./initMapVectors.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp
./initMapVectors.o: enemy.hpp dasher.hpp critter.hpp aStar.hpp
./fontController.o: fontController.hpp /usr/include/SFML/Graphics.hpp
./fontController.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./fontController.o: /usr/include/SFML/Config.hpp
./fontController.o: /usr/include/SFML/System/Clock.hpp
./fontController.o: /usr/include/SFML/System/Export.hpp
./fontController.o: /usr/include/SFML/System/Time.hpp
./fontController.o: /usr/include/SFML/System/Err.hpp
./fontController.o: /usr/include/SFML/System/FileInputStream.hpp
./fontController.o: /usr/include/SFML/System/InputStream.hpp
./fontController.o: /usr/include/SFML/System/NonCopyable.hpp
./fontController.o: /usr/include/SFML/System/Lock.hpp
./fontController.o: /usr/include/SFML/System/MemoryInputStream.hpp
./fontController.o: /usr/include/SFML/System/Mutex.hpp
./fontController.o: /usr/include/SFML/System/Sleep.hpp
./fontController.o: /usr/include/SFML/System/String.hpp
./fontController.o: /usr/include/SFML/System/Utf.hpp
./fontController.o: /usr/include/SFML/System/Utf.inl
./fontController.o: /usr/include/SFML/System/String.inl
./fontController.o: /usr/include/SFML/System/Thread.hpp
./fontController.o: /usr/include/SFML/System/Thread.inl
./fontController.o: /usr/include/SFML/System/ThreadLocal.hpp
./fontController.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./fontController.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./fontController.o: /usr/include/SFML/System/Vector2.hpp
./fontController.o: /usr/include/SFML/System/Vector2.inl
./fontController.o: /usr/include/SFML/System/Vector3.hpp
./fontController.o: /usr/include/SFML/System/Vector3.inl
./fontController.o: /usr/include/SFML/Window/Context.hpp
./fontController.o: /usr/include/SFML/Window/Export.hpp
./fontController.o: /usr/include/SFML/Window/GlResource.hpp
./fontController.o: /usr/include/SFML/Window/ContextSettings.hpp
./fontController.o: /usr/include/SFML/Window/Event.hpp
./fontController.o: /usr/include/SFML/Window/Joystick.hpp
./fontController.o: /usr/include/SFML/Window/Keyboard.hpp
./fontController.o: /usr/include/SFML/Window/Mouse.hpp
./fontController.o: /usr/include/SFML/Window/Sensor.hpp
./fontController.o: /usr/include/SFML/Window/Touch.hpp
./fontController.o: /usr/include/SFML/Window/VideoMode.hpp
./fontController.o: /usr/include/SFML/Window/Window.hpp
./fontController.o: /usr/include/SFML/Window/WindowHandle.hpp
./fontController.o: /usr/include/SFML/Window/WindowStyle.hpp
./fontController.o: /usr/include/SFML/Graphics/BlendMode.hpp
./fontController.o: /usr/include/SFML/Graphics/Export.hpp
./fontController.o: /usr/include/SFML/Graphics/CircleShape.hpp
./fontController.o: /usr/include/SFML/Graphics/Shape.hpp
./fontController.o: /usr/include/SFML/Graphics/Drawable.hpp
./fontController.o: /usr/include/SFML/Graphics/RenderStates.hpp
./fontController.o: /usr/include/SFML/Graphics/Transform.hpp
./fontController.o: /usr/include/SFML/Graphics/Rect.hpp
./fontController.o: /usr/include/SFML/Graphics/Rect.inl
./fontController.o: /usr/include/SFML/Graphics/Transformable.hpp
./fontController.o: /usr/include/SFML/Graphics/VertexArray.hpp
./fontController.o: /usr/include/SFML/Graphics/Vertex.hpp
./fontController.o: /usr/include/SFML/Graphics/Color.hpp
./fontController.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./fontController.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./fontController.o: /usr/include/SFML/Graphics/Font.hpp
./fontController.o: /usr/include/SFML/Graphics/Glyph.hpp
./fontController.o: /usr/include/SFML/Graphics/Texture.hpp
./fontController.o: /usr/include/SFML/Graphics/Image.hpp
./fontController.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./fontController.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./fontController.o: /usr/include/SFML/Graphics/View.hpp
./fontController.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./fontController.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./fontController.o: /usr/include/SFML/Graphics/Shader.hpp
./fontController.o: /usr/include/SFML/Graphics/Sprite.hpp
./fontController.o: /usr/include/SFML/Graphics/Text.hpp resourceHandler.hpp
./fontController.o: ResourcePath.hpp
./userInterface.o: userInterface.hpp /usr/include/SFML/Graphics.hpp
./userInterface.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./userInterface.o: /usr/include/SFML/Config.hpp
./userInterface.o: /usr/include/SFML/System/Clock.hpp
./userInterface.o: /usr/include/SFML/System/Export.hpp
./userInterface.o: /usr/include/SFML/System/Time.hpp
./userInterface.o: /usr/include/SFML/System/Err.hpp
./userInterface.o: /usr/include/SFML/System/FileInputStream.hpp
./userInterface.o: /usr/include/SFML/System/InputStream.hpp
./userInterface.o: /usr/include/SFML/System/NonCopyable.hpp
./userInterface.o: /usr/include/SFML/System/Lock.hpp
./userInterface.o: /usr/include/SFML/System/MemoryInputStream.hpp
./userInterface.o: /usr/include/SFML/System/Mutex.hpp
./userInterface.o: /usr/include/SFML/System/Sleep.hpp
./userInterface.o: /usr/include/SFML/System/String.hpp
./userInterface.o: /usr/include/SFML/System/Utf.hpp
./userInterface.o: /usr/include/SFML/System/Utf.inl
./userInterface.o: /usr/include/SFML/System/String.inl
./userInterface.o: /usr/include/SFML/System/Thread.hpp
./userInterface.o: /usr/include/SFML/System/Thread.inl
./userInterface.o: /usr/include/SFML/System/ThreadLocal.hpp
./userInterface.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./userInterface.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./userInterface.o: /usr/include/SFML/System/Vector2.hpp
./userInterface.o: /usr/include/SFML/System/Vector2.inl
./userInterface.o: /usr/include/SFML/System/Vector3.hpp
./userInterface.o: /usr/include/SFML/System/Vector3.inl
./userInterface.o: /usr/include/SFML/Window/Context.hpp
./userInterface.o: /usr/include/SFML/Window/Export.hpp
./userInterface.o: /usr/include/SFML/Window/GlResource.hpp
./userInterface.o: /usr/include/SFML/Window/ContextSettings.hpp
./userInterface.o: /usr/include/SFML/Window/Event.hpp
./userInterface.o: /usr/include/SFML/Window/Joystick.hpp
./userInterface.o: /usr/include/SFML/Window/Keyboard.hpp
./userInterface.o: /usr/include/SFML/Window/Mouse.hpp
./userInterface.o: /usr/include/SFML/Window/Sensor.hpp
./userInterface.o: /usr/include/SFML/Window/Touch.hpp
./userInterface.o: /usr/include/SFML/Window/VideoMode.hpp
./userInterface.o: /usr/include/SFML/Window/Window.hpp
./userInterface.o: /usr/include/SFML/Window/WindowHandle.hpp
./userInterface.o: /usr/include/SFML/Window/WindowStyle.hpp
./userInterface.o: /usr/include/SFML/Graphics/BlendMode.hpp
./userInterface.o: /usr/include/SFML/Graphics/Export.hpp
./userInterface.o: /usr/include/SFML/Graphics/CircleShape.hpp
./userInterface.o: /usr/include/SFML/Graphics/Shape.hpp
./userInterface.o: /usr/include/SFML/Graphics/Drawable.hpp
./userInterface.o: /usr/include/SFML/Graphics/RenderStates.hpp
./userInterface.o: /usr/include/SFML/Graphics/Transform.hpp
./userInterface.o: /usr/include/SFML/Graphics/Rect.hpp
./userInterface.o: /usr/include/SFML/Graphics/Rect.inl
./userInterface.o: /usr/include/SFML/Graphics/Transformable.hpp
./userInterface.o: /usr/include/SFML/Graphics/VertexArray.hpp
./userInterface.o: /usr/include/SFML/Graphics/Vertex.hpp
./userInterface.o: /usr/include/SFML/Graphics/Color.hpp
./userInterface.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./userInterface.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./userInterface.o: /usr/include/SFML/Graphics/Font.hpp
./userInterface.o: /usr/include/SFML/Graphics/Glyph.hpp
./userInterface.o: /usr/include/SFML/Graphics/Texture.hpp
./userInterface.o: /usr/include/SFML/Graphics/Image.hpp
./userInterface.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./userInterface.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./userInterface.o: /usr/include/SFML/Graphics/View.hpp
./userInterface.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./userInterface.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./userInterface.o: /usr/include/SFML/Graphics/Shader.hpp
./userInterface.o: /usr/include/SFML/Graphics/Sprite.hpp
./userInterface.o: /usr/include/SFML/Graphics/Text.hpp fontController.hpp
./userInterface.o: resourceHandler.hpp ResourcePath.hpp effectsController.hpp
./userInterface.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./userInterface.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./userInterface.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./userInterface.o: smallExplosion.hpp Powerup.hpp RenderType.hpp
./userInterface.o: enemyShot.hpp dasherShot.hpp turretShot.hpp
./userInterface.o: inputController.hpp easingTemplates.hpp player.hpp
./userInterface.o: tileController.hpp wall.hpp /usr/include/stdint.h
./userInterface.o: /usr/include/features.h /usr/include/stdc-predef.h
./userInterface.o: enemyController.hpp turret.hpp /usr/include/stdio.h
./userInterface.o: /usr/include/libio.h /usr/include/_G_config.h
./userInterface.o: /usr/include/wchar.h scoot.hpp enemy.hpp dasher.hpp
./userInterface.o: critter.hpp aStar.hpp coordinate.hpp detailController.hpp
./userInterface.o: Teleporter.hpp detailParent.hpp treasureChest.hpp
./userInterface.o: generalDetail.hpp lampLight.hpp damagedRobot.hpp rock.hpp
./userInterface.o: IntroDoor.hpp soundController.hpp
./userInterface.o: /usr/include/SFML/Audio.hpp
./userInterface.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./userInterface.o: /usr/include/SFML/Audio/Export.hpp
./userInterface.o: /usr/include/SFML/Audio/Listener.hpp
./userInterface.o: /usr/include/SFML/Audio/Music.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundStream.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundSource.hpp
./userInterface.o: /usr/include/SFML/Audio/AlResource.hpp
./userInterface.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./userInterface.o: /usr/include/SFML/Audio/Sound.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./userInterface.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./userInterface.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./treasureChest.o: treasureChest.hpp detailParent.hpp
./treasureChest.o: /usr/include/SFML/Graphics.hpp
./treasureChest.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./treasureChest.o: /usr/include/SFML/Config.hpp
./treasureChest.o: /usr/include/SFML/System/Clock.hpp
./treasureChest.o: /usr/include/SFML/System/Export.hpp
./treasureChest.o: /usr/include/SFML/System/Time.hpp
./treasureChest.o: /usr/include/SFML/System/Err.hpp
./treasureChest.o: /usr/include/SFML/System/FileInputStream.hpp
./treasureChest.o: /usr/include/SFML/System/InputStream.hpp
./treasureChest.o: /usr/include/SFML/System/NonCopyable.hpp
./treasureChest.o: /usr/include/SFML/System/Lock.hpp
./treasureChest.o: /usr/include/SFML/System/MemoryInputStream.hpp
./treasureChest.o: /usr/include/SFML/System/Mutex.hpp
./treasureChest.o: /usr/include/SFML/System/Sleep.hpp
./treasureChest.o: /usr/include/SFML/System/String.hpp
./treasureChest.o: /usr/include/SFML/System/Utf.hpp
./treasureChest.o: /usr/include/SFML/System/Utf.inl
./treasureChest.o: /usr/include/SFML/System/String.inl
./treasureChest.o: /usr/include/SFML/System/Thread.hpp
./treasureChest.o: /usr/include/SFML/System/Thread.inl
./treasureChest.o: /usr/include/SFML/System/ThreadLocal.hpp
./treasureChest.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./treasureChest.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./treasureChest.o: /usr/include/SFML/System/Vector2.hpp
./treasureChest.o: /usr/include/SFML/System/Vector2.inl
./treasureChest.o: /usr/include/SFML/System/Vector3.hpp
./treasureChest.o: /usr/include/SFML/System/Vector3.inl
./treasureChest.o: /usr/include/SFML/Window/Context.hpp
./treasureChest.o: /usr/include/SFML/Window/Export.hpp
./treasureChest.o: /usr/include/SFML/Window/GlResource.hpp
./treasureChest.o: /usr/include/SFML/Window/ContextSettings.hpp
./treasureChest.o: /usr/include/SFML/Window/Event.hpp
./treasureChest.o: /usr/include/SFML/Window/Joystick.hpp
./treasureChest.o: /usr/include/SFML/Window/Keyboard.hpp
./treasureChest.o: /usr/include/SFML/Window/Mouse.hpp
./treasureChest.o: /usr/include/SFML/Window/Sensor.hpp
./treasureChest.o: /usr/include/SFML/Window/Touch.hpp
./treasureChest.o: /usr/include/SFML/Window/VideoMode.hpp
./treasureChest.o: /usr/include/SFML/Window/Window.hpp
./treasureChest.o: /usr/include/SFML/Window/WindowHandle.hpp
./treasureChest.o: /usr/include/SFML/Window/WindowStyle.hpp
./treasureChest.o: /usr/include/SFML/Graphics/BlendMode.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Export.hpp
./treasureChest.o: /usr/include/SFML/Graphics/CircleShape.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Shape.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Drawable.hpp
./treasureChest.o: /usr/include/SFML/Graphics/RenderStates.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Transform.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Rect.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Rect.inl
./treasureChest.o: /usr/include/SFML/Graphics/Transformable.hpp
./treasureChest.o: /usr/include/SFML/Graphics/VertexArray.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Vertex.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Color.hpp
./treasureChest.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./treasureChest.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Font.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Glyph.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Texture.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Image.hpp
./treasureChest.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./treasureChest.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./treasureChest.o: /usr/include/SFML/Graphics/View.hpp
./treasureChest.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./treasureChest.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Shader.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Sprite.hpp
./treasureChest.o: /usr/include/SFML/Graphics/Text.hpp
./treasureChest.o: Framework/framework.hpp Framework/utilities.hpp
./treasureChest.o: inputController.hpp spriteSheet.hpp rng.hpp
./generalDetail.o: generalDetail.hpp detailParent.hpp
./generalDetail.o: /usr/include/SFML/Graphics.hpp
./generalDetail.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./generalDetail.o: /usr/include/SFML/Config.hpp
./generalDetail.o: /usr/include/SFML/System/Clock.hpp
./generalDetail.o: /usr/include/SFML/System/Export.hpp
./generalDetail.o: /usr/include/SFML/System/Time.hpp
./generalDetail.o: /usr/include/SFML/System/Err.hpp
./generalDetail.o: /usr/include/SFML/System/FileInputStream.hpp
./generalDetail.o: /usr/include/SFML/System/InputStream.hpp
./generalDetail.o: /usr/include/SFML/System/NonCopyable.hpp
./generalDetail.o: /usr/include/SFML/System/Lock.hpp
./generalDetail.o: /usr/include/SFML/System/MemoryInputStream.hpp
./generalDetail.o: /usr/include/SFML/System/Mutex.hpp
./generalDetail.o: /usr/include/SFML/System/Sleep.hpp
./generalDetail.o: /usr/include/SFML/System/String.hpp
./generalDetail.o: /usr/include/SFML/System/Utf.hpp
./generalDetail.o: /usr/include/SFML/System/Utf.inl
./generalDetail.o: /usr/include/SFML/System/String.inl
./generalDetail.o: /usr/include/SFML/System/Thread.hpp
./generalDetail.o: /usr/include/SFML/System/Thread.inl
./generalDetail.o: /usr/include/SFML/System/ThreadLocal.hpp
./generalDetail.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./generalDetail.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./generalDetail.o: /usr/include/SFML/System/Vector2.hpp
./generalDetail.o: /usr/include/SFML/System/Vector2.inl
./generalDetail.o: /usr/include/SFML/System/Vector3.hpp
./generalDetail.o: /usr/include/SFML/System/Vector3.inl
./generalDetail.o: /usr/include/SFML/Window/Context.hpp
./generalDetail.o: /usr/include/SFML/Window/Export.hpp
./generalDetail.o: /usr/include/SFML/Window/GlResource.hpp
./generalDetail.o: /usr/include/SFML/Window/ContextSettings.hpp
./generalDetail.o: /usr/include/SFML/Window/Event.hpp
./generalDetail.o: /usr/include/SFML/Window/Joystick.hpp
./generalDetail.o: /usr/include/SFML/Window/Keyboard.hpp
./generalDetail.o: /usr/include/SFML/Window/Mouse.hpp
./generalDetail.o: /usr/include/SFML/Window/Sensor.hpp
./generalDetail.o: /usr/include/SFML/Window/Touch.hpp
./generalDetail.o: /usr/include/SFML/Window/VideoMode.hpp
./generalDetail.o: /usr/include/SFML/Window/Window.hpp
./generalDetail.o: /usr/include/SFML/Window/WindowHandle.hpp
./generalDetail.o: /usr/include/SFML/Window/WindowStyle.hpp
./generalDetail.o: /usr/include/SFML/Graphics/BlendMode.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Export.hpp
./generalDetail.o: /usr/include/SFML/Graphics/CircleShape.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Shape.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Drawable.hpp
./generalDetail.o: /usr/include/SFML/Graphics/RenderStates.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Transform.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Rect.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Rect.inl
./generalDetail.o: /usr/include/SFML/Graphics/Transformable.hpp
./generalDetail.o: /usr/include/SFML/Graphics/VertexArray.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Vertex.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Color.hpp
./generalDetail.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./generalDetail.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Font.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Glyph.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Texture.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Image.hpp
./generalDetail.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./generalDetail.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./generalDetail.o: /usr/include/SFML/Graphics/View.hpp
./generalDetail.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./generalDetail.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Shader.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Sprite.hpp
./generalDetail.o: /usr/include/SFML/Graphics/Text.hpp
./generalDetail.o: Framework/framework.hpp Framework/utilities.hpp
./FireExplosion.o: FireExplosion.hpp /usr/include/SFML/Graphics.hpp
./FireExplosion.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./FireExplosion.o: /usr/include/SFML/Config.hpp
./FireExplosion.o: /usr/include/SFML/System/Clock.hpp
./FireExplosion.o: /usr/include/SFML/System/Export.hpp
./FireExplosion.o: /usr/include/SFML/System/Time.hpp
./FireExplosion.o: /usr/include/SFML/System/Err.hpp
./FireExplosion.o: /usr/include/SFML/System/FileInputStream.hpp
./FireExplosion.o: /usr/include/SFML/System/InputStream.hpp
./FireExplosion.o: /usr/include/SFML/System/NonCopyable.hpp
./FireExplosion.o: /usr/include/SFML/System/Lock.hpp
./FireExplosion.o: /usr/include/SFML/System/MemoryInputStream.hpp
./FireExplosion.o: /usr/include/SFML/System/Mutex.hpp
./FireExplosion.o: /usr/include/SFML/System/Sleep.hpp
./FireExplosion.o: /usr/include/SFML/System/String.hpp
./FireExplosion.o: /usr/include/SFML/System/Utf.hpp
./FireExplosion.o: /usr/include/SFML/System/Utf.inl
./FireExplosion.o: /usr/include/SFML/System/String.inl
./FireExplosion.o: /usr/include/SFML/System/Thread.hpp
./FireExplosion.o: /usr/include/SFML/System/Thread.inl
./FireExplosion.o: /usr/include/SFML/System/ThreadLocal.hpp
./FireExplosion.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./FireExplosion.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./FireExplosion.o: /usr/include/SFML/System/Vector2.hpp
./FireExplosion.o: /usr/include/SFML/System/Vector2.inl
./FireExplosion.o: /usr/include/SFML/System/Vector3.hpp
./FireExplosion.o: /usr/include/SFML/System/Vector3.inl
./FireExplosion.o: /usr/include/SFML/Window/Context.hpp
./FireExplosion.o: /usr/include/SFML/Window/Export.hpp
./FireExplosion.o: /usr/include/SFML/Window/GlResource.hpp
./FireExplosion.o: /usr/include/SFML/Window/ContextSettings.hpp
./FireExplosion.o: /usr/include/SFML/Window/Event.hpp
./FireExplosion.o: /usr/include/SFML/Window/Joystick.hpp
./FireExplosion.o: /usr/include/SFML/Window/Keyboard.hpp
./FireExplosion.o: /usr/include/SFML/Window/Mouse.hpp
./FireExplosion.o: /usr/include/SFML/Window/Sensor.hpp
./FireExplosion.o: /usr/include/SFML/Window/Touch.hpp
./FireExplosion.o: /usr/include/SFML/Window/VideoMode.hpp
./FireExplosion.o: /usr/include/SFML/Window/Window.hpp
./FireExplosion.o: /usr/include/SFML/Window/WindowHandle.hpp
./FireExplosion.o: /usr/include/SFML/Window/WindowStyle.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/BlendMode.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Export.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/CircleShape.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Shape.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Drawable.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/RenderStates.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Transform.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Rect.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Rect.inl
./FireExplosion.o: /usr/include/SFML/Graphics/Transformable.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/VertexArray.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Vertex.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Color.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Font.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Glyph.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Texture.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Image.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/View.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Shader.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Sprite.hpp
./FireExplosion.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp
./FireExplosion.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./damagedRobot.o: damagedRobot.hpp detailParent.hpp
./damagedRobot.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./damagedRobot.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./damagedRobot.o: /usr/include/SFML/System/Clock.hpp
./damagedRobot.o: /usr/include/SFML/System/Export.hpp
./damagedRobot.o: /usr/include/SFML/System/Time.hpp
./damagedRobot.o: /usr/include/SFML/System/Err.hpp
./damagedRobot.o: /usr/include/SFML/System/FileInputStream.hpp
./damagedRobot.o: /usr/include/SFML/System/InputStream.hpp
./damagedRobot.o: /usr/include/SFML/System/NonCopyable.hpp
./damagedRobot.o: /usr/include/SFML/System/Lock.hpp
./damagedRobot.o: /usr/include/SFML/System/MemoryInputStream.hpp
./damagedRobot.o: /usr/include/SFML/System/Mutex.hpp
./damagedRobot.o: /usr/include/SFML/System/Sleep.hpp
./damagedRobot.o: /usr/include/SFML/System/String.hpp
./damagedRobot.o: /usr/include/SFML/System/Utf.hpp
./damagedRobot.o: /usr/include/SFML/System/Utf.inl
./damagedRobot.o: /usr/include/SFML/System/String.inl
./damagedRobot.o: /usr/include/SFML/System/Thread.hpp
./damagedRobot.o: /usr/include/SFML/System/Thread.inl
./damagedRobot.o: /usr/include/SFML/System/ThreadLocal.hpp
./damagedRobot.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./damagedRobot.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./damagedRobot.o: /usr/include/SFML/System/Vector2.hpp
./damagedRobot.o: /usr/include/SFML/System/Vector2.inl
./damagedRobot.o: /usr/include/SFML/System/Vector3.hpp
./damagedRobot.o: /usr/include/SFML/System/Vector3.inl
./damagedRobot.o: /usr/include/SFML/Window/Context.hpp
./damagedRobot.o: /usr/include/SFML/Window/Export.hpp
./damagedRobot.o: /usr/include/SFML/Window/GlResource.hpp
./damagedRobot.o: /usr/include/SFML/Window/ContextSettings.hpp
./damagedRobot.o: /usr/include/SFML/Window/Event.hpp
./damagedRobot.o: /usr/include/SFML/Window/Joystick.hpp
./damagedRobot.o: /usr/include/SFML/Window/Keyboard.hpp
./damagedRobot.o: /usr/include/SFML/Window/Mouse.hpp
./damagedRobot.o: /usr/include/SFML/Window/Sensor.hpp
./damagedRobot.o: /usr/include/SFML/Window/Touch.hpp
./damagedRobot.o: /usr/include/SFML/Window/VideoMode.hpp
./damagedRobot.o: /usr/include/SFML/Window/Window.hpp
./damagedRobot.o: /usr/include/SFML/Window/WindowHandle.hpp
./damagedRobot.o: /usr/include/SFML/Window/WindowStyle.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/BlendMode.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Export.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/CircleShape.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Shape.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Drawable.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/RenderStates.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Transform.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Rect.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Rect.inl
./damagedRobot.o: /usr/include/SFML/Graphics/Transformable.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/VertexArray.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Vertex.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Color.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Font.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Glyph.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Texture.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Image.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/View.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Shader.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Sprite.hpp
./damagedRobot.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./damagedRobot.o: Framework/utilities.hpp spriteSheet.hpp rng.hpp
./enemyParent.o: enemyParent.hpp /usr/include/SFML/Graphics.hpp
./enemyParent.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./enemyParent.o: /usr/include/SFML/Config.hpp
./enemyParent.o: /usr/include/SFML/System/Clock.hpp
./enemyParent.o: /usr/include/SFML/System/Export.hpp
./enemyParent.o: /usr/include/SFML/System/Time.hpp
./enemyParent.o: /usr/include/SFML/System/Err.hpp
./enemyParent.o: /usr/include/SFML/System/FileInputStream.hpp
./enemyParent.o: /usr/include/SFML/System/InputStream.hpp
./enemyParent.o: /usr/include/SFML/System/NonCopyable.hpp
./enemyParent.o: /usr/include/SFML/System/Lock.hpp
./enemyParent.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemyParent.o: /usr/include/SFML/System/Mutex.hpp
./enemyParent.o: /usr/include/SFML/System/Sleep.hpp
./enemyParent.o: /usr/include/SFML/System/String.hpp
./enemyParent.o: /usr/include/SFML/System/Utf.hpp
./enemyParent.o: /usr/include/SFML/System/Utf.inl
./enemyParent.o: /usr/include/SFML/System/String.inl
./enemyParent.o: /usr/include/SFML/System/Thread.hpp
./enemyParent.o: /usr/include/SFML/System/Thread.inl
./enemyParent.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemyParent.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemyParent.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemyParent.o: /usr/include/SFML/System/Vector2.hpp
./enemyParent.o: /usr/include/SFML/System/Vector2.inl
./enemyParent.o: /usr/include/SFML/System/Vector3.hpp
./enemyParent.o: /usr/include/SFML/System/Vector3.inl
./enemyParent.o: /usr/include/SFML/Window/Context.hpp
./enemyParent.o: /usr/include/SFML/Window/Export.hpp
./enemyParent.o: /usr/include/SFML/Window/GlResource.hpp
./enemyParent.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemyParent.o: /usr/include/SFML/Window/Event.hpp
./enemyParent.o: /usr/include/SFML/Window/Joystick.hpp
./enemyParent.o: /usr/include/SFML/Window/Keyboard.hpp
./enemyParent.o: /usr/include/SFML/Window/Mouse.hpp
./enemyParent.o: /usr/include/SFML/Window/Sensor.hpp
./enemyParent.o: /usr/include/SFML/Window/Touch.hpp
./enemyParent.o: /usr/include/SFML/Window/VideoMode.hpp
./enemyParent.o: /usr/include/SFML/Window/Window.hpp
./enemyParent.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemyParent.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemyParent.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Export.hpp
./enemyParent.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Shape.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemyParent.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Transform.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Rect.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Rect.inl
./enemyParent.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemyParent.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Color.hpp
./enemyParent.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemyParent.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Font.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Texture.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Image.hpp
./enemyParent.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemyParent.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemyParent.o: /usr/include/SFML/Graphics/View.hpp
./enemyParent.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemyParent.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Shader.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemyParent.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp
./enemyParent.o: /usr/include/stdint.h /usr/include/features.h
./enemyParent.o: /usr/include/stdc-predef.h /usr/include/math.h
./bulletType1.o: bulletType1.hpp /usr/include/SFML/Graphics.hpp
./bulletType1.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./bulletType1.o: /usr/include/SFML/Config.hpp
./bulletType1.o: /usr/include/SFML/System/Clock.hpp
./bulletType1.o: /usr/include/SFML/System/Export.hpp
./bulletType1.o: /usr/include/SFML/System/Time.hpp
./bulletType1.o: /usr/include/SFML/System/Err.hpp
./bulletType1.o: /usr/include/SFML/System/FileInputStream.hpp
./bulletType1.o: /usr/include/SFML/System/InputStream.hpp
./bulletType1.o: /usr/include/SFML/System/NonCopyable.hpp
./bulletType1.o: /usr/include/SFML/System/Lock.hpp
./bulletType1.o: /usr/include/SFML/System/MemoryInputStream.hpp
./bulletType1.o: /usr/include/SFML/System/Mutex.hpp
./bulletType1.o: /usr/include/SFML/System/Sleep.hpp
./bulletType1.o: /usr/include/SFML/System/String.hpp
./bulletType1.o: /usr/include/SFML/System/Utf.hpp
./bulletType1.o: /usr/include/SFML/System/Utf.inl
./bulletType1.o: /usr/include/SFML/System/String.inl
./bulletType1.o: /usr/include/SFML/System/Thread.hpp
./bulletType1.o: /usr/include/SFML/System/Thread.inl
./bulletType1.o: /usr/include/SFML/System/ThreadLocal.hpp
./bulletType1.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./bulletType1.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./bulletType1.o: /usr/include/SFML/System/Vector2.hpp
./bulletType1.o: /usr/include/SFML/System/Vector2.inl
./bulletType1.o: /usr/include/SFML/System/Vector3.hpp
./bulletType1.o: /usr/include/SFML/System/Vector3.inl
./bulletType1.o: /usr/include/SFML/Window/Context.hpp
./bulletType1.o: /usr/include/SFML/Window/Export.hpp
./bulletType1.o: /usr/include/SFML/Window/GlResource.hpp
./bulletType1.o: /usr/include/SFML/Window/ContextSettings.hpp
./bulletType1.o: /usr/include/SFML/Window/Event.hpp
./bulletType1.o: /usr/include/SFML/Window/Joystick.hpp
./bulletType1.o: /usr/include/SFML/Window/Keyboard.hpp
./bulletType1.o: /usr/include/SFML/Window/Mouse.hpp
./bulletType1.o: /usr/include/SFML/Window/Sensor.hpp
./bulletType1.o: /usr/include/SFML/Window/Touch.hpp
./bulletType1.o: /usr/include/SFML/Window/VideoMode.hpp
./bulletType1.o: /usr/include/SFML/Window/Window.hpp
./bulletType1.o: /usr/include/SFML/Window/WindowHandle.hpp
./bulletType1.o: /usr/include/SFML/Window/WindowStyle.hpp
./bulletType1.o: /usr/include/SFML/Graphics/BlendMode.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Export.hpp
./bulletType1.o: /usr/include/SFML/Graphics/CircleShape.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Shape.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Drawable.hpp
./bulletType1.o: /usr/include/SFML/Graphics/RenderStates.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Transform.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Rect.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Rect.inl
./bulletType1.o: /usr/include/SFML/Graphics/Transformable.hpp
./bulletType1.o: /usr/include/SFML/Graphics/VertexArray.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Vertex.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Color.hpp
./bulletType1.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./bulletType1.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Font.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Glyph.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Texture.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Image.hpp
./bulletType1.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./bulletType1.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./bulletType1.o: /usr/include/SFML/Graphics/View.hpp
./bulletType1.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./bulletType1.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Shader.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Sprite.hpp
./bulletType1.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp
./bulletType1.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./turretShot.o: turretShot.hpp Effect.hpp /usr/include/SFML/Graphics.hpp
./turretShot.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./turretShot.o: /usr/include/SFML/Config.hpp
./turretShot.o: /usr/include/SFML/System/Clock.hpp
./turretShot.o: /usr/include/SFML/System/Export.hpp
./turretShot.o: /usr/include/SFML/System/Time.hpp
./turretShot.o: /usr/include/SFML/System/Err.hpp
./turretShot.o: /usr/include/SFML/System/FileInputStream.hpp
./turretShot.o: /usr/include/SFML/System/InputStream.hpp
./turretShot.o: /usr/include/SFML/System/NonCopyable.hpp
./turretShot.o: /usr/include/SFML/System/Lock.hpp
./turretShot.o: /usr/include/SFML/System/MemoryInputStream.hpp
./turretShot.o: /usr/include/SFML/System/Mutex.hpp
./turretShot.o: /usr/include/SFML/System/Sleep.hpp
./turretShot.o: /usr/include/SFML/System/String.hpp
./turretShot.o: /usr/include/SFML/System/Utf.hpp
./turretShot.o: /usr/include/SFML/System/Utf.inl
./turretShot.o: /usr/include/SFML/System/String.inl
./turretShot.o: /usr/include/SFML/System/Thread.hpp
./turretShot.o: /usr/include/SFML/System/Thread.inl
./turretShot.o: /usr/include/SFML/System/ThreadLocal.hpp
./turretShot.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./turretShot.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./turretShot.o: /usr/include/SFML/System/Vector2.hpp
./turretShot.o: /usr/include/SFML/System/Vector2.inl
./turretShot.o: /usr/include/SFML/System/Vector3.hpp
./turretShot.o: /usr/include/SFML/System/Vector3.inl
./turretShot.o: /usr/include/SFML/Window/Context.hpp
./turretShot.o: /usr/include/SFML/Window/Export.hpp
./turretShot.o: /usr/include/SFML/Window/GlResource.hpp
./turretShot.o: /usr/include/SFML/Window/ContextSettings.hpp
./turretShot.o: /usr/include/SFML/Window/Event.hpp
./turretShot.o: /usr/include/SFML/Window/Joystick.hpp
./turretShot.o: /usr/include/SFML/Window/Keyboard.hpp
./turretShot.o: /usr/include/SFML/Window/Mouse.hpp
./turretShot.o: /usr/include/SFML/Window/Sensor.hpp
./turretShot.o: /usr/include/SFML/Window/Touch.hpp
./turretShot.o: /usr/include/SFML/Window/VideoMode.hpp
./turretShot.o: /usr/include/SFML/Window/Window.hpp
./turretShot.o: /usr/include/SFML/Window/WindowHandle.hpp
./turretShot.o: /usr/include/SFML/Window/WindowStyle.hpp
./turretShot.o: /usr/include/SFML/Graphics/BlendMode.hpp
./turretShot.o: /usr/include/SFML/Graphics/Export.hpp
./turretShot.o: /usr/include/SFML/Graphics/CircleShape.hpp
./turretShot.o: /usr/include/SFML/Graphics/Shape.hpp
./turretShot.o: /usr/include/SFML/Graphics/Drawable.hpp
./turretShot.o: /usr/include/SFML/Graphics/RenderStates.hpp
./turretShot.o: /usr/include/SFML/Graphics/Transform.hpp
./turretShot.o: /usr/include/SFML/Graphics/Rect.hpp
./turretShot.o: /usr/include/SFML/Graphics/Rect.inl
./turretShot.o: /usr/include/SFML/Graphics/Transformable.hpp
./turretShot.o: /usr/include/SFML/Graphics/VertexArray.hpp
./turretShot.o: /usr/include/SFML/Graphics/Vertex.hpp
./turretShot.o: /usr/include/SFML/Graphics/Color.hpp
./turretShot.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./turretShot.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./turretShot.o: /usr/include/SFML/Graphics/Font.hpp
./turretShot.o: /usr/include/SFML/Graphics/Glyph.hpp
./turretShot.o: /usr/include/SFML/Graphics/Texture.hpp
./turretShot.o: /usr/include/SFML/Graphics/Image.hpp
./turretShot.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./turretShot.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./turretShot.o: /usr/include/SFML/Graphics/View.hpp
./turretShot.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./turretShot.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./turretShot.o: /usr/include/SFML/Graphics/Shader.hpp
./turretShot.o: /usr/include/SFML/Graphics/Sprite.hpp
./turretShot.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./turretShot.o: Framework/utilities.hpp rng.hpp
./Teleporter.o: Teleporter.hpp detailParent.hpp
./Teleporter.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./Teleporter.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./Teleporter.o: /usr/include/SFML/System/Clock.hpp
./Teleporter.o: /usr/include/SFML/System/Export.hpp
./Teleporter.o: /usr/include/SFML/System/Time.hpp
./Teleporter.o: /usr/include/SFML/System/Err.hpp
./Teleporter.o: /usr/include/SFML/System/FileInputStream.hpp
./Teleporter.o: /usr/include/SFML/System/InputStream.hpp
./Teleporter.o: /usr/include/SFML/System/NonCopyable.hpp
./Teleporter.o: /usr/include/SFML/System/Lock.hpp
./Teleporter.o: /usr/include/SFML/System/MemoryInputStream.hpp
./Teleporter.o: /usr/include/SFML/System/Mutex.hpp
./Teleporter.o: /usr/include/SFML/System/Sleep.hpp
./Teleporter.o: /usr/include/SFML/System/String.hpp
./Teleporter.o: /usr/include/SFML/System/Utf.hpp
./Teleporter.o: /usr/include/SFML/System/Utf.inl
./Teleporter.o: /usr/include/SFML/System/String.inl
./Teleporter.o: /usr/include/SFML/System/Thread.hpp
./Teleporter.o: /usr/include/SFML/System/Thread.inl
./Teleporter.o: /usr/include/SFML/System/ThreadLocal.hpp
./Teleporter.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./Teleporter.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./Teleporter.o: /usr/include/SFML/System/Vector2.hpp
./Teleporter.o: /usr/include/SFML/System/Vector2.inl
./Teleporter.o: /usr/include/SFML/System/Vector3.hpp
./Teleporter.o: /usr/include/SFML/System/Vector3.inl
./Teleporter.o: /usr/include/SFML/Window/Context.hpp
./Teleporter.o: /usr/include/SFML/Window/Export.hpp
./Teleporter.o: /usr/include/SFML/Window/GlResource.hpp
./Teleporter.o: /usr/include/SFML/Window/ContextSettings.hpp
./Teleporter.o: /usr/include/SFML/Window/Event.hpp
./Teleporter.o: /usr/include/SFML/Window/Joystick.hpp
./Teleporter.o: /usr/include/SFML/Window/Keyboard.hpp
./Teleporter.o: /usr/include/SFML/Window/Mouse.hpp
./Teleporter.o: /usr/include/SFML/Window/Sensor.hpp
./Teleporter.o: /usr/include/SFML/Window/Touch.hpp
./Teleporter.o: /usr/include/SFML/Window/VideoMode.hpp
./Teleporter.o: /usr/include/SFML/Window/Window.hpp
./Teleporter.o: /usr/include/SFML/Window/WindowHandle.hpp
./Teleporter.o: /usr/include/SFML/Window/WindowStyle.hpp
./Teleporter.o: /usr/include/SFML/Graphics/BlendMode.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Export.hpp
./Teleporter.o: /usr/include/SFML/Graphics/CircleShape.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Shape.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Drawable.hpp
./Teleporter.o: /usr/include/SFML/Graphics/RenderStates.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Transform.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Rect.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Rect.inl
./Teleporter.o: /usr/include/SFML/Graphics/Transformable.hpp
./Teleporter.o: /usr/include/SFML/Graphics/VertexArray.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Vertex.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Color.hpp
./Teleporter.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./Teleporter.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Font.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Glyph.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Texture.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Image.hpp
./Teleporter.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./Teleporter.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./Teleporter.o: /usr/include/SFML/Graphics/View.hpp
./Teleporter.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./Teleporter.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Shader.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Sprite.hpp
./Teleporter.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./Teleporter.o: Framework/utilities.hpp effectsController.hpp
./Teleporter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./Teleporter.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./Teleporter.o: smallExplosion.hpp Powerup.hpp RenderType.hpp enemyShot.hpp
./Teleporter.o: dasherShot.hpp turretShot.hpp
./drawPixels.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./drawPixels.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./drawPixels.o: /usr/include/SFML/System/Clock.hpp
./drawPixels.o: /usr/include/SFML/System/Export.hpp
./drawPixels.o: /usr/include/SFML/System/Time.hpp
./drawPixels.o: /usr/include/SFML/System/Err.hpp
./drawPixels.o: /usr/include/SFML/System/FileInputStream.hpp
./drawPixels.o: /usr/include/SFML/System/InputStream.hpp
./drawPixels.o: /usr/include/SFML/System/NonCopyable.hpp
./drawPixels.o: /usr/include/SFML/System/Lock.hpp
./drawPixels.o: /usr/include/SFML/System/MemoryInputStream.hpp
./drawPixels.o: /usr/include/SFML/System/Mutex.hpp
./drawPixels.o: /usr/include/SFML/System/Sleep.hpp
./drawPixels.o: /usr/include/SFML/System/String.hpp
./drawPixels.o: /usr/include/SFML/System/Utf.hpp
./drawPixels.o: /usr/include/SFML/System/Utf.inl
./drawPixels.o: /usr/include/SFML/System/String.inl
./drawPixels.o: /usr/include/SFML/System/Thread.hpp
./drawPixels.o: /usr/include/SFML/System/Thread.inl
./drawPixels.o: /usr/include/SFML/System/ThreadLocal.hpp
./drawPixels.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./drawPixels.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./drawPixels.o: /usr/include/SFML/System/Vector2.hpp
./drawPixels.o: /usr/include/SFML/System/Vector2.inl
./drawPixels.o: /usr/include/SFML/System/Vector3.hpp
./drawPixels.o: /usr/include/SFML/System/Vector3.inl
./drawPixels.o: /usr/include/SFML/Window/Context.hpp
./drawPixels.o: /usr/include/SFML/Window/Export.hpp
./drawPixels.o: /usr/include/SFML/Window/GlResource.hpp
./drawPixels.o: /usr/include/SFML/Window/ContextSettings.hpp
./drawPixels.o: /usr/include/SFML/Window/Event.hpp
./drawPixels.o: /usr/include/SFML/Window/Joystick.hpp
./drawPixels.o: /usr/include/SFML/Window/Keyboard.hpp
./drawPixels.o: /usr/include/SFML/Window/Mouse.hpp
./drawPixels.o: /usr/include/SFML/Window/Sensor.hpp
./drawPixels.o: /usr/include/SFML/Window/Touch.hpp
./drawPixels.o: /usr/include/SFML/Window/VideoMode.hpp
./drawPixels.o: /usr/include/SFML/Window/Window.hpp
./drawPixels.o: /usr/include/SFML/Window/WindowHandle.hpp
./drawPixels.o: /usr/include/SFML/Window/WindowStyle.hpp
./drawPixels.o: /usr/include/SFML/Graphics/BlendMode.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Export.hpp
./drawPixels.o: /usr/include/SFML/Graphics/CircleShape.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Shape.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Drawable.hpp
./drawPixels.o: /usr/include/SFML/Graphics/RenderStates.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Transform.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Rect.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Rect.inl
./drawPixels.o: /usr/include/SFML/Graphics/Transformable.hpp
./drawPixels.o: /usr/include/SFML/Graphics/VertexArray.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Vertex.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Color.hpp
./drawPixels.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./drawPixels.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Font.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Glyph.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Texture.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Image.hpp
./drawPixels.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./drawPixels.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./drawPixels.o: /usr/include/SFML/Graphics/View.hpp
./drawPixels.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./drawPixels.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Shader.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Sprite.hpp
./drawPixels.o: /usr/include/SFML/Graphics/Text.hpp
./dasherShot.o: dasherShot.hpp /usr/include/SFML/Graphics.hpp
./dasherShot.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./dasherShot.o: /usr/include/SFML/Config.hpp
./dasherShot.o: /usr/include/SFML/System/Clock.hpp
./dasherShot.o: /usr/include/SFML/System/Export.hpp
./dasherShot.o: /usr/include/SFML/System/Time.hpp
./dasherShot.o: /usr/include/SFML/System/Err.hpp
./dasherShot.o: /usr/include/SFML/System/FileInputStream.hpp
./dasherShot.o: /usr/include/SFML/System/InputStream.hpp
./dasherShot.o: /usr/include/SFML/System/NonCopyable.hpp
./dasherShot.o: /usr/include/SFML/System/Lock.hpp
./dasherShot.o: /usr/include/SFML/System/MemoryInputStream.hpp
./dasherShot.o: /usr/include/SFML/System/Mutex.hpp
./dasherShot.o: /usr/include/SFML/System/Sleep.hpp
./dasherShot.o: /usr/include/SFML/System/String.hpp
./dasherShot.o: /usr/include/SFML/System/Utf.hpp
./dasherShot.o: /usr/include/SFML/System/Utf.inl
./dasherShot.o: /usr/include/SFML/System/String.inl
./dasherShot.o: /usr/include/SFML/System/Thread.hpp
./dasherShot.o: /usr/include/SFML/System/Thread.inl
./dasherShot.o: /usr/include/SFML/System/ThreadLocal.hpp
./dasherShot.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./dasherShot.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./dasherShot.o: /usr/include/SFML/System/Vector2.hpp
./dasherShot.o: /usr/include/SFML/System/Vector2.inl
./dasherShot.o: /usr/include/SFML/System/Vector3.hpp
./dasherShot.o: /usr/include/SFML/System/Vector3.inl
./dasherShot.o: /usr/include/SFML/Window/Context.hpp
./dasherShot.o: /usr/include/SFML/Window/Export.hpp
./dasherShot.o: /usr/include/SFML/Window/GlResource.hpp
./dasherShot.o: /usr/include/SFML/Window/ContextSettings.hpp
./dasherShot.o: /usr/include/SFML/Window/Event.hpp
./dasherShot.o: /usr/include/SFML/Window/Joystick.hpp
./dasherShot.o: /usr/include/SFML/Window/Keyboard.hpp
./dasherShot.o: /usr/include/SFML/Window/Mouse.hpp
./dasherShot.o: /usr/include/SFML/Window/Sensor.hpp
./dasherShot.o: /usr/include/SFML/Window/Touch.hpp
./dasherShot.o: /usr/include/SFML/Window/VideoMode.hpp
./dasherShot.o: /usr/include/SFML/Window/Window.hpp
./dasherShot.o: /usr/include/SFML/Window/WindowHandle.hpp
./dasherShot.o: /usr/include/SFML/Window/WindowStyle.hpp
./dasherShot.o: /usr/include/SFML/Graphics/BlendMode.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Export.hpp
./dasherShot.o: /usr/include/SFML/Graphics/CircleShape.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Shape.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Drawable.hpp
./dasherShot.o: /usr/include/SFML/Graphics/RenderStates.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Transform.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Rect.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Rect.inl
./dasherShot.o: /usr/include/SFML/Graphics/Transformable.hpp
./dasherShot.o: /usr/include/SFML/Graphics/VertexArray.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Vertex.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Color.hpp
./dasherShot.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./dasherShot.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Font.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Glyph.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Texture.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Image.hpp
./dasherShot.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./dasherShot.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./dasherShot.o: /usr/include/SFML/Graphics/View.hpp
./dasherShot.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./dasherShot.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Shader.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Sprite.hpp
./dasherShot.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp
./dasherShot.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./dasherShot.o: rng.hpp
./lampLight.o: lampLight.hpp detailParent.hpp /usr/include/SFML/Graphics.hpp
./lampLight.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./lampLight.o: /usr/include/SFML/Config.hpp
./lampLight.o: /usr/include/SFML/System/Clock.hpp
./lampLight.o: /usr/include/SFML/System/Export.hpp
./lampLight.o: /usr/include/SFML/System/Time.hpp
./lampLight.o: /usr/include/SFML/System/Err.hpp
./lampLight.o: /usr/include/SFML/System/FileInputStream.hpp
./lampLight.o: /usr/include/SFML/System/InputStream.hpp
./lampLight.o: /usr/include/SFML/System/NonCopyable.hpp
./lampLight.o: /usr/include/SFML/System/Lock.hpp
./lampLight.o: /usr/include/SFML/System/MemoryInputStream.hpp
./lampLight.o: /usr/include/SFML/System/Mutex.hpp
./lampLight.o: /usr/include/SFML/System/Sleep.hpp
./lampLight.o: /usr/include/SFML/System/String.hpp
./lampLight.o: /usr/include/SFML/System/Utf.hpp
./lampLight.o: /usr/include/SFML/System/Utf.inl
./lampLight.o: /usr/include/SFML/System/String.inl
./lampLight.o: /usr/include/SFML/System/Thread.hpp
./lampLight.o: /usr/include/SFML/System/Thread.inl
./lampLight.o: /usr/include/SFML/System/ThreadLocal.hpp
./lampLight.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./lampLight.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./lampLight.o: /usr/include/SFML/System/Vector2.hpp
./lampLight.o: /usr/include/SFML/System/Vector2.inl
./lampLight.o: /usr/include/SFML/System/Vector3.hpp
./lampLight.o: /usr/include/SFML/System/Vector3.inl
./lampLight.o: /usr/include/SFML/Window/Context.hpp
./lampLight.o: /usr/include/SFML/Window/Export.hpp
./lampLight.o: /usr/include/SFML/Window/GlResource.hpp
./lampLight.o: /usr/include/SFML/Window/ContextSettings.hpp
./lampLight.o: /usr/include/SFML/Window/Event.hpp
./lampLight.o: /usr/include/SFML/Window/Joystick.hpp
./lampLight.o: /usr/include/SFML/Window/Keyboard.hpp
./lampLight.o: /usr/include/SFML/Window/Mouse.hpp
./lampLight.o: /usr/include/SFML/Window/Sensor.hpp
./lampLight.o: /usr/include/SFML/Window/Touch.hpp
./lampLight.o: /usr/include/SFML/Window/VideoMode.hpp
./lampLight.o: /usr/include/SFML/Window/Window.hpp
./lampLight.o: /usr/include/SFML/Window/WindowHandle.hpp
./lampLight.o: /usr/include/SFML/Window/WindowStyle.hpp
./lampLight.o: /usr/include/SFML/Graphics/BlendMode.hpp
./lampLight.o: /usr/include/SFML/Graphics/Export.hpp
./lampLight.o: /usr/include/SFML/Graphics/CircleShape.hpp
./lampLight.o: /usr/include/SFML/Graphics/Shape.hpp
./lampLight.o: /usr/include/SFML/Graphics/Drawable.hpp
./lampLight.o: /usr/include/SFML/Graphics/RenderStates.hpp
./lampLight.o: /usr/include/SFML/Graphics/Transform.hpp
./lampLight.o: /usr/include/SFML/Graphics/Rect.hpp
./lampLight.o: /usr/include/SFML/Graphics/Rect.inl
./lampLight.o: /usr/include/SFML/Graphics/Transformable.hpp
./lampLight.o: /usr/include/SFML/Graphics/VertexArray.hpp
./lampLight.o: /usr/include/SFML/Graphics/Vertex.hpp
./lampLight.o: /usr/include/SFML/Graphics/Color.hpp
./lampLight.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./lampLight.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./lampLight.o: /usr/include/SFML/Graphics/Font.hpp
./lampLight.o: /usr/include/SFML/Graphics/Glyph.hpp
./lampLight.o: /usr/include/SFML/Graphics/Texture.hpp
./lampLight.o: /usr/include/SFML/Graphics/Image.hpp
./lampLight.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./lampLight.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./lampLight.o: /usr/include/SFML/Graphics/View.hpp
./lampLight.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./lampLight.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./lampLight.o: /usr/include/SFML/Graphics/Shader.hpp
./lampLight.o: /usr/include/SFML/Graphics/Sprite.hpp
./lampLight.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./lampLight.o: Framework/utilities.hpp
./IntroDoor.o: IntroDoor.hpp detailParent.hpp /usr/include/SFML/Graphics.hpp
./IntroDoor.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./IntroDoor.o: /usr/include/SFML/Config.hpp
./IntroDoor.o: /usr/include/SFML/System/Clock.hpp
./IntroDoor.o: /usr/include/SFML/System/Export.hpp
./IntroDoor.o: /usr/include/SFML/System/Time.hpp
./IntroDoor.o: /usr/include/SFML/System/Err.hpp
./IntroDoor.o: /usr/include/SFML/System/FileInputStream.hpp
./IntroDoor.o: /usr/include/SFML/System/InputStream.hpp
./IntroDoor.o: /usr/include/SFML/System/NonCopyable.hpp
./IntroDoor.o: /usr/include/SFML/System/Lock.hpp
./IntroDoor.o: /usr/include/SFML/System/MemoryInputStream.hpp
./IntroDoor.o: /usr/include/SFML/System/Mutex.hpp
./IntroDoor.o: /usr/include/SFML/System/Sleep.hpp
./IntroDoor.o: /usr/include/SFML/System/String.hpp
./IntroDoor.o: /usr/include/SFML/System/Utf.hpp
./IntroDoor.o: /usr/include/SFML/System/Utf.inl
./IntroDoor.o: /usr/include/SFML/System/String.inl
./IntroDoor.o: /usr/include/SFML/System/Thread.hpp
./IntroDoor.o: /usr/include/SFML/System/Thread.inl
./IntroDoor.o: /usr/include/SFML/System/ThreadLocal.hpp
./IntroDoor.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./IntroDoor.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./IntroDoor.o: /usr/include/SFML/System/Vector2.hpp
./IntroDoor.o: /usr/include/SFML/System/Vector2.inl
./IntroDoor.o: /usr/include/SFML/System/Vector3.hpp
./IntroDoor.o: /usr/include/SFML/System/Vector3.inl
./IntroDoor.o: /usr/include/SFML/Window/Context.hpp
./IntroDoor.o: /usr/include/SFML/Window/Export.hpp
./IntroDoor.o: /usr/include/SFML/Window/GlResource.hpp
./IntroDoor.o: /usr/include/SFML/Window/ContextSettings.hpp
./IntroDoor.o: /usr/include/SFML/Window/Event.hpp
./IntroDoor.o: /usr/include/SFML/Window/Joystick.hpp
./IntroDoor.o: /usr/include/SFML/Window/Keyboard.hpp
./IntroDoor.o: /usr/include/SFML/Window/Mouse.hpp
./IntroDoor.o: /usr/include/SFML/Window/Sensor.hpp
./IntroDoor.o: /usr/include/SFML/Window/Touch.hpp
./IntroDoor.o: /usr/include/SFML/Window/VideoMode.hpp
./IntroDoor.o: /usr/include/SFML/Window/Window.hpp
./IntroDoor.o: /usr/include/SFML/Window/WindowHandle.hpp
./IntroDoor.o: /usr/include/SFML/Window/WindowStyle.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/BlendMode.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Export.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/CircleShape.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Shape.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Drawable.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/RenderStates.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Transform.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Rect.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Rect.inl
./IntroDoor.o: /usr/include/SFML/Graphics/Transformable.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/VertexArray.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Vertex.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Color.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Font.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Glyph.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Texture.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Image.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/View.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Shader.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Sprite.hpp
./IntroDoor.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./IntroDoor.o: Framework/utilities.hpp effectsController.hpp
./IntroDoor.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp rng.hpp
./IntroDoor.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./IntroDoor.o: smallExplosion.hpp Powerup.hpp RenderType.hpp enemyShot.hpp
./IntroDoor.o: dasherShot.hpp turretShot.hpp screenShakeController.hpp
./IntroDoor.o: player.hpp tileController.hpp wall.hpp /usr/include/stdint.h
./IntroDoor.o: /usr/include/features.h /usr/include/stdc-predef.h
./IntroDoor.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./IntroDoor.o: turret.hpp /usr/include/stdio.h /usr/include/libio.h
./IntroDoor.o: /usr/include/_G_config.h /usr/include/wchar.h
./IntroDoor.o: fontController.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./IntroDoor.o: aStar.hpp coordinate.hpp detailController.hpp Teleporter.hpp
./IntroDoor.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./IntroDoor.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./IntroDoor.o: damagedRobot.hpp rock.hpp soundController.hpp
./IntroDoor.o: /usr/include/SFML/Audio.hpp
./IntroDoor.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./IntroDoor.o: /usr/include/SFML/Audio/Export.hpp
./IntroDoor.o: /usr/include/SFML/Audio/Listener.hpp
./IntroDoor.o: /usr/include/SFML/Audio/Music.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundStream.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundSource.hpp
./IntroDoor.o: /usr/include/SFML/Audio/AlResource.hpp
./IntroDoor.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./IntroDoor.o: /usr/include/SFML/Audio/Sound.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./IntroDoor.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./IntroDoor.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./enemyShot.o: enemyShot.hpp /usr/include/SFML/Graphics.hpp
./enemyShot.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./enemyShot.o: /usr/include/SFML/Config.hpp
./enemyShot.o: /usr/include/SFML/System/Clock.hpp
./enemyShot.o: /usr/include/SFML/System/Export.hpp
./enemyShot.o: /usr/include/SFML/System/Time.hpp
./enemyShot.o: /usr/include/SFML/System/Err.hpp
./enemyShot.o: /usr/include/SFML/System/FileInputStream.hpp
./enemyShot.o: /usr/include/SFML/System/InputStream.hpp
./enemyShot.o: /usr/include/SFML/System/NonCopyable.hpp
./enemyShot.o: /usr/include/SFML/System/Lock.hpp
./enemyShot.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemyShot.o: /usr/include/SFML/System/Mutex.hpp
./enemyShot.o: /usr/include/SFML/System/Sleep.hpp
./enemyShot.o: /usr/include/SFML/System/String.hpp
./enemyShot.o: /usr/include/SFML/System/Utf.hpp
./enemyShot.o: /usr/include/SFML/System/Utf.inl
./enemyShot.o: /usr/include/SFML/System/String.inl
./enemyShot.o: /usr/include/SFML/System/Thread.hpp
./enemyShot.o: /usr/include/SFML/System/Thread.inl
./enemyShot.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemyShot.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemyShot.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemyShot.o: /usr/include/SFML/System/Vector2.hpp
./enemyShot.o: /usr/include/SFML/System/Vector2.inl
./enemyShot.o: /usr/include/SFML/System/Vector3.hpp
./enemyShot.o: /usr/include/SFML/System/Vector3.inl
./enemyShot.o: /usr/include/SFML/Window/Context.hpp
./enemyShot.o: /usr/include/SFML/Window/Export.hpp
./enemyShot.o: /usr/include/SFML/Window/GlResource.hpp
./enemyShot.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemyShot.o: /usr/include/SFML/Window/Event.hpp
./enemyShot.o: /usr/include/SFML/Window/Joystick.hpp
./enemyShot.o: /usr/include/SFML/Window/Keyboard.hpp
./enemyShot.o: /usr/include/SFML/Window/Mouse.hpp
./enemyShot.o: /usr/include/SFML/Window/Sensor.hpp
./enemyShot.o: /usr/include/SFML/Window/Touch.hpp
./enemyShot.o: /usr/include/SFML/Window/VideoMode.hpp
./enemyShot.o: /usr/include/SFML/Window/Window.hpp
./enemyShot.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemyShot.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemyShot.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Export.hpp
./enemyShot.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Shape.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemyShot.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Transform.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Rect.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Rect.inl
./enemyShot.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemyShot.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Color.hpp
./enemyShot.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemyShot.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Font.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Texture.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Image.hpp
./enemyShot.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemyShot.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemyShot.o: /usr/include/SFML/Graphics/View.hpp
./enemyShot.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemyShot.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Shader.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemyShot.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp Effect.hpp
./enemyShot.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./shotPuff.o: shotPuff.hpp /usr/include/SFML/Graphics.hpp
./shotPuff.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./shotPuff.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./shotPuff.o: /usr/include/SFML/System/Export.hpp
./shotPuff.o: /usr/include/SFML/System/Time.hpp
./shotPuff.o: /usr/include/SFML/System/Err.hpp
./shotPuff.o: /usr/include/SFML/System/FileInputStream.hpp
./shotPuff.o: /usr/include/SFML/System/InputStream.hpp
./shotPuff.o: /usr/include/SFML/System/NonCopyable.hpp
./shotPuff.o: /usr/include/SFML/System/Lock.hpp
./shotPuff.o: /usr/include/SFML/System/MemoryInputStream.hpp
./shotPuff.o: /usr/include/SFML/System/Mutex.hpp
./shotPuff.o: /usr/include/SFML/System/Sleep.hpp
./shotPuff.o: /usr/include/SFML/System/String.hpp
./shotPuff.o: /usr/include/SFML/System/Utf.hpp
./shotPuff.o: /usr/include/SFML/System/Utf.inl
./shotPuff.o: /usr/include/SFML/System/String.inl
./shotPuff.o: /usr/include/SFML/System/Thread.hpp
./shotPuff.o: /usr/include/SFML/System/Thread.inl
./shotPuff.o: /usr/include/SFML/System/ThreadLocal.hpp
./shotPuff.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./shotPuff.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./shotPuff.o: /usr/include/SFML/System/Vector2.hpp
./shotPuff.o: /usr/include/SFML/System/Vector2.inl
./shotPuff.o: /usr/include/SFML/System/Vector3.hpp
./shotPuff.o: /usr/include/SFML/System/Vector3.inl
./shotPuff.o: /usr/include/SFML/Window/Context.hpp
./shotPuff.o: /usr/include/SFML/Window/Export.hpp
./shotPuff.o: /usr/include/SFML/Window/GlResource.hpp
./shotPuff.o: /usr/include/SFML/Window/ContextSettings.hpp
./shotPuff.o: /usr/include/SFML/Window/Event.hpp
./shotPuff.o: /usr/include/SFML/Window/Joystick.hpp
./shotPuff.o: /usr/include/SFML/Window/Keyboard.hpp
./shotPuff.o: /usr/include/SFML/Window/Mouse.hpp
./shotPuff.o: /usr/include/SFML/Window/Sensor.hpp
./shotPuff.o: /usr/include/SFML/Window/Touch.hpp
./shotPuff.o: /usr/include/SFML/Window/VideoMode.hpp
./shotPuff.o: /usr/include/SFML/Window/Window.hpp
./shotPuff.o: /usr/include/SFML/Window/WindowHandle.hpp
./shotPuff.o: /usr/include/SFML/Window/WindowStyle.hpp
./shotPuff.o: /usr/include/SFML/Graphics/BlendMode.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Export.hpp
./shotPuff.o: /usr/include/SFML/Graphics/CircleShape.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Shape.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Drawable.hpp
./shotPuff.o: /usr/include/SFML/Graphics/RenderStates.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Transform.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Rect.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Rect.inl
./shotPuff.o: /usr/include/SFML/Graphics/Transformable.hpp
./shotPuff.o: /usr/include/SFML/Graphics/VertexArray.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Vertex.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Color.hpp
./shotPuff.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./shotPuff.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Font.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Glyph.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Texture.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Image.hpp
./shotPuff.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./shotPuff.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./shotPuff.o: /usr/include/SFML/Graphics/View.hpp
./shotPuff.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./shotPuff.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Shader.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Sprite.hpp
./shotPuff.o: /usr/include/SFML/Graphics/Text.hpp spriteSheet.hpp Effect.hpp
./shotPuff.o: Framework/framework.hpp Framework/utilities.hpp
./Powerup.o: Powerup.hpp /usr/include/SFML/Graphics.hpp
./Powerup.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./Powerup.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./Powerup.o: /usr/include/SFML/System/Export.hpp
./Powerup.o: /usr/include/SFML/System/Time.hpp
./Powerup.o: /usr/include/SFML/System/Err.hpp
./Powerup.o: /usr/include/SFML/System/FileInputStream.hpp
./Powerup.o: /usr/include/SFML/System/InputStream.hpp
./Powerup.o: /usr/include/SFML/System/NonCopyable.hpp
./Powerup.o: /usr/include/SFML/System/Lock.hpp
./Powerup.o: /usr/include/SFML/System/MemoryInputStream.hpp
./Powerup.o: /usr/include/SFML/System/Mutex.hpp
./Powerup.o: /usr/include/SFML/System/Sleep.hpp
./Powerup.o: /usr/include/SFML/System/String.hpp
./Powerup.o: /usr/include/SFML/System/Utf.hpp
./Powerup.o: /usr/include/SFML/System/Utf.inl
./Powerup.o: /usr/include/SFML/System/String.inl
./Powerup.o: /usr/include/SFML/System/Thread.hpp
./Powerup.o: /usr/include/SFML/System/Thread.inl
./Powerup.o: /usr/include/SFML/System/ThreadLocal.hpp
./Powerup.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./Powerup.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./Powerup.o: /usr/include/SFML/System/Vector2.hpp
./Powerup.o: /usr/include/SFML/System/Vector2.inl
./Powerup.o: /usr/include/SFML/System/Vector3.hpp
./Powerup.o: /usr/include/SFML/System/Vector3.inl
./Powerup.o: /usr/include/SFML/Window/Context.hpp
./Powerup.o: /usr/include/SFML/Window/Export.hpp
./Powerup.o: /usr/include/SFML/Window/GlResource.hpp
./Powerup.o: /usr/include/SFML/Window/ContextSettings.hpp
./Powerup.o: /usr/include/SFML/Window/Event.hpp
./Powerup.o: /usr/include/SFML/Window/Joystick.hpp
./Powerup.o: /usr/include/SFML/Window/Keyboard.hpp
./Powerup.o: /usr/include/SFML/Window/Mouse.hpp
./Powerup.o: /usr/include/SFML/Window/Sensor.hpp
./Powerup.o: /usr/include/SFML/Window/Touch.hpp
./Powerup.o: /usr/include/SFML/Window/VideoMode.hpp
./Powerup.o: /usr/include/SFML/Window/Window.hpp
./Powerup.o: /usr/include/SFML/Window/WindowHandle.hpp
./Powerup.o: /usr/include/SFML/Window/WindowStyle.hpp
./Powerup.o: /usr/include/SFML/Graphics/BlendMode.hpp
./Powerup.o: /usr/include/SFML/Graphics/Export.hpp
./Powerup.o: /usr/include/SFML/Graphics/CircleShape.hpp
./Powerup.o: /usr/include/SFML/Graphics/Shape.hpp
./Powerup.o: /usr/include/SFML/Graphics/Drawable.hpp
./Powerup.o: /usr/include/SFML/Graphics/RenderStates.hpp
./Powerup.o: /usr/include/SFML/Graphics/Transform.hpp
./Powerup.o: /usr/include/SFML/Graphics/Rect.hpp
./Powerup.o: /usr/include/SFML/Graphics/Rect.inl
./Powerup.o: /usr/include/SFML/Graphics/Transformable.hpp
./Powerup.o: /usr/include/SFML/Graphics/VertexArray.hpp
./Powerup.o: /usr/include/SFML/Graphics/Vertex.hpp
./Powerup.o: /usr/include/SFML/Graphics/Color.hpp
./Powerup.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./Powerup.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./Powerup.o: /usr/include/SFML/Graphics/Font.hpp
./Powerup.o: /usr/include/SFML/Graphics/Glyph.hpp
./Powerup.o: /usr/include/SFML/Graphics/Texture.hpp
./Powerup.o: /usr/include/SFML/Graphics/Image.hpp
./Powerup.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./Powerup.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./Powerup.o: /usr/include/SFML/Graphics/View.hpp
./Powerup.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./Powerup.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./Powerup.o: /usr/include/SFML/Graphics/Shader.hpp
./Powerup.o: /usr/include/SFML/Graphics/Sprite.hpp
./Powerup.o: /usr/include/SFML/Graphics/Text.hpp Effect.hpp
./Powerup.o: Framework/framework.hpp Framework/utilities.hpp
./critter.o: critter.hpp enemy.hpp /usr/include/SFML/Graphics.hpp
./critter.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./critter.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./critter.o: /usr/include/SFML/System/Export.hpp
./critter.o: /usr/include/SFML/System/Time.hpp
./critter.o: /usr/include/SFML/System/Err.hpp
./critter.o: /usr/include/SFML/System/FileInputStream.hpp
./critter.o: /usr/include/SFML/System/InputStream.hpp
./critter.o: /usr/include/SFML/System/NonCopyable.hpp
./critter.o: /usr/include/SFML/System/Lock.hpp
./critter.o: /usr/include/SFML/System/MemoryInputStream.hpp
./critter.o: /usr/include/SFML/System/Mutex.hpp
./critter.o: /usr/include/SFML/System/Sleep.hpp
./critter.o: /usr/include/SFML/System/String.hpp
./critter.o: /usr/include/SFML/System/Utf.hpp
./critter.o: /usr/include/SFML/System/Utf.inl
./critter.o: /usr/include/SFML/System/String.inl
./critter.o: /usr/include/SFML/System/Thread.hpp
./critter.o: /usr/include/SFML/System/Thread.inl
./critter.o: /usr/include/SFML/System/ThreadLocal.hpp
./critter.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./critter.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./critter.o: /usr/include/SFML/System/Vector2.hpp
./critter.o: /usr/include/SFML/System/Vector2.inl
./critter.o: /usr/include/SFML/System/Vector3.hpp
./critter.o: /usr/include/SFML/System/Vector3.inl
./critter.o: /usr/include/SFML/Window/Context.hpp
./critter.o: /usr/include/SFML/Window/Export.hpp
./critter.o: /usr/include/SFML/Window/GlResource.hpp
./critter.o: /usr/include/SFML/Window/ContextSettings.hpp
./critter.o: /usr/include/SFML/Window/Event.hpp
./critter.o: /usr/include/SFML/Window/Joystick.hpp
./critter.o: /usr/include/SFML/Window/Keyboard.hpp
./critter.o: /usr/include/SFML/Window/Mouse.hpp
./critter.o: /usr/include/SFML/Window/Sensor.hpp
./critter.o: /usr/include/SFML/Window/Touch.hpp
./critter.o: /usr/include/SFML/Window/VideoMode.hpp
./critter.o: /usr/include/SFML/Window/Window.hpp
./critter.o: /usr/include/SFML/Window/WindowHandle.hpp
./critter.o: /usr/include/SFML/Window/WindowStyle.hpp
./critter.o: /usr/include/SFML/Graphics/BlendMode.hpp
./critter.o: /usr/include/SFML/Graphics/Export.hpp
./critter.o: /usr/include/SFML/Graphics/CircleShape.hpp
./critter.o: /usr/include/SFML/Graphics/Shape.hpp
./critter.o: /usr/include/SFML/Graphics/Drawable.hpp
./critter.o: /usr/include/SFML/Graphics/RenderStates.hpp
./critter.o: /usr/include/SFML/Graphics/Transform.hpp
./critter.o: /usr/include/SFML/Graphics/Rect.hpp
./critter.o: /usr/include/SFML/Graphics/Rect.inl
./critter.o: /usr/include/SFML/Graphics/Transformable.hpp
./critter.o: /usr/include/SFML/Graphics/VertexArray.hpp
./critter.o: /usr/include/SFML/Graphics/Vertex.hpp
./critter.o: /usr/include/SFML/Graphics/Color.hpp
./critter.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./critter.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./critter.o: /usr/include/SFML/Graphics/Font.hpp
./critter.o: /usr/include/SFML/Graphics/Glyph.hpp
./critter.o: /usr/include/SFML/Graphics/Texture.hpp
./critter.o: /usr/include/SFML/Graphics/Image.hpp
./critter.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./critter.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./critter.o: /usr/include/SFML/Graphics/View.hpp
./critter.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./critter.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./critter.o: /usr/include/SFML/Graphics/Shader.hpp
./critter.o: /usr/include/SFML/Graphics/Sprite.hpp
./critter.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp
./critter.o: /usr/include/stdint.h /usr/include/features.h
./critter.o: /usr/include/stdc-predef.h effectsController.hpp
./critter.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./critter.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./critter.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./critter.o: smallExplosion.hpp Powerup.hpp RenderType.hpp enemyShot.hpp
./critter.o: dasherShot.hpp turretShot.hpp aStar.hpp tileController.hpp
./critter.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./critter.o: turret.hpp /usr/include/stdio.h /usr/include/libio.h
./critter.o: /usr/include/_G_config.h /usr/include/wchar.h fontController.hpp
./critter.o: scoot.hpp dasher.hpp coordinate.hpp /usr/include/math.h
./turret.o: turret.hpp /usr/include/stdio.h /usr/include/features.h
./turret.o: /usr/include/stdc-predef.h /usr/include/libio.h
./turret.o: /usr/include/_G_config.h /usr/include/wchar.h
./turret.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./turret.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./turret.o: /usr/include/SFML/System/Clock.hpp
./turret.o: /usr/include/SFML/System/Export.hpp
./turret.o: /usr/include/SFML/System/Time.hpp
./turret.o: /usr/include/SFML/System/Err.hpp
./turret.o: /usr/include/SFML/System/FileInputStream.hpp
./turret.o: /usr/include/SFML/System/InputStream.hpp
./turret.o: /usr/include/SFML/System/NonCopyable.hpp
./turret.o: /usr/include/SFML/System/Lock.hpp
./turret.o: /usr/include/SFML/System/MemoryInputStream.hpp
./turret.o: /usr/include/SFML/System/Mutex.hpp
./turret.o: /usr/include/SFML/System/Sleep.hpp
./turret.o: /usr/include/SFML/System/String.hpp
./turret.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./turret.o: /usr/include/SFML/System/String.inl
./turret.o: /usr/include/SFML/System/Thread.hpp
./turret.o: /usr/include/SFML/System/Thread.inl
./turret.o: /usr/include/SFML/System/ThreadLocal.hpp
./turret.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./turret.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./turret.o: /usr/include/SFML/System/Vector2.hpp
./turret.o: /usr/include/SFML/System/Vector2.inl
./turret.o: /usr/include/SFML/System/Vector3.hpp
./turret.o: /usr/include/SFML/System/Vector3.inl
./turret.o: /usr/include/SFML/Window/Context.hpp
./turret.o: /usr/include/SFML/Window/Export.hpp
./turret.o: /usr/include/SFML/Window/GlResource.hpp
./turret.o: /usr/include/SFML/Window/ContextSettings.hpp
./turret.o: /usr/include/SFML/Window/Event.hpp
./turret.o: /usr/include/SFML/Window/Joystick.hpp
./turret.o: /usr/include/SFML/Window/Keyboard.hpp
./turret.o: /usr/include/SFML/Window/Mouse.hpp
./turret.o: /usr/include/SFML/Window/Sensor.hpp
./turret.o: /usr/include/SFML/Window/Touch.hpp
./turret.o: /usr/include/SFML/Window/VideoMode.hpp
./turret.o: /usr/include/SFML/Window/Window.hpp
./turret.o: /usr/include/SFML/Window/WindowHandle.hpp
./turret.o: /usr/include/SFML/Window/WindowStyle.hpp
./turret.o: /usr/include/SFML/Graphics/BlendMode.hpp
./turret.o: /usr/include/SFML/Graphics/Export.hpp
./turret.o: /usr/include/SFML/Graphics/CircleShape.hpp
./turret.o: /usr/include/SFML/Graphics/Shape.hpp
./turret.o: /usr/include/SFML/Graphics/Drawable.hpp
./turret.o: /usr/include/SFML/Graphics/RenderStates.hpp
./turret.o: /usr/include/SFML/Graphics/Transform.hpp
./turret.o: /usr/include/SFML/Graphics/Rect.hpp
./turret.o: /usr/include/SFML/Graphics/Rect.inl
./turret.o: /usr/include/SFML/Graphics/Transformable.hpp
./turret.o: /usr/include/SFML/Graphics/VertexArray.hpp
./turret.o: /usr/include/SFML/Graphics/Vertex.hpp
./turret.o: /usr/include/SFML/Graphics/Color.hpp
./turret.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./turret.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./turret.o: /usr/include/SFML/Graphics/Font.hpp
./turret.o: /usr/include/SFML/Graphics/Glyph.hpp
./turret.o: /usr/include/SFML/Graphics/Texture.hpp
./turret.o: /usr/include/SFML/Graphics/Image.hpp
./turret.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./turret.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./turret.o: /usr/include/SFML/Graphics/View.hpp
./turret.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./turret.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./turret.o: /usr/include/SFML/Graphics/Shader.hpp
./turret.o: /usr/include/SFML/Graphics/Sprite.hpp
./turret.o: /usr/include/SFML/Graphics/Text.hpp fontController.hpp
./turret.o: resourceHandler.hpp ResourcePath.hpp effectsController.hpp
./turret.o: turretFlashEffect.hpp spriteSheet.hpp Effect.hpp
./turret.o: Framework/framework.hpp Framework/utilities.hpp rng.hpp
./turret.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./turret.o: Powerup.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./turret.o: turretShot.hpp angleFunction.hpp
./player.o: player.hpp /usr/include/SFML/Graphics.hpp
./player.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./player.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./player.o: /usr/include/SFML/System/Export.hpp
./player.o: /usr/include/SFML/System/Time.hpp
./player.o: /usr/include/SFML/System/Err.hpp
./player.o: /usr/include/SFML/System/FileInputStream.hpp
./player.o: /usr/include/SFML/System/InputStream.hpp
./player.o: /usr/include/SFML/System/NonCopyable.hpp
./player.o: /usr/include/SFML/System/Lock.hpp
./player.o: /usr/include/SFML/System/MemoryInputStream.hpp
./player.o: /usr/include/SFML/System/Mutex.hpp
./player.o: /usr/include/SFML/System/Sleep.hpp
./player.o: /usr/include/SFML/System/String.hpp
./player.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./player.o: /usr/include/SFML/System/String.inl
./player.o: /usr/include/SFML/System/Thread.hpp
./player.o: /usr/include/SFML/System/Thread.inl
./player.o: /usr/include/SFML/System/ThreadLocal.hpp
./player.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./player.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./player.o: /usr/include/SFML/System/Vector2.hpp
./player.o: /usr/include/SFML/System/Vector2.inl
./player.o: /usr/include/SFML/System/Vector3.hpp
./player.o: /usr/include/SFML/System/Vector3.inl
./player.o: /usr/include/SFML/Window/Context.hpp
./player.o: /usr/include/SFML/Window/Export.hpp
./player.o: /usr/include/SFML/Window/GlResource.hpp
./player.o: /usr/include/SFML/Window/ContextSettings.hpp
./player.o: /usr/include/SFML/Window/Event.hpp
./player.o: /usr/include/SFML/Window/Joystick.hpp
./player.o: /usr/include/SFML/Window/Keyboard.hpp
./player.o: /usr/include/SFML/Window/Mouse.hpp
./player.o: /usr/include/SFML/Window/Sensor.hpp
./player.o: /usr/include/SFML/Window/Touch.hpp
./player.o: /usr/include/SFML/Window/VideoMode.hpp
./player.o: /usr/include/SFML/Window/Window.hpp
./player.o: /usr/include/SFML/Window/WindowHandle.hpp
./player.o: /usr/include/SFML/Window/WindowStyle.hpp
./player.o: /usr/include/SFML/Graphics/BlendMode.hpp
./player.o: /usr/include/SFML/Graphics/Export.hpp
./player.o: /usr/include/SFML/Graphics/CircleShape.hpp
./player.o: /usr/include/SFML/Graphics/Shape.hpp
./player.o: /usr/include/SFML/Graphics/Drawable.hpp
./player.o: /usr/include/SFML/Graphics/RenderStates.hpp
./player.o: /usr/include/SFML/Graphics/Transform.hpp
./player.o: /usr/include/SFML/Graphics/Rect.hpp
./player.o: /usr/include/SFML/Graphics/Rect.inl
./player.o: /usr/include/SFML/Graphics/Transformable.hpp
./player.o: /usr/include/SFML/Graphics/VertexArray.hpp
./player.o: /usr/include/SFML/Graphics/Vertex.hpp
./player.o: /usr/include/SFML/Graphics/Color.hpp
./player.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./player.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./player.o: /usr/include/SFML/Graphics/Font.hpp
./player.o: /usr/include/SFML/Graphics/Glyph.hpp
./player.o: /usr/include/SFML/Graphics/Texture.hpp
./player.o: /usr/include/SFML/Graphics/Image.hpp
./player.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./player.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./player.o: /usr/include/SFML/Graphics/View.hpp
./player.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./player.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./player.o: /usr/include/SFML/Graphics/Shader.hpp
./player.o: /usr/include/SFML/Graphics/Sprite.hpp
./player.o: /usr/include/SFML/Graphics/Text.hpp tileController.hpp wall.hpp
./player.o: /usr/include/stdint.h /usr/include/features.h
./player.o: /usr/include/stdc-predef.h enemyController.hpp
./player.o: resourceHandler.hpp ResourcePath.hpp turret.hpp
./player.o: /usr/include/stdio.h /usr/include/libio.h
./player.o: /usr/include/_G_config.h /usr/include/wchar.h fontController.hpp
./player.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./player.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp
./player.o: rng.hpp bulletType1.hpp shotPuff.hpp FireExplosion.hpp
./player.o: smallExplosion.hpp Powerup.hpp RenderType.hpp enemyShot.hpp
./player.o: dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp dasher.hpp
./player.o: critter.hpp aStar.hpp coordinate.hpp detailController.hpp
./player.o: Teleporter.hpp detailParent.hpp treasureChest.hpp
./player.o: inputController.hpp generalDetail.hpp lampLight.hpp
./player.o: userInterface.hpp easingTemplates.hpp damagedRobot.hpp rock.hpp
./player.o: IntroDoor.hpp soundController.hpp /usr/include/SFML/Audio.hpp
./player.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./player.o: /usr/include/SFML/Audio/Export.hpp
./player.o: /usr/include/SFML/Audio/Listener.hpp
./player.o: /usr/include/SFML/Audio/Music.hpp
./player.o: /usr/include/SFML/Audio/SoundStream.hpp
./player.o: /usr/include/SFML/Audio/SoundSource.hpp
./player.o: /usr/include/SFML/Audio/AlResource.hpp
./player.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./player.o: /usr/include/SFML/Audio/Sound.hpp
./player.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./player.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./player.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./player.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./player.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./player.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./player.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./player.o: playerAnimationFunctions.hpp playerCollisionFunctions.hpp
./player.o: scene.hpp backgroundHandler.hpp screenShakeController.hpp
./dasher.o: dasher.hpp effectsController.hpp /usr/include/SFML/Graphics.hpp
./dasher.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./dasher.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./dasher.o: /usr/include/SFML/System/Export.hpp
./dasher.o: /usr/include/SFML/System/Time.hpp
./dasher.o: /usr/include/SFML/System/Err.hpp
./dasher.o: /usr/include/SFML/System/FileInputStream.hpp
./dasher.o: /usr/include/SFML/System/InputStream.hpp
./dasher.o: /usr/include/SFML/System/NonCopyable.hpp
./dasher.o: /usr/include/SFML/System/Lock.hpp
./dasher.o: /usr/include/SFML/System/MemoryInputStream.hpp
./dasher.o: /usr/include/SFML/System/Mutex.hpp
./dasher.o: /usr/include/SFML/System/Sleep.hpp
./dasher.o: /usr/include/SFML/System/String.hpp
./dasher.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./dasher.o: /usr/include/SFML/System/String.inl
./dasher.o: /usr/include/SFML/System/Thread.hpp
./dasher.o: /usr/include/SFML/System/Thread.inl
./dasher.o: /usr/include/SFML/System/ThreadLocal.hpp
./dasher.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./dasher.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./dasher.o: /usr/include/SFML/System/Vector2.hpp
./dasher.o: /usr/include/SFML/System/Vector2.inl
./dasher.o: /usr/include/SFML/System/Vector3.hpp
./dasher.o: /usr/include/SFML/System/Vector3.inl
./dasher.o: /usr/include/SFML/Window/Context.hpp
./dasher.o: /usr/include/SFML/Window/Export.hpp
./dasher.o: /usr/include/SFML/Window/GlResource.hpp
./dasher.o: /usr/include/SFML/Window/ContextSettings.hpp
./dasher.o: /usr/include/SFML/Window/Event.hpp
./dasher.o: /usr/include/SFML/Window/Joystick.hpp
./dasher.o: /usr/include/SFML/Window/Keyboard.hpp
./dasher.o: /usr/include/SFML/Window/Mouse.hpp
./dasher.o: /usr/include/SFML/Window/Sensor.hpp
./dasher.o: /usr/include/SFML/Window/Touch.hpp
./dasher.o: /usr/include/SFML/Window/VideoMode.hpp
./dasher.o: /usr/include/SFML/Window/Window.hpp
./dasher.o: /usr/include/SFML/Window/WindowHandle.hpp
./dasher.o: /usr/include/SFML/Window/WindowStyle.hpp
./dasher.o: /usr/include/SFML/Graphics/BlendMode.hpp
./dasher.o: /usr/include/SFML/Graphics/Export.hpp
./dasher.o: /usr/include/SFML/Graphics/CircleShape.hpp
./dasher.o: /usr/include/SFML/Graphics/Shape.hpp
./dasher.o: /usr/include/SFML/Graphics/Drawable.hpp
./dasher.o: /usr/include/SFML/Graphics/RenderStates.hpp
./dasher.o: /usr/include/SFML/Graphics/Transform.hpp
./dasher.o: /usr/include/SFML/Graphics/Rect.hpp
./dasher.o: /usr/include/SFML/Graphics/Rect.inl
./dasher.o: /usr/include/SFML/Graphics/Transformable.hpp
./dasher.o: /usr/include/SFML/Graphics/VertexArray.hpp
./dasher.o: /usr/include/SFML/Graphics/Vertex.hpp
./dasher.o: /usr/include/SFML/Graphics/Color.hpp
./dasher.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./dasher.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./dasher.o: /usr/include/SFML/Graphics/Font.hpp
./dasher.o: /usr/include/SFML/Graphics/Glyph.hpp
./dasher.o: /usr/include/SFML/Graphics/Texture.hpp
./dasher.o: /usr/include/SFML/Graphics/Image.hpp
./dasher.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./dasher.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./dasher.o: /usr/include/SFML/Graphics/View.hpp
./dasher.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./dasher.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./dasher.o: /usr/include/SFML/Graphics/Shader.hpp
./dasher.o: /usr/include/SFML/Graphics/Sprite.hpp
./dasher.o: /usr/include/SFML/Graphics/Text.hpp turretFlashEffect.hpp
./dasher.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./dasher.o: Framework/utilities.hpp rng.hpp bulletType1.hpp shotPuff.hpp
./dasher.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp RenderType.hpp
./dasher.o: enemyShot.hpp dasherShot.hpp turretShot.hpp enemy.hpp wall.hpp
./dasher.o: /usr/include/stdint.h /usr/include/features.h
./dasher.o: /usr/include/stdc-predef.h resourceHandler.hpp ResourcePath.hpp
./dasher.o: angleFunction.hpp
./scoot.o: scoot.hpp wall.hpp /usr/include/stdint.h /usr/include/features.h
./scoot.o: /usr/include/stdc-predef.h effectsController.hpp
./scoot.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./scoot.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./scoot.o: /usr/include/SFML/System/Clock.hpp
./scoot.o: /usr/include/SFML/System/Export.hpp
./scoot.o: /usr/include/SFML/System/Time.hpp /usr/include/SFML/System/Err.hpp
./scoot.o: /usr/include/SFML/System/FileInputStream.hpp
./scoot.o: /usr/include/SFML/System/InputStream.hpp
./scoot.o: /usr/include/SFML/System/NonCopyable.hpp
./scoot.o: /usr/include/SFML/System/Lock.hpp
./scoot.o: /usr/include/SFML/System/MemoryInputStream.hpp
./scoot.o: /usr/include/SFML/System/Mutex.hpp
./scoot.o: /usr/include/SFML/System/Sleep.hpp
./scoot.o: /usr/include/SFML/System/String.hpp
./scoot.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./scoot.o: /usr/include/SFML/System/String.inl
./scoot.o: /usr/include/SFML/System/Thread.hpp
./scoot.o: /usr/include/SFML/System/Thread.inl
./scoot.o: /usr/include/SFML/System/ThreadLocal.hpp
./scoot.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./scoot.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./scoot.o: /usr/include/SFML/System/Vector2.hpp
./scoot.o: /usr/include/SFML/System/Vector2.inl
./scoot.o: /usr/include/SFML/System/Vector3.hpp
./scoot.o: /usr/include/SFML/System/Vector3.inl
./scoot.o: /usr/include/SFML/Window/Context.hpp
./scoot.o: /usr/include/SFML/Window/Export.hpp
./scoot.o: /usr/include/SFML/Window/GlResource.hpp
./scoot.o: /usr/include/SFML/Window/ContextSettings.hpp
./scoot.o: /usr/include/SFML/Window/Event.hpp
./scoot.o: /usr/include/SFML/Window/Joystick.hpp
./scoot.o: /usr/include/SFML/Window/Keyboard.hpp
./scoot.o: /usr/include/SFML/Window/Mouse.hpp
./scoot.o: /usr/include/SFML/Window/Sensor.hpp
./scoot.o: /usr/include/SFML/Window/Touch.hpp
./scoot.o: /usr/include/SFML/Window/VideoMode.hpp
./scoot.o: /usr/include/SFML/Window/Window.hpp
./scoot.o: /usr/include/SFML/Window/WindowHandle.hpp
./scoot.o: /usr/include/SFML/Window/WindowStyle.hpp
./scoot.o: /usr/include/SFML/Graphics/BlendMode.hpp
./scoot.o: /usr/include/SFML/Graphics/Export.hpp
./scoot.o: /usr/include/SFML/Graphics/CircleShape.hpp
./scoot.o: /usr/include/SFML/Graphics/Shape.hpp
./scoot.o: /usr/include/SFML/Graphics/Drawable.hpp
./scoot.o: /usr/include/SFML/Graphics/RenderStates.hpp
./scoot.o: /usr/include/SFML/Graphics/Transform.hpp
./scoot.o: /usr/include/SFML/Graphics/Rect.hpp
./scoot.o: /usr/include/SFML/Graphics/Rect.inl
./scoot.o: /usr/include/SFML/Graphics/Transformable.hpp
./scoot.o: /usr/include/SFML/Graphics/VertexArray.hpp
./scoot.o: /usr/include/SFML/Graphics/Vertex.hpp
./scoot.o: /usr/include/SFML/Graphics/Color.hpp
./scoot.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./scoot.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./scoot.o: /usr/include/SFML/Graphics/Font.hpp
./scoot.o: /usr/include/SFML/Graphics/Glyph.hpp
./scoot.o: /usr/include/SFML/Graphics/Texture.hpp
./scoot.o: /usr/include/SFML/Graphics/Image.hpp
./scoot.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./scoot.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./scoot.o: /usr/include/SFML/Graphics/View.hpp
./scoot.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./scoot.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./scoot.o: /usr/include/SFML/Graphics/Shader.hpp
./scoot.o: /usr/include/SFML/Graphics/Sprite.hpp
./scoot.o: /usr/include/SFML/Graphics/Text.hpp turretFlashEffect.hpp
./scoot.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./scoot.o: Framework/utilities.hpp rng.hpp bulletType1.hpp shotPuff.hpp
./scoot.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp RenderType.hpp
./scoot.o: enemyShot.hpp dasherShot.hpp turretShot.hpp enemy.hpp
./scoot.o: resourceHandler.hpp ResourcePath.hpp angleFunction.hpp
./scene.o: mappingFunctions.hpp tileController.hpp
./scene.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./scene.o: /usr/include/SFML/System.hpp /usr/include/SFML/Config.hpp
./scene.o: /usr/include/SFML/System/Clock.hpp
./scene.o: /usr/include/SFML/System/Export.hpp
./scene.o: /usr/include/SFML/System/Time.hpp /usr/include/SFML/System/Err.hpp
./scene.o: /usr/include/SFML/System/FileInputStream.hpp
./scene.o: /usr/include/SFML/System/InputStream.hpp
./scene.o: /usr/include/SFML/System/NonCopyable.hpp
./scene.o: /usr/include/SFML/System/Lock.hpp
./scene.o: /usr/include/SFML/System/MemoryInputStream.hpp
./scene.o: /usr/include/SFML/System/Mutex.hpp
./scene.o: /usr/include/SFML/System/Sleep.hpp
./scene.o: /usr/include/SFML/System/String.hpp
./scene.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./scene.o: /usr/include/SFML/System/String.inl
./scene.o: /usr/include/SFML/System/Thread.hpp
./scene.o: /usr/include/SFML/System/Thread.inl
./scene.o: /usr/include/SFML/System/ThreadLocal.hpp
./scene.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./scene.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./scene.o: /usr/include/SFML/System/Vector2.hpp
./scene.o: /usr/include/SFML/System/Vector2.inl
./scene.o: /usr/include/SFML/System/Vector3.hpp
./scene.o: /usr/include/SFML/System/Vector3.inl
./scene.o: /usr/include/SFML/Window/Context.hpp
./scene.o: /usr/include/SFML/Window/Export.hpp
./scene.o: /usr/include/SFML/Window/GlResource.hpp
./scene.o: /usr/include/SFML/Window/ContextSettings.hpp
./scene.o: /usr/include/SFML/Window/Event.hpp
./scene.o: /usr/include/SFML/Window/Joystick.hpp
./scene.o: /usr/include/SFML/Window/Keyboard.hpp
./scene.o: /usr/include/SFML/Window/Mouse.hpp
./scene.o: /usr/include/SFML/Window/Sensor.hpp
./scene.o: /usr/include/SFML/Window/Touch.hpp
./scene.o: /usr/include/SFML/Window/VideoMode.hpp
./scene.o: /usr/include/SFML/Window/Window.hpp
./scene.o: /usr/include/SFML/Window/WindowHandle.hpp
./scene.o: /usr/include/SFML/Window/WindowStyle.hpp
./scene.o: /usr/include/SFML/Graphics/BlendMode.hpp
./scene.o: /usr/include/SFML/Graphics/Export.hpp
./scene.o: /usr/include/SFML/Graphics/CircleShape.hpp
./scene.o: /usr/include/SFML/Graphics/Shape.hpp
./scene.o: /usr/include/SFML/Graphics/Drawable.hpp
./scene.o: /usr/include/SFML/Graphics/RenderStates.hpp
./scene.o: /usr/include/SFML/Graphics/Transform.hpp
./scene.o: /usr/include/SFML/Graphics/Rect.hpp
./scene.o: /usr/include/SFML/Graphics/Rect.inl
./scene.o: /usr/include/SFML/Graphics/Transformable.hpp
./scene.o: /usr/include/SFML/Graphics/VertexArray.hpp
./scene.o: /usr/include/SFML/Graphics/Vertex.hpp
./scene.o: /usr/include/SFML/Graphics/Color.hpp
./scene.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./scene.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./scene.o: /usr/include/SFML/Graphics/Font.hpp
./scene.o: /usr/include/SFML/Graphics/Glyph.hpp
./scene.o: /usr/include/SFML/Graphics/Texture.hpp
./scene.o: /usr/include/SFML/Graphics/Image.hpp
./scene.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./scene.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./scene.o: /usr/include/SFML/Graphics/View.hpp
./scene.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./scene.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./scene.o: /usr/include/SFML/Graphics/Shader.hpp
./scene.o: /usr/include/SFML/Graphics/Sprite.hpp
./scene.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp /usr/include/stdint.h
./scene.o: /usr/include/features.h /usr/include/stdc-predef.h
./scene.o: enemyController.hpp resourceHandler.hpp ResourcePath.hpp
./scene.o: turret.hpp /usr/include/stdio.h /usr/include/libio.h
./scene.o: /usr/include/_G_config.h /usr/include/wchar.h fontController.hpp
./scene.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./scene.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./scene.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./scene.o: Powerup.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./scene.o: turretShot.hpp scoot.hpp enemy.hpp dasher.hpp critter.hpp
./scene.o: aStar.hpp coordinate.hpp initMapVectors.hpp enemyPlacementFn.hpp
./scene.o: lightingMap.h pillarPlacement.h /usr/include/math.h
./scene.o: enemyCreationFunctions.hpp scene.hpp player.hpp
./scene.o: detailController.hpp Teleporter.hpp detailParent.hpp
./scene.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./scene.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./scene.o: damagedRobot.hpp rock.hpp IntroDoor.hpp soundController.hpp
./scene.o: /usr/include/SFML/Audio.hpp
./scene.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./scene.o: /usr/include/SFML/Audio/Export.hpp
./scene.o: /usr/include/SFML/Audio/Listener.hpp
./scene.o: /usr/include/SFML/Audio/Music.hpp
./scene.o: /usr/include/SFML/Audio/SoundStream.hpp
./scene.o: /usr/include/SFML/Audio/SoundSource.hpp
./scene.o: /usr/include/SFML/Audio/AlResource.hpp
./scene.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./scene.o: /usr/include/SFML/Audio/Sound.hpp
./scene.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./scene.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./scene.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./scene.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./scene.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./scene.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./scene.o: /usr/include/SFML/Audio/SoundFileWriter.hpp backgroundHandler.hpp
./scene.o: screenShakeController.hpp
./enemy.o: enemy.hpp /usr/include/SFML/Graphics.hpp
./enemy.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./enemy.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./enemy.o: /usr/include/SFML/System/Export.hpp
./enemy.o: /usr/include/SFML/System/Time.hpp /usr/include/SFML/System/Err.hpp
./enemy.o: /usr/include/SFML/System/FileInputStream.hpp
./enemy.o: /usr/include/SFML/System/InputStream.hpp
./enemy.o: /usr/include/SFML/System/NonCopyable.hpp
./enemy.o: /usr/include/SFML/System/Lock.hpp
./enemy.o: /usr/include/SFML/System/MemoryInputStream.hpp
./enemy.o: /usr/include/SFML/System/Mutex.hpp
./enemy.o: /usr/include/SFML/System/Sleep.hpp
./enemy.o: /usr/include/SFML/System/String.hpp
./enemy.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./enemy.o: /usr/include/SFML/System/String.inl
./enemy.o: /usr/include/SFML/System/Thread.hpp
./enemy.o: /usr/include/SFML/System/Thread.inl
./enemy.o: /usr/include/SFML/System/ThreadLocal.hpp
./enemy.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./enemy.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./enemy.o: /usr/include/SFML/System/Vector2.hpp
./enemy.o: /usr/include/SFML/System/Vector2.inl
./enemy.o: /usr/include/SFML/System/Vector3.hpp
./enemy.o: /usr/include/SFML/System/Vector3.inl
./enemy.o: /usr/include/SFML/Window/Context.hpp
./enemy.o: /usr/include/SFML/Window/Export.hpp
./enemy.o: /usr/include/SFML/Window/GlResource.hpp
./enemy.o: /usr/include/SFML/Window/ContextSettings.hpp
./enemy.o: /usr/include/SFML/Window/Event.hpp
./enemy.o: /usr/include/SFML/Window/Joystick.hpp
./enemy.o: /usr/include/SFML/Window/Keyboard.hpp
./enemy.o: /usr/include/SFML/Window/Mouse.hpp
./enemy.o: /usr/include/SFML/Window/Sensor.hpp
./enemy.o: /usr/include/SFML/Window/Touch.hpp
./enemy.o: /usr/include/SFML/Window/VideoMode.hpp
./enemy.o: /usr/include/SFML/Window/Window.hpp
./enemy.o: /usr/include/SFML/Window/WindowHandle.hpp
./enemy.o: /usr/include/SFML/Window/WindowStyle.hpp
./enemy.o: /usr/include/SFML/Graphics/BlendMode.hpp
./enemy.o: /usr/include/SFML/Graphics/Export.hpp
./enemy.o: /usr/include/SFML/Graphics/CircleShape.hpp
./enemy.o: /usr/include/SFML/Graphics/Shape.hpp
./enemy.o: /usr/include/SFML/Graphics/Drawable.hpp
./enemy.o: /usr/include/SFML/Graphics/RenderStates.hpp
./enemy.o: /usr/include/SFML/Graphics/Transform.hpp
./enemy.o: /usr/include/SFML/Graphics/Rect.hpp
./enemy.o: /usr/include/SFML/Graphics/Rect.inl
./enemy.o: /usr/include/SFML/Graphics/Transformable.hpp
./enemy.o: /usr/include/SFML/Graphics/VertexArray.hpp
./enemy.o: /usr/include/SFML/Graphics/Vertex.hpp
./enemy.o: /usr/include/SFML/Graphics/Color.hpp
./enemy.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./enemy.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./enemy.o: /usr/include/SFML/Graphics/Font.hpp
./enemy.o: /usr/include/SFML/Graphics/Glyph.hpp
./enemy.o: /usr/include/SFML/Graphics/Texture.hpp
./enemy.o: /usr/include/SFML/Graphics/Image.hpp
./enemy.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./enemy.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./enemy.o: /usr/include/SFML/Graphics/View.hpp
./enemy.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./enemy.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./enemy.o: /usr/include/SFML/Graphics/Shader.hpp
./enemy.o: /usr/include/SFML/Graphics/Sprite.hpp
./enemy.o: /usr/include/SFML/Graphics/Text.hpp wall.hpp /usr/include/stdint.h
./enemy.o: /usr/include/features.h /usr/include/stdc-predef.h
./enemy.o: effectsController.hpp turretFlashEffect.hpp spriteSheet.hpp
./enemy.o: Effect.hpp Framework/framework.hpp Framework/utilities.hpp rng.hpp
./enemy.o: bulletType1.hpp shotPuff.hpp FireExplosion.hpp smallExplosion.hpp
./enemy.o: Powerup.hpp RenderType.hpp enemyShot.hpp dasherShot.hpp
./enemy.o: turretShot.hpp
./aStar.o: aStar.hpp
./wall.o: wall.hpp /usr/include/stdint.h /usr/include/features.h
./wall.o: /usr/include/stdc-predef.h
./rock.o: rock.hpp detailParent.hpp /usr/include/SFML/Graphics.hpp
./rock.o: /usr/include/SFML/Window.hpp /usr/include/SFML/System.hpp
./rock.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./rock.o: /usr/include/SFML/System/Export.hpp
./rock.o: /usr/include/SFML/System/Time.hpp /usr/include/SFML/System/Err.hpp
./rock.o: /usr/include/SFML/System/FileInputStream.hpp
./rock.o: /usr/include/SFML/System/InputStream.hpp
./rock.o: /usr/include/SFML/System/NonCopyable.hpp
./rock.o: /usr/include/SFML/System/Lock.hpp
./rock.o: /usr/include/SFML/System/MemoryInputStream.hpp
./rock.o: /usr/include/SFML/System/Mutex.hpp
./rock.o: /usr/include/SFML/System/Sleep.hpp
./rock.o: /usr/include/SFML/System/String.hpp
./rock.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./rock.o: /usr/include/SFML/System/String.inl
./rock.o: /usr/include/SFML/System/Thread.hpp
./rock.o: /usr/include/SFML/System/Thread.inl
./rock.o: /usr/include/SFML/System/ThreadLocal.hpp
./rock.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./rock.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./rock.o: /usr/include/SFML/System/Vector2.hpp
./rock.o: /usr/include/SFML/System/Vector2.inl
./rock.o: /usr/include/SFML/System/Vector3.hpp
./rock.o: /usr/include/SFML/System/Vector3.inl
./rock.o: /usr/include/SFML/Window/Context.hpp
./rock.o: /usr/include/SFML/Window/Export.hpp
./rock.o: /usr/include/SFML/Window/GlResource.hpp
./rock.o: /usr/include/SFML/Window/ContextSettings.hpp
./rock.o: /usr/include/SFML/Window/Event.hpp
./rock.o: /usr/include/SFML/Window/Joystick.hpp
./rock.o: /usr/include/SFML/Window/Keyboard.hpp
./rock.o: /usr/include/SFML/Window/Mouse.hpp
./rock.o: /usr/include/SFML/Window/Sensor.hpp
./rock.o: /usr/include/SFML/Window/Touch.hpp
./rock.o: /usr/include/SFML/Window/VideoMode.hpp
./rock.o: /usr/include/SFML/Window/Window.hpp
./rock.o: /usr/include/SFML/Window/WindowHandle.hpp
./rock.o: /usr/include/SFML/Window/WindowStyle.hpp
./rock.o: /usr/include/SFML/Graphics/BlendMode.hpp
./rock.o: /usr/include/SFML/Graphics/Export.hpp
./rock.o: /usr/include/SFML/Graphics/CircleShape.hpp
./rock.o: /usr/include/SFML/Graphics/Shape.hpp
./rock.o: /usr/include/SFML/Graphics/Drawable.hpp
./rock.o: /usr/include/SFML/Graphics/RenderStates.hpp
./rock.o: /usr/include/SFML/Graphics/Transform.hpp
./rock.o: /usr/include/SFML/Graphics/Rect.hpp
./rock.o: /usr/include/SFML/Graphics/Rect.inl
./rock.o: /usr/include/SFML/Graphics/Transformable.hpp
./rock.o: /usr/include/SFML/Graphics/VertexArray.hpp
./rock.o: /usr/include/SFML/Graphics/Vertex.hpp
./rock.o: /usr/include/SFML/Graphics/Color.hpp
./rock.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./rock.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./rock.o: /usr/include/SFML/Graphics/Font.hpp
./rock.o: /usr/include/SFML/Graphics/Glyph.hpp
./rock.o: /usr/include/SFML/Graphics/Texture.hpp
./rock.o: /usr/include/SFML/Graphics/Image.hpp
./rock.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./rock.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./rock.o: /usr/include/SFML/Graphics/View.hpp
./rock.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./rock.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./rock.o: /usr/include/SFML/Graphics/Shader.hpp
./rock.o: /usr/include/SFML/Graphics/Sprite.hpp
./rock.o: /usr/include/SFML/Graphics/Text.hpp Framework/framework.hpp
./rock.o: Framework/utilities.hpp spriteSheet.hpp rng.hpp
./main.o: /usr/include/SFML/Audio.hpp /usr/include/SFML/System.hpp
./main.o: /usr/include/SFML/Config.hpp /usr/include/SFML/System/Clock.hpp
./main.o: /usr/include/SFML/System/Export.hpp
./main.o: /usr/include/SFML/System/Time.hpp /usr/include/SFML/System/Err.hpp
./main.o: /usr/include/SFML/System/FileInputStream.hpp
./main.o: /usr/include/SFML/System/InputStream.hpp
./main.o: /usr/include/SFML/System/NonCopyable.hpp
./main.o: /usr/include/SFML/System/Lock.hpp
./main.o: /usr/include/SFML/System/MemoryInputStream.hpp
./main.o: /usr/include/SFML/System/Mutex.hpp
./main.o: /usr/include/SFML/System/Sleep.hpp
./main.o: /usr/include/SFML/System/String.hpp
./main.o: /usr/include/SFML/System/Utf.hpp /usr/include/SFML/System/Utf.inl
./main.o: /usr/include/SFML/System/String.inl
./main.o: /usr/include/SFML/System/Thread.hpp
./main.o: /usr/include/SFML/System/Thread.inl
./main.o: /usr/include/SFML/System/ThreadLocal.hpp
./main.o: /usr/include/SFML/System/ThreadLocalPtr.hpp
./main.o: /usr/include/SFML/System/ThreadLocalPtr.inl
./main.o: /usr/include/SFML/System/Vector2.hpp
./main.o: /usr/include/SFML/System/Vector2.inl
./main.o: /usr/include/SFML/System/Vector3.hpp
./main.o: /usr/include/SFML/System/Vector3.inl
./main.o: /usr/include/SFML/Audio/InputSoundFile.hpp
./main.o: /usr/include/SFML/Audio/Export.hpp
./main.o: /usr/include/SFML/Audio/Listener.hpp
./main.o: /usr/include/SFML/Audio/Music.hpp
./main.o: /usr/include/SFML/Audio/SoundStream.hpp
./main.o: /usr/include/SFML/Audio/SoundSource.hpp
./main.o: /usr/include/SFML/Audio/AlResource.hpp
./main.o: /usr/include/SFML/Audio/OutputSoundFile.hpp
./main.o: /usr/include/SFML/Audio/Sound.hpp
./main.o: /usr/include/SFML/Audio/SoundBuffer.hpp
./main.o: /usr/include/SFML/Audio/SoundBufferRecorder.hpp
./main.o: /usr/include/SFML/Audio/SoundRecorder.hpp
./main.o: /usr/include/SFML/Audio/SoundFileFactory.hpp
./main.o: /usr/include/SFML/Audio/SoundFileFactory.inl
./main.o: /usr/include/SFML/Audio/SoundFileReader.hpp
./main.o: /usr/include/SFML/Audio/SoundFileWriter.hpp
./main.o: /usr/include/SFML/Graphics.hpp /usr/include/SFML/Window.hpp
./main.o: /usr/include/SFML/Window/Context.hpp
./main.o: /usr/include/SFML/Window/Export.hpp
./main.o: /usr/include/SFML/Window/GlResource.hpp
./main.o: /usr/include/SFML/Window/ContextSettings.hpp
./main.o: /usr/include/SFML/Window/Event.hpp
./main.o: /usr/include/SFML/Window/Joystick.hpp
./main.o: /usr/include/SFML/Window/Keyboard.hpp
./main.o: /usr/include/SFML/Window/Mouse.hpp
./main.o: /usr/include/SFML/Window/Sensor.hpp
./main.o: /usr/include/SFML/Window/Touch.hpp
./main.o: /usr/include/SFML/Window/VideoMode.hpp
./main.o: /usr/include/SFML/Window/Window.hpp
./main.o: /usr/include/SFML/Window/WindowHandle.hpp
./main.o: /usr/include/SFML/Window/WindowStyle.hpp
./main.o: /usr/include/SFML/Graphics/BlendMode.hpp
./main.o: /usr/include/SFML/Graphics/Export.hpp
./main.o: /usr/include/SFML/Graphics/CircleShape.hpp
./main.o: /usr/include/SFML/Graphics/Shape.hpp
./main.o: /usr/include/SFML/Graphics/Drawable.hpp
./main.o: /usr/include/SFML/Graphics/RenderStates.hpp
./main.o: /usr/include/SFML/Graphics/Transform.hpp
./main.o: /usr/include/SFML/Graphics/Rect.hpp
./main.o: /usr/include/SFML/Graphics/Rect.inl
./main.o: /usr/include/SFML/Graphics/Transformable.hpp
./main.o: /usr/include/SFML/Graphics/VertexArray.hpp
./main.o: /usr/include/SFML/Graphics/Vertex.hpp
./main.o: /usr/include/SFML/Graphics/Color.hpp
./main.o: /usr/include/SFML/Graphics/PrimitiveType.hpp
./main.o: /usr/include/SFML/Graphics/ConvexShape.hpp
./main.o: /usr/include/SFML/Graphics/Font.hpp
./main.o: /usr/include/SFML/Graphics/Glyph.hpp
./main.o: /usr/include/SFML/Graphics/Texture.hpp
./main.o: /usr/include/SFML/Graphics/Image.hpp
./main.o: /usr/include/SFML/Graphics/RectangleShape.hpp
./main.o: /usr/include/SFML/Graphics/RenderTarget.hpp
./main.o: /usr/include/SFML/Graphics/View.hpp
./main.o: /usr/include/SFML/Graphics/RenderTexture.hpp
./main.o: /usr/include/SFML/Graphics/RenderWindow.hpp
./main.o: /usr/include/SFML/Graphics/Shader.hpp
./main.o: /usr/include/SFML/Graphics/Sprite.hpp
./main.o: /usr/include/SFML/Graphics/Text.hpp player.hpp tileController.hpp
./main.o: wall.hpp /usr/include/stdint.h /usr/include/features.h
./main.o: /usr/include/stdc-predef.h enemyController.hpp resourceHandler.hpp
./main.o: ResourcePath.hpp turret.hpp /usr/include/stdio.h
./main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
./main.o: fontController.hpp effectsController.hpp turretFlashEffect.hpp
./main.o: spriteSheet.hpp Effect.hpp Framework/framework.hpp
./main.o: Framework/utilities.hpp rng.hpp bulletType1.hpp shotPuff.hpp
./main.o: FireExplosion.hpp smallExplosion.hpp Powerup.hpp RenderType.hpp
./main.o: enemyShot.hpp dasherShot.hpp turretShot.hpp scoot.hpp enemy.hpp
./main.o: dasher.hpp critter.hpp aStar.hpp coordinate.hpp
./main.o: detailController.hpp Teleporter.hpp detailParent.hpp
./main.o: treasureChest.hpp inputController.hpp generalDetail.hpp
./main.o: lampLight.hpp userInterface.hpp easingTemplates.hpp
./main.o: damagedRobot.hpp rock.hpp IntroDoor.hpp soundController.hpp
./main.o: backgroundHandler.hpp scene.hpp screenShakeController.hpp
