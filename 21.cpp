#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

bool gameStatus = false;

class Card
{
    public:
        int number;
        string suit;
        int id;
        Card(int num, string s, int n) : number(num), suit(s), id(n) {}
        string display() const
        {
            string value;
            if(number==1)
                value = "A";
            else if(number==11)
                value = "J";
            else if(number==12)
                value = "Q";
            else if(number==13)
                value = "K";
            else value = to_string(number);

            string suitSymbol;
            if(suit == "Hearts")
                suitSymbol = "\u2665";
            else if(suit == "Diamonds")
                suitSymbol = "\u2666";
            else if(suit == "Clubs")
                suitSymbol = "\u2663";
            else if(suit == "Spades")
                suitSymbol = "\u2660";

            return value + suitSymbol;
        }
};

class Deck
{
public:
    vector<Card> cards;
    Deck()
    {
        int cardId = 1;
        for (const auto& suit:{"Hearts", "Diamonds", "Clubs", "Spades"})
        {
            for (int number = 1; number <= 13; number++)
            {
                cards.push_back(Card(number, suit, cardId++));
            }
        }
    }
    void shuffle()
    {
        random_device rd;
        mt19937 gen(rd());
        std::shuffle(cards.begin(), cards.end(), gen);
    }
    Card dealCard()
    {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

class Hand
{
    public:
    int point=0;
    vector<Card> cards;
    void getCard(const Card card)
    {
        cards.push_back(card);
    }
    void clear()
    {
        cards.clear();
    }
    int checkCard()
    {
        int sum=0;
        int acepiece=0;
        for(const Card& card : cards)
        {
            if(card.number>=10)
                sum+=10;
            else if(card.number==1) 
            {
                sum+=11;
                acepiece++;
            }
            else sum+=card.number;
        }
        while(sum>21&&acepiece>0)
        {
            sum-=10;
            acepiece--;
        }
        return sum;
    }
    void showCard(Hand hand)
    {
        for(const Card& card : hand.cards)
        {
            cout<<card.display()<<" ";
        }
    }
};

static int start()
{
    char open;
    cout<<"==欢迎来到21点扑克游戏！=="<<endl;
    cout<<"=1.开始游戏="<<endl;
    cout<<"=2.结束游戏="<<endl; 
    while(gameStatus==false)
    {
        cin>>open;
        switch(open)
        {
            case '1':
                gameStatus = true;
                cout<<endl<<"====游戏开始===="<<endl;
                break;
            case '2':
                cout<<endl<<"====游戏结束===="<<endl;
                return 0;
            default:
                cout<<endl<<"无效输入，请重试！"<<endl;
                break;
        }
    }
    return 1;
}

class blackJack
{
    private:
    Deck deck;
    Hand playerHand;
    Hand computerHand;
    public:
    void gameStart()
    {
        deck.shuffle();
        playerHand.getCard(deck.dealCard());
        playerHand.getCard(deck.dealCard());
        computerHand.getCard(deck.dealCard());
        computerHand.getCard(deck.dealCard());
        playerHand.point=playerHand.checkCard();
        computerHand.point=computerHand.checkCard();
        cout<<"庄家的手牌:"<<computerHand.cards[0].display()<<" ??"<<endl<<endl;
        cout<<"你的手牌:"<<playerHand.cards[0].display()<<" "<<playerHand.cards[1].display()<<endl<<endl;
    }

    void gameCore()
    {
        char choice=0;
        cout<<"你选择……"<<endl<<"=1.要牌="<<endl<<"=2.停牌="<<endl<<"=3.退出="<<endl;
        while(choice!='3'&&playerHand.point<22)
        {
            cin>>choice;
            switch(choice)
            {
                case '1':
                    playerHand.getCard(deck.dealCard());
                    playerHand.point=playerHand.checkCard();
                    cout<<"你的手牌:";
                    playerHand.showCard(playerHand);
                    cout<<endl<<endl;
                    if(playerHand.point>21)
                    {
                        cout<<"爆牌！你输了。"<<endl<<"=游戏结束="<<endl;
                        gameStatus=false;
                    }
                    return;
                case '2':
                    while(computerHand.point<17)
                    {
                        cout<<"庄家摸牌中……"<<endl;
                        computerHand.getCard(deck.dealCard());
                        computerHand.point=computerHand.checkCard();
                    }
                    cout<<"你的手牌:";
                    playerHand.showCard(playerHand);
                    cout<<endl;
                    cout<<"庄家的手牌:";
                    computerHand.showCard(computerHand);
                    cout<<endl<<endl;
                    cout<<"====游戏结果===="<<endl<<"你的点数："<<playerHand.point<<endl<<"庄家点数："<<computerHand.point<<endl;
                    if(computerHand.point>21)
                    {
                        cout<<"庄家爆牌！"<<endl<<"=玩家获胜="<<endl;
                        gameStatus=false;
                        return;
                    }
                    if(computerHand.point>playerHand.point)
                        cout<<"=庄家获胜="<<endl;
                    else if(computerHand.point<playerHand.point)
                        cout<<"=玩家获胜="<<endl;
                    else cout<<"=平局="<<endl;
                    gameStatus=false;
                    return;
                case '3':
                    cout<<"=游戏结束="<<endl;
                    gameStatus=false;
                    return;
                default:
                    cout<<"无效输入，请重试！"<<endl;
                    break;
            }
        }
    }
};

int main()
{
    char control='1';
    while(control!='0')
    {
        if(start()==0)
            return 0;
        blackJack game;
        game.gameStart();
        while(gameStatus==true)
            game.gameCore();
        cout<<endl<<"按0退出"<<endl;
        cout<<"按下任意键重新开始游戏……"<<endl<<endl;
        cin>>control;
        if(control=='0')
            return 0;
    }
    return 0;
}