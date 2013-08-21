#include "ArrayList.h"

/**
 * Implement class List
 */
namespace arrayList
{

  List::List()
  {
    elementCount = 0;
  }

  /**
   * Return first index
   */
  index List::firstPosition()
  {
    if(elementCount)
      return 0;
    else
      return -1;
  }

  /**
   * Return last index
   */
  index List::endPosition()
  {
    return (elementCount);
  }

  /**
   * Given a index position, function will 
   * return next index.
   */
  index List::nextPosition(index position)
  {
    return (position + 1);
  }

  /**
   * Get data element at given index
   */
  data List::retrieveElement(index position)
  {
    if(position < elementCount && position > -1)
      return array[position];
    else
      {
		//Error
		throw "Index Out of Bound Exception";
      }
  }

  /**
   * Insert an element at given position.
   */
  void List::insertElement(index position,data element)
  {
    if(position > -1)
      {
	if(elementCount >= MAX_SIZE)
	  throw "Array Overflow Exception";
	for (int i= elementCount; i > position; --i)
	  {
	    array[i] = array [i-1];
	  }
	array[position] = element;
	elementCount++;
      }
    else
      {
	//Error
	throw "Index Out of Bound Exception";
      }
  }

  /**
   * Append an element to end of list
   */
  void List::addElement(data element)
  {
    if(elementCount >= MAX_SIZE)
      throw "Array Overflow Exception";
    array[elementCount++]=element;
  }

  /**
   * Delete an element at given position
   */
  void List::deleteElement(index position)
  {
    if(position > -1)
      {
	for (int i= position+1; i < elementCount; i++)
	  {
	    array[i-1] = array [i];
	  }
	elementCount--;
      }
    else
      {
	//Error
	throw "Index Out of Bound Exception";
      }
  }

  /**
   * Print element of list in sequential order
   * to given stream.
   */
  void List::displayElements(std::ostream& dataOut)
  {
    for (int i = 0; i < elementCount; ++i)
      dataOut << array[i] << " ";
  }
}
