#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
using namespace sf;

class Button :public Sprite {     //继承SFML的Sprite类
public:
	enum BtnState {
		NORMAL, HOVER, CLICK, RELEASE
	};
	int btnState;
	Texture tNormal;            //三种不同状态的纹理
	Texture tHover;
	Texture tClick;
	int checkMouse(Vector2i, Event);	//检查鼠标状态
	int checkMouse1(Vector2i, Event);
	void setTextures(Texture, Texture);                    //加载纹理，两种状态
	void setTextures(Texture, Texture, Texture);        //加载纹理，三种状态
	void setState(int);
	void offset(double, double);
};

