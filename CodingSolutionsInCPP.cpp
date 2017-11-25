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

/*
Justified Text
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
You should pack your words in a greedy approach; that is, pack as many words as you can in each line.

Pad extra spaces ‘ ‘ when necessary so that each line has exactly L characters.
Extra spaces between words should be distributed as evenly as possible.
If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
For the last line of text, it should be left justified and no extra space is inserted between words.

Your program should return a list of strings, where each string represents a single line.
*/

vector<string> fullJustify(vector<string> &A, int B) {
    vector<string> retVector;
    vector<int> nums;
    int j = 0, k = 0;
    string currString = "";
    int currNum = 0;
    
    for (int i = 0; i < A.size(); i++) {
        int wordSize = int(A[i].size());
        int testNum = int(currString.size()) + wordSize + currNum;
        if(testNum <= B) {
            currString += A[i];
            ++currNum;
        } else {
            nums.push_back(currNum);
            currString = A[i];
            currNum = 1;
        }
        if (i == A.size() - 1) nums.push_back(currNum);
    }
    
    for (int i = 0; i < nums.size(); i++) retVector.push_back("");
    
    int countCurrLetters = 0;
    int tot_spaces_left = 0;
    int extra_space_for_each = 0;
    int extra_extra_space = 0;
    
    while (j < A.size()) {
        
        countCurrLetters = 0;
        
        for (int i = 0; i < nums[k]; i++) {
            countCurrLetters += int(A[j+i].size());
        }
        
        tot_spaces_left = (B - countCurrLetters);
        
        extra_extra_space = (nums[k] - 1) != 0 ? tot_spaces_left%(nums[k] - 1) : 0;
        
        if (k == nums.size() - 1) {
            for (int i = 0; i < nums[k]; i++) {
                retVector[k] += A[j];
                if (tot_spaces_left > 0) {
                    retVector[k] += " ";
                    --tot_spaces_left;
                }
                j++;
            }
            while (tot_spaces_left > 0) {
                retVector[k] += " ";
                --tot_spaces_left;
            }
        } else {
            for (int i = 0; i < nums[k]; i++) {
                extra_space_for_each = (nums[k] == 1) ? tot_spaces_left : int((tot_spaces_left/(nums[k] - 1)));
                retVector[k] += A[j];
                j++;
                if (extra_extra_space > 0) {
                    retVector[k] += " ";
                    --extra_extra_space;
                }
                if (retVector[k].size() == B) {
                    break;
                }
                while(extra_space_for_each > 0) {
                    retVector[k] += " ";
                    --extra_space_for_each;
                }
            }
        }
        
        k++;
    }
    
    return retVector;
}


/*
Checks to see if string is a palindrome. A very simple approach.
*/

bool isPalindromeSimple(string A) {
    int i = 0;
    int j = int(A.size()) - 1;
    while (i <= j) {
        if (A[i] != A[j])
            return false;
        i++;
        j--;
    }
    return true;
}

/*
Minimum Characters required to make a String Palindromic
You are given a string. The only operation allowed is to insert characters in the beginning of the string. 
How many minimum characters are needed to be inserted to make the string a palindrome string
*/

int minCharactersRequiredToMakePalindrome(string A) {
    char first = A[0];
    
    int i = A.size() - 1;
    int k = 0;
    
    while (i >= 0) {
        if (A[i] == first) {
            string toCheck = A.substr(0, i+1);
            if (isPalindromeSimple(toCheck)) {
                return A.size() - (i+1);
            }
        }
        i--;
    }
    
    return A.size() - 1;
}

/*
Length of Last Word
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
If the last word does not exist, return 0.
Note: A word is defined as a character sequence consists of non-space characters only.
*/

int lengthOfLastWord(const string &A) {
    if (A.size() < 1) return 0;
    int i = int(A.size()) - 1;
    int retVal = 0;
    
    while(A[i] == ' ') {
        --i;
    }
    
    while (i >= 0 ) {
        if (A[i] == ' ') return retVal;
        ++retVal;
        --i;
    }
    
    return retVal;
}

/*
Noble Integer
Given an integer array, find if an integer p exists in the array such that the number of integers greater than p in the array equals to p
If such an integer is found return 1 else return -1.
*/

int nobleInteger(vector<int> &A) {
    sort(A.begin(), A.end());
    
    for (int i = 0; i < A.size(); i++) {
        if (i == A.size() - 1 && A[i] == 0) return 1;
        if (A[i] == (A.size() - i - 1) && A[i+1] > A[i]) {
            return 1;
        }
    }

    return -1;
}
