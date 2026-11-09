#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;

    // Validation
	if(argc == 4)
	{
		if(cla_validation(argc,argv) == SUCCESS)
		{
			printf("Arguments are valid\n");
		}
		else
		{
			printf("Arguments Are Invalid \n");
			return FAILURE;
		}
	}
	else
	{
		printf("Invalid Arguments\n");
		return FAILURE;
	}
    // Create 2 lists of operands
    if(( create_list (argv[1] , &head1 , &tail1 )) == FAILURE)
	{
		printf("Unable To Insert into list first operand\n");
		return FAILURE;
	}
	if(( create_list (argv[3] , &head2 , &tail2 )) == FAILURE)
	{
		printf("Unable To Insert into list second operand \n");
		return FAILURE;
	}
    print_list(head1);
	printf("\n");
	print_list(head2);
    remove_pre_zeros(&head1);
	printf("\n");
	print_list(head1);

	remove_pre_zeros(&head2);
	printf("\n");
	print_list(head2);
    // Remove pre zeros

    char oper = argv[2][0];

    switch(oper)
    {
	case '+':
	    addition(tail1, tail2, &headR, &tailR);
		remove_pre_zeros(&headR);
		printf("\n");
	    print_list(headR);
	    break;

	case '-':
	    subtraction(tail1, tail2, &headR, &tailR);
		remove_pre_zeros(&headR);
		printf("\n");
	    print_list(headR);
	    break;

	case 'x':
	case 'X':
	    multiplication(tail1,tail2, &headR,&tailR);
		remove_pre_zeros(&headR);
		printf("\n");
	    print_list(headR);
	    break;

	case '/':
	    division(head1,head2,&headR,&tailR);
		remove_pre_zeros(&headR);
		printf("\n");
	    print_list(headR);
	    break;

	default:
	    printf("Invalid operator\n");
    }
	
}

