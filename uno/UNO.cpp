#include "UNO.h"
#include "Button.h"

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







UNO::UNO()
{
	Window_Width = 1920;
	Window_Height = 1080;

	window.create(sf::VideoMode(Window_Width, Window_Height), L"UNO");
}

UNO::~UNO() {}

void UNO::Initial()
{

	window.setFramerateLimit(60);	//设置游戏帧率

	gameOver = false;
	gameQuit = false;

	myCard_num = 7;		//我的卡牌数量
	enemyCard_num = 7;	//敌方卡牌数量

	stage_state = 1;//1为刚开始，0为游戏开始打斗

	music_state = true;//音乐状态

	isGameOverState = ncNo;	//初始化游戏的结束状态（未结束）
	isGameBegin = false;	//初始化游戏是否开始

	LoadMesiaData();
}

void UNO::InitialCard() {

	srand((unsigned)time(NULL));
	int a;		//随机数
	int x, y;
	for (int i = 0; i < myCard_num; i++) {
		a = rand() % 53;
		if (a < 52) {
			x = a / 13;
			y = a % 13;
			myCard_array[i].card = card_sprite1[x][y];
			myCard_array[i].card_suit = x;
			myCard_array[i].card_rank = y;
			std::cout << "mycard:  " << x << " " << y << std::endl;
		}
		else {
			myCard_array[i].card = card_sprite2[a - 52];
			myCard_array[i].card_suit = 4;
			myCard_array[i].card_rank = a - 52;
			std::cout << "mycard:  " << a << std::endl;
		}
	}

	for (int i = 0; i < enemyCard_num; i++) {
		a = rand() % 54 + 1;
		if (a < 52) {
			x = a / 13;
			y = a % 13;
			enemyCard_array[i].card = card_sprite1[x][y];
			enemyCard_array[i].card_suit = x;
			enemyCard_array[i].card_rank = y;
			std::cout << "enemycard:  " << x << " " << y << std::endl;
		}
		else {
			enemyCard_array[i].card = card_sprite2[a - 52];
			enemyCard_array[i].card_suit = 4;
			enemyCard_array[i].card_rank = a - 52;
			std::cout << "enemycard:  " << a << std::endl;
		}

	}

	//paidui = card_sprite2[2];

	std::cout << "游戏数据初始化已好" << std::endl;
}

void UNO::LoadMesiaData()
{
	if (!tBackground[0].loadFromFile("./data/images/bg_menu.jpg"))
	{
		std::cout << "No bg_menu image found." << std::endl;
	}
	sBackground[0].setTexture(tBackground[0]);
	//sBackground[0].setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	if (!tBackground[1].loadFromFile("./data/images/bg_game.jpg"))
	{
		std::cout << "No bg_game image found." << std::endl;
	}
	sBackground[1].setTexture(tBackground[1]);
	//sBackground[1].setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	//加载开始按钮
	if (!tMusicBtnNormal.loadFromFile("./data/images/but_play.png"))
	{
		std::cout << "No but_play image found." << std::endl;
	}
	sMusicBtnNormal.setTexture(tMusic1BtnNormal);
	//startBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%
	if (!tStartBtnNormal.loadFromFile("./data/images/but_play.png"))
	{
		std::cout << "No but_play image found." << std::endl;
	}
	startBtn.setTextures(tStartBtnNormal, tStartBtnNormal, tStartBtnNormal);
	//startBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	//音量键开关

	if (!tMusic1BtnNormal.loadFromFile("./data/images/audio_icon.png", IntRect(0, 0, 71, 71)))
	{
		std::cout << "No audio_icon image found." << std::endl;

	}
	if (!tMusic2BtnNormal.loadFromFile("./data/images/audio_icon.png", IntRect(71, 0, 71, 71)))
	{
		std::cout << "No audio_icon image found." << std::endl;
	}
	//Music1Btn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%	

	Music1Btn.setTextures(tMusic1BtnNormal, tMusic1BtnNormal, tMusic1BtnNormal);
	//Music1Btn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	Music2Btn.setTextures(tMusic2BtnNormal, tMusic2BtnNormal, tMusic2BtnNormal);
	//Music2Btn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	//退出按钮
	if (!tExitBtnNormal.loadFromFile("./data/images/but_exit.png"))
	{
		std::cout << "No but_exit image found." << std::endl;
	}
	exitBtn.setTextures(tExitBtnNormal, tExitBtnNormal, tExitBtnNormal);
	//exitBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%


	//加载卡牌纹理 4*13 i是行 j是列
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {

			if (!card_texture1[i][j].loadFromFile("./data/images/cards.png", sf::IntRect(j * CARD_WIDTH, i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT)))
			{
				std::cout << "No cards image found." << i << " " << j << std::endl;
			}
			card_sprite1[i][j].setTextures(card_texture1[i][j], card_texture1[i][j], card_texture1[i][j]);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (!card_texture2[i].loadFromFile("./data/images/cards.png", sf::IntRect(i * CARD_WIDTH, 4 * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT)))
		{
			std::cout << "No cards image found." << i << " " << std::endl;
		}
		card_sprite2[i].setTextures(card_texture2[i], card_texture2[i], card_texture2[i]);
	}

	//四个方块纹理导入
	for (int i = 0; i < 4; i++) {
		if (!ButColor_s[i].loadFromFile("./data/images/colors.png", sf::IntRect(i * 104, 0, 104, 102)))
		{
			std::cout << "No colors image found." << i << " " << std::endl;
		}
		ButColor[i].setTexture(ButColor_s[i]);
	}

	//uno按钮纹理导入
	if (!unoBtn_t.loadFromFile("./data/images/but_uno.png"))
	{
		std::cout << "No unoBtn image found." << " " << std::endl;
	}
	unoBtn.setTextures(unoBtn_t, unoBtn_t, unoBtn_t);


	//uno_cloud纹理导入
	for (int i = 0; i < 2; i++) {
		if (!uno_cloud_t[i].loadFromFile("./data/images/cloud.png", sf::IntRect(i * 261, 0, 261, 194)))
		{
			std::cout << "No colors image found." << i << " " << std::endl;
		}
		uno_cloud[i].setTexture(uno_cloud_t[i]);
	}


	std::cout << "加载纹理已好" << std::endl;
}

void UNO::LoadMusic() {

	if (!bj_music_file.loadFromFile("./data/music/bj.ogg")) {
		std::cout << "No uno music found." << std::endl;
	}
	bj_music.setBuffer(bj_music_file);

}

//绘制发牌动画
void UNO::drawdealCard() {

}

void UNO::startMusic() {
	bj_music.play();
	bj_music.setLoop(true);
}

void UNO::stopMusic() {
	//bj_music.stop();
	bj_music.pause();
}

void UNO::Input()
{
	sf::Event event;

	Vector2i mousePosition = Mouse::getPosition(window);

	while (window.pollEvent(event))
	{
		//可以通过点击取消和按下键盘Esc键退出游戏
		if (event.type == sf::Event::Closed)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}

		//鼠标交互（目前只设置了左右键单击）
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Mouse::Left Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "Mouse::Right Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;
		}
		//鼠标左键
		//if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		//{
		//	if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300)
		//	{
		//		LButtonDown(Mouse::getPosition(window));	//鼠标单击
		//		std::cout << "Mouse::Left Pressed" << std::endl;
		//	}
		//	else
		//	{
		//		//LButtinDblClk(Mouse::getPosition(window));	//鼠标双击
		//		std::cout << "Mouse::Left Double Clicked" << std::endl;
		//	}
		//}
		//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		//{
		//	if (mouseDlbClkReady)
		//	{
		//		mouseClickTimer.restart();	//左键按下时对鼠标事件重新计时
		//		std::cout << "Mouse::Left Released" << std::endl;
		//	}
		//}
		//鼠标右键
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			RButtonDown(Mouse::getPosition(window));	//鼠标单击

		}

	}

	//音乐开关
	if (music_state) {
		if (Music1Btn.checkMouse(mousePosition, event) == 3) {
			music_state = false;
			std::cout << "音乐关" << std::endl;
			startMusic();
		}

	}
	else {
		if (Music2Btn.checkMouse(mousePosition, event) == 3) {
			music_state = true;
			std::cout << "音乐开" << std::endl;
			stopMusic();
		}

	}

	//切换背景
	if (stage_state) {

		if (startBtn.checkMouse(mousePosition, event) == 3) {

			std::cout << "游戏中" << std::endl;
			InitialCard();
			drawdealCard();
			stage_state = 0;
			myCard_num = 7;
			enemyCard_num = 7;
			exitBtn.btnState = 1;
		}



	}
	else {
		//////////游戏中的鼠标检测///////////////////////////////

		if (exitBtn.checkMouse(mousePosition, event) == 3) {

			//退出游戏
			std::cout << "初始页面" << std::endl;
			startBtn.btnState = 1;
			stage_state = 1;
		}

		for (int i = 0; i < myCard_num; i++) {
			if (i < myCard_num - 1) {
				if (myCard_array[i].card.checkMouse1(mousePosition, event) == 3) {

					ButColorNum = myCard_array[i].card_suit;

					if (myCard_array[i].card_suit == 4) {
						paidui = card_sprite2[myCard_array[i].card_rank];
					}
					else {
						paidui = card_sprite1[myCard_array[i].card_suit][myCard_array[i].card_rank];
					}

					//删除卡牌

					for (int j = i; j < myCard_num - 1; j++) {
						std::cout << j << " delete  " << std::endl;
						myCard_array[j].card = myCard_array[j + 1].card;
						myCard_array[j].card_rank = myCard_array[j + 1].card_rank;
						myCard_array[j].card_suit = myCard_array[j + 1].card_suit;
					}
					myCard_num--;
					myCard_array[i].card.btnState = 1;

				}
			}
			else {
				if (myCard_array[i].card.checkMouse(mousePosition, event) == 3) {

					ButColorNum = myCard_array[i].card_suit;

					if (myCard_array[i].card_suit == 4) {
						paidui = card_sprite2[myCard_array[i].card_rank];
					}
					else {
						paidui = card_sprite1[myCard_array[i].card_suit][myCard_array[i].card_rank];
					}

					//删除卡牌


					for (int j = i; j < myCard_num - 1; j++) {
						std::cout << j << " delete  " << std::endl;
						myCard_array[j].card = myCard_array[j + 1].card;
						myCard_array[j].card_rank = myCard_array[j + 1].card_rank;
						myCard_array[j].card_suit = myCard_array[j + 1].card_suit;
					}
					myCard_num--;
					myCard_array[i].card.btnState = 1;


				}
			}
		}

		if (paiding.checkMouse(mousePosition, event) == 3 && myCard_num <= 24) {
			std::cout << "摸牌" << myCard_num << std::endl;
			srand((unsigned)time(NULL));
			int a;		//随机数
			int x, y;
			a = rand() % 53;
			if (a < 52) {
				x = a / 13;
				y = a % 13;
				myCard_array[myCard_num].card = card_sprite1[x][y];
				myCard_array[myCard_num].card_suit = x;
				myCard_array[myCard_num].card_rank = y;
				std::cout << "mycard:  " << x << " " << y << std::endl;
			}
			else {
				myCard_array[myCard_num].card = card_sprite2[a - 52];
				myCard_array[myCard_num].card_suit = 4;
				myCard_array[myCard_num].card_rank = a - 52;
				std::cout << "mycard:  " << a << std::endl;
			}
			myCard_num++;
		}

		if (unoBtn.checkMouse(mousePosition, event) == 3 && myCard_num == 1) {

			drawUnoflag = true;
			time1 = clock.restart();

			unoBtn.btnState = 1;
		}
	}

}

void UNO::RButtonDown(Vector2i mPoint)	//鼠标右击
{
	int i, j;
	//获取鼠标当前点击的块


}

void UNO::LButtonDown(Vector2i mPoint)	//鼠标左击
{
	int i, j;
#	//获取鼠标当前点击的块

	//检测是否点到了牌

}

void UNO::Logic()
{

}

void UNO::Draw()
{
	window.clear(); //清屏

	//绘制背景
	//std::cout << stage_state << std::endl;
	if (stage_state) {

		sBackground[0].setPosition(0, 0);
		window.draw(sBackground[0]);
		//开始按钮
		startBtn.setPosition(PLAY_X, PLAY_Y);
		window.draw(startBtn);

		//音乐按钮
		if (music_state) {
			Music1Btn.setPosition(MUSIC_X, MUSIC_Y);
			window.draw(Music1Btn);
		}
		else {
			Music2Btn.setPosition(MUSIC_X, MUSIC_Y);
			window.draw(Music2Btn);
		}


	}
	else {

		sBackground[1].setPosition(0, 0);
		window.draw(sBackground[1]);

		//音乐按钮
		if (music_state) {
			Music1Btn.setPosition(MUSIC_X, MUSIC_Y);
			window.draw(Music1Btn);
		}
		else {
			Music2Btn.setPosition(MUSIC_X, MUSIC_Y);
			window.draw(Music2Btn);
		}

		//退出按钮
		exitBtn.setPosition(EXIT_X, EXIT_Y);
		window.draw(exitBtn);

		/*card_sprite1[0][12].setPosition(821, 432);
		window.draw(card_sprite1[0][12]);*/

		paiding.setTextures(card_texture2[2], card_texture2[2], card_texture2[2]);
		paiding.setPosition(805, 420);
		window.draw(paiding);

		//颜色方块
		if (ButColorNum < 4) {
			ButColor[ButColorNum].setPosition(1140, 426);
			window.draw(ButColor[ButColorNum]);
		}
		else {
			ButColor[0].setPosition(1140, 426);
			window.draw(ButColor[0]);
		}



		//uno按钮
		unoBtn.setPosition(1140, 556);
		window.draw(unoBtn);

		if (drawUnoflag == true) {
			time2 = clock.getElapsedTime();
			if (time2.asSeconds() <= 3) {
				uno_cloud[0].setPosition(1240, 556 - 150);
				window.draw(uno_cloud[0]);
			}
			else {
				drawUnoflag = false;
			}
		}
		else {

		}


		//出牌的地方
		paidui.setPosition(961, 420);
		window.draw(paidui);


		//绘制我的卡牌
		for (int i = 0; i < myCard_num; i++) {
			myCard_array[i].card.setPosition(i * CARD_WIDTH / 2 + 300, 750);
			//std::cout << myCard_num << " " << i << " " << myCard_array[i].card_suit << "  " << myCard_array[i].card_rank << std::endl;
			window.draw(myCard_array[i].card);
		}

		for (int i = 0; i < enemyCard_num; i++) {
			enemyCard_array[i].card.setPosition(i * CARD_WIDTH / 2 + 300, 30);
			//std::cout << myCard_num << " " << i << " " << enemyCard_array[i].card_suit << "  " << enemyCard_array[i].card_rank << std::endl;
			window.draw(enemyCard_array[i].card);
		}


	}

	//DrawButton();


	if (isGameOverState)
		DrawGameEnd();

	window.display();
}
void UNO::DrawGameEnd()
{

}
void UNO::DrawButton()
{
	Vector2i LeftCorner; //用于记录按钮在窗口的位置
	int ButtonWidth = 71;
	int ButtonHeight = 71;
	int detaX;
	detaX = Window_Width - ButtonWidth; //指定x坐标
	LeftCorner.y = Window_Height - ButtonHeight;//指定高度

	//music_on,
	LeftCorner.x = detaX;
	sMusicBtnNormal.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //四个整数值，分别表示左上角顶点的横坐标和纵坐标，以及矩形的宽度和高度。
	sMusicBtnNormal.setPosition(LeftCorner.x, LeftCorner.y);
	music_on.left = LeftCorner.x;
	music_on.top = LeftCorner.y;
	music_on.width = ButtonWidth;
	music_on.height = ButtonHeight;
	window.draw(sMusicBtnNormal);
	//music_off
	LeftCorner.x = detaX;
	sMusicBtnNormal.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //四个整数值，分别表示左上角顶点的横坐标和纵坐标，以及矩形的宽度和高度。
	sMusicBtnNormal.setPosition(LeftCorner.x, LeftCorner.y);
	music_off.left = LeftCorner.x;
	music_off.top = LeftCorner.y;
	music_off.width = ButtonWidth;
	music_off.height = ButtonHeight;
	window.draw(sMusicBtnNormal);
}

void UNO::Run()
{
	Initial();
	LoadMusic();
	startMusic();
	do
	{

		while (window.isOpen() && gameOver == false)
		{
			Input();

			Logic();

			Draw();
		}
	} while (!gameQuit && window.isOpen());
}


