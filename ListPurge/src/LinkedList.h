
#ifndef LIST_H_
#define LIST_H_


namespace linkedList
{
  typedef int data;
  
  struct Node
  {
    data element;
    struct Node* next;
  };
  
  
  typedef Node * index;
  
  class List
  {
  private:
    int elementCount;
    struct Node* head;
    struct Node* lastNode;
    
  public:
    List();
    ~List();
    index firstPosition();
    index endPosition();
    index nextPosition(index position);
    data retrieveElement(index position);
    void addElement(data element);
    void deleteElement(index position);
    void displayElements();
  };
  

}

using namespace linkedList;

#endif
