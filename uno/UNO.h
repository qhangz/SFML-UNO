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
	bool mouseHover;	//鼠标覆盖到卡牌时卡牌上移一段距离
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
	int changecolorFlag;	//判断此时是否需要进行颜色变换


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
	sf::Texture tUno_cloud;
	sf::Sprite sUno_cloud;
	sf::IntRect Uno_cloud[2];

	//四个方块纹理导入
	sf::Texture tRectColor;
	sf::Sprite sRectColor;
	sf::IntRect RectColor[4];
	int buttonColorNum = 4;

	//打出的牌的地方
	//sf::IntRect sDiscardPile;

	//摸牌的地方
	sf::IntRect cardPileIntRect;

	//用于游戏回合内的倒计时 
	float durationTime = 10.f;	//初始设置的游戏回合时间设为10秒
	float COUNTDOWN_DURATION = durationTime;	//游戏回合时间，用于动态增加
	sf::Clock countdownClock;
	sf::Clock pauseClock;	//用于暂停游戏计时	
	sf::Time pauseTime;		//暂停时的时间值
	sf::Font font;
	float elapsedSeconds;	//restart（）后已运行时间
	float remainingSeconds;		//当前回合剩余时间
	float pauserSeconds;
	int mutexClock = 0;
	int pauseClockFlag = 0;

	//绘制变换颜色的动画的纹理素材导入
	sf::Texture tChangeColorAnimation;
	sf::Sprite sChangeColorAnimation;
	sf::IntRect rChangeColorAnimation;
	//绘制变换颜色的动画的计时器
	sf::Clock changeClock;
	sf::Time changeTime1;
	sf::Time changeTime2;
	int changeI = 0, changeJ = 0, changeScaleX = 1, changeScaleY = 1;
	int changeI1 = 0, changeJ1 = 0;
	//
	sf::Texture tChangeColorPanel;
	sf::Sprite sChangeColorPanel;

	///////////	///// /////////////////////////////////////////////////////////////////////////////////////////
		//旧变量

	Button exitBtn;		//退出按钮
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//加载退出按钮纹理

	//uno的按钮，喊uno的按钮
	Button UnoBtn;
	sf::Texture tUnoBtn;
	int drawUnoFlag = false;

	//uno_cloud，绘制uno动画的俩个纹理
	/*sf::Sprite sUno_cloud;
	sf::Texture tUno_cloud;*/

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
	void ExamineCard(int i);		//检查功能牌，并实现逻辑
	void DrawTimer();	//游戏回合内的倒计时绘制
	void GamePause();
	void PauseTimer(float p);	//用于计时器暂停
	void ContinueTimer(float p);	//用于重新开始计时
	void isMouseHover(Vector2i mPoint);	//用于鼠标覆盖卡牌判定

	void DeleteCard(Card* card, int cardNum, int i);	//删除指定卡牌的函数
	void TouchingCard(Card* card, int cardNum);		//摸牌的函数
	void ChangeColor();		//改变颜色的函数
	void SendCard();	//绘制发牌动画函数
	void DrawBan();		//绘制禁掉动画
	void DrawTurn();	//绘制转换方向动画


	void Draw();
	void DrawButton();		//绘制按钮
	void DrawGameEnd();

};
