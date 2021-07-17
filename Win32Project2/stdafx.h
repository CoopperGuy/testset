// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <typeinfo>
using namespace std;


#include "d3d9.h"
#pragma comment(lib ,"d3d9.lib")
#include "d3dx9.h"
#pragma comment(lib ,"d3dx9.lib")

#include "../Headers/Include.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
