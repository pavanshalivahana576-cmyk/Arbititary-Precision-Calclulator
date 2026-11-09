#include "apc.h"

/* free an intermediate list (local helper) */
static void free_temp_list(node *head)
{
    node *next;

    while (head != NULL)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

void division(node *head1, node *head2, node **headR, node **tailR)
{
    /* ---------- division by zero check ---------- */
    node *temp = head2->next;
    int zero = 1;

    while (temp != NULL)
    {
        if (temp->data != 0)
        {
            zero = 0;
            break;
        }
        temp = temp->next;
    }

    if (zero)
    {
        printf("\nError Division BY Zero\n");
        exit(EXIT_FAILURE);
    }

    /* ---------- signs ---------- */
    int sign1 = head1->data;
    int sign2 = head2->data;
    int sign  = sign1 * sign2;

    /* ---------- tails and digit counts ---------- */
    node *tail1 = head1;
    node *tail2 = head2;
    int count1 = 0, count2 = 0;

    while (tail1->next != NULL)
    {
        tail1 = tail1->next;
        count1++;
    }

    while (tail2->next != NULL)
    {
        tail2 = tail2->next;
        count2++;
    }

    /* dividend has fewer digits than divisor -> quotient is 0 */
    if (count1 < count2)
    {
        insert_last(headR, tailR, 0);
        insert_first(headR, tailR, 1);
        return;
    }

    /* ---------- work on magnitudes ---------- */
    head1->data = 1;
    head2->data = 1;

    node *curHead = head1;      
    node *curTail = tail1;
    node *newHead = NULL;
    node *newTail = NULL;

    unsigned long long num = 0;

    while (compare_list(curHead, head2) != OPERAND2)
    {
        subtraction(curTail, tail2, &newHead, &newTail);

        /* equal magnitudes: subtraction returns a lone 0 without a sign node */
        if (newHead->next == NULL)
            insert_first(&newHead, &newTail, 1);

        /* remove leading zeros so compare_list works correctly */
        remove_pre_zeros(&newHead);

        /* free the old remainder, but never the caller's dividend */
        if (curHead != head1)
            free_temp_list(curHead);

        curHead = newHead;
        curTail = newTail;

        newHead = NULL;
        newTail = NULL;

        num++;
    }

    /* free the last remainder */
    if (curHead != head1)
        free_temp_list(curHead);

    /* ---------- restore original signs ---------- */
    head1->data = sign1;
    head2->data = sign2;

    /* ---------- build quotient list ---------- */
    if (num == 0)
    {
        insert_last(headR, tailR, 0);
        sign = 1;
    }
    else
    {
        while (num > 0)
        {
            insert_first(headR, tailR, (int)(num % 10));
            num = num / 10;
        }
    }

    /* quotient sign */
    insert_first(headR, tailR, sign);
}