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

//音乐按钮坐标
#define MUSIC_X 1776
#define MUSIC_Y 0
//开始按钮坐标
#define PLAY_X 875
#define PLAY_Y 800
//退出按钮坐标
#define EXIT_X 1848
#define EXIT_Y 0
//卡牌大小
#define CARD_WIDTH 156
#define CARD_HEIGHT 242

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
	ChangeColor,
}Rank;



class Card {
public:
	int card_x;
	int card_y;
	sf::IntRect Rect;
};


class UNO
{
public:
	RenderWindow window;
	UNO();
	~UNO();


	//定义场景
	int windowWidth, windowHeight, stageWidth, stageHeight;



	///////////Logic逻辑变量定义///////////////////////////////////////////////////////

	bool gameOver, gameQuit;
	bool isGameBegin;	//判断游戏是否开始
	int isGameOverState;	//游戏结束的状态
	bool mouseDblClkReady;	//用于鼠标双击监测
	int GameFlag;		//判断用户操作的变量，0为电脑操作，1为用户操作
	int myCard_num, enemyCard_num;		//双方卡牌数量
	int music_state;	//判断音乐状态
	int sDiscardPile_i, sDiscardPile_j;		//出牌的地方
	int cardPile_i = 4, cardPile_j = 2;		//摸牌的地方
	bool touchingFlag;		//摸牌的判断
	bool showingFlag;		//出牌的判断


	/////////纹理导入变量////////////////////////////////////////////////////////////////////////////////////////
	sf::Texture tCards;				//卡牌纹理导入
	sf::Sprite sCards;				//卡牌精灵对象
	Card myCard[24], enemyCard[24];		//双方卡组


	sf::Texture tBackground[2];		//创建纹理对象
	sf::Sprite sBackground[2];		//创建精灵对象

	Button startBtn;	//开始按钮
	sf::Texture tStartBtnNormal;	//加载开始纹理

	Card myCard_array[24], enemyCard_array[24];

	sf::Sound bj_music;
	sf::SoundBuffer bj_music_file;	//加载背景音乐

	sf::Texture tMusicBtn;		//音乐开关纹理
	sf::Sprite MusicBtn;		//音乐开关精灵对象
	sf::IntRect MusicIntRect, Music_offIntRect;		//音乐开关

	//绘制uno动画的计时器
	sf::Clock clock;
	sf::Time time1;
	sf::Time time2;
	//绘制uno动画导入纹理
	/*sf::Texture tUno_cloud;
	sf::IntRect Uno_cloud[2];*/

	//四个方块纹理导入
	sf::Texture tRectColor;
	sf::Sprite sRectColor;
	sf::IntRect RectColor[4];

	//打出的牌的地方
	//sf::IntRect sDiscardPile;

	//摸牌的地方
	sf::IntRect cardPileIntRect;

	//用于游戏回合内的倒计时 
	const float COUNTDOWN_DURATION = 3.f;	//游戏回合计时设为10秒
	sf::Clock countdownClock;
	sf::Font font;

	///////////	///// /////////////////////////////////////////////////////////////////////////////////////////
		//旧变量

	Button Music1Btn, Music2Btn;	//音量开关
	sf::Texture tMusic1BtnNormal, tMusic1BtnHover, tMusic1BtnClick, tMusicBtnNormal;   //加载音量开关纹理
	sf::Texture tMusic2BtnNormal, tMusic2BtnHover, tMusic2BtnClick;   //加载音量开关纹理
	sf::Sprite sMusicBtnNormal, sMusic1BtnHover, sMusic1BtnClick;
	sf::IntRect music_on, music_off;		//音量开关纹理区域

	Button exitBtn;		//退出按钮
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//加载退出按钮纹理

	//加载卡牌纹理 4种颜色卡牌
	Button sCard_1[4][13];
	sf::Texture tCard_1[4][13];

	//变换颜色卡牌，+4卡牌，封面卡牌
	Button sCard_2[3];
	sf::Texture tCard_2[3];

	//四个方块纹理导入
	sf::Sprite sButtonColor[4];
	sf::Texture tButtonColor[4];
	int buttonColorNum = 4;

	//uno的按钮，喊uno的按钮
	Button UnoBtn;
	sf::Texture tUnoBtn;
	int drawUnoFlag = false;

	//打出的牌的地方
	sf::Sprite sDiscardPile;

	//摸牌的地方
	Button cardPile;
	sf::Texture tCardPile;

	//uno_cloud，绘制uno动画的俩个纹理
	sf::Sprite sUno_cloud[2];
	sf::Texture tUno_cloud[2];

	//绘制uno动画的计时器
	/*sf::Clock clock;
	sf::Time time1;
	sf::Time time2;*/

	//？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？//

	void Run();

	void Initial();
	void InitialCard();		//初始化双方卡牌
	void LoadMesiaData();	//加载图片纹理
	void LoadMusic();		//加载音乐文件
	void DrawDealCard();	//绘制发牌动画
	void StartMusic();
	void StopMusic();

	void Input();			//输入函数
	void RButtonDown(Vector2i mPoint);	//鼠标右击
	void LButtonDown(Vector2i mPoint);	//鼠标左击

	void Logic();			//主逻辑函数
	void ComputerLogic();	//电脑的逻辑判断
	void PlayerLogic();	//玩家逻辑判断
	void DrawTimer();	//游戏回合内的倒计时绘制
	void DeleteCard(Card* card, int cardNum, int i);	//删除指定卡牌的函数
	void TouchingCard(Card* card, int cardNum);		//摸牌的函数

	void Draw();
	void DrawButton();		//绘制按钮
	void DrawGameEnd();

};