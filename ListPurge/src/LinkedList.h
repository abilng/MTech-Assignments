
#ifndef LIST_H_
#define LIST_H_


namespace linkedList
{
	class List
	{
		int elementCount;
		struct Node* firstNode;
		struct Node* lastNode;

		public:
		List();
		int firstPosition();
		int endPosition();
		int nextPosition(int position);
		int retrieveElement(int position);
		void addElement(int element);
		void deleteElement(int position);
		void displayElements();
	};



	struct Node
	{
		int element;
		struct Node* nextNode;
	};
}

using namespace linkedList;

#endif
