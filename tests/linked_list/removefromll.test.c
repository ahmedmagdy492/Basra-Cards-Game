#include <unity/unity.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include "../../Card.h"
#include "../../LinkedList.h"

LinkedList ground;
Card *card;
Card *card2;
Card *card3;
Card* card4;

void setUp() {
  card = (Card*)malloc(sizeof(Card));
  card->value = 5;
  card->type = diamond;
  card2 = (Card*)malloc(sizeof(Card));
  card2->value = 3;
  card2->type = redheart;
  card3 = (Card*)malloc(sizeof(Card));
  card3->value = 0;
  card3->type = queen;
  card4 = (Card*)malloc(sizeof(Card));
  card4->value = 10;
  card4->type = tree;
}

void test_appendwithMoreThan1Input() {
  AppendToLL(&ground, card);
  AppendToLL(&ground, card2);
  AppendToLL(&ground, card3);
  AppendToLL(&ground, card4);

  Node* ptr = ground.head;

  TEST_ASSERT_TRUE(ptr->card->value == 5);
  TEST_ASSERT_TRUE(ptr->card->type == diamond);

  ptr = ptr->next;

  TEST_ASSERT_TRUE(ptr->card->value == 3);
  TEST_ASSERT_TRUE(ptr->card->type == redheart);

  ptr = ptr->next;

  TEST_ASSERT_TRUE(ptr->card->value == 0);
  TEST_ASSERT_TRUE(ptr->card->type == queen);

  ptr = ptr->next;

  TEST_ASSERT_TRUE(ptr->card->value == 10);
  TEST_ASSERT_TRUE(ptr->card->type == tree);

  ptr = ptr->next;

  TEST_ASSERT_NULL(ptr);
}

void test_removefromLlcorrect_output() {
  AppendToLL(&ground, card);
  AppendToLL(&ground, card2);
  AppendToLL(&ground, card3);
  AppendToLL(&ground, card4);
  
  RemoveFromLL(&ground, card3);

  Node* ptr = ground.head;

  printf("actual = %d, expected = 5\n", ptr->card->value);
  TEST_ASSERT_TRUE(ptr->card->value == 5);
  TEST_ASSERT_TRUE(ptr->card->type == diamond);

  ptr = ptr->next;

  printf("actual = %d, expected = 3\n", ptr->card->value);
  TEST_ASSERT_TRUE(ptr->card->value == 3);
  TEST_ASSERT_TRUE(ptr->card->type == redheart);

  ptr = ptr->next;

  printf("actual = %d, expected = 10\n", ptr->card->value);
  TEST_ASSERT_TRUE(ptr->card->value == 10);
  TEST_ASSERT_TRUE(ptr->card->type == tree);

  ptr = ptr->next;

  TEST_ASSERT_NULL(ptr);
}

void tearDown() {
  free(card);
  free(card2);
  free(card3);
  free(card4);
}

int main() {
  UNITY_BEGIN();

  //RUN_TEST(test_appendwithMoreThan1Input);
  RUN_TEST(test_removefromLlcorrect_output);

  UNITY_END();
}
