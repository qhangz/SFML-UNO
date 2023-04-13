#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include <stdlib.h>
#include <time.h> 
#include "Button.h"
using namespace sf;

//枚举定义游戏状态
typedef enum GAMEOVERSTATE
{
	ncNo,	//游戏未结束
	ncWIN,	//游戏胜利
	ncLOSE,	//游戏失败
};

// 定义牌的花色
typedef enum Suit {
	Red,
	Green,
	Blue,
	Yellow,
	NONE,
}Suit;

// 定义牌的类型
typedef enum Rank {
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Skip,
	Reverse,
	AddTwo,
	AddFour,
	ChangeClor,
}Rank;

class Card {
public:
	int  card_suit;
	int card_rank;
	Button card;
};


class UNO
{
public:
	RenderWindow window;
	UNO();
	~UNO();

	int stage_state;	//判断场景状态
	bool music_state;	//判断音乐状态



	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	bool isGameBegin;	//判断游戏是否开始
	int isGameOverState;	//游戏结束的状态
	bool mouseDlbClkReady;	//用于鼠标双击监测

	int myCard_num, enemyCard_num;		//双方卡牌数量


	sf::Texture tBackground[2];		//创建纹理对象
	sf::Sprite sBackground[2];		//创建精灵对象

	Button startBtn;	//开始按钮
	sf::Texture tStartBtnNormal, tStartBtnHover, tStartBtnClick;	//加载开始纹理

	Card myCard_array[24], enemyCard_array[24];

	sf::Texture tmyCard1BtnNormal[24], tmyCard1BtnHover[24], tmyCardBtnClick[24];   //加载音量开关纹理

	sf::Sound bj_music;
	sf::SoundBuffer bj_music_file;	//加载背景音乐

	Button Music1Btn, Music2Btn;	//音量开关
	sf::Texture tMusic1BtnNormal, tMusic1BtnHover, tMusic1BtnClick, tMusicBtnNormal;   //加载音量开关纹理
	sf::Texture tMusic2BtnNormal, tMusic2BtnHover, tMusic2BtnClick;   //加载音量开关纹理
	sf::Sprite sMusicBtnNormal, sMusic1BtnHover, sMusic1BtnClick;
	sf::IntRect music_on, music_off;		//音量开关纹理区域


	Button exitBtn;		//退出按钮
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//加载退出按钮纹理

	//加载卡牌纹理 4种颜色卡牌
	Button card_sprite1[4][13];
	sf::Texture card_texture1[4][13];

	//变换颜色卡牌，+4卡牌，封面卡牌
	Button card_sprite2[3];
	sf::Texture card_texture2[3];

	//四个方块纹理导入
	sf::Sprite ButColor[4];
	sf::Texture ButColor_s[4];
	int ButColorNum = 4;

	//uno的按钮，喊uno的按钮
	Button unoBtn;
	sf::Texture unoBtn_t;
	int drawUnoflag = false;

	//打出的牌的地方
	sf::Sprite paidui;

	//摸牌的地方
	Button paiding;
	sf::Texture paiding_wenli;

	//uno_cloud
	sf::Sprite uno_cloud[2];
	sf::Texture uno_cloud_t[2];

	sf::Clock clock;
	sf::Time time1;
	sf::Time time2;

	//sf::Sprite card[4][]

	void Run();

	void Initial();
	void InitialCard();		//初始化双方卡牌
	void LoadMesiaData();	//加载图片纹理
	void LoadMusic();		//加载音乐文件
	void drawdealCard();	//绘制发牌动画
	void startMusic();
	void stopMusic();

	void Input();
	void RButtonDown(Vector2i mPoint);	//鼠标右击
	void LButtonDown(Vector2i mPoint);	//鼠标左击

	void Logic();

	void Draw();
	void DrawButton();
	void DrawGameEnd();

};

