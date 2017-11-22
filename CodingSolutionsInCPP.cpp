//
//  CodingSolutionsInCPP.cpp
//  CodingPracticeCPP
//
//  Created by Ali Mir.
//  Copyright © 2017 Ali Mir. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

/*
 PRETTYPRINT
 Print concentric rectangular pattern in a 2d matrix.
 Let us show you some examples to clarify what we mean.
 */
vector<vector<int>> prettyPrint(int A) {
    vector<vector<int>> retMatrix;
    int len = A*2-1;
    int direction = 0;
    int top = 0, bottom = len-1, left = 0, right = len-1;
    int currNum = A;
    
    for (int i = 0; i < len; i++) {
        retMatrix.push_back(vector<int>());
        for (int j = 0; j < len; j++) {
            retMatrix[i].push_back(0);
        }
    }
    
    while (left <= right && top <= bottom) {
        if (direction == 0) {
            for (int i = left; i <= right; i++) {
                retMatrix[top][i] = currNum;
            }
            top++;
        } else if (direction == 1) {
            for (int i = top; i <= bottom; i++) {
                retMatrix[i][right] = currNum;
            }
            right--;
        } else if (direction == 2) {
            for (int i = right; i >= left; i--) {
                retMatrix[bottom][i] = currNum;
            }
            bottom--;
        } else {
            for (int i = bottom; i >= top; i--) {
                retMatrix[i][left] = currNum;
            }
            left++;
        }
        if (direction == 3) currNum--;
        direction  = (direction + 1) % 4;
    }
    
    return retMatrix;
}

/*
 NUMRANGE
 
 Given an array of non negative integers A, and a range (B, C),
 find the number of continuous subsequences in the array which have sum S in the range [B, C] or B <= S <= C
 
 Continuous subsequence is defined as all the numbers A[i], A[i + 1], .... A[j]
 where 0 <= i <= j < size(A)
 */

int numRange(vector<int> &A, int B, int C) {
    int retNum = 0;
    vector<int> workingArray;
    
    for (int i = 0; i < A.size(); i++) {
        int tempSum = 0;
        for (int j = i; j < A.size(); j++) {
            tempSum += A[j];
            if (tempSum > C) break;
            workingArray.push_back(tempSum);
        }
    }
    
    for (int i = 0; i < workingArray.size(); i++) {
        if (workingArray[i] >= B && workingArray[i] <= C) {
            retNum++;
        }
    }
    return retNum;
}

/* Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printLinkedList(ListNode *A) {
    while (A != NULL) {
        cout << A->val;
        if (A->next != NULL) cout << "->";
        A = A->next;
    }
    cout << endl;
}

/*
 Reverse a linked list.
 */

ListNode* reverse(ListNode *A) {
    if (A == NULL || A->next == NULL) return A;
    
    ListNode *current = NULL;
    ListNode *oldNext;
    
    while (A != NULL) {
        oldNext = A->next;
        A->next = current;
        current = A;
        if (oldNext == NULL) break;
        A = oldNext;
    }
    
    return A;
}

/*
 Divides the linked list into half (odd is lower bound) and returns the head of the second half of the linked list.
 */

ListNode* divide(ListNode* A) {
    if (A == NULL || A->next == NULL) return A;
    ListNode *runner = A;
    while(runner != NULL) {
        runner = runner->next;
        if (runner->next == NULL) break;
        runner = runner->next;
        if (runner->next == NULL) break;
        A = A->next;
    }
    ListNode *retNode = A->next;
    A->next = NULL;
    return retNode;
}

/*
 SUBTRACT
 
 Given a singly linked list, modify the value of first half nodes such that :
 
 1st node’s new value = the last node’s value - first node’s current value
 2nd node’s new value = the second last node’s value - 2nd node’s current value,
 and so on …
 */

ListNode* subtract(ListNode* A) {
    if (A == NULL || A->next == NULL) return A;
    ListNode *firstHead = A;
    ListNode *secondHead = divide(A);
    ListNode *reversedSecondHead = reverse(secondHead);
    ListNode *tempSecond = reversedSecondHead;
    
    while(A != NULL) {
        A->val = reversedSecondHead->val - A->val;
        if (A->next == NULL) break;
        A = A->next;
        reversedSecondHead = reversedSecondHead->next;
    }
    
    
    ListNode *finalSecond = reverse(tempSecond);
    A->next = finalSecond;
    return firstHead;
}

/*
 Longest Consecutive Sequence
 Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 */

int longestConsecutive(const vector<int> &A) {
    unordered_set<int> Set;
    int j = 0;
    int retVal = 0;
    
    for (int i = 0; i < A.size(); i++)
        Set.insert(A[i]);
    
    for (int i = 0; i < A.size(); i++) {
        if (Set.find(A[i] - 1) == Set.end()) {
            // First seq.
            j = A[i];
            while (Set.find(j) != Set.end())
                j++;
            retVal = max(retVal, j-A[i]);
        }
    }
    return retVal;
}
