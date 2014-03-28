
#include "Sort.h"


/* Description: Merge sorts list of edges.
 * Input: Linked list of edges.
 * Output: Sorted linked list of edges.
 */
void Sort::MergeSort(struct GraphEdge** edgeSet)
{
	struct GraphEdge* edge = *edgeSet;
	struct GraphEdge* list1 = NULL;
	struct GraphEdge* list2 = NULL;

	/* Base case -- length 0 or 1 */
	if ((edge == NULL) || (edge->nextEdge == NULL))
		return;

	/* Split head into 'list1' and 'list2' sublists */
	FrontBackSplit(edge, &list1, &list2);

	/* Recursively sort the sublists */
	MergeSort(&list1);
	MergeSort(&list2);

	/* answer = merge the two sorted lists together */
	*edgeSet = SortedMerge(list1,list2);
}


/* Description: Helper routine for Merge sort.
 * Input: Two sorted linked lists of edges to be merged.
 * Output: Merges the sorted linked lists.
 */
struct GraphEdge* Sort::SortedMerge(struct GraphEdge* list1, struct GraphEdge* list2)
{
	struct GraphEdge* result = NULL;

	/* Base cases */
	if (list1 == NULL)
		return(list2);
	else if (list2 == NULL)
		return(list1);

	/* Pick either a or b, and recur */
	if (list1->label <= list2->label)
	{
		result = list1;
		result->nextEdge = SortedMerge(list1->nextEdge, list2);
	}
	else
	{
		result = list2;
		result->nextEdge = SortedMerge(list1, list2->nextEdge);
	}
	return(result);
}


/* Description: Helper routine for Merge sort.
 * Input: Addresses of two empty lists .
 * Output: .
 */
void Sort::FrontBackSplit(struct GraphEdge* source,
		struct GraphEdge** frontRef, struct GraphEdge** backRef)
{

	struct GraphEdge* fast;
	struct GraphEdge* slow;
	if (source == NULL || source->nextEdge == NULL)
	{
		/* length < 2 cases */
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->nextEdge;

		/* Advance 'fast' two nodes, and advance 'slow' one node */
		while (fast != NULL)

		{
			fast = fast->nextEdge;
			if (fast != NULL)
			{
				slow = slow->nextEdge;
				fast = fast->nextEdge;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
      	  at that point. */
		*frontRef = source;
		*backRef = slow->nextEdge;
		slow->nextEdge = NULL;
	}
}
