/** pagequeue.c
 * ===========================================================
 * Name: Dixon Ryan, Apr 23 2026
 * Section: CS483 / M4
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue* newQ = malloc(sizeof(PageQueue));

    newQ->head = NULL;
    newQ->tail = NULL;
    newQ->size = 0;
    newQ->maxSize = maxSize;

    return newQ;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {

    //baseline checks:
    /*if(pq->size == 0 || pq->head == NULL || pq->tail == NULL){
        return -1;
    }*/



    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
        PqNode* current = pq->tail;

        long code = 0;

        while(current!=NULL){
            // HIT path (page found at depth d):
            //   - Remove the node from its current position and re-insert
            //     it at the tail (most recently used).
            //   - Return d.
            if(current->pageNum == pageNum){
                PqNode* before = current->prev;
                PqNode* after = current->next;

                //have to account for if we hit on a head or tail before we move the node
                if (current == pq->head){
                    pq->head = after;
                }
                if (current == pq->tail){
                    pq->tail = before;
                }

                //normal situation
                if (before != NULL) {
                    before->next = after;
                } else {
                    pq->head = after;   // current was head
                }

                //normal situation
                if (after != NULL) {
                    after->prev = before;
                }

                //if current is already at the tail, no need to bother with rest of stuff
                if (current == pq->tail) {
                    return code;
                }

                //append to tail
                current->prev = pq->tail;
                current->next = NULL;

                pq->tail->next = current;
                pq->tail = current;

                return code;
            }
            else{
                //keep searching
                code++;
                current = current->prev;
            }
        }

    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.

        //new malloc
        PqNode* newNode = malloc(sizeof(PqNode));
        newNode->pageNum = pageNum;
        newNode->prev = pq->tail;
        newNode->next = NULL;

        //pq is null        
        if (pq->tail == NULL) {
            pq->head = newNode;
            pq->tail = newNode;
        }
        else{
            //not null, set ot tail
            pq->tail->next = newNode;
            pq->tail = newNode;
        }
        //increment pq size
        pq->size++;

        //eviction
        if(pq->size > pq->maxSize){
            PqNode* oldHead = pq->head;
            pq->head = oldHead->next;

            if (pq->head != NULL) {
                pq->head->prev = NULL;
            } else {
                pq->tail = NULL;
            }
            //decrement and free
            pq->size--;
            free(oldHead);
        }
            
    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* current = pq->head;

    //keep freeing until list is empty; size don't matter because list is gonna be freed
    while (current != NULL) {
        PqNode* next = current->next;
        free(current);
        current = next;
    }

    //free list
    free(pq);

}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
}
