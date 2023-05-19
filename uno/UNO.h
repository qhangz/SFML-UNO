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
//摸牌位置
#define CARDPILE_X 805
#define CARDPILE_Y 420
//出牌位置
#define SDISCARDPILE_X 961
#define SDISCARDPILE_Y 420
//score位置
#define SCORE_X 337
#define SCORE_Y 223


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
	int gradient_i = 0, gradient_j;
	int gradientCount = 0;
	int gradientColorChangeCount = 0;	//变换颜色的计数
	sf::IntRect Rect;
	sf::IntRect GradientRect;
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
	int music_state = 0;	//判断音乐状态
	int sDiscardPile_i, sDiscardPile_j;		//出牌的地方
	int cardPile_i = 4, cardPile_j = 2;		//摸牌的地方
	bool touchingFlag;		//摸牌的判断
	bool showingFlag;		//出牌的判断
	int sendCardX, sendCardY;
	int fps = 60;

	int aCardFlag = 0;	//判断是否处于动画中
	int cardFlag;	//判断是摸牌还是出牌 1为摸牌 0为出牌
	int cardFlag1;	//判断是否是哪个摸牌，哪个出牌，1为用户，0为电脑
	int cardFlag2;	//判断是主动摸牌还是被强制摸牌,1为主动，0为被动。
	int touchNum;
	float aCardX1, aCardX2, aCardY1, aCardY2;
	float aCardDx, aCardDy;
	int click_state = 0;
	int animationFlag;		//0为无操作，1为选择颜色，2为改换颜色动画播放，3为选择颜色前的摸牌动画，5为禁掉动画，7位转换动画

	int touch_flag;
	float banScale = 1;		//禁掉动画放大背书
	float banScaleSpeed = 0.05;		//放大速度
	float banScaleMax = 1.75;	//放大最大值
	float traRotate = 8;	//旋转速度
	float straScale = 1.5;		//旋转放大倍数
	int enemyCardCount[5];	//统计电脑卡牌里的各个卡牌颜色数量
	int enemyCardMax = -1;	//记录电脑卡牌里的卡牌颜色数量最大值
	int unoFlag;

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

	sf::Clock BtClock;
	sf::Time BtTime1;
	sf::Time BtTime2;

	//
	sf::Clock computerClock;
	sf::Time computerTime;

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

	float cardSpeed = 0.38;

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

	//牌移动动画
	sf::Clock CardClock;
	sf::Time CardTime1;
	sf::Time CardTime2;
	float aCardX, aCardY;		//CardAnimation的x, y动态变换


	//修改颜色面板
	sf::Texture tChangeColorPanel;
	sf::Sprite sChangeColorPanel;

	//提示框素材
	sf::Texture tGradient;
	sf::Sprite sGradient;

	//禁掉动画
	sf::Texture tBan;
	sf::Sprite sBan;

	//转换动画
	sf::Texture tTran;
	sf::Sprite sTran;

	//游戏结束的输赢绘制
	sf::Texture tgameWin;
	sf::Sprite sgameWin;

	sf::Texture tgameLose;
	sf::Sprite sgameLose;

	//重新开始游戏
	sf::Texture tgameRestart;
	sf::Sprite sgameRestart;
	sf::IntRect igameRestart;

	//返回主页
	sf::Texture thomePage;
	sf::Sprite shomePage;
	sf::IntRect ihomePage;

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
	void CardAnimation(int x1, int y1, int x2, int y2, bool flag);	//绘制发牌动画函数
	void DrawBan();		//绘制禁掉动画
	void DrawTurn();	//绘制转换方向动画
	void gameEndEvent();	//游戏结束后可执行的事件


	void Draw();
	void DrawButton();		//绘制按钮
	void DrawGameEnd();

};

