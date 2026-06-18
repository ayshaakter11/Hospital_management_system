#include <stdio.h>
#include "head.h"

int main()
{
    int choice, adminChoice, userChoice;

    while(1)
    {
        printf("\n====================================\n");
        printf("     HOSPITAL MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. User Panel\n");
        printf("2. Admin Panel\n");
        printf("3. Exit\n");

        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); // Clear the input buffer
            continue;
        }

        /* ================= USER PANEL ================= */
        if(choice == 1)
        {
            while(1)
            {
                printf("\n-------- USER PANEL --------\n");
                printf("1. Doctor List\n");
                printf("2. Book Appointment\n");
                printf("3. Cancel Appointment\n");
                printf("4. Diagnostic Facilities\n");
                printf("5. Generate Bill\n");
                printf("6. Back\n");

                printf("Enter choice: ");
                if (scanf("%d", &userChoice) != 1) {
                    printf("Invalid input!\n");
                    while(getchar() != '\n');
                    continue;
                }

                if(userChoice == 1)      doctorList();
                else if(userChoice == 2) bookAppointment();
                else if(userChoice == 3) cancelAppointment();
                else if(userChoice == 4) diagnosticList();
                else if(userChoice == 5) generateBill();
                else if(userChoice == 6) break;
                else                     printf("Invalid choice!\n");
            }
        }

        /* ================= ADMIN PANEL ================= */
        else if(choice == 2)
        {
            // Crucial Fix: Only enter if passwordCheck() returns 1 (true)
            if (passwordCheck() == 1)
            {
                while(1)
                {
                    printf("\n-------- ADMIN PANEL --------\n");
                    printf("1. Add Doctor\n");
                    printf("2. Edit Doctor\n");
                    printf("3. Delete Doctor\n");
                    printf("4. View Appointments\n");
                    printf("5. View Bills\n");
                    printf("6. Back\n");

                    printf("Enter choice: ");
                    if (scanf("%d", &adminChoice) != 1) {
                        printf("Invalid input!\n");
                        while(getchar() != '\n');
                        continue;
                    }

                    if(adminChoice == 1)      addDoctor();
                    else if(adminChoice == 2) editDoctor();
                    else if(adminChoice == 3) deleteDoctor();
                    else if(adminChoice == 4) viewAppointment();
                    else if(adminChoice == 5) viewBill();
                    else if(adminChoice == 6) break;
                    else                      printf("Invalid choice!\n");
                }
            }
            else
            {
                printf("Access Denied: Incorrect Password.\n");
            }
        }

        /* ================= EXIT ================= */
        else if(choice == 3)
        {
            printf("Exiting system...\n");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
