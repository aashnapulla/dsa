#include "linked-list.h"

void LinkedList::reverse_until(int x)
{
  // TODO: Implement the linked list reversal function
  // Don't forget to set tail ptr correctly as well !

  // - DO NOT ALLOCATE ANY MEMORY
  // - DO NOT USE RECURSION (RECURSION ALLOCATES MEMORY)
  if (head == nullptr){
    return;
  }
  if (head->next == nullptr || head->data == x){
    return;
  }
 
  ListNode* prev = head;
  ListNode* curr =head->next;
  int target = 0;
  bool check = false;
  while(prev!= nullptr){
    if (prev->data == x){
      check = true;
      break;
    }
    prev=prev->next;
    target+=1;
  }
  prev = head;
  if(!check){
    return;
  }


  while(prev->data!=x){
    ListNode* temp = curr;
    curr = curr->next;
    temp->next = prev;
    prev = temp;
    
  }
  if (prev == tail){
    tail = head;
  }

  head->next = curr;
  head = prev;

  

  

}
