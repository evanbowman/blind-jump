#pragma once
#ifndef TEXTUREENUM_HPP
#define TEXTUREENUM_HPP

enum class Texture {
		vignette,
			vignetteShadow,
			lamplight,
			introLevel,
			playerShadow,
			playerDown,
			playerUp = playerDown + 6,
			playerLeft = playerUp + 6,
			playerRight = playerLeft + 7,
			playerDash = playerRight + 7,
			playerDeath = playerDash + 12,
			};

#endif
