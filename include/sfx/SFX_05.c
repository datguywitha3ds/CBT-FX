/*

	SFX_05

	Sound Effect File.

	Info:
		Length			:	16
		Bank			:	0
		Priority		:	0
		Channels used	:	Duty channel 2 & Noise channel

	This file was generated by hammer2cbt

*/
#define SFX_05_Length 16
#define SFX_05_Bank 0
#define SFX_05_CH_Used 255
#define SFX_05_Priority 0
#define CBTFX_PLAY_SFX_05 CBTFX_init(&SFX_05[0][0], 16, 0, 255)
#include "../cbtfx.h"

const unsigned char SFX_05[16][CBTFX_LENGTH] = {
	CBTFX_FRAME(1, 17, 15, 2, FX_E_1, 17, 15, 80),
	CBTFX_FRAME(3, 17, 15, 2, FX_C_1, 17, 15, 128),
	CBTFX_FRAME(1, 17, 15, 2, FX_As0, 17, 15, 48),
	CBTFX_FRAME(2, 17, 15, 2, FX_Gs0, 17, 15, 96),
	CBTFX_FRAME(3, 17, 15, 2, FX_Fs0, 17, 15, 112),
	CBTFX_FRAME(2, 17, 15, 2, FX_F_0, 17, 15, 64),
	CBTFX_FRAME(4, 17, 15, 2, FX_E_0, 17, 10, 96),
	CBTFX_FRAME(2, 17, 15, 2, FX_Ds0, 17, 12, 112),
	CBTFX_FRAME(2, 17, 8, 2, FX_D_0, 17, 8, 80),
	CBTFX_FRAME(2, 17, 4, 2, FX_Cs0, 17, 4, 32),
	CBTFX_FRAME(2, 17, 1, 2, FX_C_0, 17, 5, 80),
	CBTFX_FRAME(2, 0, 0, 0, FX_E_3, 17, 5, 64),
	CBTFX_FRAME(4, 0, 0, 0, FX_E_3, 17, 3, 48),
	CBTFX_FRAME(5, 0, 0, 0, FX_E_3, 17, 2, 32),
	CBTFX_FRAME(7, 0, 0, 0, FX_E_3, 17, 1, 32)
};