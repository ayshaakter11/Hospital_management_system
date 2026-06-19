#include "head.h"

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== Hospital Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                viewPatients();
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
