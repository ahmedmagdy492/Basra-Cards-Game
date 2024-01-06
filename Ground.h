#pragma once

Card* FindAMatchFromGround(LinkedList* this, Card* card) {
  Node* ptr = this->head;

  while(ptr != NULL) {
    if(card->value == 0 && ptr->card->value == 0 && card->type == ptr->card->type) {
      return ptr->card;
    }
    else if(card->value == ptr->card->value && card->value != 0) {
      return ptr->card;
    }
    ptr = ptr->next;
  }

  return NULL;
}

int FindMatchingCardsFromGround(LinkedList* ground, Card* clicked_card, Card** sum_cards) {
  if(ground->head == NULL) {
    return 0;
  }

  Node* first = ground->head;
  Node* second = ground->head->next;
  int counter = 0;

  while(first != NULL) {
    second = first->next;
    while(second != NULL) {
      if(first->card->value != 0 && second->card->value != 0) {
        if((first->card->value + second->card->value) == clicked_card->value) {
          sum_cards[counter++] = first->card;
          sum_cards[counter++] = second->card;
          return counter;
        }
      }
      second = second->next;
    }
    first = first->next;
  }

  return 0;
}
