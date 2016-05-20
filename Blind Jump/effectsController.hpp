//
//  effectsController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef effectsController_hpp
#define effectsController_hpp

#include <stdio.h>
#include "SFML/graphics.hpp"
#include "turretFlashEffect.hpp"
#include "bulletType1.hpp"
#include "shotPuff.hpp"
#include "turretShot.hpp"
#include "explosion32effect.hpp"
#include "teleporterSmoke.hpp"
#include "enemyShot.hpp"
#include "dasherShot.hpp"
#include "healthEffect.hpp"
#include "fontController.hpp"
#include "energyBeam.hpp"
#include "dashSmoke.hpp"
#include "FireExplosion.hpp"
#include "smallExplosion.hpp"
#include "Powerup.hpp"
#include "ResourcePath.hpp"
#include "RenderType.hpp"

class ScreenShakeController;

class effectsController {
private:
    sf::Texture powerupTxtr[2];
    sf::Sprite powerupSpr[2];
    sf::Texture blueExplosionTxtr[9];
    sf::Sprite blueExplosionSpr[9];
    sf::Sprite smallExplosionSpr[6];
    sf::Texture smallExplosionTxtr[6];
    sf::Texture fireExplosionGlowTxtr;
    sf::Sprite fireExplosionGlowSpr;
    sf::Texture blueFireGlowTxtr;
    sf::Sprite blueFireGlowSpr;
    sf::Sprite fireExplosionSpr[9];
    sf::Texture fireExplosionTxtr[9];
    sf::Sprite dashSmokeSprites[8];
    sf::Texture dashSmokeTextures[8];
    sf::Sprite energyBeamSprites[6];
    sf::Texture energyBeamTextures[6];
    sf::Sprite turretFlashSprites[5];
    sf::Texture turretFlashTextures[5];
    sf::Sprite redGlowSprite;
    sf::Texture redGlowTexture;
    sf::Sprite blueGlowSprite;
    sf::Texture blueGlowTexture;
    sf::Sprite orbShotSprites[4];
    sf::Texture orbShotTextures[4];
    sf::Sprite bubbleShotSpr[2];
    sf::Texture bubbleShotTex[2];
    sf::Sprite bulletSprites[3];
    sf::Texture bulletTexture[2];
    sf::Texture bulletGlow[1];
    sf::Sprite puffSprites[4];
    sf::Texture puffTexture[4];
    sf::Texture exp32Texture[6];
    sf::Sprite exp32Sprites[6];
    sf::Sprite warpEffectSprites[6];
    sf::Texture warpEffectTextures[6];
    sf::Sprite smokeSprites[6];
    sf::Texture smokeTextures[6];
    sf::Sprite healthEffectSprites[5];
    sf::Texture healthEffectTextures[5];
    sf::Sprite dasherShotSprites[2];
    sf::Texture dasherShotTextures[2];
    sf::Texture newItemText;
    sf::Sprite newItemSpr;
    sf::Texture healthRestoredTex;
    sf::Sprite healthRestoredSpr;
    std::vector<SmallExplosion> smallExplosions;
    std::vector<EnergyBeam> energyBeams;
    std::vector<FireExplosion> fireExplosions;
    std::vector<Enemyshot> enemyShots;
    std::vector<turretFlashEffect> turretFlashes;
    std::vector<bulletType1> bullets;
    std::vector<shotPuff> puffs;
    std::vector<bulletType1> bulletLowerLayer;
    std::vector<turretShot> turretShots;
    std::vector<TeleporterSmoke> warpEffects;
    std::vector<DashSmoke> dodgeEffects;
    sf::Texture turretShotText[2];
    sf::Sprite turretShotSpr[2];
    std::vector<Explosion32effect> bigExplosions;
    std::vector<HealthEffect> healthEffects;
    std::vector<DasherShot> dasherShots;
    std::vector<sf::Sprite*> glowSprs;
    std::vector<sf::Sprite*> glowSprs2;
    std::vector<Powerup> hearts;
    std::vector<Powerup> coins;
    
public:
    effectsController();
    void draw(sf::RenderTexture&, std::vector<std::tuple<sf::Sprite, float, Rendertype>>&);
    void update(float, float, ScreenShakeController*, sf::Time &);
    void addTurretFlash(float, float);
    void addBullet(bool, char, float, float);
    void drawLower(sf::RenderTexture&);
    void clear();
    void addDodgeEffect(float, float, int, int);
    void addTurretShot(float, float, short);
    void addDasherShot(float, float, short);
    void addScootShot(float, float, short, float, float);
    void addWarpEffect(float, float);
    void addFireExplosion(float, float);
    void addBlueExplosion(float, float);
    void addExplosion(float, float);
    void addHealthEffect(float, float);
    void addSmallExplosion(float, float);
    void addHearts(float, float);
    void addCoins(float, float);
    void addPlayerHealthEffect(float, float, float, float);
    void addLvP1(float, float, FontController& font);
    void addLvP3(float, float, FontController& font);
    void addLvP30(float, float, FontController& font);
    void addLvP10(float, float, FontController& font);
    void addHpRestored(float, float);
    void addNewItem(float, float, FontController& font);
    void addPuff(float, float);
    void addEnergyBeam(float, float, float, float);
    void addMissile(float, float);
    void addOrbshotTrail(float, float);
    void addEnemyShot(float, float, short);
    void addOrbShot(unsigned char, float, float, float, float);
    std::vector<bulletType1>& getBulletLayer1();
    std::vector<bulletType1>& getBulletLayer2();
    void addSmokeEffect(float, float);
    // Now accessor functions for the class' private member datafields
    std::vector<Enemyshot>* getEnemyShots();
    std::vector<Powerup>* getHearts();
    std::vector<Powerup>* getCoins();
    std::vector<turretShot>* getTurretShots();
    std::vector<DasherShot>* getDasherShots();
    std::vector<sf::Sprite*>* getGlowSprs();
    std::vector<sf::Sprite*>* getGlowSprs2();
    std::vector<FireExplosion>* getExplosions();
    void condClearGlowSpr(sf::Sprite*);
};

#endif /* effectsController_hpp */
