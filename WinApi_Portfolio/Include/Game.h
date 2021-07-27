#pragma once
// 모든 기능을 포함시킵니다.

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <list>
#include <unordered_map>
#include <vector>
#include "Defines.h"
#include "Struct.h"
#include "Flag.h"
#include <string>
#include "resource.h"

using namespace std;


template<typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter; 
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->Second);
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
		SAFE_RELEASE(iter->Second);
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