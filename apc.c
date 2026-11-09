#include "apc.h"

// Function definitions
// CLA valid Function

#include "apc.h"

// CLA validation function
int cla_validation(int argc, char *argv[])
{
    if (argc != 4)
        return FAILURE;

    int i = 0;

    // Validate first operand
    if (argv[1] == NULL || argv[1][0] == '\0')
        return FAILURE;

    if (argv[1][0] == '+' || argv[1][0] == '-')
        i = 1;

    // Reject sign without digits
    if (argv[1][i] == '\0')
        return FAILURE;

    while (argv[1][i] != '\0')
    {
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
            return FAILURE;

        i++;
    }

    // Validate operator
    if (argv[2] == NULL || argv[2][0] == '\0')
        return FAILURE;

    if (argv[2][1] != '\0' ||
        !(argv[2][0] == '+' || argv[2][0] == '-' ||
          argv[2][0] == 'x' || argv[2][0] == 'X' || argv[2][0] == '/'))
    {
        return FAILURE;
    }

    int j = 0;

    // Validate third operand
    if (argv[3] == NULL || argv[3][0] == '\0')
        return FAILURE;

    if (argv[3][0] == '+' || argv[3][0] == '-')
        j = 1;

    // Reject sign without digits
    if (argv[3][j] == '\0')
        return FAILURE;

    while (argv[3][j] != '\0')
    {
        if (!(argv[3][j] >= '0' && argv[3][j] <= '9'))
            return FAILURE;

        j++;
    }

    return SUCCESS;
}

// FUNCTION create_list
int create_list(char *opr,node **head,node **tail)
{
    int i;
    
    if(opr[0] == '-')
    {
        if(insert_last(head,tail,-1) != SUCCESS)
        {
            return FAILURE;
        }
    }
    else if((opr[0] >= '0' && opr[0] <='9') || opr[0] == '+')
    {
        if(insert_last(head,tail,+1) != SUCCESS)
        {
            return FAILURE;
        }
    }
    if(opr[0] == '-' || opr[0] == '+' )
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    while( opr[i] != '\0')
    {
        if((insert_last(head, tail,opr[i] - '0')) != SUCCESS)
        {
            return FAILURE;
        }

        i++;
    }
    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    node *newnode = malloc(sizeof(node));

    if (newnode == NULL)
        return FAILURE;

    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = *tail;

    if (*tail == NULL)
    {
        *head = newnode;
    }
    else
    {
        (*tail)->next = newnode;
    }

    *tail = newnode;

    return SUCCESS;
}
// print list 
void print_list(node *head)
{
    if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d <-", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    if (head)
		        printf("> ");
	    }
    	printf(" Tail\n");
    }
}
void remove_pre_zeros(node **head)
{
    node *temp = (*head)->next;

    while (temp != NULL && temp->data == 0 && temp->next != NULL)
    {
        (*head)->next = temp->next;
        temp->next->prev = *head;

        free(temp);
        temp = (*head)->next;
    }
}
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    
    if(new == NULL)
    return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if(*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }
    else
    {
        (*head)->prev = new;
        new->next = *head ; 
        *head =new;
        return SUCCESS;
    }
    return FAILURE;
}
int compare_list(node *head1, node *head2)
{
    int l1 = 0, l2 = 0;

    node *t1 = head1->next;
    node *t2 = head2->next;

    while(t1 != NULL)
    {
        l1++;
        t1 = t1->next;
    }

    while(t2 != NULL)
    {
        l2++;
        t2 = t2->next;
    }

    if(l1 > l2)
        return OPERAND1;

    else if(l2 > l1)
        return OPERAND2;

    t1 = head1->next;
    t2 = head2->next;

    while(t1 != NULL && t2 != NULL)
    {
        if(t1->data > t2->data)
            return OPERAND1;

        else if(t1->data < t2->data)
            return OPERAND2;

        t1 = t1->next;
        t2 = t2->next;
    }

    return SAME;
}

int list_len(node *tail)
{
    node *temp = tail;
    if(tail == NULL)
    return FAILURE;
    int count = 0;
    while(temp->prev != NULL)
    {
        count++;
        temp = temp->prev;
    }

    return count;
}

#include "apc.h"

void add_opposite_signs(node *tail1, node *tail2,
                        node **headR, node **tailR,
                        int sign1, int sign2)
{
    int n1 = list_len(tail1);
    int n2 = list_len(tail2);
    int cmp = 0;

    node *temp1 = tail1;
    node *temp2 = tail2;

    /* Compare magnitudes by digit count */
    if (n1 > n2)
        cmp = 1;
    else if (n1 < n2)
        cmp = -1;
    else
    {
        /* Compare digits from most significant to least significant */
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
            else if (temp1->data < temp2->data)
            {
                cmp = -1;
                break;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    /* Equal magnitudes produce zero */
    if (cmp == 0)
    {
        insert_first(headR, tailR, 0);
        return;
    }

    /* Select the larger magnitude */
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

    int borrow = 0;

    /* Subtract digits from right to left */
    while (temp1->prev != NULL && temp2->prev != NULL)
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

    /* Process remaining digits of the larger number */
    while (temp1->prev != NULL)
    {
        int d1 = temp1->data - borrow;
        borrow = 0;

        if (d1 < 0)
        {
            d1 += 10;
            borrow = 1;
        }

        insert_first(headR, tailR, d1);

        temp1 = temp1->prev;
    }

    /* Sign follows the operand with the larger magnitude */
    if (cmp > 0)
        insert_first(headR, tailR, sign1);
    else
        insert_first(headR, tailR, sign2);
}
