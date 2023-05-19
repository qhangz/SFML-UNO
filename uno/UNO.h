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

//���ְ�ť����
#define MUSIC_X 1776
#define MUSIC_Y 0
//��ʼ��ť����
#define PLAY_X 875
#define PLAY_Y 800
//�˳���ť����
#define EXIT_X 1848
#define EXIT_Y 0
//���ƴ�С
#define CARD_WIDTH 156
#define CARD_HEIGHT 242
//����λ��
#define CARDPILE_X 805
#define CARDPILE_Y 420
//����λ��
#define SDISCARDPILE_X 961
#define SDISCARDPILE_Y 420
//scoreλ��
#define SCORE_X 337
#define SCORE_Y 223


//ö�ٶ�����Ϸ״̬
typedef enum GAMEOVERSTATE
{
	ncNo,	//��Ϸδ����
	ncWIN,	//��Ϸʤ��
	ncLOSE,	//��Ϸʧ��
};

// �����ƵĻ�ɫ
typedef enum Suit {
	Red,
	Green,
	Blue,
	Yellow,
	NONE,
}Suit;

// �����Ƶ�����
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
	int gradientColorChangeCount = 0;	//�任��ɫ�ļ���
	sf::IntRect Rect;
	sf::IntRect GradientRect;
	bool mouseHover;	//��긲�ǵ�����ʱ��������һ�ξ���
};


class UNO
{
public:
	RenderWindow window;
	UNO();
	~UNO();


	//���峡��
	int windowWidth, windowHeight, stageWidth, stageHeight;



	///////////Logic�߼���������///////////////////////////////////////////////////////

	bool gameOver, gameQuit;
	bool isGameBegin;	//�ж���Ϸ�Ƿ�ʼ
	int isGameOverState;	//��Ϸ������״̬
	bool mouseDblClkReady;	//�������˫�����
	int GameFlag;		//�ж��û������ı�����0Ϊ���Բ�����1Ϊ�û�����
	int myCard_num, enemyCard_num;		//˫����������
	int music_state = 0;	//�ж�����״̬
	int sDiscardPile_i, sDiscardPile_j;		//���Ƶĵط�
	int cardPile_i = 4, cardPile_j = 2;		//���Ƶĵط�
	bool touchingFlag;		//���Ƶ��ж�
	bool showingFlag;		//���Ƶ��ж�
	int sendCardX, sendCardY;
	int fps = 60;

	int aCardFlag = 0;	//�ж��Ƿ��ڶ�����
	int cardFlag;	//�ж������ƻ��ǳ��� 1Ϊ���� 0Ϊ����
	int cardFlag1;	//�ж��Ƿ����ĸ����ƣ��ĸ����ƣ�1Ϊ�û���0Ϊ����
	int cardFlag2;	//�ж����������ƻ��Ǳ�ǿ������,1Ϊ������0Ϊ������
	int touchNum;
	float aCardX1, aCardX2, aCardY1, aCardY2;
	float aCardDx, aCardDy;
	int click_state = 0;
	int animationFlag;		//0Ϊ�޲�����1Ϊѡ����ɫ��2Ϊ�Ļ���ɫ�������ţ�3Ϊѡ����ɫǰ�����ƶ�����5Ϊ����������7λת������

	int touch_flag;
	float banScale = 1;		//���������Ŵ���
	float banScaleSpeed = 0.05;		//�Ŵ��ٶ�
	float banScaleMax = 1.75;	//�Ŵ����ֵ
	float traRotate = 8;	//��ת�ٶ�
	float straScale = 1.5;		//��ת�Ŵ���
	int enemyCardCount[5];	//ͳ�Ƶ��Կ�����ĸ���������ɫ����
	int enemyCardMax = -1;	//��¼���Կ�����Ŀ�����ɫ�������ֵ
	int unoFlag;

	/////////���������////////////////////////////////////////////////////////////////////////////////////////
	sf::Texture tCards;				//����������
	sf::Sprite sCards;				//���ƾ������
	Card myCard[24], enemyCard[24];		//˫������

	sf::Texture tBackground[2];		//�����������
	sf::Sprite sBackground[2];		//�����������

	Button startBtn;	//��ʼ��ť
	sf::Texture tStartBtnNormal;	//���ؿ�ʼ����

	Card myCard_array[24], enemyCard_array[24];

	sf::Sound bj_music;
	sf::SoundBuffer bj_music_file;	//���ر�������

	sf::Texture tMusicBtn;		//���ֿ�������
	sf::Sprite MusicBtn;		//���ֿ��ؾ������
	sf::IntRect MusicIntRect, Music_offIntRect;		//���ֿ���

	//����uno�����ļ�ʱ��
	sf::Clock clock;
	sf::Time time1;
	sf::Time time2;

	sf::Clock BtClock;
	sf::Time BtTime1;
	sf::Time BtTime2;

	//
	sf::Clock computerClock;
	sf::Time computerTime;

	//����uno������������
	sf::Texture tUno_cloud;
	sf::Sprite sUno_cloud;
	sf::IntRect Uno_cloud[2];

	//�ĸ�����������
	sf::Texture tRectColor;
	sf::Sprite sRectColor;
	sf::IntRect RectColor[4];
	int buttonColorNum = 4;

	//������Ƶĵط�
	//sf::IntRect sDiscardPile;

	//���Ƶĵط�
	sf::IntRect cardPileIntRect;

	//������Ϸ�غ��ڵĵ���ʱ 
	float durationTime = 10.f;	//��ʼ���õ���Ϸ�غ�ʱ����Ϊ10��
	float COUNTDOWN_DURATION = durationTime;	//��Ϸ�غ�ʱ�䣬���ڶ�̬����
	sf::Clock countdownClock;
	sf::Clock pauseClock;	//������ͣ��Ϸ��ʱ	
	sf::Time pauseTime;		//��ͣʱ��ʱ��ֵ
	sf::Font font;
	float elapsedSeconds;	//restart������������ʱ��
	float remainingSeconds;		//��ǰ�غ�ʣ��ʱ��
	float pauserSeconds;
	int mutexClock = 0;
	int pauseClockFlag = 0;

	float cardSpeed = 0.38;

	//���Ʊ任��ɫ�Ķ����������زĵ���
	sf::Texture tChangeColorAnimation;
	sf::Sprite sChangeColorAnimation;
	sf::IntRect rChangeColorAnimation;
	//���Ʊ任��ɫ�Ķ����ļ�ʱ��
	sf::Clock changeClock;
	sf::Time changeTime1;
	sf::Time changeTime2;
	int changeI = 0, changeJ = 0, changeScaleX = 1, changeScaleY = 1;
	int changeI1 = 0, changeJ1 = 0;

	//���ƶ�����
	sf::Clock CardClock;
	sf::Time CardTime1;
	sf::Time CardTime2;
	float aCardX, aCardY;		//CardAnimation��x, y��̬�任


	//�޸���ɫ���
	sf::Texture tChangeColorPanel;
	sf::Sprite sChangeColorPanel;

	//��ʾ���ز�
	sf::Texture tGradient;
	sf::Sprite sGradient;

	//��������
	sf::Texture tBan;
	sf::Sprite sBan;

	//ת������
	sf::Texture tTran;
	sf::Sprite sTran;

	//��Ϸ��������Ӯ����
	sf::Texture tgameWin;
	sf::Sprite sgameWin;

	sf::Texture tgameLose;
	sf::Sprite sgameLose;

	//���¿�ʼ��Ϸ
	sf::Texture tgameRestart;
	sf::Sprite sgameRestart;
	sf::IntRect igameRestart;

	//������ҳ
	sf::Texture thomePage;
	sf::Sprite shomePage;
	sf::IntRect ihomePage;

	///////////	///// /////////////////////////////////////////////////////////////////////////////////////////
		//�ɱ���

	Button exitBtn;		//�˳���ť
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//�����˳���ť����

	//uno�İ�ť����uno�İ�ť
	Button UnoBtn;
	sf::Texture tUnoBtn;
	int drawUnoFlag = false;

	//uno_cloud������uno��������������
	/*sf::Sprite sUno_cloud;
	sf::Texture tUno_cloud;*/

	//����������������������������������������������������������������������������������������������������������������������//

	void Run();

	void Initial();
	void InitialCard();		//��ʼ��˫������
	void LoadMesiaData();	//����ͼƬ����
	void LoadMusic();		//���������ļ�
	void DrawDealCard();	//���Ʒ��ƶ���
	void StartMusic();
	void StopMusic();

	void Input();			//���뺯��
	void RButtonDown(Vector2i mPoint);	//����һ�
	void LButtonDown(Vector2i mPoint);	//������

	void Logic();			//���߼�����
	void ComputerLogic();	//���Ե��߼��ж�
	void PlayerLogic();	//����߼��ж�
	void ExamineCard(int i);		//��鹦���ƣ���ʵ���߼�
	void DrawTimer();	//��Ϸ�غ��ڵĵ���ʱ����
	void GamePause();
	void PauseTimer(float p);	//���ڼ�ʱ����ͣ
	void ContinueTimer(float p);	//�������¿�ʼ��ʱ
	void isMouseHover(Vector2i mPoint);	//������긲�ǿ����ж�

	void DeleteCard(Card* card, int cardNum, int i);	//ɾ��ָ�����Ƶĺ���
	void TouchingCard(Card* card, int cardNum);		//���Ƶĺ���
	void ChangeColor();		//�ı���ɫ�ĺ���
	void CardAnimation(int x1, int y1, int x2, int y2, bool flag);	//���Ʒ��ƶ�������
	void DrawBan();		//���ƽ�������
	void DrawTurn();	//����ת�����򶯻�
	void gameEndEvent();	//��Ϸ�������ִ�е��¼�


	void Draw();
	void DrawButton();		//���ư�ť
	void DrawGameEnd();

};

