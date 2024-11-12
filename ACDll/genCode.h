#pragma once
#include <stdint.h>

class Vector3 {
public:
	float x;
	float z;
	float y;
};

class Player
{
public:
	Vector3 headposition; //0x0004
	Vector3 velocity; //0x0010
	Vector3 N00000052; //0x001C
	Vector3 position; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	float roll; //0x003C
	char pad_0040[172]; //0x0040
	int32_t health; //0x00EC
	char pad_00F0[236]; //0x00F0
	int32_t kills; //0x01DC
	char pad_01E0[4]; //0x01E0
	int32_t deaths; //0x01E4
	char pad_01E8[29]; //0x01E8
	char name[16]; //0x0205
	char pad_0215[335]; //0x0215
	class weapon* currweapon; //0x0364

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x0368

class weapon
{
public:
	char pad_0000[20]; //0x0000
	class ammoclip* ammoptr; //0x0014
}; //Size: 0x0018

class ammoclip
{
public:
	int32_t ammo; //0x0000
}; //Size: 0x0004

class EntityList{
public:
	Player* players[64];
};