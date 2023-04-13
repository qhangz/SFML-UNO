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
	int checkMouse(Vector2i, Event);	//������״̬
	int checkMouse1(Vector2i, Event);
	void setTextures(Texture, Texture);                    //������������״̬
	void setTextures(Texture, Texture, Texture);        //������������״̬
	void setState(int);
	void offset(double, double);
};

