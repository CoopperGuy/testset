#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1



#define ERR_MSG(message)					\
MessageBox(nullptr, message, L"System Error", MB_OK);

#define DECLARE_SINGLETON(className)						\
public:														\
static className* Get_Instance()							\
{															\
	if (!m_pInstance)										\
		m_pInstance = new className;						\
	return m_pInstance;										\
}															\
static void Destroy_Instance()								\
{															\
	if (m_pInstance)										\
	{														\
		delete m_pInstance;									\
		m_pInstance = nullptr;								\
	}														\
}															\
private:													\
	static className* m_pInstance;							
#define IMPLEMENT_SINGLETON(ClassName)						\
ClassName* ClassName::m_pInstance = nullptr; 

#endif // !__DEFINE_H__
