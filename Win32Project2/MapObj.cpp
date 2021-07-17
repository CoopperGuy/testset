#include "stdafx.h"
#include "MapObj.h"


CMapObj::CMapObj()
	:m_iDrawID(0)
{
}


CMapObj::~CMapObj()
{
}

void CMapObj::Set_Animation(int _StartID, int _EndID, bool _bReset)
{
	if (_bReset)
	{
		if (m_iDrawID < _EndID)
			++m_iDrawID;
		else
			m_iDrawID = _StartID;
	}
	else
	{
		if (m_iDrawID < _EndID)
			++m_iDrawID;
	}

}
