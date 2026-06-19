#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>

struct Patient
{
    int id;
    char name[50];
    int age;
};

struct Patient patients[100];
int totalPatients = 0;

/* Function declarations */
void addPatient();
void viewPatients();

/* Function definitions */

void addPatient()
{
    printf("\nEnter Patient ID: ");
    scanf("%d", &patients[totalPatients].id);

    printf("Enter Full Name: ");
    scanf(" %[^\n]", patients[totalPatients].name);

    printf("Enter Age: ");
    scanf("%d", &patients[totalPatients].age);

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
        printf("ID   : %d\n", patients[i].id);
        printf("Name : %s\n", patients[i].name);
        printf("Age  : %d\n", patients[i].age);
    }
}

#endif
