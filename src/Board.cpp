#include "Board.h"
std::mt19937 Board::engine(std::random_device{}());

#define DEBUG

Board::Board()
{
	rank = -1;
	currentrank = 1;
	timer = -1;
	areaL = -1;
	areaR = -1;
	edgeNumLeft = -1;
	score = 0;
	eventCountTimer = -1;
	
	memset(boardData, 0, sizeof(boardData));

	dice = new Dice();

	InitRandomGenerator();

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
	{
		cards[i] = std::make_shared<Card>();
	}


	// カードの初期配置(手札の配分と7のセット)
	// ホストの場合のみ行う
	if (GameManager::role == Role::Server)
	{
		Shuffle();
		//! クライアント側は山札の更新を待つ
		Distribute(MAX_PLAYER);
#ifdef DEBUG
		SortHand(Area::Area_Player1);
		ShowHand(Area::Area_Player1);
#else
		SortHand((Area)(GameManager::playerId + 2));
		ShowHand((Area)(GameManager::playerId + 2));
#endif // DEBUG
	}
}

Board::~Board()
{
	// カードの破棄
	for(auto card : cards)
	{
		card.reset();
	}

	delete dice;
}

void Board::Draw()
{
	// テーブルのモデルの描画
	MV1DrawModel(modelHandle);

	// カードの描画
	MV1SetPosition(Card::modelHandle, Card::position_model);
	MV1SetRotationXYZ(Card::modelHandle, Card::rotate_model);
	MV1SetScale(Card::modelHandle, Card::scale_model);
	MV1DrawModel(Card::modelHandle);

	//
	dice->Update();
}

void Board::Move(Card& card)
{
}

void Board::Update()
{
	Draw();
	
	if (GameManager::isClear)
	{
		for (int i = 0; i < 4; i++)
		{
		
		}
		//DrawFormatString(100, 120, GetColor(255, 255, 255), "aaaaaa");
		//DrawGraph(0,0,winHandle,TRUE);
	}

	for (auto& card : cards)
	{
		card->ManualUpdate();
	}

	//DrawFormatString(
	//	10, 10, GetColor(0, 255, 0),
	//	"P1 = %d", handData[0].size());
	//DrawFormatString(
	//	150, 10, GetColor(0, 255, 0),
	//	"P2 = %d", handData[1].size());
	//DrawFormatString(
	//	300, 10, GetColor(0, 255, 0),
	//	"P3 = %d", handData[2].size());


	for (int i = 0; i < SUIT_NUM; ++i)
	{
		for (int j = 0; j < DECK_RANGE; ++j)
		{
			DrawBox(
				DEFAULT_CARD_POSITION.x + (FIELD_BEZEL.x + CARD_WIDTH) * j,
				DEFAULT_CARD_POSITION.y + (FIELD_BEZEL.y + CARD_HEIGHT) * i,
				DEFAULT_CARD_POSITION.x + (FIELD_BEZEL.x + CARD_WIDTH) * j + CARD_WIDTH,
				DEFAULT_CARD_POSITION.y + (FIELD_BEZEL.y + CARD_HEIGHT) * i + CARD_HEIGHT,
				GetColor(255, 255, 255), FALSE);
		}
	}
	if(eventCountTimer ==0)
	{
		
		eventCountTimer = -1;
	}

	if(eventCountTimer >0)
	{
		eventCountTimer--;
	}

#ifdef _DEBUG
	if(CheckHitKey(KEY_INPUT_R))
	{
		auto num = Random::GetRandomInt(1,6);
		dice->Roll(num);
	}
#endif // _DEBUG

}

void Board::ManualLoad()
{
	Card::modelHandle = MV1LoadModel("Assets/model/Cards/Cards.mv1");
	modelHandle = MV1LoadModel("Assets/model/Table/Table.mv1");
	winHandle = LoadGraph("Assets/Sprite/playerWin.png");
	if (dice != nullptr) dice->ManualLoad();

	// テーブの座標は固定のため、初期化時に設定
	MV1SetPosition(modelHandle, { 950,500,500 });
	MV1SetRotationXYZ(modelHandle, { (float)Deg2Rad(-90.0f),0,0 });
	MV1SetScale(modelHandle, { 1.5f,1.5f,1.5f });
}
void Board::AddScore(int value)
{
	GameManager::score[GameManager::playerId] = score += value;
}
bool Board::CanPlace(const Card& card)
{
	// 手札のカードか
	if (card.area == Area::Area_Board || card.area == Area::Area_Invalid) return false;
	// 制限エリア内か
	int num = card.number;
	if (areaL != -1) // エリア制限されているか
	{
		if (areaL > num || areaR < num)
		{
			return false;
		}
	}
	// 隣接するカードが置かれているか

	auto suit = card.suit;
	auto arrayNum = num - 1;
	auto left = arrayNum - 1;
	if (left < 0) left = DECK_RANGE - 1;
	auto right = arrayNum + 1;
	if (right >= DECK_RANGE) right = 0;
	if (boardData[suit][left] == '1') return true;
	if (boardData[suit][right] == '1') return true;

	return false;
}

void Board::SubscribeEventCallback(const std::function<void(EventData&)>& _eventCallback)
{
	eventOccurrenceCallback = _eventCallback;
}

void Board::DrawingEvent()
{
	std::uniform_int_distribution<> dist(0, 4);

	auto diceNum = dist(engine);
	// ダイスロールアニメーション
	dice->Roll(diceNum);
	// 抽選結果に応じて関数を実行
	switch (diceNum)
	{
	case 0:
		FeverTime();
		break;
	case 1:
		LuckyNumber();
		break;
	case 2:
		LimitArea();
		break;
	case 3:
		MoveArea();
		break;
	case 4:
		ShuffleHand();
		break;
	default:
		Bomb();
		break;
	}

	eventCountTimer = EVENT_TIME;
}

void Board::InitEventMember()
{
	// イベントで使う変数のイニシャライズ
	coolTime = PLACE_COOL_TIME;
	areaL = -1;
	areaR = -1;
	luckyNum = -1;
}

void Board::Shuffle()
{
	//! シャッフルする配列
	std::vector<int> v;

	for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
		v.push_back(i);

	// シャッフル
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(v.begin(), v.end(), engine);

	// 領域座標を更新
	for (int i = 0; i < v.size(); ++i)
		cards[i]->areaNumber = v[i];
}

void Board::Distribute(int playerNum)
{
	for(auto card : cards)
	{
		card->area = (Area)(card->areaNumber % playerNum + 2);
	}

	for (int i = 0; i < playerNum; ++i)
	{
		std::vector<std::shared_ptr<Card>> playerHand;
		for (auto card : cards)
		{
			if (card->area == (Area)(i + 2))
			{
				playerHand.push_back(card);
			}
		}
		handData.push_back(playerHand);
	}
}

void Board::ShowHand(Area playerArea)
{
	int index = (int)playerArea - 2;
	std::vector<std::shared_ptr<Card>> handVec;
	handVec = handData[index];

	float merginX = -8;
	float merginY = -25;

	//
	// 中央を基準にして手札を表示する
	//

	std::vector<std::shared_ptr<Card>>::iterator centerCard;

	for (auto it = handVec.begin(); it != handVec.end(); ++it)
	{
		if ((*it)->areaNumber == (int)(handVec.size() / 2))
		{
			centerCard = it;
			break;
		}
	}

	for (auto it = handVec.begin(); it != handVec.end(); ++it)
	{
		HWDotween::DoAction(&(*it)->position, { 
			merginX* ((*it)->areaNumber - (*centerCard)->areaNumber + 7),
			merginY, 0 }, 30);
		HWDotween::DoAction(&(*it)->rotate, { 0, 0, 180 }, 30);
	}

	static bool isFirst = true;
	if(isFirst)
	{
		HWDotween::DoDelay(60)->OnComplete([&] {
			for (int i = 0; i < SUIT_NUM * DECK_RANGE; ++i)
			{
				if (cards[i]->number == 7)
					CardOnBoard(cards[i], (int)(cards[i]->area - 2));
			}
#ifdef DEBUG
			ShowHand(Area::Area_Player1);
#else
			ShowHand((Area)(GameManager::playerId + 2));
#endif // DEBUG			
			});
			isFirst = false;
	}
}

void Board::CardOnBoard(std::shared_ptr<Card> _card, int _index)
{
	_card->AreaChange(Area_Board);
	boardData[(int)_card->suit][_card->number - 1] = '1';

#ifdef DEBUG
	handData[Area::Area_Player1 - 2].erase(
		std::remove(handData[Area::Area_Player1 - 2].begin(), handData[Area::Area_Player1 - 2].end(), _card),
		handData[Area::Area_Player1 - 2].end());
	SortHand(Area::Area_Player1);
	if (handData[Area::Area_Player1 - 2].size() <= 0)
	{
		
	}
#else
	handData[_index].erase(
		std::remove(handData[_index].begin(), handData[_index].end(), _card),
		handData[_index].end());
	SortHand((Area)(GameManager::playerId + 2));

	// あがり判定
	if (handData[GameManager::playerId].size() <= 0)
	{
		GameManager::isClear = true;
	}
#endif // DEBUG
}

void Board::SortHand(Area playerArea)
{
	int index = (int)playerArea - 2;
	std::vector<std::shared_ptr<Card>> handVec;
	std::copy(handData[index].begin(), handData[index].end(),
		std::back_inserter(handVec));

	std::sort(handVec.begin(), handVec.end(), [](std::shared_ptr<Card> a, std::shared_ptr<Card> b) {
		if (a->number == b->number)
			return a->suit < b->suit;
		return a->number < b->number;
		});

	for (int i = 0; i < handVec.size(); ++i)
	{
		handVec[i]->areaNumber = i;
	}
}

int Board::CalculateScore(std::shared_ptr<Card>& card)
{
	/// 各クライアントで処理後に計算
	int add = PLACE_CARD;

	if(IsCompleteRowOfSuit(card->number))
	{
		add += ROW_COMPLETE;
	}

	if(IsCompleteColumnAt(card->suit))
	{
		add += LINE_COMPLETE;
	}

	if(IsLuckyNumber(card->number))
	{
		add += PLACE_CARD * 4;
	}

	return add;
}

bool Board::IsCompleteRowOfSuit(int num)
{
	for(int i = 0; i < SUIT_NUM; ++i)
	{
		auto index = num + i * DECK_RANGE - 1;
		if(cards[index]->area != Area::Area_Board)
		{
			return false;
		}
	}
	return true;
}

bool Board::IsCompleteColumnAt(const Suit& suit)
{
	for (int i = 0; i < DECK_RANGE; ++i)
	{
		auto index = i +  static_cast<int>(suit) * DECK_RANGE -1;
		if (cards[index]->area != Area::Area_Board)
		{
			return false;
		}
	}
	return true;
}

bool Board::IsDerangement(const std::vector<std::vector<std::shared_ptr<Card>>>& original, const std::vector<std::vector<std::shared_ptr<Card>>>& shuffled)
{
	for (int i = 0; i < original.size(); ++i)
	{
		if (original[i] == shuffled[i]) // 元の位置と同じカードならNG
			return false;
	}
	return true;
}

void Board::InitRandomGenerator()
{
	std::random_device seed_gen;
	engine.seed(seed_gen());
}

void Board::Bomb()
{
	/// 導火線の長さを決める
	/// カードを置いたときに導火線を進める処理()
	/// 爆発する処理
	/// フラグを落とす処理
}

void Board::FeverTime()
{
	/// クールタイム大幅短縮
	coolTime = coolTime / 2;
}

void Board::LuckyNumber(int num)
{
	/// 盤面の数字を見て意味のない数字をいれない
	if(GameManager::role == Role::Server)
	{
		/// 埋まっていないカードを探す
		std::vector<std::shared_ptr<Card>> unfilledCards;
		for(auto& card : cards)
		{
			if (card->area != Area::Area_Board) unfilledCards.push_back(card);
		}
		auto index = Random::GetRandomInt(0, unfilledCards.size());
		luckyNum = unfilledCards[index]->number;

		EventData eventData;
		int eventIndex = static_cast<int>(Event::Event_LuckyNumber);
		eventData.eventType = static_cast<unsigned char>(eventIndex);
		eventData.data = static_cast<unsigned char>(luckyNum);

	}
	else
	{
		luckyNum = num;
	}
}

void Board::LimitArea(int left, int right)
{
	/// 盤面の状況からあまり意味のないエリア制限を無いようにしたい
	if(GameManager::role == Role::Server)
	{
		/// 埋まっていないカードを探す
		std::vector<std::shared_ptr<Card>> unfilledCards;
		for (auto& card : cards)
		{
			if (card->area != Area::Area_Board) unfilledCards.push_back(card);
		}
		int number1 = -1;
		int number2 = -1;

		// 同じ数字じゃなくなるまで抽選
		do
		{
			auto index1 = Random::GetRandomInt(0, unfilledCards.size());
			auto number1 = unfilledCards[index1]->number;
			
			auto index2 = Random::GetRandomInt(0, unfilledCards.size());
			auto number2 = unfilledCards[index2]->number;
		} while (number1 != number2);
		
		if (number1 > number2)
		{
			areaL = number2;
			areaR = number1;
		}
		else
		{
			areaL = number1;
			areaR = number2;
		}

		auto limit = (areaR-1) * DECK_RANGE + areaL;

		EventData data;
		int eventIndex = static_cast<int>(Event::Event_LimitArea);
		data.eventType = static_cast<unsigned char>(eventIndex);
		data.data = static_cast<unsigned char>(limit);

		//UDPConnection::SendEventData(data);
		eventOccurrenceCallback(data);
	}
	else
	{
		areaL = left;
		areaR = right;
	}
}

void Board::MoveArea(bool left, int num)
{
	if(GameManager::role == Role::Server)
	{
		auto IsLeft = Random::GetRandomInt(0, 1);
		auto num = Random::GetRandomInt(1, DECK_RANGE);

		//auto data = num + IsLeft * (DECK_RANGE ); // 右の場合 1 ~ 13,左の場合 14 ~ 27 
		unsigned char data = IsLeft << 7;
		data += num;

		EventData eventData;
		auto add = num * IsLeft ? 1 : -1;
		cards[0]->leftEdgeNum += add;

		int eventIndex = static_cast<int>(Event::Event_MoveArea);
		eventData.eventType = static_cast<unsigned char>(eventIndex);
		eventData.data = data;

		//UDPConnection::SendEventData(eventData);
		eventOccurrenceCallback(eventData);
	}
	else
	{
		auto add = num * left ? 1 : -1;
		cards[0]->leftEdgeNum += add;
	}
	cards[0]->leftEdgeNum = (cards[0]->leftEdgeNum - 1 + DECK_RANGE) % DECK_RANGE + 1;


	for(auto card : cards)
	{
		card->Slide();
	}
}

void Board::ShuffleHand()
{
	/// 手札情報を更新する
	/// サーバーのみ実行
	if(GameManager::role == Role::Server)
	{
		auto playerNum = GameManager::connectNum;
		std::vector<std::vector<std::shared_ptr<Card>>> playerHands(playerNum);

		for(auto card : cards)
		{
			if(card->area !=Area::Area_Board )
			{
				auto owner = static_cast<int>(card->area) -2;
				playerHands[owner].push_back(card);
			}
		}
		// 元の配列をコピー
		std::vector<std::vector<std::shared_ptr<Card>>> originalHands = playerHands;

		do
		{
			std::shuffle(playerHands.begin(), playerHands.end(), engine);
		} 
		while (!IsDerangement(originalHands, playerHands));

		//エリアを更新する処理

		for(int i = 0; i < playerNum; ++i)
		{
			for(auto card: playerHands[i])
			{
				card->area = (Area)(i + 2);
			}
		}

		EventData eventData;
		int eventIndex = static_cast<int>(Event::Event_ShuffleHand);
		eventData.eventType = static_cast<unsigned char>(eventIndex);
		eventData.data = '1'; // フラグ

		//UDPConnection::SendEventData(eventData);
		eventOccurrenceCallback(eventData);
	}

	/// エリア更新に合わせて手札を移動する処理

}
