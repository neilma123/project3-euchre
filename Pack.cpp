// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Pack.h"
// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){
    int countPack = 0;
    for (int i = 0;  i < 4; ++i){
        for (int j = 0; j < 6; ++j){
            Card currCard(RANK_NAMES_BY_WEIGHT[j+7], SUIT_NAMES_BY_WEIGHT[i]);
            cards[countPack++] = currCard;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
    
    std::string rank = "";
    std::string of = "";
    std::string suit = "";
    for (int i = 0; i < PACK_SIZE && (pack_input >> rank >> of >> suit); ++i){
            Card curr(rank, suit);
            cards[i] = curr;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    int placeholder = next;
    Card *placeholder2 = &cards[placeholder];
    next+=1;
    return *placeholder2;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){next = 0;}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    const int halfDeck = PACK_SIZE / 2;
    
    for(int i = 0; i < 7; ++i){
        std::array<Card, (halfDeck)> auxCards1;
        std::array<Card, (halfDeck)> auxCards2;
        
        //create two auxiliary arrays
        //do a nested for loop before this
        for (int i = 0; i < PACK_SIZE; ++i){
            if (next < halfDeck){
                auxCards1[i] = deal_one();
            }
            else {
                auxCards2[i-12] = deal_one();
            }
        }
        
        reset();
        
//        then seam together
        for(int j = 0; j < PACK_SIZE; j+=2){
            cards[j] = auxCards2[j/2];
            cards[j + 1] = auxCards1[j/2];
        }
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    if (next == PACK_SIZE){
        return true;
    }
    return false;
}
