#pragma once

Card* FindAMatchFromGround(LinkedList* this, Card* card) {
  Node* ptr = this->head;

  while(ptr != NULL) {
    if(card->value == 0 && ptr->card->value == 0 && card->type == ptr->card->type) {
      return card;
    }
    else if(card->value == ptr->card->value) {
      return card;
    }
    ptr = ptr->next;
  }

  return NULL;
}
