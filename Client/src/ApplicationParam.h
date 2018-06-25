#pragma once

#include <wtypes.h>

enum class EWindowStatus: char
{
	normalWindow,	//��ͨ����
	maxWindow,		//��󻯴���
	fullWindow,	//����ģʽȫ��
	fullScreen	//�Ǵ���ģʽȫ��
};

//��ʼ��Application����Ĳ����ṹ
struct SApplicationParam
{
	LPCTSTR wndClassName;
	LPCTSTR title;

	UINT width;
	UINT height;

	EWindowStatus windowStatus;
};