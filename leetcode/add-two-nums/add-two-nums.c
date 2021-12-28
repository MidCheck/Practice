#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* new_node(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    if (node == NULL) return NULL;
    node->val = val;
    node->next = NULL;
    return node;
}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head, *cur, *node;
    int value, flag;
    
    head = NULL;
    cur = NULL;
    
    flag = 0;
    while (l1 != NULL && l2 != NULL) {
        value = l1->val + l2->val + flag;
        node = new_node(value % 10);
        if (node == NULL) return head;
        if (head == NULL) head = node;
        else cur->next = node; 
        cur = node;
        flag = value >= 10 ? 1 : 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    for (; l1 != NULL; l1 = l1->next) {
        value = l1->val + flag;
        node = new_node(value % 10);
        if (node == NULL) return head;
        cur->next = node;
        cur = node;
        flag = value >= 10 ? 1 : 0;
    }
    
    for (; l2 != NULL; l2 = l2->next) {
        value = l2->val + flag;
        node = new_node(value % 10);
        if (node == NULL) return head;
        cur->next = node;
        cur = node;
        flag = value >= 10 ? 1 : 0;
    }
    
    if (flag) {
        node = new_node(flag);
        if (node == NULL) return head;
        cur->next = node;
    }
    
    return head;
}
