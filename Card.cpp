// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below



// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


    // rank and suit names
    static constexpr const char* const RANK_TWO = "Two";
    static constexpr const char* const RANK_THREE = "Three";
    static constexpr const char* const RANK_FOUR = "Four";
    static constexpr const char* const RANK_FIVE = "Five";
    static constexpr const char* const RANK_SIX = "Six";
    static constexpr const char* const RANK_SEVEN = "Seven";
    static constexpr const char* const RANK_EIGHT = "Eight";
    static constexpr const char* const RANK_NINE = "Nine";
    static constexpr const char* const RANK_TEN = "Ten";
    static constexpr const char* const RANK_JACK = "Jack";
    static constexpr const char* const RANK_QUEEN = "Queen";
    static constexpr const char* const RANK_KING = "King";
    static constexpr const char* const RANK_ACE = "Ace";
    
    static constexpr const char* const SUIT_SPADES = "Spades";
    static constexpr const char* const SUIT_HEARTS = "Hearts";
    static constexpr const char* const SUIT_CLUBS = "Clubs";
    static constexpr const char* const SUIT_DIAMONDS = "Diamonds";
    
    //EFFECTS Initializes Card to the Two of Spades
Card::Card(){
    
    rank = RANK_TWO;
    suit = SUIT_SPADES;
    
}
    
    //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
    //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
    //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
    //EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in){
    Card::rank = rank_in;
    Card::suit = suit_in;
}
    
    //EFFECTS Returns the rank
std::string Card::get_rank() const{return Card::rank;}

    
    //EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const{return Card::suit;}
    
    //REQUIRES trump is a valid suit
    //EFFECTS Returns the suit
    //HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const{
    if(get_suit() == trump){return Card::suit;}
    else if (is_left_bower(trump) == true){return trump;}
    else return Card::suit;
}

    //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const{
    if(get_rank() == RANK_JACK || get_rank() == RANK_QUEEN ||
        get_rank() == RANK_KING || get_rank() == RANK_ACE){return true;}
    else return false;
}
    

    
    //REQUIRES trump is a valid suit
    //EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
    if(get_rank() == RANK_JACK){
        if(get_suit()==trump){return true;}
        else return false;
    }
    else return false;
}
    
    //REQUIRES trump is a valid suit
    //EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
    //if vs else if here
    if(get_rank() == RANK_JACK){
        if(get_suit()== SUIT_CLUBS && trump == SUIT_SPADES){return true;}
        else if(get_suit() == SUIT_SPADES && trump == SUIT_CLUBS){return true;}
        else if(get_suit() == SUIT_HEARTS && trump == SUIT_DIAMONDS){return true;}
        else if(get_suit() == SUIT_DIAMONDS && trump == SUIT_HEARTS){return true;}
    }
    //check
    return false;
}
    
    //REQUIRES trump is a valid suit
    //EFFECTS Returns true if the card is a trump card.  All cards of the trump
    // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
    if(get_suit() == trump){return true;}
    else if(is_left_bower(trump)){return true;}
    else return false;
}
    






// Ranks in order from lowest rank to highest rank.

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
    int suitLHS = 0;
    int suitRHS = 0;
    int rankLHS = 0;
    int rankRHS = 0;
    
    //rank loop
    
    for(int i = 0; i < NUM_RANKS; ++i){
        if(RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()){
            rankLHS = i;
        }
        if(RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()){
            rankRHS = i;
        }
    }
    
    //suit loop
    for(int i = 0; i < NUM_SUITS; ++i){
        if(SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()){
            suitLHS = i;
        }
        if(SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()){
            suitRHS = i;
        }
    }
    
    
    
    if(rankLHS < rankRHS){return true;}
    else if (rankLHS > rankRHS){return false;}
    else if(suitLHS < suitRHS){return true;}
    else if(suitLHS > suitRHS){return false;}
    else if(suitLHS == suitRHS && rankLHS == rankRHS){return false;}
    else if(suitLHS == suitRHS && rankLHS < rankRHS){return true;}
    else if(suitLHS == suitRHS && rankLHS > rankRHS){return false;}
    
    else return false;
}

//get rank&suit of both
//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    if(lhs < rhs){return true;}
    else if(lhs == rhs){return true;}
    else return false;
}





//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    if (!(lhs < rhs) && !(lhs == rhs)){return true;}
    else {return false;}
}
//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    if(lhs > rhs){return true;}
    else if (lhs == rhs){return true;}
    else return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    if (lhs.get_suit() == rhs.get_suit() && rhs.get_rank() == lhs.get_rank()){
        return true;
    }
     else return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if(lhs == rhs){return false;}
    else return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    if(suit == SUIT_CLUBS){return SUIT_SPADES;}
    if(suit == SUIT_HEARTS){return SUIT_DIAMONDS;}
    if(suit == SUIT_SPADES){return SUIT_CLUBS;}
    return SUIT_HEARTS;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
    
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if(a.get_suit() != trump && b.get_suit() == trump){return true;}
   
    else if(a.get_suit() != trump && b.get_suit() != trump){
        if(a < b){return true;}
        else if (a == b){return false;}
    }
    else if(a.get_suit() == trump && b.get_suit() == trump){
        if(a < b){return true;}
    }
    else if (a == b){return false;}
    else{return false;};
    return true;
}
//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if (a == b && b == led_card){return false;}
    else if (a == b){return false;}
    else if (a.is_right_bower(trump)){return false;}
    else if (b.is_right_bower(trump)){return true;}
    else if (a.is_left_bower(trump)){return false;}
    else if (b.is_left_bower(trump)){return true;}
    else if(a.get_suit() == trump && b.get_suit() == trump){
        if(a < b){return true;}
        else if (a == b){return false;}
        else {return false;}
    }
    else if (a.is_trump(trump) && !b.is_trump(trump)){return false;}
    else if (!a.is_trump(trump) && b.is_trump(trump)){return true;}
    else if(a.get_suit() == led_card.get_suit() && b.get_suit() == led_card.get_suit()){
        if(a < b){return true;}
        else if (a > b){return false;}
    }
    else if(a.get_suit() == led_card.get_suit() && !(b.get_suit() == led_card.get_suit())){
        if (b.is_trump(trump)){return true;}
        else {return false;}
    }
    else if(!(a.get_suit() == led_card.get_suit()) &&
            (b.get_suit() == led_card.get_suit())){return true;}
    else if(a.get_suit() == led_card.get_suit() &&
            b.get_suit() == trump){return true;}
    else if(a.get_suit() == trump && b.get_suit() == led_card.get_suit()){return false;}
    return true;
}
