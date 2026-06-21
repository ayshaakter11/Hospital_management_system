#include <stdio.h>
#include "hospital.h"

int main() {
    int choice;

    while(1) {
        printf("=== MAIN MENU ===\n");
        printf("1. Add Patient\n");
        printf("2. View Information\n");
        printf("3. AI Psychologist Advisor\n"); 
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addPatient();
        } 
        else if (choice == 2) {
            viewpatients(); 
        } 
        else if (choice == 3) {
            aiPsychologist(); // Calls the serious psychologist chatbot
        } 
        else if (choice == 4) {
            printf("Exiting program...\n");
            break;
        } 
        else {
            printf("Invalid choice! Please try again.\n\n");
        }
    }

    return 0;

}
