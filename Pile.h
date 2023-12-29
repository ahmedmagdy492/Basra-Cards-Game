#pragma once

// should be included after cards and after stack

void ShuffleThePile(Stack* pile) {
  int i = 0;
  for(;i < StackCount(pile); ++i) {
    int rand_index1 = GetRandomValue(0, StackCount(pile));
    int rand_index2 = GetRandomValue(0, StackCount(pile));
    Card* temp = pile->cards[rand_index1];
    pile->cards[rand_index1] = pile->cards[rand_index2];
    pile->cards[rand_index2] = temp;
  }
}

void CreateThePile(Stack* pile) {
  int i = 1;
  for(; i <= 10; ++i) {
    Push(pile, CreateCard(i, redheart));
    Push(pile, CreateCard(i, blackheart));
    Push(pile, CreateCard(i, diamond));
    Push(pile, CreateCard(i, tree));
  }

  for(i = 0; i < 4; ++i) {
    Push(pile, CreateCard(0, jack));
    Push(pile, CreateCard(0, queen));
    Push(pile, CreateCard(0, king));
  }
}

void CleanThePile(Stack* pile) {
  Card* ptr = Pop(pile);
  while(ptr != NULL) {
    free(ptr);
    ptr = Pop(pile);
  }
}
