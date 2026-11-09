
#include "apc.h"

void subtraction(node *tail1, node *tail2,
                 node **headR, node **tailR)
{
    if (tail1 == NULL || tail2 == NULL)
        return;

    node *temp1 = tail1;
    node *temp2 = tail2;

    /* Get signs */
    while (temp1->prev != NULL)
        temp1 = temp1->prev;

    int sign1 = temp1->data;

    while (temp2->prev != NULL)
        temp2 = temp2->prev;

    int sign2 = temp2->data;

    /* Different signs: add magnitudes */
    if (sign1 != sign2)
    {
        int carry = 0;

        temp1 = tail1;
        temp2 = tail2;

        while (temp1->prev != NULL &&
               temp2->prev != NULL)
        {
            int sum = temp1->data + temp2->data + carry;

            insert_first(headR, tailR, sum % 10);
            carry = sum / 10;

            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }

        while (temp1->prev != NULL)
        {
            int sum = temp1->data + carry;

            insert_first(headR, tailR, sum % 10);
            carry = sum / 10;

            temp1 = temp1->prev;
        }

        while (temp2->prev != NULL)
        {
            int sum = temp2->data + carry;

            insert_first(headR, tailR, sum % 10);
            carry = sum / 10;

            temp2 = temp2->prev;
        }

        if (carry)
            insert_first(headR, tailR, carry);

        /* Result sign */
        if ((*headR)->data != 0 || *headR != *tailR)
            insert_first(headR, tailR,
                         (sign1 == 1) ? 1 : -1);

        return;
    }

    /* Same signs: compare magnitudes */
    int n1 = list_len(tail1) - 1;
    int n2 = list_len(tail2) - 1;
    int cmp = 0;

    if (n1 > n2)
        cmp = 1;
    else if (n1 < n2)
        cmp = -1;
    else
    {
        temp1 = tail1;
        temp2 = tail2;

        while (temp1->prev != NULL)
            temp1 = temp1->prev;

        while (temp2->prev != NULL)
            temp2 = temp2->prev;

        temp1 = temp1->next;
        temp2 = temp2->next;

        while (temp1 != NULL && temp2 != NULL)
        {
            if (temp1->data > temp2->data)
            {
                cmp = 1;
                break;
            }

            if (temp1->data < temp2->data)
            {
                cmp = -1;
                break;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    /* Equal magnitudes */
    if (cmp == 0)
    {
        insert_first(headR, tailR, 0);
        return;
    }

    /* Select larger magnitude */
    if (cmp > 0)
    {
        temp1 = tail1;
        temp2 = tail2;
    }
    else
    {
        temp1 = tail2;
        temp2 = tail1;
    }

    /* Subtract digit by digit */
    int borrow = 0;

    while (temp1->prev != NULL &&
           temp2->prev != NULL)
    {
        int d1 = temp1->data - borrow;
        int d2 = temp2->data;

        borrow = 0;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }

        insert_first(headR, tailR, d1 - d2);

        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }

    while (temp1->prev != NULL)
    {
        int digit = temp1->data - borrow;
        borrow = 0;

        if (digit < 0)
        {
            digit += 10;
            borrow = 1;
        }

        insert_first(headR, tailR, digit);
        temp1 = temp1->prev;
    }

 
    /* Determine result sign */
    if (cmp > 0)
    {
        insert_first(headR, tailR,
                     (sign1 == 1) ? 1 : -1);
    }
    else
    {
        insert_first(headR, tailR,
                     (sign1 == 1) ? -1 : 1);
    }
}
