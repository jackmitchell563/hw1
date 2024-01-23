#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

/**
* Adds a new value to the back of the list
*   - MUST RUN in O(1)
*/
void ULListStr::push_back(const std::string& val){
  size_++;
  if(!head_ or (tail_->last == 10)){ // empty list or tail node full,
    Item* newitem = new Item; //        so need a new node
    newitem->val[(newitem->last)++] = val; // newitem->last is 0 by default
    if(!head_){ // empty list
      head_ = tail_ = newitem;
      return;
    }
    // tail node full
    tail_->next = newitem;
    newitem->prev = tail_;
    tail_ = newitem;
    return;
  }
  tail_->val[(tail_->last)++] = val; // if tail node exists and isn't full
}

/**
* Removes a value from the back of the list
*   - MUST RUN in O(1)
*/
void ULListStr::pop_back(){
  if(!head_) return;
  size_--;
  if(tail_->last - tail_->first == 1){ // one item before popping, so need to deallocate
    if(head_ == tail_){
      delete head_;
      head_ = tail_ = nullptr;
      return;
    }
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = nullptr;
    return;
  }
  (tail_->last)--;
}

/**
* Adds a new value to the front of the list.
* If there is room before the 'first' value in
* the head node add it there, otherwise, 
* allocate a new head node.
*   - MUST RUN in O(1)
*/
void ULListStr::push_front(const std::string& val){
  size_++;
  if(!head_ or (head_->first == 0)){ // empty list or head node full,
    Item* newitem = new Item; //        so need a new node
    newitem->first = 9, newitem->last = 10; // newitem->first/last are 0 by default
    newitem->val[newitem->first] = val;
    if(!head_){ // empty list
      head_ = tail_ = newitem;
      return;
    }
    // head node full
    head_->prev = newitem;
    newitem->next = head_;
    head_ = newitem;
    return;
  }
  head_->val[--(head_->first)] = val; // if head node exists and isn't full
}

/**
* Removes a value from the front of the list
*   - MUST RUN in O(1)
*/
void ULListStr::pop_front(){
  if(!head_) return;
  size_--;
  if(head_->last - head_->first == 1){ // one item before popping, so need to deallocate
    if(head_ == tail_){ delete head_; head_ = tail_ = nullptr; return; }
    head_ = head_->next;
    delete head_->prev;
    head_->prev = nullptr;
    return;
  }
  (head_->first)++;
}

/**
* Returns a const reference to the back element
*   - MUST RUN in O(1)
*/
std::string const & ULListStr::back() const{
  return tail_->val[(tail_->last) - 1];
}

/**
* Returns a const reference to the front element
*   - MUST RUN in O(1)
*/
std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

/** 
* Returns a pointer to the item at index, loc,
*  if loc is valid and NULL otherwise
*   - MUST RUN in O(n) 
*/
std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc > size_ or loc < 0) return nullptr;
  Item* curr = head_;
  unsigned int currdex = head_->first, count = 0;
  while(count++ < loc and nullptr != curr){
    if(currdex < 9){
      currdex++;
    } else{
      currdex = 0;
      curr = curr->next;
    }
  }
  return &curr->val[currdex];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
