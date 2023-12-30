#pragma once


struct Player {
  uint16_t score;
  uint8_t basra_count;
  LinkedList cur_set;
  Stack pocket;
};

typedef struct Player Player;

Stack clicked_cards;

void DrawPlayerCards(Player* this) {
  Node* ptr = this->cur_set.head;

  while(ptr != NULL) {
    DrawCard(ptr->card);
    ptr = ptr->next;
  }
}

void DistributeCards(Stack* pile, Player* player1, Player* computer) {
  int i = 0;
  for(; i < 4; ++i) {
    Card* card = Pop(pile);
    if(card != NULL) {
      card->x = WIDTH/2 + (card->width-i*card->width);
      card->y = HEIGHT - card->height;
      AppendToLL(&player1->cur_set, card);
    }
    Card* com_card = Pop(pile);
    if(com_card != NULL) {
      AppendToLL(&computer->cur_set, com_card);
    }
  }
}
