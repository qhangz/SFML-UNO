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
	/*sf::Texture tUno_cloud;
	sf::IntRect Uno_cloud[2];*/

	//�ĸ�����������
	sf::Texture tRectColor;
	sf::Sprite sRectColor;
	sf::IntRect RectColor[4];

	//������Ƶĵط�
	//sf::IntRect sDiscardPile;

	//���Ƶĵط�
	sf::IntRect cardPileIntRect;

	//������Ϸ�غ��ڵĵ���ʱ 
	const float COUNTDOWN_DURATION = 3.f;	//��Ϸ�غϼ�ʱ��Ϊ10��
	sf::Clock countdownClock;
	sf::Font font;

	///////////	///// /////////////////////////////////////////////////////////////////////////////////////////
		//�ɱ���

	Button Music1Btn, Music2Btn;	//��������
	sf::Texture tMusic1BtnNormal, tMusic1BtnHover, tMusic1BtnClick, tMusicBtnNormal;   //����������������
	sf::Texture tMusic2BtnNormal, tMusic2BtnHover, tMusic2BtnClick;   //����������������
	sf::Sprite sMusicBtnNormal, sMusic1BtnHover, sMusic1BtnClick;
	sf::IntRect music_on, music_off;		//����������������

	Button exitBtn;		//�˳���ť
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//�����˳���ť����

	//���ؿ������� 4����ɫ����
	Button sCard_1[4][13];
	sf::Texture tCard_1[4][13];

	//�任��ɫ���ƣ�+4���ƣ����濨��
	Button sCard_2[3];
	sf::Texture tCard_2[3];

	//�ĸ�����������
	sf::Sprite sButtonColor[4];
	sf::Texture tButtonColor[4];
	int buttonColorNum = 4;

	//uno�İ�ť����uno�İ�ť
	Button UnoBtn;
	sf::Texture tUnoBtn;
	int drawUnoFlag = false;

	//������Ƶĵط�
	sf::Sprite sDiscardPile;

	//���Ƶĵط�
	Button cardPile;
	sf::Texture tCardPile;

	//uno_cloud������uno��������������
	sf::Sprite sUno_cloud[2];
	sf::Texture tUno_cloud[2];

	//����uno�����ļ�ʱ��
	/*sf::Clock clock;
	sf::Time time1;
	sf::Time time2;*/

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
	void DrawTimer();	//��Ϸ�غ��ڵĵ���ʱ����
	void DeleteCard(Card* card, int cardNum, int i);	//ɾ��ָ�����Ƶĺ���
	void TouchingCard(Card* card, int cardNum);		//���Ƶĺ���

	void Draw();
	void DrawButton();		//���ư�ť
	void DrawGameEnd();

};