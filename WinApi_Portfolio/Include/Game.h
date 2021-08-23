#pragma once
// 모든 기능을 포함시킵니다.

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <math.h>
#include <functional>
#include <time.h>
#include "Sound/fmod.hpp"

#pragma comment(lib, "msimg32")
#pragma comment(lib, "fmod_vc")
//#pragma comment(lib, "fmod64_vc")

using namespace FMOD;
using namespace std;


#include "resource.h"
#include "Defines.h"
#include "Flag.h"
#include "Struct.h"


template <typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

template<typename T>
void Safe_Release_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE(iter->second);
	}

	p.clear();
}

template<typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	p.clear();
}

template<typename T>
void Safe_Release_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	p.clear();
}