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

	window.setFramerateLimit(60);	//������Ϸ֡��

	gameOver = false;
	gameQuit = false;

	GameFlag = 1;

	myCard_num = 7;		//�ҵĿ�������
	enemyCard_num = 7;	//�з���������

	music_state = 0;//����״̬


	isGameOverState = ncNo;	//��ʼ����Ϸ�Ľ���״̬��δ������
	isGameBegin = false;	//��ʼ����Ϸ�Ƿ�ʼ

	LoadMesiaData();
}

void UNO::InitialCard() {
	srand(time(NULL));
	int a;		//�����
	int x, y;
	myCard_num = 7;
	enemyCard_num = 7;
	for (int i = 0; i < myCard_num; i++) {
		a = rand() % 53;
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
		a = rand() % 54 + 1;
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

	std::cout << "��Ϸ���ݳ�ʼ���Ѻ�" << std::endl;
}

void UNO::LoadMesiaData()
{
	if (!tBackground[0].loadFromFile("./data/images/bg_menu.jpg"))
	{
		std::cout << "No bg_menu image found." << std::endl;
	}
	sBackground[0].setTexture(tBackground[0]);
	//sBackground[0].setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%

	if (!tBackground[1].loadFromFile("./data/images/bg_game.jpg"))
	{
		std::cout << "No bg_game image found." << std::endl;
	}
	sBackground[1].setTexture(tBackground[1]);
	//sBackground[1].setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%

	//���ؿ�ʼ��ť
	//startBtn.setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%
	if (!tStartBtnNormal.loadFromFile("./data/images/but_play.png"))
	{
		std::cout << "No but_play image found." << std::endl;
	}
	startBtn.SetTextures(tStartBtnNormal, tStartBtnNormal, tStartBtnNormal);
	//startBtn.setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%

	//���������������޸�
	if (!tMusicBtn.loadFromFile("./data/images/audio_icon.png")) {
		std::cout << "No audio_icon image found." << std::endl;
	}
	MusicBtn.setTexture(tMusicBtn);
	//Music1Btn.setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%	



	//�˳���ť
	if (!tExitBtnNormal.loadFromFile("./data/images/but_exit.png"))
	{
		std::cout << "No but_exit image found." << std::endl;
	}
	exitBtn.SetTextures(tExitBtnNormal, tExitBtnNormal, tExitBtnNormal);
	//exitBtn.setScale(0.8f, 0.8f);//������ͼƬ�ȱ���С��80%


	//���ؿ�������
	if (!tCards.loadFromFile("./data/images/cards.png"))
	{
		std::cout << "No cards image found." << std::endl;
	}
	sCards.setTexture(tCards);

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {

			if (!tCard_1[i][j].loadFromFile("./data/images/cards.png", sf::IntRect(j * CARD_WIDTH, i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT)))
			{
				std::cout << "No cards image found." << i << " " << j << std::endl;
			}
			sCard_1[i][j].SetTextures(tCard_1[i][j], tCard_1[i][j], tCard_1[i][j]);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (!tCard_2[i].loadFromFile("./data/images/cards.png", sf::IntRect(i * CARD_WIDTH, 4 * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT)))
		{
			std::cout << "No cards image found." << i << " " << std::endl;
		}
		sCard_2[i].SetTextures(tCard_2[i], tCard_2[i], tCard_2[i]);
	}*/

	//�ĸ�����������


	if (!tRectColor.loadFromFile("./data/images/colors.png"/*, sf::IntRect(i * 104, 0, 104, 102)*/))
	{
		std::cout << "No colors image found." << " " << std::endl;
	}
	sRectColor.setTexture(tRectColor);

	//uno��ť������
	if (!tUnoBtn.loadFromFile("./data/images/but_uno.png"))
	{
		std::cout << "No unoBtn image found." << " " << std::endl;
	}
	UnoBtn.SetTextures(tUnoBtn, tUnoBtn, tUnoBtn);

	//uno_cloud������
	for (int i = 0; i < 2; i++) {
		if (!tUno_cloud[i].loadFromFile("./data/images/cloud.png", sf::IntRect(i * 261, 0, 261, 194)))
		{
			std::cout << "No colors image found." << i << " " << std::endl;
		}
		sUno_cloud[i].setTexture(tUno_cloud[i]);
	}
	//��������
	if (!font.loadFromFile("./data/Fonts/ZCOOLKuaiLe-Regular.ttf"))
	{
		std::cout << "Not find Font" << std::endl;
	}

	std::cout << "���������Ѻ�" << std::endl;

}

void UNO::LoadMusic() {

	if (!bj_music_file.loadFromFile("./data/music/bj.ogg")) {
		std::cout << "No uno music found." << std::endl;
	}
	bj_music.setBuffer(bj_music_file);

}

//���Ʒ��ƶ���
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
		//����ͨ�����ȡ���Ͱ��¼���Esc���˳���Ϸ
		if (event.type == sf::Event::Closed)
		{
			window.close();	//���ڿ����ƶ���������С����С�������������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();	//���ڿ����ƶ���������С����С�������������Ҫ�رգ���Ҫ�Լ�ȥ����close()����
			gameQuit = true;
		}

		//��꽻����Ŀǰֻ���������Ҽ�������
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Mouse::Left Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;
			if (isGameOverState == ncNo) {
				//������ť�ļ��
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
				//�ҵĿ��Ƶ������
				for (int i = 0; i < myCard_num; i++) {
					if (myCard[i].Rect.contains(event.mouseButton.x, event.mouseButton.y)) {
						std::cout << "����" << i << std::endl;

						myCard_num--;
						sDiscardPile_i = myCard[i].card_x;
						sDiscardPile_j = myCard[i].card_y;
						buttonColorNum = myCard[i].card_x;
						DeleteCard(myCard, myCard_num, i);
						//�л��ɵ��Բ���
						GameFlag = 0;
						countdownClock.restart();
					}
				}
				//���Ƶļ���
				if (cardPileIntRect.contains(event.mouseButton.x, event.mouseButton.y)) {
					std::cout << "����" << std::endl;
					TouchingCard(myCard, myCard_num);
					myCard_num++;
					//���滻�ɵ��Բ���
					GameFlag = 0;
					countdownClock.restart();
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			std::cout << "Mouse::Right Pressed" << std::endl;
			std::cout << "Mouse.X:" << event.mouseButton.x << std::endl;
			std::cout << "Mouse.Y:" << event.mouseButton.y << std::endl;
		}
		//������
		//if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		//{
		//	if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300)
		//	{
		//		LButtonDown(Mouse::getPosition(window));	//��굥��
		//		std::cout << "Mouse::Left Pressed" << std::endl;
		//	}
		//	else
		//	{
		//		//LButtinDblClk(Mouse::getPosition(window));	//���˫��
		//		std::cout << "Mouse::Left Double Clicked" << std::endl;
		//	}
		//}
		//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		//{
		//	if (mouseDlbClkReady)
		//	{
		//		mouseClickTimer.restart();	//�������ʱ������¼����¼�ʱ
		//		std::cout << "Mouse::Left Released" << std::endl;
		//	}
		//}
		//����Ҽ�
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
		{
			RButtonDown(Mouse::getPosition(window));	//��굥��

		}

	}


	//�л�����
	if (!isGameBegin) {

		if (startBtn.CheckMouse(mousePosition, event) == 3) {

			std::cout << "��Ϸ��" << std::endl;
			InitialCard();
			DrawDealCard();
			isGameBegin = true;
			exitBtn.btnState = 1;
			countdownClock.restart();
		}



	}
	else {
		//////////��Ϸ�е������///////////////////////////////

		if (exitBtn.CheckMouse(mousePosition, event) == 3) {

			//�˳���Ϸ
			std::cout << "��ʼҳ��" << std::endl;
			startBtn.btnState = 1;
			isGameBegin = false;
		}
	}

}

void UNO::RButtonDown(Vector2i mPoint)	//����һ�
{
	int i, j;
	//��ȡ��굱ǰ����Ŀ�


}

void UNO::TouchingCard(Card* card, int cardNum) {
	int a;		//�����
	int x, y;
	a = rand() % 53;
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

void UNO::LButtonDown(Vector2i mPoint)	//������
{
	int i, j;
#	//��ȡ��굱ǰ����Ŀ�

	//����Ƿ�㵽����

}

//������Ϸ����ʱ�䣨��ʱ����
//������Ϸ����ʱ�䣨��ʱ����
void UNO::DrawTimer()
{

	// ����ʣ���ʱ��
	float elapsedSeconds = countdownClock.getElapsedTime().asSeconds(); //��ʱ��ת��Ϊ��������¼�Ѿ����ŵ�ʱ��
	float remainingSeconds = COUNTDOWN_DURATION - elapsedSeconds; //ͨ���õ���ʱ��ʱ���ȥ�Ѿ����ŵ�ʱ�䣬�������ʣ�¶�������ܵ���Ŀ�굹��ʱʱ��

	//��鵹��ʱ�Ƿ����
	if (remainingSeconds <= 0.f)
	{
		//�޸�GameFlag
		if (GameFlag == 0)
		{
			GameFlag = 1;
		}
		else
		{
			GameFlag = 0;
		}

		//���¿�ʼ����ʱ
		countdownClock.restart();
		remainingSeconds = COUNTDOWN_DURATION;
	}

	//����ʣ��ʱ������һ������ʱ��
	std::string countdownString = std::to_string(static_cast<int>(remainingSeconds)); //���������͵�remainingSecondsǿ��ת��Ϊ�ַ������Ͳ���ֵ��countdownString����
	if (GameFlag == 0)
	{
		countdownString = "Computer Remaining:  " + countdownString;
	}
	else
	{
		countdownString = "Player Remaining:  " + countdownString;
	}

	//��Text����ȥ��ʾ����ʱ����
	sf::Text countdownText(countdownString, font, 50);
	countdownText.setPosition(window.getSize().x / 4.f, window.getSize().y / 2.f);
	countdownText.setOrigin(countdownText.getLocalBounds().width / 2.f, countdownText.getLocalBounds().height / 2.f);

	window.draw(countdownText);
}

void UNO::Logic()
{
	if (GameFlag == 0) {	//���Բ����߼��ж�

		ComputerLogic();

	}
	else {			//�û������߼��ж�
		PlayerLogic();
	}
}

void UNO::ComputerLogic()
{
	//���ûغ�ʱ��
	//countdownClock.restart();
	//��������computer�Ļغ�
	GameFlag = 0;

}

void UNO::PlayerLogic()
{
	//���ûغ�ʱ��
	//countdownClock.restart();
	//��������player�Ļغ�
	GameFlag = 1;

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
	window.clear(); //����

	//���Ʊ���
	//std::cout << stage_state << std::endl;
	if (!isGameBegin) {

		sBackground[0].setPosition(0, 0);
		window.draw(sBackground[0]);

		//��ʼ��ť
		startBtn.setPosition(PLAY_X, PLAY_Y);
		window.draw(startBtn);

		//���ְ�ť
		MusicBtn.setTextureRect(sf::IntRect(music_state * 71, 0, 71, 71));
		MusicBtn.setPosition(MUSIC_X, MUSIC_Y);
		MusicIntRect.left = MUSIC_X;
		MusicIntRect.top = MUSIC_Y;
		MusicIntRect.width = 71;
		MusicIntRect.height = 71;
		window.draw(MusicBtn);


	}
	else {
		//��Ϸ�еı�������
		sBackground[1].setPosition(0, 0);
		window.draw(sBackground[1]);

		DrawTimer();

		//���ְ�ť
		MusicBtn.setTextureRect(sf::IntRect(music_state * 71, 0, 71, 71));
		MusicBtn.setPosition(MUSIC_X, MUSIC_Y);
		MusicIntRect.left = MUSIC_X;
		MusicIntRect.top = MUSIC_Y;
		MusicIntRect.width = 71;
		MusicIntRect.height = 71;
		window.draw(MusicBtn);

		//�˳���ť
		exitBtn.setPosition(EXIT_X, EXIT_Y);
		window.draw(exitBtn);

		//��ɫ����
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



		//uno��ť
		UnoBtn.setPosition(1140, 556);
		window.draw(UnoBtn);

		if (drawUnoFlag == true) {
			time2 = clock.getElapsedTime();
			if (time2.asSeconds() <= 3) {
				sUno_cloud[0].setPosition(1240, 556 - 150);
				window.draw(sUno_cloud[0]);
			}
			else {
				drawUnoFlag = false;
			}
		}
		else {

		}


		//���Ƶĵط�
		sDiscardPile.setPosition(961, 420);
		window.draw(sDiscardPile);

		//�����ҵĿ���
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
		//����enemy����
		for (int i = 0; i < enemyCard_num; i++) {
			sCards.setTextureRect(sf::IntRect(enemyCard[i].card_y * CARD_WIDTH, enemyCard[i].card_x * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
			sCards.setPosition(i * CARD_WIDTH / 2 + 300, 30);
			window.draw(sCards);
		}
		//���ƵĻ���
		sCards.setTextureRect(sf::IntRect(sDiscardPile_j * CARD_WIDTH, sDiscardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
		sCards.setPosition(961, 420);
		window.draw(sCards);
		//���ƵĻ���
		sCards.setTextureRect(sf::IntRect(cardPile_j * CARD_WIDTH, cardPile_i * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));
		sCards.setPosition(805, 420);
		cardPileIntRect.left = 805;
		cardPileIntRect.top = 420;
		cardPileIntRect.width = CARD_WIDTH;
		cardPileIntRect.height = CARD_HEIGHT;
		window.draw(sCards);
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
	Vector2i LeftCorner; //���ڼ�¼��ť�ڴ��ڵ�λ��
	int ButtonWidth = 71;
	int ButtonHeight = 71;
	int detaX;
	detaX = windowWidth - ButtonWidth; //ָ��x����
	LeftCorner.y = windowHeight - ButtonHeight;//ָ���߶�

	//music_on,
	LeftCorner.x = detaX;
	sMusicBtnNormal.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //�ĸ�����ֵ���ֱ��ʾ���ϽǶ���ĺ�����������꣬�Լ����εĿ�Ⱥ͸߶ȡ�
	sMusicBtnNormal.setPosition(LeftCorner.x, LeftCorner.y);
	music_on.left = LeftCorner.x;
	music_on.top = LeftCorner.y;
	music_on.width = ButtonWidth;
	music_on.height = ButtonHeight;
	window.draw(sMusicBtnNormal);
	//music_off
	LeftCorner.x = detaX;
	sMusicBtnNormal.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //�ĸ�����ֵ���ֱ��ʾ���ϽǶ���ĺ�����������꣬�Լ����εĿ�Ⱥ͸߶ȡ�
	sMusicBtnNormal.setPosition(LeftCorner.x, LeftCorner.y);
	music_off.left = LeftCorner.x;
	music_off.top = LeftCorner.y;
	music_off.width = ButtonWidth;
	music_off.height = ButtonHeight;
	window.draw(sMusicBtnNormal);
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


