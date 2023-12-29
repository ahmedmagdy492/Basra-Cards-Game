#pragma once

Card* FindAMatchFromGround(LinkedList* this, Card* card) {
  Node* ptr = this->head;

  while(ptr != NULL) {
    if(card == ptr->card) {
      return card;
    }
    ptr = ptr->next;
  }

  return NULL;
}
