#pragma once

struct Node {
  struct Node* next;
  struct Node* prev;
  Card* card;
};

typedef struct Node Node;

struct LinkedList {
  struct Node* head;
  struct Node* tail;
};

typedef struct LinkedList LinkedList;

void AppendToLL(LinkedList* this, Card* card) {
  if(this->head == NULL) {
    this->head = (Node*)malloc(sizeof(Node));
    this->tail = this->head;
    this->head->card = card;
    this->head->next = NULL;
    this->tail->next = NULL;
    this->head->prev = NULL;
    this->tail->prev = NULL;
  }
  else if(this->head == this->tail) {
    this->head->next = (Node*)malloc(sizeof(Node));
    this->head->next->card = card;
    this->tail = this->head->next;
    this->tail->prev = this->head;
    this->head->prev = NULL;
    this->tail->next = NULL;
  }
  else {
    this->tail->next = (Node*)malloc(sizeof(Node));
    this->tail->next->card = card;
    Node* temp = this->tail;
    this->tail = this->tail->next;
    this->tail->prev = temp;
    this->tail->next = NULL;
  }
}

Node* GetFirstFromLL(LinkedList* this) {
  return this->head;
}

void RemoveLastFromLL(LinkedList* this) {
  if(this->tail != NULL) {
    Node* temp = this->tail;
    this->tail = this->tail->prev;
    this->tail->next = NULL;
    free(temp);
  }
}

void RemoveFromLL(LinkedList* this, Card* card) {
  if(this->head != NULL) {
    Node* ptr = this->head, *prev = NULL;
    while(ptr != NULL) {
      if(ptr->card == card) {
	if(this->head == this->tail) {
	  this->head = this->tail = NULL;
	}
	else if(ptr == this->tail) {
	  this->tail = ptr->prev;
	  this->tail->next = NULL;
	}
	else if(ptr == this->head) {
	  this->head = ptr->next;
	}
	else {
	  prev->next = ptr->next;
	  ptr->next->prev = prev;
	}
	break;
      }
      prev = ptr;
      ptr = ptr->next;
    }
  }
}

void CleanupLL(LinkedList* this) {
  if(this->head != NULL) {
    Node* ptr = this->head;
    while(ptr != NULL) {
      Node* temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
  }
}

int CountLL(LinkedList* this) {
  Node* ptr = this->head;
  int count = 0;

  while(ptr != NULL) {
    ++count;
    ptr = ptr->next;
  }
  
  return count;
}
