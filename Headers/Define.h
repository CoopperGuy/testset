#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1


#endif // !__DEFINE_H__
