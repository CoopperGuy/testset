#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__


namespace OBJID
{
	enum ID { PLAYER, PLAYERBULLET, MONSTER, BOSSBULLET, BOSSTHROW, ITEM, MAPOBJ, END };
}
namespace UIID {
	enum ID{ MENUUI, STAGEUI, OVERUI, END};
}
namespace EDITID
{
	enum ID {TILE0, TILE1, TILE2, LINE, PLAYER, NORMAL_MONSTER, JUMP_MONSTER, BOSS, MONSTERDEL,
		PITEM, GUNITEM, GUIDEITEM, ITEMDEL,
		MAPSWORD, MAPMOVETRI, MAPTRI, MAPTOTEM, MAPDEL, END };
}
#endif // !__ENUM_H__
