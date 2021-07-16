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
	tagObjInfo(int _hp, int _atk,int _score, float _spd, float _agl) :hp(_hp), atk(_atk),spd(_spd), agl(_agl),score(_score) {

	}
	int hp;
	int atk;
	int score;
	float spd;
	float agl;

}OBJINFO;
//ddd
typedef struct tagGravity {
	tagGravity(float _p,float _t,float _y,bool _j,bool _g)
	:m_fJumpPower(_p),m_fJumpTime(_t),m_fJumpY(_y),m_bJump(_j),m_bg(_g){

	}
	float		m_fJumpPower;
	float		m_fJumpTime;
	float		m_fJumpY;
	bool		m_bJump;
	bool		m_bg;
}GRAVITY;
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

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImageInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	DWORD dwDrawID;
	DWORD dwOption;
}TILE;
#endif // !__STRUCT_H__
