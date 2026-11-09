#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2 = tail2;
    node *current_tail = NULL;
    int flag = 0;
    node *temp11 = tail1;
    node *temp22 = tail2;
    int n1 = 0,n2 =0 ; 
    while(temp11->prev != NULL)
    {
        if(temp11->data >= 1 && temp11->data <= 9)
        n1++;
        temp11 = temp11->prev;
    }
    while(temp22->prev != NULL)
    {
        if(temp22->data >= 1 && temp22->data <= 9)
        n2++;
       temp22 = temp22->prev;
    }
    if(n1 == 0  || n2 == 0)
    {
        insert_last(headR, tailR, 0);
        insert_first(headR,tailR,1);
        return ;
    }
    if((temp11->data == 1 && temp22->data == 1) || (temp11->data == -1 && temp22->data == -1))
    {
        flag = 1;
    }
    else if((temp11->data == 1 && temp22->data == -1) || (temp11->data == -1 && temp22->data == 1))
    {
        flag = 2;
    }
    temp22 = tail2;
    temp11 = tail1;
    int n = 0;
    while(temp22->prev != NULL)
    {
        int carry = 0;
        
        mul(tail1,temp22->data,headR,tailR,n);

        temp22 = temp22->prev;

        n++;
         
    }
    if(flag == 1)
    insert_first(headR,tailR,1);
    else if(flag == 2)
    insert_first(headR,tailR,-1);
}
void mul(node *tail1,int n,node **headR,node **tailR,int count)
{
    node *temp = tail1;
    node *temp1 = *tailR;
    int carry = 0;
    if(*headR == NULL &&  *tailR == NULL)
    {
        while(temp->prev != NULL)
        {
            int k = (n * temp->data) + carry;
            carry = k / 10;
            k = k % 10;
            insert_first(headR,tailR,k);
            temp = temp->prev;
        }
        if(carry != 0)
        insert_first(headR,tailR,carry);
    }
    else
    {
        while(count-- && temp1 != NULL)
            temp1 = temp1->prev;

        while(temp->prev != NULL)
        {
            int k = (n * temp->data) + carry;

            if(temp1 != NULL)
            {
                k += temp1->data;
                temp1->data = k % 10;
                temp1 = temp1->prev;
            }
            else
            {
                insert_first(headR, tailR, k % 10);
            }

            carry = k / 10;
            temp = temp->prev;
        }

        if(carry != 0)
            insert_first(headR, tailR, carry);
    }
}