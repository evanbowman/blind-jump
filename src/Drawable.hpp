#pragma once

#include "GfxContext.hpp"
#include "framework/framework.hpp"
#include <type_traits>

template <size_t margin = 128, typename T>
bool isWithinView(const T & target, const sf::View & view) {
    const sf::Vector2f targetPos = target.getPosition();
    const sf::Vector2f viewCenter = view.getCenter();
    const sf::Vector2f viewSize = view.getSize();
    if (targetPos.x > viewCenter.x - viewSize.x / 2 - margin &&
        targetPos.x < viewCenter.x + viewSize.x / 2 + margin &&
        targetPos.y > viewCenter.y - viewSize.y / 2 - margin &&
        targetPos.y < viewCenter.y + viewSize.y / 2 + margin) {
        return true;
    }
    return false;
}

struct ForceMain {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.targetRef->draw(ct.getSprite());
    }
};

struct ForceShadow {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.targetRef->draw(ct.getShadow());
    }
};

struct DrawMainRaw {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.faces.emplace_back(ct.getSprite(),
                               ct.getPosition().y + CallerType::drawOffset,
                               Rendertype::shadeNone, 0.f);
    }
};

struct DrawMain {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.faces.emplace_back(ct.getSprite(),
                               ct.getPosition().y + CallerType::drawOffset,
                               Rendertype::shadeDefault, 0.f);
    }
};

struct DrawShadow {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.shadows.emplace_back(ct.getShadow(), 0.f, Rendertype::shadeNone,
                                 0.f);
    }
};

struct DrawGlowFloor {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.glowSprs1.push_back(ct.getGlow());
    }
};

struct DrawGlowAll {
    using value_type = int;
    template <typename CallerType> void run(CallerType & ct, GfxContext & gfx) {
        gfx.glowSprs1.push_back(ct.getGlow());
        gfx.glowSprs2.push_back(ct.getGlow());
    }
};

template <typename T> struct Wrapper {
    typedef T wrappedType;
    typedef typename wrappedType::value_type value_type;
    wrappedType wrapee;
    Wrapper() : wrapee{} {}
};

template <typename... Args> struct RenderPolicy : public Wrapper<Args>... {
    RenderPolicy() : Wrapper<Args>{}... {}
    template <typename CallerType>
    void draw(const CallerType & ct, GfxContext & gfxContext,
              const sf::View & view) {
        if (isWithinView(ct, view)) {
            call<CallerType, Args...>(ct, gfxContext);
        }
    }
    template <typename CallerType, typename T, typename... Ts>
    void call(const CallerType & ct, GfxContext & gfxContext) {
        Wrapper<T>::wrapee.run(ct, gfxContext);
        call<CallerType, Ts...>(ct, gfxContext);
    }
    template <typename CallerType, typename... Ts>
    auto call(const CallerType &, GfxContext &) ->
        typename std::enable_if<sizeof...(Ts) == 0>::type {}
};

template <typename Base, typename DrawPolicy>
class Drawable : private DrawPolicy {
public:
    void draw(GfxContext & gfxContext, const sf::View & view) {
        DrawPolicy::draw(*static_cast<Base *>(this), gfxContext, view);
    }
};
