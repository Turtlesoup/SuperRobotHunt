#ifndef COLLISION_LAYERS_H
#define COLLISION_LAYERS_H

enum COLLISION_LAYERS
{
	NO_LAYER = 0x000,
	LAYER_1 = 0x001,
	LAYER_2 = 0x002,
	LAYER_3 = 0x004,
	LAYER_4 = 0x008,
	LAYER_5 = 0x010,
	LAYER_6 = 0x020,
	LAYER_7 = 0x040,
	LAYER_8 = 0x080,
	LAYER_9 = 0x100,
	LAYER_10 = 0x200,
	LAYER_11 = 0x400,
	LAYER_12 = 0x800
};

inline COLLISION_LAYERS operator<< (COLLISION_LAYERS a, COLLISION_LAYERS b)
{
	return static_cast<COLLISION_LAYERS>(static_cast<int>(a) << static_cast<int>(b));
}

inline COLLISION_LAYERS operator>> (COLLISION_LAYERS a, COLLISION_LAYERS b)
{
	return static_cast<COLLISION_LAYERS>(static_cast<int>(a) >> static_cast<int>(b));
}

inline COLLISION_LAYERS operator~ (COLLISION_LAYERS a)
{
	return (COLLISION_LAYERS)~(int)a;
}

inline COLLISION_LAYERS operator| (COLLISION_LAYERS a, COLLISION_LAYERS b)
{
	return static_cast<COLLISION_LAYERS>(static_cast<int>(a) | static_cast<int>(b));
}

inline COLLISION_LAYERS operator& (COLLISION_LAYERS a, COLLISION_LAYERS b)
{
	return static_cast<COLLISION_LAYERS>(static_cast<int>(a) & static_cast<int>(b));
}

inline COLLISION_LAYERS operator^ (COLLISION_LAYERS a, COLLISION_LAYERS b)
{
	return (COLLISION_LAYERS)((int)a ^ (int)b);
}

inline COLLISION_LAYERS& operator|= (COLLISION_LAYERS& a, COLLISION_LAYERS b)
{
	return (COLLISION_LAYERS&)((int&)a |= (int)b);
}

inline COLLISION_LAYERS& operator&= (COLLISION_LAYERS& a, COLLISION_LAYERS b)
{
	return (COLLISION_LAYERS&)((int&)a &= (int)b);
}

inline COLLISION_LAYERS& operator^= (COLLISION_LAYERS& a, COLLISION_LAYERS b)
{
	return (COLLISION_LAYERS&)((int&)a ^= (int)b);
}

#endif