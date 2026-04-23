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
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
        PqNode* current = pq->tail;
        for(long i = pq->size; i>= 0; i--){

            // HIT path (page found at depth d):
            //   - Remove the node from its current position and re-insert
            //     it at the tail (most recently used).
            //   - Return d.
            if(current->pageNum == pageNum){
                PqNode* before = current->prev;
                PqNode* after = current->next;

                before->next = after;

                pq->tail->next = current;
                pq->tail = current;

                return i;
            }
            else{
                current = current->prev;
            }
        }

    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.

        PqNode* newNode = malloc(sizeof(PqNode));
        newNode->pageNum = pageNum;
        newNode->prev = pq->tail;
        newNode->next = NULL;

        pq->tail = newNode;
            
    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* current = pq->head;
    PqNode* next = current->next;

    for(int i = 0; i<pq->size; i++){
        free(current);
        current = next;
        next = current->next;
    }

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
