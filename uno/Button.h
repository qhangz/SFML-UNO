#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
using namespace sf;

class Button :public Sprite {     //�̳�SFML��Sprite��
public:
	enum BtnState {
		NORMAL, HOVER, CLICK, RELEASE
	};
	int btnState;
	Texture tNormal;            //���ֲ�ͬ״̬������
	Texture tHover;
	Texture tClick;
	int CheckMouse(Vector2i, Event);	//������״̬
	int CheckMouse1(Vector2i, Event);
	void SetTextures(Texture, Texture);                    //������������״̬
	void SetTextures(Texture, Texture, Texture);        //������������״̬
	void SetState(int);
	void Offset(double, double);
};