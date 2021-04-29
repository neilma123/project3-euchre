// Project UID 1d9f47bfc76643019cfbf037641defe1
#include<iostream>
#include <cassert>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<string>
#include "Player.h"
#include "Pack.h"
using namespace std;
class Game{
public:
    Game(Player *f, Player *s, Player *t, Player *l){
        
        team1.push_back(f);
        team2.push_back(s);
        team1.push_back(t);
        team2.push_back(l);
        allfour.push_back(f);
        allfour.push_back(s);
        allfour.push_back(t);
        allfour.push_back(l);
        round = 1;
        trick = 0;
        totalPointst1 = 0;
        totalPointst2 = 0;

        //        currLineup = allfour;
    }
    bool checkShuffleDeck(string checkShuffle){
        if (checkShuffle == "shuffle"){
            return true;
        }
        else if (checkShuffle == "noshuffle"){
            return false;
        }
        else {
            assert(false);
        }
    }
    void printHandNum(const int numHand){
        cout << "Hand " << numHand << endl;
    }
    void printDealer(const int numHand){
        dealer = numHand % 4;
        currLineup.clear();
        if (dealer == 0){
            currLineup.push_back(allfour[1]);
            currLineup.push_back(allfour[2]);
            currLineup.push_back(allfour[3]);
            currLineup.push_back(allfour[0]);
        }
        else if (dealer == 1){
            currLineup.push_back(allfour[2]);
            currLineup.push_back(allfour[3]);
            currLineup.push_back(allfour[0]);
            currLineup.push_back(allfour[1]);
        }
        else if (dealer == 2){
            currLineup.push_back(allfour[3]);
            currLineup.push_back(allfour[0]);
            currLineup.push_back(allfour[1]);
            currLineup.push_back(allfour[2]);
        }
        else if (dealer == 3){
            currLineup.push_back(allfour[0]);
            currLineup.push_back(allfour[1]);
            currLineup.push_back(allfour[2]);
            currLineup.push_back(allfour[3]);
        }
        cout << allfour[dealer]->get_name() << " deals" << endl;
    }
    Card getCard(){
        return pack->deal_one();
    }
    void dealTwo(Player * currPlayer){
        for (int i = 0; i < 2; ++i){
            currPlayer->add_card(getCard());
        }
    }
    void dealThree(Player * currPlayer){
        for (int i = 0; i < 3; ++i){
            currPlayer->add_card(getCard());
        }
    }
    void deal_three_two(){
        if (dealer == 0){
            dealThree(allfour[1]);
            dealTwo(allfour[2]);
            dealThree(allfour[3]);
            dealTwo(allfour[dealer]);
        }
        else if (dealer == 1){
            dealThree(allfour[2]);
            dealTwo(allfour[3]);
            dealThree(allfour[0]);
            dealTwo(allfour[dealer]);
        }
        else if (dealer == 2){
            dealThree(allfour[3]);
            dealTwo(allfour[0]);
            dealThree(allfour[1]);
            dealTwo(allfour[dealer]);
        }
        else if (dealer == 3){
            dealThree(allfour[0]);
            dealTwo(allfour[1]);
            dealThree(allfour[2]);
            dealTwo(allfour[dealer]);
        }
    }
    void deal_two_three(){
        if (dealer == 0){
            dealTwo(allfour[1]);
            dealThree(allfour[2]);
            dealTwo(allfour[3]);
            dealThree(allfour[dealer]);
        }
        else if (dealer == 1){
            dealTwo(allfour[2]);
            dealThree(allfour[3]);
            dealTwo(allfour[0]);
            dealThree(allfour[dealer]);
        }
        else if (dealer == 2){
            dealTwo(allfour[3]);
            dealThree(allfour[0]);
            dealTwo(allfour[1]);
            dealThree(allfour[dealer]);
        }
        else if (dealer == 3){
            dealTwo(allfour[0]);
            dealThree(allfour[1]);
            dealTwo(allfour[2]);
            dealThree(allfour[dealer]);
        }
    }
    void deal(){
        if (checkShuffleDeck(checkShuffle)){
            pack->shuffle();
        }
        deal_three_two();
        deal_two_three();
    }
    string makeTrump(){
        upcard = getCard();
        cout << upcard << " turned up" << endl;
        string trump = upcard.get_suit();
        string &trump1 = trump;
        bool ordered = false;
        round = 1;
        for (int i = 0; i < 4; ++i){
            if (ordered){
                break;
            }
            if (i == 3){
                ordered = currLineup[3]->make_trump(upcard, true, round, trump1);
                if (ordered){
                    playerOrdered = currLineup[i];
                    cout << currLineup[i]->get_name() << " orders up "
                    << trump1 << endl << endl;
                    currLineup[3]->add_and_discard(upcard);
                }
                else {
                    cout << currLineup[i]->get_name() << " passes" << endl;
                }
            }
            else {
                ordered = currLineup[i]->make_trump(upcard, false, round, trump1);
                if (ordered){
                    playerOrdered = currLineup[i];
                    cout << currLineup[i]->get_name() << " orders up "
                    << trump1 << endl << endl;
                    currLineup[3]->add_and_discard(upcard);
                }
                else {
                    cout << currLineup[i]->get_name() << " passes" << endl;
                }
            }
        }
        if (!ordered){
            round += 1;
        }
        for (int i = 0; i < 4; ++i){
            if (ordered){
                break;
            }
            if (i == 3){
                ordered = currLineup[3]->make_trump(upcard, true, round, trump1);
                if (ordered){
                    playerOrdered = currLineup[i];
                    cout << currLineup[i]->get_name() << " orders up "
                    << trump1 << endl << endl;
                }
                else {
                    cout << currLineup[i]->get_name() << " passes" << endl;
                }
            }
            else {
                ordered = currLineup[i]->make_trump(upcard, false, round, trump1);
                if (ordered){
                    playerOrdered = currLineup[i];
                    cout << currLineup[i]->get_name() << " orders up "
                    << trump1 << endl << endl;
                }
                else {
                    cout << currLineup[i]->get_name() << " passes" << endl;
                }
            }
        }
        return trump1;
    }
    void play_tricks(string trump, int i){
        Player *winner;
        Card f = currLineup[0]->lead_card(trump);
        cout << f.get_rank() << " of " << f.get_suit();
        cout << " led by " << currLineup[0]->get_name() << endl;
        Card s = currLineup[1]->play_card(f, trump);
        cout << s.get_rank() << " of " << s.get_suit();
        cout << " played by " << currLineup[1]->get_name() << endl;
        Card t = currLineup[2]->play_card(f, trump);
        cout << t.get_rank() << " of " << t.get_suit();
        cout << " played by " << currLineup[2]->get_name() << endl;
        Card l = currLineup[3]->play_card(f, trump);
        cout << l.get_rank() << " of " << l.get_suit();
        cout << " played by " << currLineup[3]->get_name() << endl;
        vector<Card *> trickCards;
        trickCards.push_back(&f);
        trickCards.push_back(&s);
        trickCards.push_back(&t);
        trickCards.push_back(&l);
        winner = eval_winner(trickCards, trump);
        for (int i = 0; i < 4; ++i){
            if (allfour[i] == winner){
                points[i] += 1;
            }
        }
        cout << winner->get_name() << " takes the trick" << endl << endl;
        currLineup = new_leader(winner);
        
    }
    Player * eval_winner(vector<Card *> trickCards, string trump){
        Card * high;
        Card * led = trickCards[0];
        int player = 0;
        if (!Card_less(*trickCards[0], *trickCards[1], *led, trump)){
            high = trickCards[0];
            player = 0;
        }
        else {
            high = trickCards[1];
            player = 1;
        }
        if (!Card_less(*trickCards[2], *high, *led, trump)){
            high = trickCards[2];
            player = 2;
        }
        if (!Card_less(*trickCards[3], *high, *led, trump)){
            high = trickCards[3];
            player = 3;
        }
        return currLineup[player];
    }
    vector<Player *> new_leader(Player *winner){
        if (winner == allfour[0]){
            return allfour;
        }
        else if (winner == allfour[1]){
            vector<Player *> casetwo;
            casetwo.push_back(allfour[1]);
            casetwo.push_back(allfour[2]);
            casetwo.push_back(allfour[3]);
            casetwo.push_back(allfour[0]);
            return casetwo;
        }
        else if (winner == allfour[2]){
            vector<Player *> casethree;
            casethree.push_back(allfour[2]);
            casethree.push_back(allfour[3]);
            casethree.push_back(allfour[0]);
            casethree.push_back(allfour[1]);
            return casethree;
        }
        else if (winner == allfour[3]){
            vector<Player *> casefour;
            casefour.push_back(allfour[3]);
            casefour.push_back(allfour[0]);
            casefour.push_back(allfour[1]);
            casefour.push_back(allfour[2]);
            return casefour;
        }
        else {
            assert(false);
            vector<Player *> error;
            error.push_back(nullptr);
            return error;
        }
    }
    void eval_team_winner(){
        int team1pts = 0;
        int team2pts = 0;
        for (int i = 0; i < 4; ++i){
            if (i % 2 == 0){
                team1pts += points[i];
            }
            if (i % 2 == 1){
                team2pts += points[i];
            }
        }
        if (team1pts > team2pts){
            cout << team1[0]->get_name() << " and "
            << team1[1]->get_name() << " win the hand" << endl;
        }
        else {
            cout << team2[0]->get_name() << " and "
            << team2[1]->get_name() << " win the hand" << endl;
        }
        
        int numPlayerOrdered = 0;
        for (int i = 0; i < 4; ++i){
            if (playerOrdered == allfour[i]){
                numPlayerOrdered = i;
            }
        }
        if (team1pts > team2pts){
            if (numPlayerOrdered == 1 || numPlayerOrdered == 3){
                totalPointst1 += 2;
                cout << "euchred!" << endl;
                print_total_points();
                return;
            }
            else if (team1pts == 5){
                totalPointst1 += 2;
                cout << "march!" << endl;
                print_total_points();
                return;
            }
            
            else{
                
                totalPointst1 += 1;
                print_total_points();
                return;
            }
        }
        if (team2pts > team1pts){
            if (numPlayerOrdered == 0 || numPlayerOrdered == 2){
                totalPointst2 += 2;
                cout << "euchred!" << endl;
                print_total_points();
                return;
            }
            else if (team2pts == 5){
                totalPointst2 += 2;
                cout << "march!" << endl;
                print_total_points();
                return;
            }
            else {
                
                totalPointst2 += 1;
                print_total_points();
                return;
            }
        }
    }
    void print_total_points(){
        cout << team1[0]->get_name() << " and "
        << team1[1]->get_name() << " have "
        << totalPointst1 << " points" << endl;
        cout << team2[0]->get_name() << " and "
        << team2[1]->get_name() << " have "
        << totalPointst2 << " points" << endl << endl;
    }
    void play(int i, int ptw_in, string checkShuffle_in, Pack pack1){
        pack = &pack1;
        ptw = ptw_in;
        checkShuffle = checkShuffle_in;
        if (checkDone()){
            return;
        }
        points = {0,0,0,0};
        printHandNum(i);
        printDealer(i);
        deal();
        string trump = makeTrump();
        for (int i = 0; i < 5; ++i){
            play_tricks(trump, i);
        }
        eval_team_winner();
        if (totalPointst1 >= ptw){
            cout << team1[0]->get_name() << " and "
            << team1[1]->get_name() << " win!" << endl;
            return;
        }
        else if (totalPointst2 >= ptw){
            cout << team2[0]->get_name() << " and "
            << team2[1]->get_name() << " win!" << endl;
            return;
        }
        round  = 1;
        pack->reset();
    }
    int getTotal1(){
        return totalPointst1;
    }
    int getTotal2(){
        return totalPointst2;
    }
    bool checkDone(){
        if (totalPointst1 >= ptw){
            return true;
        }
        if (totalPointst2 >= ptw){
            return true;
        }
        else {
            return false;
        }
    }
private:
    Pack *pack;
    string filename;
    string checkShuffle;
    vector<Player *> team1;
    vector<Player *> team2;
    vector<Player *> allfour;
    int dealer = 0;
    int round;
    Card upcard;
    int trick;
    vector<int> points = {0,0,0,0};
    Player *playerOrdered;
    int totalPointst1;
    int totalPointst2;
    vector<Player *> currLineup;
    int ptw;
};
int main(int argc, char *argv[]){
    string filename  = argv[1];
    string checkShuffle = argv[2];
    int ptw = stoi(argv[3]);
    string char0 = argv[4];
    string type0 = argv[5];
    string char1 = argv[6];
    string type1 = argv[7];
    string char2 = argv[8];
    string type2 = argv[9];
    string char3 = argv[10];
    string type3 = argv[11];
    if (!(argc == 12 && (ptw <= 100 && ptw >= 1) &&
          (checkShuffle == "shuffle" || checkShuffle == "noshuffle") &&
          (type0 == "Simple" || type0 == "Human") &&
          (type1 == "Simple" || type1 == "Human") &&
          (type2 == "Simple" || type2 == "Human") &&
          (type3 == "Simple" || type3 == "Human"))){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    for (int i = 0; i < 12; ++i){
        cout << argv[i] << " ";
    }
    cout << endl;
    ifstream fin(filename);
    if (!fin.is_open()){
        cout << "Error opening " << filename << endl;
        return 1;
    }
    Player *f;
    Player *s;
    Player *t;
    Player *l;
    f = Player_factory(char0, type0);
    s = Player_factory(char1, type1);
    t = Player_factory(char2, type2);
    l = Player_factory(char3, type3);
    Pack pack(fin);
    Game game(f, s, t, l);
    bool done = false;
    int i = 0;
    while (!done){
        game.play(i, ptw, checkShuffle, pack);
        i += 1;
        done = game.checkDone();
    }
    delete f;
    delete s;
    delete t;
    delete l;
    return 0;
}
