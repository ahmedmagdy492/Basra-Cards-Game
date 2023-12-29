#pragma once
#include <stdint.h>

#define MAX_ELEMENTS 100

// should be included after card.h
struct Stack
{
  int top; // will point to the next element starting from 0
  Card* cards[MAX_ELEMENTS];
};

typedef struct Stack Stack;

Card* Peek(Stack* this) {
  if((this->top-1) < 0)
    return NULL;
  return this->cards[this->top-1];
}

void Push(Stack* this, Card* card) {
  if(card != NULL) {
    this->cards[this->top++] = card;
  }
}

Card* Pop(Stack* this) {
  if(--(this->top) < 0)
    return NULL;
  return this->cards[this->top];
}

int StackCount(Stack* this) {
  if((this->top-1) < 0)
    return 0;
  return this->top;
}
