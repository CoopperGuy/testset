#pragma once

#ifndef __CPLAYER_H__
#define __CPLAYER_H__
//현재 만들어야 되는거
//점수,라이프,무기 스왑?

#define MAX_INVEN 5

#include "Obj.h"
#include "Item.h"
class CPlayer :
	public CObj
{
public:
	enum BULLETTYPE{ BULLET_MELEE,BULLET_NORMAL,BULLET_GUIDE,BULLET_END};
	typedef struct tagBullet {
		tagBullet(int _c,int _m,BULLETTYPE _id , DWORD _pd)
			: cur_magazine(_c),max_magazine(_m),BulletID(_id),PatternDelay(_pd){
		}
		tagBullet operator+(tagBullet b1) {
			BulletID = b1.BulletID;
			cur_magazine += b1.cur_magazine;
			if (cur_magazine > max_magazine)
				cur_magazine = max_magazine;
			PatternDelay = b1.PatternDelay;
			return *this;
		}
		int cur_magazine;
		int max_magazine;
		BULLETTYPE BulletID;
		DWORD PatternDelay;

	}BULLET;
private:
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	void Jumping();
	void Drop();
	void Offset();
	void Shut_Bullet();
public:
	CPlayer::BULLET getItemType(CItem::ITEMTAG _tag);
public:
	void Set_Point(int _point) { m_tObjInfo.score += _point; }
	void Set_Bullet(CItem::ITEMTAG _tag);
	void Set_Immortal() { isImmortal = true; ImmortalTime = GetTickCount(); }
public:
	int Get_Point() { return m_tObjInfo.score; }
	bool Get_Immortal() { return isImmortal; }
	const vector<BULLET>& Get_Inven()const { return Inven; }
public:
	static CObj* Create();
private:
	template<typename T>
	CObj* Create_Bullet(int _y)
	{
		CObj* pobj = new T;
		
		return pobj;
	}
private:
	GRAVITY m_tG;
	vector<BULLET> Inven;	
	DWORD PatternTime;
	DWORD ImmortalTime;
	DWORD ImmortalDelay=400;
	int cur_Weapon;
	bool isImmortal = false;
	//test
};


#endif // !__CPLAYER_H__
