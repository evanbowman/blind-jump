//
//  GradientCircle.hpp
//  gradientCircleTest
//
//  Created by Evan Bowman on 5/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef GradientCircle_hpp
#define GradientCircle_hpp

#include "SFML/Graphics.hpp"

class GradientCircle : public sf::Drawable {
private:
    sf::VertexArray vertices;
    float radius, xPos, yPos;
    virtual void draw(sf::RenderTarget& target, const sf::RenderStates states) const;
    
public:
    GradientCircle();
    void setCenterColor(const sf::Color);
    void setOuterColor(const sf::Color);
    sf::Color getCenterColor() const;
    sf::Color getOuterColor() const;
    void setRadius(float);
    float getRadius() const;
    void setPosition(float, float);
    void setPointCount(int);
};

#endif /* GradientCircle_hpp */
