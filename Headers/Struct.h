#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;
	//D3DXVECTOR2; 
	//D3DXVECTOR4; //x,y,z,w
}INFO;

typedef struct tagObjInfo {
	tagObjInfo(int _hp, int _atk, float _spd, float _agl) :hp(_hp), atk(_atk),spd(_spd), agl(_agl) {

	}
	int hp;
	int atk;
	float spd;
	float agl;
}OBJINFO;
//ddd

typedef struct tagLinePos
{
	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _x, float _y) : fX(_x), fY(_y) {}

	float	fX;
	float	fY;
}LINEPOS;
typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeftPos, LINEPOS& _tRightPos)
		: tLeftPos(_tLeftPos), tRightPos(_tRightPos) {}

	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;
}LINEINFO;
#endif // !__STRUCT_H__
