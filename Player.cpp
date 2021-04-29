// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include <algorithm>
#include <cassert>
using namespace std;
class HumanPlayer : public Player{
public:
    const std::string & get_name() const override{
        return name;
        
    }
    void add_card(const Card &c) override{
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer, int round, std::string &order_up_suit) const override{
        std::string decision;
        //int numOfCard;
        //std::cin>> numOfCard;
        if(round == 1){
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
            cin >> decision;
            if (decision == "pass"){return false;}
            else{return true;}
        }
        
        if (round == 2 && !is_dealer){
            print_hand();
            cout << "Human player " << name << ", please enter a suit, or \"pass\":" << endl;
            cin >> decision;
            if(decision == "pass"){return false;}
            else{
                order_up_suit = decision;
                return true;
            }
            //else{add_and_discard(upcard);}
            //wrong
        }
        
        else{return true;}
    }
    
    void add_and_discard(const Card &upcard) override{
        vector<Card> sorted_hand = sort_hand();
        print_hand();
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name << ", please select a card to discard:" << endl;
        int numCardReplaced;
        cin>>numCardReplaced;
        if(numCardReplaced > -1){
            for (int i = 0; i < hand.size(); ++i){
                if (hand[i] == sorted_hand[numCardReplaced]){
                    hand[i] = upcard;
                }
            }
        }
        else if (numCardReplaced == -1){return;}
        
    }
    Card lead_card(const std::string &trump) override{
        vector<Card> sorted_hand = sort_hand();
        print_hand();
        cout << "Human player " << name << ", please select a card:" << endl;
        int numOfCard;
        cin >>numOfCard;
        return removedCard(sorted_hand, numOfCard);
    }
    Card play_card(const Card &led_card, const std::string &trump) override{
        vector<Card> sorted_hand = sort_hand();
        print_hand();
        cout << "Human player " << name << ", please select a card:" << endl;
        int numOfCard;
        cin >>numOfCard;
        return removedCard(sorted_hand, numOfCard);
    }
    
    HumanPlayer(const std::string &name_in){
        name = name_in;
    }
private:
    Card played1;
    Card played2;
    Card played3;
    Card played4;
    Card played5;
    std::string name;
    int numplayed = 0;
    std::vector<Card> hand;
    Card removedCard(vector<Card> sorted_hand, int numOfCard){
        if (numplayed == 0){
            played1 = sorted_hand[numOfCard];
            numplayed +=1;
            return played1;
        }
        else if (numplayed == 1){
            played2 = sorted_hand[numOfCard];
            numplayed +=1;
            return played2;
        }
        else if (numplayed == 2){
            played3 = sorted_hand[numOfCard];
            numplayed +=1;
            return played3;
        }
        else if (numplayed == 3){
            played4 = sorted_hand[numOfCard];
            numplayed +=1;
            return played4;
        }
        else {
            numplayed = 0;
            hand.clear();
            return sorted_hand[0];
        }
    }
    void resetnumleft(){
        numplayed = 0;
    }
    std::vector<Card> sort_hand(std::string trump) const{
        std::vector<Card> trumpHand;
        std::vector<Card> nonTrump;
        std::vector<Card> bowers;
        
        for (auto card: hand){
            if (card.is_left_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_right_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_trump(trump)){
                trumpHand.push_back(card);
            }
            else {
                nonTrump.push_back(card);
            }
        }
        if (bowers.size() == 2){
            Card placeholder1;
            Card placeholder2;
            for (auto card: bowers){
                if (card.is_left_bower(trump)){
                    placeholder1 = card;
                }
                else if (card.is_right_bower(trump)){
                    placeholder2 = card;
                }
            }
            bowers[0] = placeholder1;
            bowers[1] = placeholder2;
        }
        std::vector<Card> sorted_hand;
        for (auto nt: nonTrump){
            sorted_hand.push_back(nt);
        }
        for (auto t: trumpHand){
            sorted_hand.push_back(t);
        }
        for (auto card: bowers){
            sorted_hand.push_back(card);
        }
        return sorted_hand;
    }
    std::vector<Card> sort_hand_no_trump() const{
        std::vector<Card> sorted_hand;
        for (auto card: hand){
            sorted_hand.push_back(card);
        }
        sort(sorted_hand.begin(), sorted_hand.end());
        return sorted_hand;
    }
    void print_hand() const{
        std::vector<Card> sorted_hand = sort_hand();
        for(size_t i = 0; i < hand.size() - numplayed; ++i){
            std::cout << "Human player " << name <<"'s hand: [" << i << "] " << sorted_hand[i] << std::endl;
        }
    }
    std::vector<Card> sort_hand() const{
        std::vector<Card> sorted_hand;
        if (numplayed == 0){
            for (auto card: hand){
                sorted_hand.push_back(card);
            }
        }
        if (numplayed == 1){
            for (auto card: hand){
                if (card  == played1){
                    continue;
                }
                sorted_hand.push_back(card);
            }
        }
        if (numplayed == 2){
            for (auto card: hand){
                if (card  == played1){
                    continue;
                }
                if (card  == played2){
                    continue;
                }
                sorted_hand.push_back(card);
            }
        }
        if (numplayed == 3){
            for (auto card: hand){
                if (card  == played1){
                    continue;
                }
                if (card  == played2){
                    continue;
                }
                if (card  == played3){
                    continue;
                }
                sorted_hand.push_back(card);
            }
        }
        if (numplayed == 4){
            for (auto card: hand){
                if (card  == played1){
                    continue;
                }
                if (card  == played2){
                    continue;
                }
                if (card  == played3){
                    continue;
                }
                if (card  == played4){
                    continue;
                }
                sorted_hand.push_back(card);
            }
        }
        
        if (numplayed == 5){
            for (auto card: hand){
                if (card  == played1){
                    continue;
                }
                if (card  == played2){
                    continue;
                }
                if (card  == played3){
                    continue;
                }
                if (card  == played4){
                    continue;
                }
                if (card  == played5){
                    continue;
                }
                sorted_hand.push_back(card);
            }
        }
        sort(sorted_hand.begin(), sorted_hand.end());
        return sorted_hand;
    }
};
class SimplePlayer : public Player{
public:
    const std::string & get_name() const override{
        return name;
    }
    void add_card(const Card &c) override{
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override{
        order_up_suit = upcard.get_suit();
        if (round == 1){
            int numFaces = 0;
            for (auto card: hand){
                if(card.is_face() && card.get_suit() == order_up_suit){
                    numFaces += 1;
                }
                else if (card.is_left_bower(order_up_suit)){
                    numFaces += 1;
                }
            }
            if (numFaces >= 2){
                return true;
            }
            else {
                return false;
            }
        }
        else if (round == 2 && !(is_dealer)){
            int numFaces = 0;
            order_up_suit = Suit_next(order_up_suit);
            for (auto card: hand){
                if(card.is_face() && card.get_suit() == order_up_suit){
                    numFaces += 1;
                }
                else if (card.is_left_bower(order_up_suit) || card.is_right_bower(order_up_suit)){
                    numFaces += 1;
                }
            }
            if (numFaces >= 1){
                return true;
            }
            else {
                return false;
            }
        }
        else {
            order_up_suit = Suit_next(order_up_suit);
            return true;
        }
    }
    void add_and_discard(const Card &upcard) override{
        hand.push_back(upcard);
        std::vector<Card> trumpHand;
        std::vector<Card> nonTrump;
        std::vector<Card> bowers;
        
        for (auto card: hand){
            if (card.is_left_bower(upcard.get_suit())){
                bowers.push_back(card);
            }
            else if (card.is_right_bower(upcard.get_suit())){
                bowers.push_back(card);
            }
            else if (card.is_trump(upcard.get_suit())){
                trumpHand.push_back(card);
            }
            else {
                nonTrump.push_back(card);
            }
        }
        std::sort(trumpHand.begin(), trumpHand.end());
        std::sort(nonTrump.begin(), nonTrump.end());
        if (bowers.size() == 2){
            Card placeholder1;
            Card placeholder2;
            for (auto card: bowers){
                if (card.is_left_bower(upcard.get_suit())){
                    placeholder1 = card;
                }
                else if (card.is_right_bower(upcard.get_suit())){
                    placeholder2 = card;
                }
            }
            bowers[0] = placeholder1;
            bowers[1] = placeholder2;
        }
        hand.clear();
        for (auto nt: nonTrump){
            hand.push_back(nt);
        }
        for (auto t: trumpHand){
            hand.push_back(t);
        }
        for (auto card: bowers){
            hand.push_back(card);
        }
        hand.erase(hand.begin());
    }
    Card lead_card(const std::string &trump) override{
        bool led = false;
        if (hand.size() == 1){
            Card placeholder = hand[0];
            hand.erase(hand.begin());
            return placeholder;
        }
        vector<vector<Card>> sorted = sort_hand(trump, led);
        hand.clear();
        for (int i = 0; i < 3; ++i){
            for (auto card: sorted[i]){
                hand.push_back(card);
            }
        }
        if (sorted[0].size() > 0){
            hand.erase(hand.begin() + sorted[0].size() - 1);
            return sorted[0][sorted[0].size() - 1];
        }
        else if (sorted[2].size() > 0){
            hand.erase(hand.begin() + sorted[0].size() + sorted[1].size() + sorted[2].size() - 1);
            return sorted[2][sorted[2].size() - 1];
        }
        else if (sorted[1].size() > 0){
            hand.erase(hand.begin() + sorted[0].size() + sorted[1].size() - 1);
            return sorted[1][sorted[1].size() - 1];
        }
        else {
            assert(false);
        }
        
    }
    Card play_card(const Card &led_card, const std::string &trump) override{
        if (hand.size() == 1){
            Card placeholder = hand[0];
            hand.erase(hand.begin());
            return placeholder;
        }
        bool led = true;
        vector<vector<Card>> sorted = sort_hand(trump, led, led_card);
        hand.clear();
        for (int i = 0; i < 4; ++i){
            for (auto card: sorted[i]){
                hand.push_back(card);
            }
        }
        if (led_card.is_trump(trump)){
            if (sorted[3].size() > 0){
                hand.erase(hand.begin() + sorted[0].size() + sorted[1].size() + sorted[2].size() + sorted[3].size() - 1);
                return sorted[3][sorted[3].size() - 1];
                
            }
            else if (sorted[2].size() > 0){
                hand.erase(hand.begin() + sorted[0].size() + sorted[1].size() + sorted[2].size() - 1);
                return sorted[2][sorted[2].size() - 1];
            }
            else{
                hand.erase(hand.begin());
                return sorted[0][0];
            }
        }
        else {
            if (sorted[1].size() > 0){
                hand.erase(hand.begin() + sorted[0].size() + sorted[1].size() - 1);
                return sorted[1][sorted[1].size() - 1];
            }
            else {
                if (sorted[0].size() > 0){
                    hand.erase(hand.begin());
                    return sorted[0][0];
                }
                else if (sorted[2].size() > 0){
                    hand.erase(hand.begin());
                    return sorted[2][0];
                }
                else if (sorted[3].size() > 0){
                    hand.erase(hand.begin());
                    return sorted[3][0];
                }
                else {
                    return hand[0];
                }
            }
        }
    }
    SimplePlayer(const std::string &name_in){
        name = name_in;
    }
private:
    std::string name;
    std::vector<Card> hand;
    vector<vector<Card>> sort_hand(std::string trump, bool led){
        std::vector<Card> trumpHand;
        std::vector<Card> nonTrump;
        std::vector<Card> bowers;
        for (auto card: hand){
            if (card.is_left_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_right_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_trump(trump)){
                trumpHand.push_back(card);
            }
            else {
                nonTrump.push_back(card);
            }
        }
        std::sort(trumpHand.begin(), trumpHand.end());
        std::sort(nonTrump.begin(), nonTrump.end());
        if (bowers.size() == 2){
            Card placeholder1;
            Card placeholder2;
            for (auto card: bowers){
                if (card.is_left_bower(trump)){
                    placeholder1 = card;
                }
                else if (card.is_right_bower(trump)){
                    placeholder2 = card;
                }
            }
            bowers[0] = placeholder1;
            bowers[1] = placeholder2;
        }
        vector<vector<Card>> finalHand;
        finalHand.push_back(nonTrump);
        finalHand.push_back(trumpHand);
        finalHand.push_back(bowers);
        return finalHand;
    }
    vector<vector<Card>> sort_hand(std::string trump, bool led, Card led_card){
        std::vector<Card> trumpHand;
        std::vector<Card> nonTrump;
        std::vector<Card> ledsuit;
        std::vector<Card> bowers;
        for (auto card: hand){
            if (card.is_left_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_right_bower(trump)){
                bowers.push_back(card);
            }
            else if (card.is_trump(trump)){
                trumpHand.push_back(card);
            }
            else if (card.get_suit(trump) == led_card.get_suit(trump)){
                ledsuit.push_back(card);
            }
            else {
                nonTrump.push_back(card);
            }
        }
        std::sort(trumpHand.begin(), trumpHand.end());
        std::sort(nonTrump.begin(), nonTrump.end());
        std::sort(ledsuit.begin(), ledsuit.end());
        if (bowers.size() == 2){
            Card placeholder1;
            Card placeholder2;
            for (auto card: bowers){
                if (card.is_left_bower(trump)){
                    placeholder1 = card;
                }
                else if (card.is_right_bower(trump)){
                    placeholder2 = card;
                }
            }
            bowers[0] = placeholder1;
            bowers[1] = placeholder2;
        }
        
        vector<vector<Card>> finalHand;
        finalHand.push_back(nonTrump);
        finalHand.push_back(ledsuit);
        finalHand.push_back(trumpHand);
        finalHand.push_back(bowers);
        return finalHand;
    }
};
Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple"){
        return new SimplePlayer(name);
    }
    else if (strategy == "Human"){
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
