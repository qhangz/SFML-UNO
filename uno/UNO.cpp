#include "UNO.h"
#include "Button.h"



UNO::UNO()
{
	windowWidth = 1920;
	windowHeight = 1080;

	window.create(sf::VideoMode(windowWidth, windowHeight), L"UNO");
}

UNO::~UNO() {}

void UNO::Initial()
{

	window.setFramerateLimit(60);	//设置游戏帧率

	gameOver = false;
	gameQuit = false;
	//gamePause = false;

	GameFlag = 1;

	myCard_num = 7;		//我的卡牌数量
	enemyCard_num = 7;	//敌方卡牌数量

	music_state = 0;//音乐状态


	isGameOverState = ncNo;	//初始化游戏的结束状态（未结束）
	isGameBegin = false;	//初始化游戏是否开始

	changecolorFlag = 0;	//变量为1时要进行游戏改变颜色

	mutexClock = 0;

	LoadMesiaData();
}

void UNO::InitialCard() {
	srand(time(NULL));
	int a;		//随机数
	int x, y;
	myCard_num = 7;
	enemyCard_num = 7;
	for (int i = 0; i < myCard_num; i++) {
		a = rand() % 54;
		if (a < 52) {
			x = a / 13;
			y = a % 13;
			myCard[i].card_x = x;
			myCard[i].card_y = y;
			std::cout << "mycard:  " << x << " " << y << std::endl;
		}
		else {
			myCard[i].card_x = 4;
			myCard[i].card_y = a - 52;
			std::cout << "mycard:  " << a << std::endl;
		}
	}

	for (int i = 0; i < enemyCard_num; i++) {
		a = rand() % 54;
		if (a < 52) {
			x = a / 13;
			y = a % 13;
			enemyCard[i].card_x = x;
			enemyCard[i].card_y = y;
			std::cout << "enemycard:  " << x << " " << y << std::endl;
		}
		else {
			enemyCard[i].card_x = 4;
			enemyCard[i].card_y = a - 52;
			std::cout << "enemycard:  " << a << std::endl;
		}
	}

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
	//startBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%
	if (!tStartBtnNormal.loadFromFile("./data/images/but_play.png"))
	{
		std::cout << "No but_play image found." << std::endl;
	}
	startBtn.SetTextures(tStartBtnNormal, tStartBtnNormal, tStartBtnNormal);
	//startBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%

	//音量键开关纹理修改
	if (!tMusicBtn.loadFromFile("./data/images/audio_icon.png")) {
		std::cout << "No audio_icon image found." << std::endl;
	}
	MusicBtn.setTexture(tMusicBtn);
	//Music1Btn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%	

	//退出按钮
	if (!tExitBtnNormal.loadFromFile("./data/images/but_exit.png"))
	{
		std::cout << "No but_exit image found." << std::endl;
	}
	exitBtn.SetTextures(tExitBtnNormal, tExitBtnNormal, tExitBtnNormal);
	//exitBtn.setScale(0.8f, 0.8f);//将背景图片等比缩小了80%


	//加载卡牌纹理
	if (!tCards.loadFromFile("./data/images/cards.png"))
	{
		std::cout << "No cards image found." << std::endl;
	}
	sCards.setTexture(tCards);

	//uno方块纹理导入
	if (!tRectColor.loadFromFile("./data/images/colors.png"/*, sf::IntRect(i * 104, 0, 104, 102)*/))
	{
		std::cout << "No colors image found." << " " << std::endl;
	}
	sRectColor.setTexture(tRectColor);

	//uno按钮纹理导入
	if (!tUnoBtn.loadFromFile("./data/images/but_uno.png"))
	{
		std::cout << "No unoBtn image found." << " " << std::endl;
	}
	UnoBtn.SetTextures(tUnoBtn, tUnoBtn, tUnoBtn);

	//uno_cloud纹理导入
	if (!tUno_cloud.loadFromFile("./data/images/cloud.png", sf::IntRect(0, 0, 261, 194)))
	{
		std::cout << "No colors image found." << " " << std::endl;
	}
	sUno_cloud.setTexture(tUno_cloud);

	//uno变换颜色纹理导入
	if (!tChangeColorAnimation.loadFromFile("./data/images/change_color.png"))
	{
		std::cout << "No change color image found." << " " << std::endl;
	}
	sChangeColorAnimation.setTexture(tChangeColorAnimation);

	//uno变换颜色面板导入Panel
	if (!tChangeColorPanel.loadFromFile("./data/images/credits_panel.png"))
	{
		std::cout << "No credits panel image found." << " " << std::endl;
	}
	sChangeColorPanel.setTexture(tChangeColorPanel);


	//加载字体
	if (!font.loadFromFile("./data/Fonts/ZCOOLKuaiLe-Regular.ttf"))
	{
		std::cout << "Not find Font" << std::endl;
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
void UNO::DrawDealCard() {

}

void UNO::StartMusic() {
	bj_music.play();
	bj_music.setLoop(true);
	
}

void UNO::StopMusic() {
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
			if (isGameOverState == ncNo) {
				//音量按钮的检测
				if (MusicIntRect.contains(event.mouseButton.x, event.mouseButton.y)) {
					music_state = 1 - music_state;
					std::cout << music_state << std::endl;
					if (!music_state) {
						StartMusic();
					}
					else {
						StopMusic();
					}
				}

			}
			if (GameFlag == 1) {
				//我的卡牌点击监听
				for (int i = 0; i < myCard_num; i++) {
					if (myCard[i].Rect.contains(event.mouseButton.x, event.mouseButton.y)) {
						std::cout << "用户出牌" << i << std::endl;
						sDiscardPile_i = myCard[i].card_x;
						sDiscardPile_j = myCard[i].card_y;
						if (myCard[i].card_x == 4) {

						}
						else {
							buttonColorNum = myCard[i].card_x;
						}
						DeleteCard(myCard, myCard_num, i);
						myCard_num--;
						//切换成电脑操作
						GameFlag = 0;
						ExamineCard(0);
						countdownClock.restart();
					}
				}
				//摸牌的监听
				if (cardPileIntRect.contains(event.mouseButton.x, event.mouseButton.y) && myCard_num < 24) {
					std::cout << "用户摸牌" << std::endl;
					TouchingCard(myCard, myCard_num);
					myCard_num++;
					//切替换成电脑操作 
					GameFlag = 0;
					countdownClock.restart();
				}
				if (changecolorFlag == 1) {
					for (int i = 0; i < 4; i++) {
						if (RectColor[i].contains(event.mouseButton.x, event.mouseButton.y) && myCard_num < 24) {
							changecolorFlag = 2;
							std::cout << "变换颜色" << i << "颜色逻辑" << changecolorFlag << std::endl;
							buttonColorNum = i;
						}
					}
				}
			}

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


	//切换背景
	if (!isGameBegin) {

		if (startBtn.CheckMouse(mousePosition, event) == 3) {

			std::cout << "游戏中" << std::endl;
			InitialCard();
			DrawDealCard();
			isGameBegin = true;
			exitBtn.btnState = 1;
			countdownClock.restart();
			GameFlag = 1;
		}



	}
	else {
		//////////游戏中的鼠标检测///////////////////////////////

		if (exitBtn.CheckMouse(mousePosition, event) == 3) {

			//退出游戏
			std::cout << "初始页面" << std::endl;
			startBtn.btnState = 1;
			isGameBegin = false;
		}

		if (UnoBtn.CheckMouse(mousePosition, event) == 3) {

			UnoBtn.btnState = 1;
			drawUnoFlag = true;
			time1 = clock.restart();
			std::cout << "Uno" << drawUnoFlag << std::endl;
		}
	}

}

void UNO::RButtonDown(Vector2i mPoint)	//鼠标右击
{
	

}

void UNO::TouchingCard(Card* card, int cardNum) {
	int a;		//随机数
	int x, y;
	a = rand() % 54;
	if (a < 52) {
		x = a / 13;
		y = a % 13;
		card[cardNum].card_x = x;
		card[cardNum].card_y = y;
		std::cout << "mycard:  " << x << " " << y << std::endl;
	}
	else {
		card[cardNum].card_x = 4;
		card[cardNum].card_y = a - 52;
		std::cout << "mycard:  " << a << std::endl;
	}
}

void UNO::LButtonDown(Vector2i mPoint)	//鼠标左击
{
	
}

//绘制游戏运行时间（计时器）
//绘制游戏运行时间（计时器）
void UNO::DrawTimer()
{

	// 计算剩余的时间
	if (mutexClock == 0)
	{
		elapsedSeconds = countdownClock.getElapsedTime().asSeconds(); //将时间转换为秒数，记录已经流逝的时间
		remainingSeconds = COUNTDOWN_DURATION - elapsedSeconds; //通过用倒计时总时间减去已经流逝的时间，计算出还剩下多少秒才能到达目标倒计时时间
	}

	
	//检查倒计时是否结束
	if (remainingSeconds <= 0.f)
	{
		//修改GameFlag
		if (GameFlag == 0)
		{
			GameFlag = 1;
		}
		else
		{
			GameFlag = 0;
		}

		//重新开始倒计时
		countdownClock.restart();
		if (mutexClock == 0) {
			COUNTDOWN_DURATION = durationTime;	//将游戏回合时间重置
		}
		remainingSeconds = COUNTDOWN_DURATION;
	}

	//根据剩余时间生成一个倒计时数
	std::string countdownString = std::to_string(static_cast<int>(remainingSeconds)); //将整数类型的remainingSeconds强制转换为字符串类型并赋值给countdownString变量
	if (GameFlag == 0)
	{
		countdownString = "Conputer Remaining:  " + countdownString;
	}
	else
	{
		countdownString = "Player Remaining:  " + countdownString;
	}

	//用Text对象去显示倒计时数字
	sf::Text countdownText(countdownString, font, 50);
	countdownText.setPosition(window.getSize().x / 4.f, window.getSize().y / 2.f);
	countdownText.setOrigin(countdownText.getLocalBounds().width / 2.f, countdownText.getLocalBounds().height / 2.f);

	window.draw(countdownText);
	
}
//暂停计时器
void UNO::PauseTimer(float pauseTime)
{
	mutexClock = 1;
	COUNTDOWN_DURATION = durationTime + pauseTime;
	pauseClock.restart();
	mypauseTime = pauseTime;
}
//重新开始计时
void UNO::ContinueTimer()
{
	if (pauseClock.getElapsedTime().asSeconds() >= mypauseTime)
	{
		mutexClock = 0;
	}
	
}

void UNO::Logic()
{
	if (GameFlag == 0) {	//电脑操作逻辑判断

		ComputerLogic();

	}
	else {			//用户操作逻辑判断
		PlayerLogic();

	}
}

void UNO::ExamineCard(int i) {		//i为1是用户变卡牌
	if (i) {
		if (sDiscardPile_i == 4 && sDiscardPile_j == 0) {		//变换颜色卡牌
			int a = rand() % 4;
			buttonColorNum = a;
		}
		else if (sDiscardPile_i == 4 && sDiscardPile_j == 1) {		//变换颜色并给对方加四张卡牌
			int a = rand() % 4;
			buttonColorNum = a;
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			std::cout << "用户摸4牌" << std::endl;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 10) {		//禁掉下一个人的卡牌
			GameFlag = 1 - GameFlag;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 11) {		//逆转方向
			GameFlag = 1 - GameFlag;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 12) {		//给下一个人加俩张卡牌
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			TouchingCard(myCard, myCard_num);
			myCard_num++;
			std::cout << "用户摸2牌" << std::endl;
		}
	}
	else {		//i为0是电脑变卡牌
		if (sDiscardPile_i == 4 && sDiscardPile_j == 0) {		//变换颜色卡牌
			changecolorFlag = 1;
		}
		else if (sDiscardPile_i == 4 && sDiscardPile_j == 1) {		//变换颜色并给对方加四张卡牌
			changecolorFlag = 1;
			TouchingCard(enemyCard, enemyCard_num);
			enemyCard_num++;
			TouchingCard(enemyCard, enemyCard_num);
			enemyCard_num++;
			TouchingCard(enemyCard, enemyCard_num);
			enemyCard_num++;
			TouchingCard(enemyCard, enemyCard_num);
			enemyCard_num++;
			std::cout << "电脑摸4牌" << std::endl;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 10) {		//禁掉下一个人的卡牌
			GameFlag = 1 - GameFlag;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 11) {		//逆转方向
			GameFlag = 1 - GameFlag;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 12) {		//给下一个人加俩张卡牌
			TouchingCard(enemyCard, enemyCard_num);
			enemyCard_num++;
			TouchingCard(enemyCard, enemyCard_num);
			std::cout << "电脑摸2牌" << std::endl;
			enemyCard_num++;
		}
	}
}

void UNO::ComputerLogic()
{
	//重置回合时间
	//countdownClock.restart();
	//声明这是computer的回合
	int touch_flag = 1;
	std::cout << buttonColorNum << std::endl;
	for (int i = 0; i < enemyCard_num; i++) {
		std::cout << enemyCard[i].card_x << " " << enemyCard[i].card_y << "sDiscardPile  " << sDiscardPile_i << " " << sDiscardPile_j << " " << enemyCard_num << std::endl;
		if (enemyCard[i].card_x == buttonColorNum) {

			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			buttonColorNum = enemyCard[i].card_x;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}
			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;
			//切换成用户操作
			GameFlag = 1;
			touch_flag = 0;
			ExamineCard(GameFlag);
			countdownClock.restart();
			break;

		}
		else if (enemyCard[i].card_y == sDiscardPile_j) {
			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}
			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;
			//切换成用户操作
			GameFlag = 1;
			touch_flag = 0;
			ExamineCard(GameFlag);
			countdownClock.restart();
			break;
		}
		else if (enemyCard[i].card_x == 4) {
			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}
			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;
			//切换成用户操作
			GameFlag = 1;
			touch_flag = 0;
			ExamineCard(GameFlag);
			countdownClock.restart();
			break;
		}
	}
	if (touch_flag) {
		std::cout << "电脑摸牌" << std::endl;
		TouchingCard(enemyCard, enemyCard_num);
		enemyCard_num++;
		//切替换成电脑操作 
		GameFlag = 1;
		ExamineCard(GameFlag);
		countdownClock.restart();
	}
	GameFlag = 1;
}

void UNO::PlayerLogic()
{
	//重置回合时间
	//countdownClock.restart();
	//声明这是player的回合

}

void UNO::ChangeColor() {

}

void UNO::DeleteCard(Card* card, int cardNum, int i) {

	for (int j = i; j < cardNum - 1; j++) {
		std::cout << j << " delete  " << std::endl;
		card[j].Rect = myCard_array[j + 1].Rect;
		card[j].card_x = card[j + 1].card_x;
		card[j].card_y = card[j + 1].card_y;
	}

}

void UNO::Draw()
{
	window.clear(); //清屏

	//绘制背景
	//std::cout << stage_state << std::endl;
	if (!isGameBegin) {

		sBackground[0].setPosition(0, 0);
		window.draw(sBackground[0]);

		//开始按钮
		startBtn.setPosition(PLAY_X, PLAY_Y);
		window.draw(startBtn);

		//音乐按钮
		MusicBtn.setTextureRect(sf::IntRect(music_state * 71, 0, 71, 71));
		MusicBtn.setPosition(MUSIC_X, MUSIC_Y);
		MusicIntRect.left = MUSIC_X;
		MusicIntRect.top = MUSIC_Y;
		MusicIntRect.width = 71;
		MusicIntRect.height = 71;
		window.draw(MusicBtn);


	}
	else {
		//游戏中的背景绘制
		sBackground[1].setPosition(0, 0);
		window.draw(sBackground[1]);

		DrawTimer();

		//音乐按钮
		MusicBtn.setTextureRect(sf::IntRect(music_state * 71, 0, 71, 71));
		MusicBtn.setPosition(MUSIC_X, MUSIC_Y);
		MusicIntRect.left = MUSIC_X;
		MusicIntRect.top = MUSIC_Y;
		MusicIntRect.width = 71;
		MusicIntRect.height = 71;
		window.draw(MusicBtn);

		//退出按钮
		exitBtn.setPosition(EXIT_X, EXIT_Y);
		window.draw(exitBtn);

		//颜色方块
		if (buttonColorNum < 4) {
			sRectColor.setTextureRect(sf::IntRect(buttonColorNum * 104, 0, 104, 102));
			sRectColor.setPosition(1140, 426);
			window.draw(sRectColor);
		}
		else {
			sRectColor.setTextureRect(sf::IntRect(0 * 104, 0, 104, 102));
			sRectColor.setPosition(1140, 426);
			window.draw(sRectColor);
		}



		//uno按钮
		UnoBtn.setPosition(1140, 556);
		window.draw(UnoBtn);

		if (drawUnoFlag == true) {
			time2 = clock.getElapsedTime();
			if (time2.asSeconds() <= 3) {
				sUno_cloud.setPosition(1240, 556 - 150);
				window.draw(sUno_cloud);
			}
			else {
				drawUnoFlag = false;
			}
		}
		else {

		}




		//绘制我的卡牌
		for (int i = 0; i < myCard_num; i++) {
			sCards.setTextureRect(sf::IntRect(myCard[i].card_y * CARD_WIDTH, myCard[i].card_x * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
			sCards.setPosition(i * CARD_WIDTH / 2 + 300, 750);
			if (i < myCard_num - 1) {
				myCard[i].Rect.left = i * CARD_WIDTH / 2 + 300;
				myCard[i].Rect.top = 750;
				myCard[i].Rect.width = CARD_WIDTH / 2;
				myCard[i].Rect.height = CARD_HEIGHT;
			}
			else {
				myCard[i].Rect.left = i * CARD_WIDTH / 2 + 300;
				myCard[i].Rect.top = 750;
				myCard[i].Rect.width = CARD_WIDTH;
				myCard[i].Rect.height = CARD_HEIGHT;
			}
			window.draw(sCards);
		}
		//绘制enemy卡牌
		for (int i = 0; i < enemyCard_num; i++) {
			sCards.setTextureRect(sf::IntRect(enemyCard[i].card_y * CARD_WIDTH, enemyCard[i].card_x * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
			sCards.setPosition(i * CARD_WIDTH / 2 + 300, 30);
			window.draw(sCards);
		}
		//出牌的绘制
		sCards.setTextureRect(sf::IntRect(sDiscardPile_j * CARD_WIDTH, sDiscardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
		sCards.setPosition(961, 420);
		window.draw(sCards);
		//摸牌的绘制
		sCards.setTextureRect(sf::IntRect(cardPile_j * CARD_WIDTH, cardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
		sCards.setPosition(805, 420);
		cardPileIntRect.left = 805;
		cardPileIntRect.top = 420;
		cardPileIntRect.width = CARD_WIDTH;
		cardPileIntRect.height = CARD_HEIGHT;
		window.draw(sCards);

		if (changecolorFlag == 1) {
			sChangeColorPanel.setPosition(960 - 275, 540 - 305 * 0.75 * 0.5);
			sChangeColorPanel.setScale(sf::Vector2f(1, 0.75));
			sf::Color color = Color(0, 0, 0, 255);
			sChangeColorPanel.setColor(color);
			window.draw(sChangeColorPanel);
			for (int i = 0; i < 4; i++) {
				sRectColor.setTextureRect(sf::IntRect(i * 104, 0, 104, 102));
				sRectColor.setPosition(585 + 25 + 104 + i * 132, 540 - 305 * 0.75 * 0.5 + 64);
				RectColor[i].left = 585 + 25 + 104 + i * 132;
				RectColor[i].top = 540 - 305 * 0.75 * 0.5 + 64;
				RectColor[i].width = 104;
				RectColor[i].height = 102;
				window.draw(sRectColor);
			}
		}
		else if (changecolorFlag == 2) {


			changecolorFlag = 0;
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

}

void SimpleRandDemo(int n)
{
	// Print n random numbers.
	int i;
	for (i = 0; i < n; i++)
		printf(" %6d\n", rand());
}

void RangedRandDemo(int range_min, int range_max, int n)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int i;
	for (i = 0; i < n; i++)
	{
		int u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)
			+ range_min;
		printf(" %6d\n", u);
	}
}

void UNO::Run()
{
	Initial();
	LoadMusic();
	StartMusic();
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


