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

	window.setFramerateLimit(fps);	//设置游戏帧率

	gameOver = false;
	gameQuit = false;

	GameFlag = 1;

	myCard_num = 7;		//我的卡牌数量
	enemyCard_num = 7;	//敌方卡牌数量

	//music_state = 0;//音乐状态

	mutexClock = 0;

	isGameOverState = ncNo;	//初始化游戏的结束状态（未结束）
	isGameBegin = false;	//初始化游戏是否开始

	animationFlag = 0;	//变量为1时要进行游戏改变颜色

	
	InitialCard();
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

	//加载Gradient
	if (!tGradient.loadFromFile("./data/images/gradient.png"))
	{
		std::cout << "No Gradient panel image found." << " " << std::endl;
	}
	sGradient.setTexture(tGradient);

	//加载禁掉动画
	if (!tBan.loadFromFile("./data/images/download.png"))
	{
		std::cout << "No Ban panel image found." << " " << std::endl;
	}
	sBan.setTexture(tBan);

	//加载转换动画
	if (!tTran.loadFromFile("./data/images/change_clockwise.png"))
	{
		std::cout << "No Transition panel image found." << " " << std::endl;
	}
	sTran.setTexture(tTran);

	//加载字体
	if (!font.loadFromFile("./data/Fonts/ZCOOLKuaiLe-Regular.ttf"))
	{
		std::cout << "Not find Font" << std::endl;
	}

	//加载游戏输赢版面
	if (!tgameWin.loadFromFile("./data/images/gameWin.png"))
	{
		std::cout << "Not find gameWin.png";
	}
	sgameWin.setTexture(tgameWin);
	if (!tgameLose.loadFromFile("./data/images/gameLose.png"))
	{
		std::cout << "Not find gameLose.png";
	}
	sgameLose.setTexture(tgameLose);

	if (!tgameRestart.loadFromFile("./data/images/but_restart.png"))
	{
		std::cout << "Not find but_restart.png";
	}
	sgameRestart.setTexture(tgameRestart);
	if (!thomePage.loadFromFile("./data/images/but_home.png"))
	{
		std::cout << "Not find but_home.png";
	}
	shomePage.setTexture(thomePage);

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
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Q)
		{
			gameOver = true;
			isGameOverState = ncLOSE;
			startBtn.btnState = 1;
		}

		//鼠标交互（目前只设置了左右键单击）
		//我的卡牌点击监听

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			/*std::cout << "Mouse::Left Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;*/
		
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

			if (isGameOverState == ncNo) {

				if (GameFlag == 1 && aCardFlag == 0 && animationFlag == 0) {
					//我的卡牌点击监听
					for (int i = 0; i < myCard_num; i++) {
						if (myCard[i].Rect.contains(event.mouseButton.x, event.mouseButton.y)) {
							std::cout << aCardFlag << "用户出牌" << i << std::endl;
							sDiscardPile_i = myCard[i].card_x;
							sDiscardPile_j = myCard[i].card_y;
							if (myCard[i].card_x == 4) {

							}
							else {
								buttonColorNum = myCard[i].card_x;
							}
							//出牌的动画
							if (aCardFlag == 0) {
								std::cout << "用户出牌" << i << std::endl;
								CardClock.restart();
								aCardFlag = 1;
								cardFlag = 0;
								cardFlag1 = 1;
								aCardX1 = i * CARD_WIDTH / 2 + 300;
								aCardY1 = 750;
								aCardX2 = SDISCARDPILE_X;
								aCardY2 = SDISCARDPILE_Y;
								aCardX = aCardX1;
								aCardY = aCardY1;
								aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
								aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
								PauseTimer(remainingSeconds);
								std::cout << "aCardX" << aCardX << "aCardY" << aCardY << "aCardDx" << aCardDx << "aCradDy" << aCardDy << std::endl;
							}

							DeleteCard(myCard, myCard_num, i);
							myCard_num--;
							//切换成电脑操作
							/*GameFlag = 0;

							ExamineCard(0);


							countdownClock.restart();*/
						}

					}
					//摸牌的监听
					if (cardPileIntRect.contains(event.mouseButton.x, event.mouseButton.y) && myCard_num < 24) {
						std::cout << "用户摸牌" << std::endl;
						//摸牌的动画
						if (aCardFlag == 0) {
							CardClock.restart();
							aCardFlag = 1;
							cardFlag = 1;
							cardFlag1 = 1;
							PauseTimer(remainingSeconds);
							aCardX1 = CARDPILE_X;
							aCardY1 = CARDPILE_Y;
							aCardX = aCardX1;
							aCardY = aCardY1;
							aCardX2 = (myCard_num)*CARD_WIDTH / 2 + 300;
							aCardY2 = 750;
							aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
							aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
						}

						//TouchingCard(myCard, myCard_num);
						//myCard_num++;
						//切替换成电脑操作 
					}
				}
				if (animationFlag == 1 && GameFlag == 1 && aCardFlag == 0) {
					for (int i = 0; i < 4; i++) {
						if (RectColor[i].contains(event.mouseButton.x, event.mouseButton.y) && myCard_num < 24) {
							animationFlag = 2;
							changeClock.restart();
							std::cout << "变换颜色" << i << "颜色逻辑" << animationFlag << std::endl;
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
		//鼠标覆盖卡牌
		isMouseHover(Mouse::getPosition(window));

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
	int i, j;
	//获取鼠标当前点击的块


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
	int i, j;
#	//获取鼠标当前点击的块

	//检测是否点到了牌

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
	else {
		countdownClock.restart();
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
		countdownString = "Computer Remaining:  " + countdownString;
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
void UNO::PauseTimer(float p)
{
	std::cout << p << "暂停时间" << std::endl;
	mutexClock = 1;
	COUNTDOWN_DURATION = p;
}
//重新开始计时
void UNO::ContinueTimer(float p)
{
	std::cout << p << "开始时间" << std::endl;
	mutexClock = 0;
	pauseClockFlag = 1;
	COUNTDOWN_DURATION = p;
}

void UNO::Logic()
{
	if (GameFlag == 0 && aCardFlag == 0) {	//电脑操作逻辑判断

		/*changeClock.restart();
		changeTime2 = changeClock.getElapsedTime();*/
		/*if (changeTime2.asSeconds() < 2) {

		}
		else {
			ComputerLogic();
		}*/
		//std::cout << "remainingSeconds: " << remainingSeconds << std::endl;
		if (remainingSeconds < 7.1 && remainingSeconds > 6.9) {
			//std::cout << "remainingSeconds: " << remainingSeconds << std::endl;
			ComputerLogic();
		}
	}
	else {			//用户操作逻辑判断
		PlayerLogic();

	}
}

void UNO::isMouseHover(Vector2i mPoint)
{
	//std::cout << mPoint.x << "," << mPoint.y << std::endl;
	//获取鼠标坐标(mPoint.x,mPoint.y)
	for (int i = 0; i < myCard_num; i++)
	{
		//if鼠标在卡牌区域内
		if ((mPoint.x > myCard[i].Rect.left && mPoint.x < myCard[i].Rect.left + myCard[i].Rect.width) && (mPoint.y > myCard[i].Rect.top && mPoint.y < myCard[i].Rect.top + myCard[i].Rect.height))
		{
			myCard[i].mouseHover = true;
		}
		else
		{
			myCard[i].mouseHover = false;
		}
	}

}

void UNO::ExamineCard(int i) {		//i为1是用户变卡牌
	if (i && aCardFlag == 0) {
		if (sDiscardPile_i == 4 && sDiscardPile_j == 0) {		//变换颜色卡牌
			int a = rand() % 4;
			buttonColorNum = a;
		}
		else if (sDiscardPile_i == 4 && sDiscardPile_j == 1) {		//变换颜色并给对方加四张卡牌
			int a = rand() % 4;
			buttonColorNum = a;
			if (aCardFlag == 0) {
				CardClock.restart();
				PauseTimer(remainingSeconds);
				aCardFlag = 4;
				cardFlag2 = 1;
				cardFlag1 = 1;
				cardFlag = 1;
				CardClock.restart();
				aCardX1 = CARDPILE_X;
				aCardY1 = CARDPILE_Y + 50;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardX2 = (enemyCard_num)*CARD_WIDTH / 2 + 300;
				aCardY2 = 750;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
			}

			std::cout << "用户摸4牌" << std::endl;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 10) {		//禁掉下一个人的卡牌
			animationFlag = 5;
			changeClock.restart();
			std::cout << "ban::" << animationFlag << " " << remainingSeconds << std::endl;
			PauseTimer(remainingSeconds);
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 11) {		//逆转方向
			animationFlag = 7;
			changeClock.restart();
			std::cout << "ban::" << animationFlag << " " << remainingSeconds << std::endl;
			PauseTimer(remainingSeconds);
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 12) {		//给下一个人加俩张卡牌
			if (aCardFlag == 0) {
				CardClock.restart();
				PauseTimer(remainingSeconds);
				aCardFlag = 2;
				cardFlag1 = 1;
				cardFlag2 = 1;
				cardFlag = 1;
				CardClock.restart();
				aCardX1 = CARDPILE_X;
				aCardY1 = CARDPILE_Y + 30;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardX2 = (enemyCard_num)*CARD_WIDTH / 2 + 300;
				aCardY2 = 750;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
			}
			std::cout << "用户摸2牌" << std::endl;
		}
	}
	else if (aCardFlag == 0) {		//i为0是电脑变卡牌
		if (sDiscardPile_i == 4 && sDiscardPile_j == 0) {		//变换颜色卡牌
			animationFlag = 3;
			PauseTimer(remainingSeconds);
		}
		else if (sDiscardPile_i == 4 && sDiscardPile_j == 1) {		//变换颜色并给对方加四张卡牌
			animationFlag = 3;
			if (aCardFlag == 0) {
				CardClock.restart();
				PauseTimer(remainingSeconds);
				aCardFlag = 4;
				cardFlag1 = 0;
				cardFlag2 = 1;
				cardFlag = 1;
				CardClock.restart();
				aCardX1 = CARDPILE_X;
				aCardY1 = CARDPILE_Y - 30;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardX2 = (myCard_num)*CARD_WIDTH / 2 + 300;
				aCardY2 = 30;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
			}

			std::cout << "电脑摸4牌" << std::endl;
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 10) {		//禁掉下一个人的卡牌
			animationFlag = 5;
			changeClock.restart();
			std::cout << "ban::" << animationFlag << " " << remainingSeconds << std::endl;
			PauseTimer(remainingSeconds);
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 11) {		//逆转方向
			animationFlag = 7;
			changeClock.restart();
			std::cout << "ban::" << animationFlag << " " << remainingSeconds << std::endl;
			PauseTimer(remainingSeconds);
		}
		else if (sDiscardPile_i < 4 && sDiscardPile_j == 12) {		//给下一个人加俩张卡牌
			if (aCardFlag == 0) {
				CardClock.restart();
				PauseTimer(remainingSeconds);
				aCardFlag = 2;
				cardFlag1 = 0;
				cardFlag2 = 1;
				cardFlag = 1;
				CardClock.restart();
				aCardX1 = CARDPILE_X;
				aCardY1 = CARDPILE_Y - 30;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardX2 = (myCard_num)*CARD_WIDTH / 2 + 300;
				aCardY2 = 30;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
			}
			std::cout << "电脑摸2牌" << std::endl;
		}

	}
}

void UNO::ComputerLogic()
{
	//重置回合时间
	//countdownClock.restart();
	//声明这是computer的回合
	touch_flag = 1;
	std::cout << buttonColorNum << std::endl;
	for (int i = 0; i < enemyCard_num; i++) {
		std::cout << enemyCard[i].card_x << " " << enemyCard[i].card_y << "sDiscardPile  " << sDiscardPile_i << " " << sDiscardPile_j << " " << enemyCard_num << std::endl;
		if (enemyCard[i].card_x == buttonColorNum && aCardFlag == 0) {

			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			buttonColorNum = enemyCard[i].card_x;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}
			//出牌的动画
			if (aCardFlag == 0) {
				CardClock.restart();
				aCardFlag = 1;
				cardFlag = 0;
				cardFlag1 = 0;
				aCardX1 = i * CARD_WIDTH / 2 + 300;
				aCardY1 = 30;
				aCardX2 = SDISCARDPILE_X;
				aCardY2 = SDISCARDPILE_Y;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
				PauseTimer(remainingSeconds);
			}

			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;

			//切换成用户操作

			break;

		}
		else if (enemyCard[i].card_y == sDiscardPile_j && aCardFlag == 0) {
			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}
			//出牌的动画
			if (aCardFlag == 0) {
				CardClock.restart();
				aCardFlag = 1;
				cardFlag = 0;
				cardFlag1 = 0;
				aCardX1 = i * CARD_WIDTH / 2 + 300;
				aCardY1 = 30;
				aCardX2 = SDISCARDPILE_X;
				aCardY2 = SDISCARDPILE_Y;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
				PauseTimer(remainingSeconds);
			}
			//切换成用户操作
			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;
			break;
		}
		else if (enemyCard[i].card_x == 4 && aCardFlag == 0) {
			std::cout << "电脑出牌" << i << std::endl;
			sDiscardPile_i = enemyCard[i].card_x;
			sDiscardPile_j = enemyCard[i].card_y;
			if (enemyCard[i].card_x == 4) {

			}
			else {
				buttonColorNum = enemyCard[i].card_x;
			}

			//出牌的动画
			if (aCardFlag == 0) {
				CardClock.restart();
				aCardFlag = 1;
				cardFlag = 0;
				cardFlag1 = 0;
				aCardX1 = i * CARD_WIDTH / 2 + 300;
				aCardY1 = 30;
				aCardX2 = SDISCARDPILE_X;
				aCardY2 = SDISCARDPILE_Y;
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
				PauseTimer(remainingSeconds);
			}
			//切换成用户操作
			DeleteCard(enemyCard, enemyCard_num, i);
			enemyCard_num--;
			break;
		}
	}
	if (touch_flag) {
		std::cout << "电脑摸牌" << std::endl;

		if (aCardFlag == 0) {
			CardClock.restart();
			PauseTimer(remainingSeconds);
			aCardFlag = 1;
			cardFlag1 = 0;
			cardFlag = 1;
			CardClock.restart();
			aCardX1 = CARDPILE_X;
			aCardY1 = CARDPILE_Y - 30;
			aCardX = aCardX1;
			aCardY = aCardY1;
			aCardX2 = (enemyCard_num)*CARD_WIDTH / 2 + 300;
			aCardY2 = 30;
			aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
			aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
		}

		//切替换成电脑操作 
		GameFlag = 1;
		//ExamineCard(GameFlag);
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
	//std::cout << "remaningSeconds: " << remainingSeconds << std::endl;
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
			sRectColor.setColor(sf::Color(255, 255, 255, 255));
			window.draw(sRectColor);
		}
		else {
			sRectColor.setTextureRect(sf::IntRect(0 * 104, 0, 104, 102));
			sRectColor.setPosition(1140, 426);
			sRectColor.setColor(sf::Color(0, 0, 0, 0));
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
			sGradient.setTextureRect(sf::IntRect(myCard[i].gradient_i * CARD_WIDTH, 0, CARD_WIDTH, CARD_HEIGHT));
			myCard[i].gradientCount++;
			myCard[i].gradientColorChangeCount++;
			if (myCard[i].gradientCount == 6) {
				myCard[i].gradientCount = 0;
				myCard[i].gradient_i++;
				myCard[i].gradient_i = myCard[i].gradient_i % 10;
				//if (myCard[i].gradient_i == 0) {
				//}
			}
			if (myCard[i].gradientColorChangeCount == 1)
			{
				sGradient.setColor(Color(255, 0, 255));
			}
			else if (myCard[i].gradientColorChangeCount == 11)
			{
				sGradient.setColor(Color(255, 255, 0));
			}
			else if (myCard[i].gradientColorChangeCount == 21)
			{
				sGradient.setColor(Color(0, 255, 255));
			}
			else if (myCard[i].gradientColorChangeCount == 31)
			{
				sGradient.setColor(Color(0, 0, 255));
			}
			else if (myCard[i].gradientColorChangeCount == 41)
			{
				sGradient.setColor(Color(0, 255, 0));
			}
			else if (myCard[i].gradientColorChangeCount == 51)
			{
				sGradient.setColor(Color(255, 0, 0));
			}
			else if (myCard[i].gradientColorChangeCount >= 61)
			{
				myCard[i].gradientColorChangeCount = 0;
			}
			if (i < myCard_num - 1) {
				myCard[i].Rect.left = i * CARD_WIDTH / 2 + 300;
				myCard[i].Rect.top = 750;
				myCard[i].Rect.width = CARD_WIDTH / 2;
				myCard[i].Rect.height = CARD_HEIGHT;
				//如果鼠标覆盖到牌上，则y坐标上移
				if (myCard[i].mouseHover == true) {
					myCard[i].Rect.top -= 40;
				}
			}
			else {
				myCard[i].Rect.left = i * CARD_WIDTH / 2 + 300;
				myCard[i].Rect.top = 750;
				myCard[i].Rect.width = CARD_WIDTH;
				myCard[i].Rect.height = CARD_HEIGHT;
				//如果鼠标覆盖到牌上，则y坐标上移
				if (myCard[i].mouseHover == true) {
					myCard[i].Rect.top -= 40;
				}
			}

			sCards.setTextureRect(sf::IntRect(myCard[i].card_y * CARD_WIDTH, myCard[i].card_x * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
			sCards.setPosition(myCard[i].Rect.left, myCard[i].Rect.top);
			window.draw(sCards);
			if (myCard[i].card_x == buttonColorNum) {
				//std::cout << "adw" << myCard[i].card_x << " " << buttonColorNum << std::endl;
				sGradient.setPosition(myCard[i].Rect.left, myCard[i].Rect.top);
				window.draw(sGradient);
			}
			else if (myCard[i].card_x == 4) {
				sGradient.setPosition(myCard[i].Rect.left, myCard[i].Rect.top);
				window.draw(sGradient);
			}
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
		sCards.setPosition(CARDPILE_X, CARDPILE_Y);
		cardPileIntRect.left = 805;
		cardPileIntRect.top = 420;
		cardPileIntRect.width = CARD_WIDTH;
		cardPileIntRect.height = CARD_HEIGHT;
		window.draw(sCards);

		if (aCardFlag) {
			CardAnimation(aCardX1, aCardY1, aCardX2, aCardY2, cardFlag);
		}
		BtTime2 = BtClock.getElapsedTime();
		changeTime2 = changeClock.getElapsedTime();
		//std::cout << "ani" << animationFlag << " " << BtTime2.asSeconds() << std::endl;


		if (animationFlag == 1) {
			sChangeColorPanel.setPosition(960 - 275, 540 - 305 * 0.75 * 0.5);
			sChangeColorPanel.setScale(sf::Vector2f(1, 0.75));
			window.draw(sChangeColorPanel);
			for (int i = 0; i < 4; i++) {
				sRectColor.setTextureRect(sf::IntRect(i * 104, 0, 104, 102));
				sRectColor.setPosition(585 + 25 + 104 + i * 132, 540 - 305 * 0.75 * 0.5 + 64);
				sRectColor.setColor(sf::Color(255, 255, 255, 255));
				RectColor[i].left = 585 + 25 + 104 + i * 132;
				RectColor[i].top = 540 - 305 * 0.75 * 0.5 + 64;
				RectColor[i].width = 104;
				RectColor[i].height = 102;
				window.draw(sRectColor);
			}
		}
		else if (animationFlag == 2) {
			if (changeTime2.asSeconds() <= 1) {
				//std::cout << "绘制变换动画1" << std::endl;
				sChangeColorAnimation.setTextureRect(sf::IntRect(changeJ * 328, changeI * 315, 328, 315));
				sChangeColorAnimation.setPosition(960 - 328 / 2, 540 - 315 / 2);
				changeJ1 = changeJ1 + 5;
				changeI1 = changeI1 + 5;
				if (changeJ1 % 10 == 0) {
					changeJ = (changeJ1 / 10) % 6;
				}
				else if (changeJ1 == 60) {
					changeJ1 = 0;
				}
				if (changeI1 % 10 == 0) {
					changeI = (changeI1 / 10) % 3;
				}
				else if (changeI1 == 30) {
					changeI1 = 0;
				}
				changeJ = changeJ % 6;
				changeI = changeI % 3;
				window.draw(sChangeColorAnimation);
			}
			else if (changeTime2.asSeconds() <= 3) {
				//std::cout << "绘制变换动画2" << std::endl;
				switch (buttonColorNum)
				{
				case 0:
					changeI = 1;
					changeJ = 0;
					break;
				case 1:
					changeI = 0;
					changeJ = 2;
					break;
				case 2:
					changeI = 2;
					changeJ = 2;
					break;
				case 3:
					changeI = 1;
					changeJ = 4;
					break;
				default:
					break;
				}
				sChangeColorAnimation.setTextureRect(sf::IntRect(changeJ * 328, changeI * 315, 328, 315));
				sChangeColorAnimation.setPosition(960 - 328 / 2, 540 - 315 / 2);
				sChangeColorAnimation.setScale(changeScaleX, changeScaleY);
				changeScaleX = changeScaleX + 0.1;
				changeScaleY = changeScaleY + 0.1;
				window.draw(sChangeColorAnimation);
			}
			else {
				changeI = 0;
				changeJ = 0;
				changeScaleX = 1;
				changeScaleY = 1;
				animationFlag = 0;
				GameFlag = 0;
				ContinueTimer(COUNTDOWN_DURATION);
				std::cout << "change" << animationFlag << std::endl;
			}
		}
		else if (animationFlag == 6) {	//禁掉动画
			PauseTimer(remainingSeconds);
			//std::cout << "BtTime2  " << BtTime2.asSeconds() << std::endl;
			if (BtTime2.asSeconds() <= 2) {
				sBan.setPosition(960, 540);
				sBan.setOrigin(146, 150);
				sBan.setScale(banScale, banScale);
				banScale = banScale + banScaleSpeed;
				if (banScale > banScaleMax) {
					banScaleSpeed = -banScaleSpeed;
				}
				else if (banScale < 1) {
					banScaleSpeed = -banScaleSpeed;
				}
				window.draw(sBan);
			}
			/*else if (changeTime2.asSeconds() <= 2) {

			}
			else if (changeTime2.asSeconds() <= 3) {

			}*/
			else {

				animationFlag = 0;
				GameFlag = GameFlag;
				ContinueTimer(durationTime);
				std::cout << "禁掉动画" << animationFlag << std::endl;
			}
		}
		else if (animationFlag == 8) {	//转换顺序动画
			if (BtTime2.asSeconds() <= 1.5) {

				sTran.setOrigin(146, 150);
				sTran.setPosition(960, 540);
				sTran.setScale(straScale, straScale);
				//sTran.setRotation(traRotate);
				sTran.rotate(traRotate);
				window.draw(sTran);
			}
			else if (BtTime2.asSeconds() <= 3) {

				//sTran.setOrigin(146, 150);
				sTran.setPosition(960, 540);
				sTran.setScale(straScale, straScale);
				sTran.rotate(-traRotate);
				window.draw(sTran);
			}
			else {

				animationFlag = 0;
				GameFlag = GameFlag;
				ContinueTimer(durationTime);
				std::cout << "转换动画" << animationFlag << std::endl;
			}
		}


	}




	//DrawButton();


	/*if (isGameOverState)
		DrawGameEnd();*/

	window.display();
}

void UNO::CardAnimation(int x1, int y1, int x2, int y2, bool flag) {	//x1，y1是起始位置，x2，y2是终点位置，flag为1是摸牌，flag为0是出牌
	CardTime2 = CardClock.getElapsedTime();
	//std::cout << "aCardFlag:" << aCardFlag << "CardFlag:" << cardFlag << std::endl;
	if (CardTime2.asSeconds() <= cardSpeed) {
		if (cardFlag) {
			if (cardFlag1) {
				aCardX = aCardX + aCardDx;
				aCardY = aCardY + aCardDy;
				sCards.setTextureRect(sf::IntRect(cardPile_j * CARD_WIDTH, cardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));

				//std::cout << "X:" << aCardX << " Y:" << aCardY << "dX:" << aCardDx << "dY:" << aCardDy << std::endl;

				sCards.setPosition(aCardX, aCardY);
				window.draw(sCards);
			}
			else {
				aCardX = aCardX + aCardDx;
				aCardY = aCardY + aCardDy;
				sCards.setTextureRect(sf::IntRect(cardPile_j * CARD_WIDTH, cardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
				//std::cout << "X:" << aCardX << " Y:" << aCardY << "dX:" << aCardDx << "dY:" << aCardDy << std::endl;

				sCards.setPosition(aCardX, aCardY);
				window.draw(sCards);
			}
		}
		else {
			//std::cout << "X:" << aCardX << " Y:" << aCardY << "dX:" << aCardDx << "dY:" << aCardDy << std::endl;
			if (cardFlag1) {
				aCardX = aCardX + aCardDx;
				aCardY = aCardY + aCardDy;
				sCards.setTextureRect(sf::IntRect(sDiscardPile_j * CARD_WIDTH, sDiscardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));

				//std::cout << "X:" << aCardX << " Y:" << aCardY << "dX:" << aCardDx << "dY:" << aCardDy << std::endl;

				sCards.setPosition(aCardX, aCardY);
				window.draw(sCards);
			}
			else {
				aCardX = aCardX + aCardDx;
				aCardY = aCardY + aCardDy;
				sCards.setTextureRect(sf::IntRect(sDiscardPile_j * CARD_WIDTH, sDiscardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
				//std::cout << "X:" << aCardX << " Y:" << aCardY << "dX:" << aCardDx << "dY:" << aCardDy << std::endl;

				sCards.setPosition(aCardX, aCardY);
				window.draw(sCards);
			}
		}
	}
	else {
		if (cardFlag)	//1为摸牌
		{
			if (cardFlag1) {
				TouchingCard(myCard, myCard_num);
				myCard_num++;
				//GameFlag = 1;
				if (cardFlag2) {
					GameFlag = 0;
					cardFlag2 = 1;
				}
				else {
					GameFlag = 1;
				}
				//ExamineCard(GameFlag);
				countdownClock.restart();
				ContinueTimer(durationTime);
				aCardFlag--;
			}
			else
			{
				TouchingCard(enemyCard, enemyCard_num);
				enemyCard_num++;
				//GameFlag = 0;
				if (cardFlag2) {
					GameFlag = 1;
					cardFlag2 = 0;
				}
				else {
					GameFlag = 0;
				}
				//ExamineCard(GameFlag);
				countdownClock.restart();
				ContinueTimer(durationTime);
				aCardFlag--;
			}
		}
		else	//0为出牌
		{
			if (cardFlag1) {
				std::cout << "用户删卡" << std::endl;
				/*DeleteCard(myCard, myCard_num, (aCardX1 - 300) / CARD_WIDTH * 2);
				myCard_num--;*/
				//GameFlag = 0;

				aCardFlag--;
				ExamineCard(0);

				if (animationFlag == 5) {
					animationFlag = 6;
					GameFlag = 1;
					BtClock.restart();
					PauseTimer(remainingSeconds);
				}
				else if (animationFlag == 7) {
					animationFlag = 8;
					GameFlag = 1;
					BtClock.restart();
					PauseTimer(remainingSeconds);
				}
				else if (animationFlag == 3) {
					GameFlag = 1;
				}
				else {
					GameFlag = 0;
					ContinueTimer(durationTime);
				}

				countdownClock.restart();
				ContinueTimer(durationTime);
			}
			else
			{
				std::cout << "电脑删卡" << std::endl;
				/*DeleteCard(enemyCard, enemyCard_num, (aCardX1 - 300) / CARD_WIDTH * 2);
				enemyCard_num--;*/



				aCardFlag--;
				ExamineCard(1);

				//countdownClock.restart();

				if (animationFlag == 5) {
					ContinueTimer(COUNTDOWN_DURATION);
					animationFlag = 6;
					GameFlag = 0;
					BtClock.restart();
					std::cout << "animationBan" << animationFlag << std::endl;
					PauseTimer(remainingSeconds);
				}
				else if (animationFlag == 7) {
					ContinueTimer(COUNTDOWN_DURATION);
					animationFlag = 8;
					GameFlag = 0;
					BtClock.restart();
					std::cout << "animationBan" << animationFlag << std::endl;
					PauseTimer(remainingSeconds);
				}
				else {
					GameFlag = 1;
					ContinueTimer(durationTime);
				}

				countdownClock.restart();
				ContinueTimer(durationTime);

			}
		}
		ContinueTimer(COUNTDOWN_DURATION);

		if (aCardFlag) {
			if (cardFlag) {
				CardClock.restart();
				PauseTimer(remainingSeconds);
				aCardX = aCardX1;
				aCardY = aCardY1;
				aCardX2 = (myCard_num)*CARD_WIDTH / 2 + 300;
				aCardY2 = aCardY2;
				aCardDx = (aCardX2 - aCardX1) / cardSpeed / fps;
				aCardDy = (aCardY2 - aCardY1) / cardSpeed / fps;
			}
			else {

			}
		}
		else {
			if (animationFlag == 3) {
				animationFlag = 1;
				PauseTimer(remainingSeconds);
			}
		}
	}

}

void UNO::DrawButton() {

}
void UNO::DrawTurn() {

}

void UNO::GamePause() {

}

void UNO::DrawGameEnd()
{
	Vector2i LeftCorner;
	int PanelWidth = sgameWin.getLocalBounds().width;
	int PanleHeight = sgameWin.getLocalBounds().height;
	LeftCorner.x = (windowWidth - PanelWidth) / 2;
	LeftCorner.y = (windowHeight - PanleHeight) / 2;

	//绘制游戏胜利或失败面板
	if (isGameOverState == ncWIN)
	{
		sgameWin.setPosition(LeftCorner.x, LeftCorner.y);
		window.draw(sgameWin);
	}
	else if (isGameOverState == ncLOSE)
	{
		sgameLose.setPosition(LeftCorner.x, LeftCorner.y);
		window.draw(sgameLose);
	}
	Vector2i score;
	score.x = SCORE_X;
	score.y = SCORE_Y;
	//用Text对象去显示score
	int myScore = 0;
	for (int i = 0; i < enemyCard_num; i++) {
		if (enemyCard[i].card_x < 4 && enemyCard[i].card_y <= 9)
		{
			myScore += enemyCard[i].card_y * 1;
		}
		else if (enemyCard[i].card_x < 4 && enemyCard[i].card_y > 9)
		{
			if (enemyCard[i].card_y == 12)
			{
				myScore += 20;
			}
			else
			{
				myScore += 10;
			}
		}
		else if (enemyCard[i].card_x == 4)
		{
			if (enemyCard[i].card_y == 0)
			{
				myScore += 10;
			}
			else if (enemyCard[i].card_y == 1)
			{
				myScore += 40;
			}
		}
	
	}
	
	std::string scoreString = std::to_string(static_cast<int>(myScore)); //将整数类型的myScore强制转换为字符串类型并赋值给scoreString变量
	sf::Text scoreText(scoreString, font, 40);
	scoreText.setPosition(score.x + LeftCorner.x, score.y + LeftCorner.y);
	window.draw(scoreText);
	
	//绘制游戏重新开始按钮
	Vector2i btn;
	btn.x = LeftCorner.x ;
	btn.y = LeftCorner.y + PanleHeight;
	btn.x += (PanelWidth - sgameRestart.getLocalBounds().width - shomePage.getLocalBounds().width) / 3;
	sgameRestart.setPosition(btn.x, btn.y);
	sgameRestart.setTextureRect(sf::IntRect(0, 0, sgameRestart.getLocalBounds().width, sgameRestart.getLocalBounds().height));
	igameRestart.left = btn.x;
	igameRestart.top = btn.y;
	igameRestart.width = sgameRestart.getLocalBounds().width;
	igameRestart.height = sgameRestart.getLocalBounds().height;
	window.draw(sgameRestart);

	//绘制返回主页的按钮
	btn.x += (PanelWidth - sgameRestart.getLocalBounds().width - shomePage.getLocalBounds().width) / 3 + sgameRestart.getLocalBounds().width;
	shomePage.setPosition(btn.x, btn.y);
	shomePage.setTextureRect(sf::IntRect(0, 0, shomePage.getLocalBounds().width, shomePage.getLocalBounds().height));
	ihomePage.left = btn.x;
	ihomePage.top = btn.y;
	ihomePage.width = shomePage.getLocalBounds().width;
	ihomePage.height = shomePage.getLocalBounds().height;
	window.draw(shomePage);

	window.display();
}

void UNO::gameEndEvent()
{
	Event e;
	while (window.pollEvent(e))
	{
		//鼠标左键事件
		if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
		{
			//重新开始游戏按钮
			if (igameRestart.contains(e.mouseButton.x, e.mouseButton.y))
			{
				isGameBegin = false;
				isGameOverState = ncNo;
				gameOver = false;
				gameQuit = false;
			}
			// 返回主页按钮
			if (ihomePage.contains(e.mouseButton.x, e.mouseButton.y))
			{
				isGameBegin = false;
				isGameOverState = ncNo;
				gameOver = false;
			}
			
			//音量按钮的检测
			if (MusicIntRect.contains(e.mouseButton.x, e.mouseButton.y)) {
				music_state = 1 - music_state;
				std::cout << music_state << std::endl;
				if (!music_state) {
					StartMusic();
				}
				else {
					StopMusic();
				}
			}
			//音乐按钮
			MusicBtn.setTextureRect(sf::IntRect(music_state * 71, 0, 71, 71));
			MusicBtn.setPosition(MUSIC_X, MUSIC_Y);
			window.draw(MusicBtn);
			DrawGameEnd();
		}
		
		/*if (e.type == Event::EventType::KeyReleased && e.key.code == Keyboard::Y)
		{
			gameOver = false;
		}*/
		//可以通过点击取消和按下键盘Esc键退出游戏
		if (e.type == sf::Event::Closed)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}
		if (e.type == sf::Event::EventType::KeyReleased && e.key.code == sf::Keyboard::Escape)
		{
			window.close();	//窗口可以移动、调整大小和最小化。但是如果需要关闭，想要自己去调用close()函数
			gameQuit = true;
		}
	}
}

void UNO::Run()
{
	LoadMesiaData();
	LoadMusic();
	StartMusic();
	do
	{
		Initial();
		
		while (window.isOpen() && gameOver == false)
		{

			Input();

			Logic();
			//std::cout << isGameBegin;
			Draw();

		}
		DrawGameEnd();
		while (gameOver)
		{
			gameEndEvent();
		}
		std::cout << isGameBegin;
	} while (!gameQuit && window.isOpen());

}


