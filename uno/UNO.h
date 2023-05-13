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
	sf::IntRect Rect;
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
	int music_state;	//�ж�����״̬
	int sDiscardPile_i, sDiscardPile_j;		//���Ƶĵط�
	int cardPile_i = 4, cardPile_j = 2;		//���Ƶĵط�
	bool touchingFlag;		//���Ƶ��ж�
	bool showingFlag;		//���Ƶ��ж�
	int changecolorFlag;	//�жϴ�ʱ�Ƿ���Ҫ������ɫ�任


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
	//
	sf::Texture tChangeColorPanel;
	sf::Sprite sChangeColorPanel;

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
	void SendCard();	//���Ʒ��ƶ�������
	void DrawBan();		//���ƽ�������
	void DrawTurn();	//����ת�����򶯻�


	void Draw();
	void DrawButton();		//���ư�ť
	void DrawGameEnd();

};
