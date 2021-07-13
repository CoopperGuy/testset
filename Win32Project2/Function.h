#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template<class T>
void Safe_Delete(T& rObj)
{
	if (rObj)
	{
		delete rObj;
		rObj = nullptr;
	}
}

#endif // !__FUNCTION_H__
