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
