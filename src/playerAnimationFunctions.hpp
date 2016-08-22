//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once

//Decodes the horizontal movement based on the input (animation sprites are not in sequence, and I reused some of them). It's long, so we dont want this in the player object
inline uint8_t horizontalAnimationDecoder(uint8_t index) {
	switch(index) {
		case 0:
			return 0;
			break;
			
		case  1:
			return 1;
			break;
			
		case 2:
			return 2;
			break;
			
		case 3:
			return 3;
			break;
			
		case 4:
			return 4;
			break;
			
		case 5:
			return 5;
			break;
			
		default:
			return 0;
			break;
	}
}

inline uint8_t verticalAnimationDecoder(uint8_t index) {
	switch(index) {
		case 0:
			return 1;
			break;
			
		case  1:
			return 2;
			break;
			
		case 2:
			return 2;
			break;
			
		case 3:
			return 1;
			break;
			
		case 4:
			return 0;
			break;
			
		case 5:
			return 3;
			break;
			
		case 6:
			return 4;
			break;
			
		case 7:
			return 4;
			break;
			
		case 8:
			return 3;
			break;
			
		case 9:
			return 0;
			break;
			
		default:
			return 0;
			break;
	}
}
