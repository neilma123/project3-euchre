// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    string rankin = "Nine";
    string suitin = "Diamonds";
    Card c(rankin, suitin);
    ASSERT_EQUAL(Card::RANK_NINE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());
}

TEST(test_rankin_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_equality) {
   
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c3(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(c == c2);
    ASSERT_TRUE(c != c3);
    ASSERT_FALSE(c == c3);
}

TEST(test_card_greaterthanlessthan_samesuit) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c > c2);
    ASSERT_TRUE(c3 < c2);
}

TEST(test_card_greaterthanlessthan_assorted) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c >= c2);
    ASSERT_TRUE(c3 < c2);
}

TEST(test_card_samerankdiffsuit) {
    Card c(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(c > c2);
}

TEST(test_isface) {
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, c.is_face());
}

TEST(test_is_bower) {
    string trump = "Spades";
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(true, c.is_right_bower(trump));
    ASSERT_EQUAL(true, c2.is_left_bower(trump));
    
}

TEST(test_istrump) {
    string trump = "Clubs";
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, c.is_trump(trump));
}

TEST(test_suitnext) {
    string testSuit = "Clubs";
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_SPADES, Suit_next(testSuit));
}

TEST(test_cardlessA1) {
    string trump = "Clubs";
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card_less(c, c2, trump), true);
}

TEST(test_cardlessA2) {
    string trump = "Clubs";
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card_less(c, c2, trump), true);
}
TEST(test_cardlessA3) {
    string trump = "Diamonds";
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c2, c, trump), true);
}

TEST(test_cardless2) {
    string trump = "Clubs"; //should I use Card::SUIT_CLUBS
    // string led = "Hearts";
    //this is failing --> not now??
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c3(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c, c2, c, trump), true);
}

TEST(test_cardless3) {
    string trump = "Diamonds";
    //test for same rank diff suit
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    Card c3(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card_less(c, c2, c3, trump), true);
    ASSERT_EQUAL(Card_less(c2, c, c, trump), true);
}

TEST(test_cardless4) {
    string trump = "Clubs";
    //test for left bower vs facecard
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c, c3, c2, trump), true);
}

TEST(test_cardless5) {
    string trump = "Hearts";
    //test for left bower vs right bower
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c2, c, c3, trump), true);
}

TEST(test_cardless6) {
    string trump = "Clubs";
    //false case
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c3(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c2, c, c, trump), false);
}

TEST(test_cardless7) {
    string trump = "Hearts";
    //test for left bower vs right bower
    Card c(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c2, c3, c3, trump), true);
    ASSERT_EQUAL(Card_less(c3, c, c3, trump), true);
}

TEST(test_cardless8) {
    string trump = "Clubs";
    //test for left bower vs facecard
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c3(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card_less(c, c3, c2, trump), true);
    ASSERT_EQUAL(Card_less(c3, c2, c2, trump), true);
}

TEST(getter_functions) {
    //test getter functions
    //^^ there will be a secret bug for both of the get_suits
    string trump = "Clubs";
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.get_rank(), Card::RANK_KING);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_HEARTS);
    ASSERT_EQUAL(c2.get_suit(trump), Card::SUIT_CLUBS);
    ASSERT_EQUAL(c2.get_rank(), Card::RANK_JACK);
}

TEST(test_equaltos) {
    //D>C>H>S
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c4(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c5(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(c > c2);
    ASSERT_TRUE(c3 < c2);
    ASSERT_TRUE(c3 <= c4);
    ASSERT_TRUE(c3 >= c4);
    ASSERT_TRUE(c3 <= c);
    ASSERT_TRUE(c3 <= c5);

}

TEST(test_os) {
    ostringstream answer;
    answer << "Nine of Spades";
    ostringstream test;
    Card c(Card::RANK_NINE, Card::SUIT_SPADES);
    test << c;
    ASSERT_EQUAL(test.str(), answer.str());
}

TEST_MAIN()
