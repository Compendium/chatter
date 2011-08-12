#ifndef _INPUT_HPP
#define _INPUT_HPP

#include <iostream>
#include <SDL/SDL.h>

class Input
{
	public:
	enum Key
	{
		/*//alphabet
		kA,	kB,	kC,	kD,	kE,	kF,	kG,	kH,	kI,	kJ,	kK,	kL,	kM,	kN,	kO,	kP,	kQ,	kR,	kS,	kT,	kU,	kV,	kW,	kX,	kY,	kZ,
		//numeric
		k0,	k1,	k2,	k3,	k4,	k5,	k6,	k7,	k8,	k9,
		//command keys
		kEnter, kBackspace, kTab, kLShift, kRShift, kEscape
		*/

		//alphabet
		kA = SDLK_a,
		kB = SDLK_b,
		kC = SDLK_c,
		kD = SDLK_d,
		kE = SDLK_e,
		kF = SDLK_f,
		kG = SDLK_g,
		kH = SDLK_h,
		kI = SDLK_i,
		kJ = SDLK_j,
		kK = SDLK_k,
		kL = SDLK_l,
		kM = SDLK_m,
		kN = SDLK_n,
		kO = SDLK_o,
		kP = SDLK_p,
		kQ = SDLK_q,
		kR = SDLK_r,
		kS = SDLK_s,
		kT = SDLK_t,
		kU = SDLK_u,
		kV = SDLK_v,
		kW = SDLK_w,
		kX = SDLK_x,
		kY = SDLK_y,
		kZ = SDLK_z,

		//numeric
		k0 = SDLK_0,
		k1 = SDLK_1,
		k2 = SDLK_2,
		k3 = SDLK_3,
		k4 = SDLK_4,
		k5 = SDLK_5,
		k6 = SDLK_6,
		k7 = SDLK_7,
		k8 = SDLK_8,
		k9 = SDLK_9,

		//command keys
		kEnter = SDLK_RETURN,
		kBackspace = SDLK_BACKSPACE,
		kTab = SDLK_TAB,
		kLShift = SDLK_LSHIFT,
		kRShift = SDLK_RSHIFT
	};

	public:
	Input();
	~Input();

	/* Text mode stuff */
	void enableTextmode();	//keyboard layout translation for example from standard QWERTY to DVORAK, so the user can type in his favourite layout
	void disableTextmode();
	unsigned char getChar();
	/* --------------- */

	int refresh();
	bool isPressed(Key k);
	bool isReleased(Key k);

	bool closeRequested();
	//#ifdef USE_SDL
	const unsigned char* getKeyState();
	//#endif

	private:
	bool close_requested;		
	bool textmode;

	//#ifdef USE_SDL
	SDL_Event event;
	unsigned char* keystate;
	//#endif
};


#endif