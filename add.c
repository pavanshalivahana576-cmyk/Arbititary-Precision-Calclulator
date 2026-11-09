
#include "apc.h"

void addition(node *tail1, node *tail2,
              node **headR, node **tailR)
{
    int sign1, sign2;

    node *temp1 = tail1;
    while (temp1->prev != NULL)
        temp1 = temp1->prev;
    sign1 = temp1->data;

    node *temp2 = tail2;
    while (temp2->prev != NULL)
        temp2 = temp2->prev;
    sign2 = temp2->data;

    int flag = 0;

    if (sign1 == -1 && sign2 == -1)
        flag = 1;

    /* Both signs are the same: add magnitudes */
    if ((sign1 == 1 && sign2 == 1) ||
        (sign1 == -1 && sign2 == -1))
    {
        int sum = 0, carry = 0;

        temp1 = tail1;
        temp2 = tail2;

        while (temp1->prev != NULL && temp2->prev != NULL)
        {
            sum = temp1->data + temp2->data + carry;
            carry = sum / 10;

            insert_first(headR, tailR, sum % 10);

            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }

        while (temp2->prev != NULL)
        {
            sum = temp2->data + carry;
            carry = sum / 10;

            insert_first(headR, tailR, sum % 10);

            temp2 = temp2->prev;
        }

        while (temp1->prev != NULL)
        {
            sum = temp1->data + carry;
            carry = sum / 10;

            insert_first(headR, tailR, sum % 10);

            temp1 = temp1->prev;
        }

        if (carry != 0)
            insert_first(headR, tailR, carry);

        /* Insert sign unless the result is zero */
        if (!((*headR)->data == 0 && (*headR)->next == NULL))
        {
            if (flag == 0)
                insert_first(headR, tailR, 1);
            else
                insert_first(headR, tailR, -1);
        }
    }
    /* Different signs: subtract magnitudes */
    else if (sign1 != sign2)
    {
        add_opposite_signs(tail1, tail2,
                           headR, tailR, sign1, sign2);
    }
}

