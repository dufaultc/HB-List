//This file contains all functions I created to complete Assignment 3.
//This file is used in conjunction with main.c, makefile, and assignment3.h
//Programmer: Cameron Dufault

#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Returns a pointer to an HB list with n ≥ 0 horizontal nodes,
 and each of the bottom lists has a number of nodes that is a
 random number in [0,m], m ≥ 0. The keys of each list are randomly
 generated and in increasing order
*/
HBnodePtr createHBlist(int n, int m) {
  int x;
  int y;
  x = time(NULL);

  int carryOver = 0;
  int carryOverSL = 0;
  srand(x);

  SLnodePtr currentNodeSL;

  HBnodePtr head = NULL;
  HBnodePtr currentNode;

  for (int i = 0; i < n; i++) {
    srand(x);
    x = x + (carryOver + 1);
    y = x;

    if (i == 0) {

      head = malloc(sizeof(struct HBnode));

      head->next = NULL;
      head->key = carryOver + rand() % 10;
      head->bottom = NULL;

      // managing key values
      carryOver = head->key;
      carryOverSL = head->key;

      x = x + carryOver;
      srand(x);

    }

    else {
      if (i == 1) {
        head->next = malloc(sizeof(struct HBnode));
        currentNode = head->next;

      } else {
        currentNode->next = malloc(sizeof(struct HBnode));
        currentNode = currentNode->next;
      }

      currentNode->next = NULL;
      currentNode->key = carryOver + rand() % 10;
      currentNode->bottom = NULL;

      // managing key values
      carryOver = currentNode->key;
      carryOverSL = currentNode->key;

      x = x + carryOver;
      srand(x);
    }
    for (int j = 0; j < ((rand() % (m + 2)) - 1); j++) {

      if (i == 0 && j == 0) {
        head->bottom = malloc(sizeof(struct SLnode));
        currentNodeSL = head->bottom;
      } else if (j == 0) {
        currentNode->bottom = malloc(sizeof(struct SLnode));
        currentNodeSL = currentNode->bottom;
      } else {
        currentNodeSL->next = malloc(sizeof(struct SLnode));
        currentNodeSL = currentNodeSL->next;
      }

      y = y + (carryOverSL + 1);
      srand(y);

      currentNodeSL->next = NULL;
      currentNodeSL->key = carryOverSL + rand() % 10;

      // managing key values
      carryOverSL = currentNodeSL->key;
    }
  }

  return head;
}

//outputting the structure in readable form
void printHBlist(HBnodePtr L) {

  HBnodePtr currentNode = L;
  SLnodePtr currentNodeSL;
  while (currentNode != NULL) {
    printf("   ||%d||", currentNode->key);
    currentNodeSL = currentNode->bottom;

    currentNode = currentNode->next;

    while (currentNodeSL != NULL) {
      printf("%d ", currentNodeSL->key);
      currentNodeSL = currentNodeSL->next;
    }
  }
}


/*Converts an HB list into a SL list and returns a pointer to the latter 
  in non-increasing order without using arrays and sorting
*/
SLnodePtr flattenList(const HBnodePtr L) {
  HBnodePtr currentNode = L;
  SLnodePtr currentNodeSL;

  SLnodePtr headSL = NULL;
  SLnodePtr currentOther = NULL;

  int temp;
  int count = 1;
  int doneflag = 0;
  int multCount = 0;

  if (currentNode != NULL) {
    headSL = malloc(sizeof(struct SLnode));
    headSL->key = currentNode->key;
    headSL->next = NULL;

    int high;
    int passes = 0;

    while (doneflag == 0) {
      if (passes == 0) {
        temp = headSL->key;
        high = 100000000;

      } else {
        temp = high;
        high = 100000000;
      }

      doneflag = 1;
      multCount = 0;

      if (currentNode != NULL) {
        passes = passes + 1;
      }

      while (currentNode != NULL) {

        if ((currentNode->key > temp) && (currentNode->key < high)) {
          high = currentNode->key;
          doneflag = 0;
        }

        if (currentNode->key == temp) {
          multCount = multCount + 1;
        }

        currentNodeSL = currentNode->bottom;
        currentNode = currentNode->next;

        while (currentNodeSL != NULL) {
          if ((currentNodeSL->key > temp) && (currentNodeSL->key < high)) {

            high = currentNodeSL->key;
            doneflag = 0;
          }

          if (currentNodeSL->key == temp) {
            multCount = multCount + 1;
          }
          currentNodeSL = currentNodeSL->next;
        }
      }

      if (doneflag == 0 && passes == 1) {
        if (multCount > 1) {
          headSL->next = malloc(sizeof(struct SLnode));
          currentOther = headSL->next;
          currentOther->key = temp;
          currentOther->next = NULL;

          for (int i = 1; i < (multCount - 1); i++) {
            currentOther->next = malloc(sizeof(struct SLnode));
            currentOther = currentOther->next;
            currentOther->key = temp;
            currentOther->next = NULL;
          }

          currentOther->next = malloc(sizeof(struct SLnode));
          currentOther = currentOther->next;

          currentOther->key = high;
          currentOther->next = NULL;

        } else {

          headSL->next = malloc(sizeof(struct SLnode));
          currentOther = headSL->next;

          currentOther->key = high;
          currentOther->next = NULL;
        }

        currentNode = L;

      } else if (doneflag == 0) {

        if (multCount != 1) {
          for (int j = 1; j < (multCount); j++) {
            currentOther->next = malloc(sizeof(struct SLnode));
            currentOther = currentOther->next;
            currentOther->key = temp;
            currentOther->next = NULL;
          }
        }
        currentOther->next = malloc(sizeof(struct SLnode));
        currentOther = currentOther->next;

        currentOther->key = high;
        currentOther->next = NULL;
        currentNode = L;

      } else if ((doneflag == 1) && (multCount != 1)) {
        for (int j = 1; j < (multCount); j++) {
          currentOther->next = malloc(sizeof(struct SLnode));
          currentOther = currentOther->next;
          currentOther->key = temp;
          currentOther->next = NULL;
        }
      }
    }
  }

  return headSL;
}

//Outputs the keys in a SL list at L
void printSLlist(SLnodePtr L) {
  printf("\n");
  SLnodePtr currentNodeSL;
  currentNodeSL = L;
  while (currentNodeSL != NULL) {
    printf(" ||%d||", currentNodeSL->key);

    currentNodeSL = currentNodeSL->next;
  }
}

//Frees all the memory allocated for the list at L.
void freeSLlist(SLnodePtr L) {

  SLnodePtr toFree;
  while (L != NULL) {
    toFree = L;
    L = L->next;
    free(toFree);
  }
}

//Frees all the memory allocated for the list at L.
void freeHBlist(HBnodePtr L) {
  SLnodePtr currentSLnode;
  SLnodePtr toFreeSL;
  HBnodePtr toFreeHB;
  while (L != NULL) {
    toFreeHB = L;
    currentSLnode = L->bottom;

    L = L->next;
    free(toFreeHB);

    while (currentSLnode != NULL) {
      toFreeSL = currentSLnode;
      currentSLnode = currentSLnode->next;
      free(toFreeSL);
    }
  }
}