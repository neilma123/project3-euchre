// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;
/*
 list of functions to test:
 ----remember that they will be different for simple and human-----
 ^^ or do i need to test for human?
 
 make_trump
 add_card***
 add_and_discard***
 play_card
 test os
 leadcard***
 test playerfactory???
 //use add and discard somewhere --> test inside of lead card
 */
//led card is left bower write tests for this --> play card, lead card
TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    //why do i use -> here?
    delete alice;
}

/*TEST(test_player_factory) {
    //how do i check if it's simpleplayer or humanplayer?
    Player *alice = Player_factory("Alice", "Simple");
    Player *chad = Player_factory("Chad", "Human");
    ASSERT_EQUAL("Simple", alice)
    ASSERT_EQUAL("Human", alice->get_name());
    delete alice;
    delete chad;
                 
}
*/



TEST(test_leadcard_alltrump) {
    //tests all trump & if recognizes left bower as highest in this set
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_KING, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c4(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c5(Card::RANK_TEN, Card::SUIT_SPADES);
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Card leftBower(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, leftBower); //check led card
    delete bob;
}

TEST(test_leadcard_notrump) {
    //tests none trump
    //highest card should be king of diamonds
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c4(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c5(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Card answer(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led, answer); //check led card
    delete bob;
}
TEST(test_leadcard_mixed) {
    //tests mixed set
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_SPADES); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Card upcard(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    bob->add_and_discard(upcard);
    Card answer(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card card_led = bob->lead_card(Card::SUIT_CLUBS);
    ASSERT_EQUAL(card_led, answer); //check led card
    delete bob;
}


TEST(test_maketrumpR1Scen1) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   false,           //Bob not the dealer
                                   1,              //first round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    
    delete bob;
}

TEST(test_maketrumpR1Scen2) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   false,           //Bob not the dealer
                                   1,              //first round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    
    delete bob;
}

TEST(test_maketrumpR2Scen1) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_ACE, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   false,           //Bob not the dealer
                                   2,              //first round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    //check this, is it supposed to be hearts?
    
    delete bob;
}

//test from hell
/*TEST(test_maketrumpR2Scen2) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_ACE, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   false,           //Bob not the dealer
                                   2,              //second round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    //why is this diamonds and not hearts??
    
    delete bob;
    //this is wrong, is supposed to return hearts
}
*/
TEST(test_maketrumpR1Scen3) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   true,           //Bob is the dealer
                                   1,              //second round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);
    //why is this diamonds and not hearts??
    
    delete bob;
    //this is wrong, is supposed to return hearts
}

TEST(test_maketrumpR2Scen3) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_NINE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   true,           //Bob is the dealer
                                   2,              //second round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_CLUBS);
    //why is this diamonds and not hearts??
    
    delete bob;
    //this is wrong, is supposed to return hearts
}

TEST(test_screwed) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card upcard(Card::RANK_ACE, Card::SUIT_HEARTS);
    string trump = Card::SUIT_HEARTS;
    bool orderup = bob->make_trump(
                                   upcard,    //upcard
                                   true,           //Bob is the dealer
                                   2,              //first round
                                   trump           //suit ordered up (if any)
                                   );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_DIAMONDS);
    
    delete bob;
}


TEST(test_play_card_1) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_DIAMONDS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card ledCard(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    string trump = Card::SUIT_HEARTS;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c);
    delete bob;
}

TEST(test_play_card_cantfollow) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_KING, Card::SUIT_HEARTS); //RIGHT BOWER
    Card c3(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_NINE, Card::SUIT_HEARTS); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card ledCard(Card::RANK_NINE, Card::SUIT_CLUBS);
    string trump = Card::SUIT_HEARTS;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c);
    delete bob;
}

TEST(test_play_card_followleft) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_NINE, Card::SUIT_HEARTS); //RIGHT BOWER
    Card c3(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c5(Card::RANK_JACK, Card::SUIT_SPADES); //lowest NON-TRUMP
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card ledCard(Card::RANK_NINE, Card::SUIT_CLUBS);
    string trump = Card::SUIT_CLUBS;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c5);
    delete bob;
}

TEST(test_play_card_leftbower) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_KING, Card::SUIT_SPADES);
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c4(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    bob->add_card(c);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    
    Card ledCard(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_DIAMONDS;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c5);
    delete bob;
}

TEST(test_play_card_leftled) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    bob->add_card(c);
    bob->add_card(c2);
    
    Card ledCard(Card::RANK_ACE, Card::SUIT_HEARTS);
    string trump = Card::SUIT_SPADES;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c);
    delete bob;
}

TEST(test_play_card_ledtrump) {
    Player * bob = Player_factory("Bob", "Simple");
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    bob->add_card(c);
    bob->add_card(c2);
    
    Card ledCard(Card::RANK_ACE, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    Card card_played = bob->play_card(ledCard, trump); //Diamonds is led
    //Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, c2);
    delete bob;
}




//we need to fix play card to count left bower as member of the same suit

/*TEST(test_os) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    //why do i use -> here?
    delete alice;
}
*/
// Add more tests here
//for make_trump test for if it's round 1, round 2 with dealer, round 2 without dealer
TEST_MAIN()
