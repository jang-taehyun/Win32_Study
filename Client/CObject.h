#pragma once

/**
* Object
* - Object가 가져야되는 기본 정보 : 위치, 크기
*/

class CObject
{
public:
	POINT m_ptPos;
	POINT m_ptScale;

public:
	CObject();
	~CObject();
};

