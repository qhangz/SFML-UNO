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

	int stage_state;	//�жϳ���״̬
	bool music_state;	//�ж�����״̬



	bool gameOver, gameQuit;
	int Window_Width, Window_Height, stageWidth, stageHeight;
	bool isGameBegin;	//�ж���Ϸ�Ƿ�ʼ
	int isGameOverState;	//��Ϸ������״̬
	bool mouseDlbClkReady;	//�������˫�����

	int myCard_num, enemyCard_num;		//˫����������


	sf::Texture tBackground[2];		//�����������
	sf::Sprite sBackground[2];		//�����������

	Button startBtn;	//��ʼ��ť
	sf::Texture tStartBtnNormal, tStartBtnHover, tStartBtnClick;	//���ؿ�ʼ����

	Card myCard_array[24], enemyCard_array[24];

	sf::Texture tmyCard1BtnNormal[24], tmyCard1BtnHover[24], tmyCardBtnClick[24];   //����������������

	sf::Sound bj_music;
	sf::SoundBuffer bj_music_file;	//���ر�������

	Button Music1Btn, Music2Btn;	//��������
	sf::Texture tMusic1BtnNormal, tMusic1BtnHover, tMusic1BtnClick, tMusicBtnNormal;   //����������������
	sf::Texture tMusic2BtnNormal, tMusic2BtnHover, tMusic2BtnClick;   //����������������
	sf::Sprite sMusicBtnNormal, sMusic1BtnHover, sMusic1BtnClick;
	sf::IntRect music_on, music_off;		//����������������


	Button exitBtn;		//�˳���ť
	sf::Texture tExitBtnNormal, tExitBtnHover, tExitBtnClick;		//�����˳���ť����

	//���ؿ������� 4����ɫ����
	Button card_sprite1[4][13];
	sf::Texture card_texture1[4][13];

	//�任��ɫ���ƣ�+4���ƣ����濨��
	Button card_sprite2[3];
	sf::Texture card_texture2[3];

	//�ĸ�����������
	sf::Sprite ButColor[4];
	sf::Texture ButColor_s[4];
	int ButColorNum = 4;

	//uno�İ�ť����uno�İ�ť
	Button unoBtn;
	sf::Texture unoBtn_t;
	int drawUnoflag = false;

	//������Ƶĵط�
	sf::Sprite paidui;

	//���Ƶĵط�
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
	void InitialCard();		//��ʼ��˫������
	void LoadMesiaData();	//����ͼƬ����
	void LoadMusic();		//���������ļ�
	void drawdealCard();	//���Ʒ��ƶ���
	void startMusic();
	void stopMusic();

	void Input();
	void RButtonDown(Vector2i mPoint);	//����һ�
	void LButtonDown(Vector2i mPoint);	//������

	void Logic();

	void Draw();
	void DrawButton();
	void DrawGameEnd();

};

