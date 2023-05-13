#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
int btnState;
#include "Button.h"

void Button::SetTextures(Texture _tNormal, Texture _tClick) {
	tNormal = _tNormal;
	tClick = _tClick;
	setTexture(tNormal);        //默认加载普通纹理
}
void Button::SetTextures(Texture _tNormal, Texture _tHover, Texture _tClick) {
	tNormal = _tNormal;
	tHover = _tHover;
	tClick = _tClick;
	setTexture(tNormal);        //默认加载普通纹理    
}
void Button::SetState(int state) {
	btnState = state;
	switch (btnState) {
	case 0:
		setTexture(tNormal); break;
	case 1:
		setTexture(tHover); break;
	case 2:
		setTexture(tClick); break;
	case 3:
		setTexture(tNormal); break;
	default:
		break;
	}
}
int Button::CheckMouse(Vector2i mouse, Event event) {
	//判断鼠标是不是在按钮内，前提是放正的矩形，一般情况下都是这样，如果是奇形怪状的需要再写别的方法
	if ((mouse.x > getPosition().x && mouse.x < getPosition().x + getTexture()->getSize().x) &&
		(mouse.y > getPosition().y && mouse.y < getPosition().y + getTexture()->getSize().y)) {
		if (event.type == Event::EventType::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {            //如果在范围里按下左键，一定是CLICK状态                                                                                //如果按下左建时
			SetState(CLICK);
		}
		else if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {    //如果范围内释放左键，
			if (btnState == CLICK) {                                                                                    //如果之前是CLICK状态，那么就是RELEASE状态，表示按下
				SetState(RELEASE);                                                                                        //否则的话什么也不干
			}
		}
		else {                                                                                                        //如果鼠标移动的话，检测是不是按着的，不是就表示HOVER状态咯
			if (btnState != CLICK) {
				SetState(HOVER);
			}
		}
	}
	else {                                                                                                            //鼠标在按钮范围外
		if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {            //在范围外释放鼠标左键
			SetState(NORMAL);                                                                                            //回归NORMAL状态
		}
		else if (btnState == HOVER) {                                                                                    //如果是HOVER，也就是也没有按下过，回归NORMAL状态
			SetState(NORMAL);                                                                                            //其他就保持原样 比如按住不放的时候
		}
	}
	return btnState;                                                                                                    //最后返回按钮状态
}

int Button::CheckMouse1(Vector2i mouse, Event event) {
	//判断鼠标是不是在按钮内，前提是放正的矩形，一般情况下都是这样，如果是奇形怪状的需要再写别的方法
	if ((mouse.x > getPosition().x && mouse.x < getPosition().x + getTexture()->getSize().x / 2) &&
		(mouse.y > getPosition().y && mouse.y < getPosition().y + getTexture()->getSize().y)) {
		if (event.type == Event::EventType::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {            //如果在范围里按下左键，一定是CLICK状态                                                                                //如果按下左建时
			SetState(CLICK);
		}
		else if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {    //如果范围内释放左键，
			if (btnState == CLICK) {                                                                                    //如果之前是CLICK状态，那么就是RELEASE状态，表示按下
				SetState(RELEASE);                                                                                        //否则的话什么也不干
			}
		}
		else {                                                                                                        //如果鼠标移动的话，检测是不是按着的，不是就表示HOVER状态咯
			if (btnState != CLICK) {
				SetState(HOVER);
			}
		}
	}
	else {                                                                                                            //鼠标在按钮范围外
		if (event.type == Event::EventType::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {            //在范围外释放鼠标左键
			SetState(NORMAL);                                                                                            //回归NORMAL状态
		}
		else if (btnState == HOVER) {                                                                                    //如果是HOVER，也就是也没有按下过，回归NORMAL状态
			SetState(NORMAL);                                                                                            //其他就保持原样 比如按住不放的时候
		}
	}
	return btnState;                                                                                                    //最后返回按钮状态
}

void Button::Offset(double _x, double _y) {
	setPosition(getPosition().x + _x, getPosition().y + _y);
}