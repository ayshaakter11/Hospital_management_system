#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

/* Data storage using arrays */
int id[100];
char name[100][50];
int age[100];

int totalPatients = 0;

/* Function declarations */
void addPatient();
void viewPatients();

/* Function definitions */

void addPatient()
{
    printf("\nEnter Patient ID: ");
    scanf("%d", &id[totalPatients]);

    printf("Enter Full Name: ");
    scanf(" %[^\n]", name[totalPatients]);

    printf("Enter Age: ");
    scanf("%d", &age[totalPatients]);

    totalPatients++;

    printf("\nPatient Added Successfully!\n");
}

void viewPatients()
{
    if(totalPatients == 0)
    {
        printf("\nNo Patient Found!\n");
        return;
    }

    printf("\n===== Patient List =====\n");

    for(int i = 0; i < totalPatients; i++)
    {
        printf("\nPatient %d\n", i + 1);
        printf("ID   : %d\n", id[i]);
        printf("Name : %s\n", name[i]);
        printf("Age  : %d\n", age[i]);
    }
}

#endif
