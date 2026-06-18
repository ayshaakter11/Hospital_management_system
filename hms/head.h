#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUCTURES
   ========================= */

struct Doctor
{
    int id;
    char name[50];
    char department[30];
    float fee;
    char time[30];
};

struct Patient
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[30];
    char doctor[50];
    char date[20];
    char time[20];
};

struct Bill
{
    int billID;
    char patientName[50];
    char doctorName[50];
    float doctorFee;
    float testFee;
    float totalFee;
};

/* =========================
   FUNCTION PROTOTYPES
   ========================= */
void doctorList();
void addDoctor();
void editDoctor();
void deleteDoctor();
void showDiseases();
void bookAppointment();
void viewAppointment();
int generateAppointmentID();
void cancelAppointment();
void diagnosticList();
void generateBill();
void viewBill();
int passwordCheck();
void adminPanel();

/* DOCTOR FUNCTIONS */
void doctorList()
{
    FILE *fp = fopen("doctor.txt", "r");
    struct Doctor d;

    if (fp == NULL)
    {
        printf("\nNo doctor records found!\n");
        return;
    }

    printf("\n================ CURRENT DOCTOR ROSTER ================\n");
    printf("%-10s %-25s %-20s %-12s %-15s\n", "ID", "Name", "Department", "Fee", "Shift/Time");
    printf("----------------------------------------------------------------------\n");

    while (fscanf(fp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
    {
        printf("%-10d %-25s %-20s %-12.2f %-15s\n", d.id, d.name, d.department, d.fee, d.time);
    }
    printf("======================================================================\n");

    fclose(fp);
}
void showDiseases()
{
    printf("\n--- SELECT SPECIALTY / DISEASE CATEGORY ---\n");
    printf("1. Medicine\n");
    printf("2. Skin\n");
    printf("3. Cardiology\n");
    printf("4. Orthopedic\n");
    printf("5. Dental\n");
}
int generateDoctorID()
{
    FILE *fp = fopen("doctor.txt", "r");
    struct Doctor d;
    int max = 0;

    if(fp == NULL)
        return 101;   // Starting doctor ID if file doesn't exist

    while(fscanf(fp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
    {
        if(d.id > max)
        {
            max = d.id;
        }
    }

    fclose(fp);
    return (max == 0) ? 101 : max + 1;
}

void selectDepartment(char *dest)
{
    int deptChoice;
    while(1) {
        printf("\n--- SELECT DEPARTMENT ---\n");
        printf("1. Medicine\n");
        printf("2. Skin\n");
        printf("3. Cardiology\n");
        printf("4. Orthopedic\n");
        printf("5. Dental\n");
        printf("Enter choice (1-5): ");
        if (scanf("%d", &deptChoice) == 1) {
            if(deptChoice == 1)      { strcpy(dest, "Medicine"); break; }
            else if(deptChoice == 2) { strcpy(dest, "Skin"); break; }
            else if(deptChoice == 3) { strcpy(dest, "Cardiology"); break; }
            else if(deptChoice == 4) { strcpy(dest, "Orthopedic"); break; }
            else if(deptChoice == 5) { strcpy(dest, "Dental"); break; }
        }
        printf("Invalid choice! Please select between 1 and 5.\n");
        while(getchar() != '\n'); // Clear buffer
    }
}
/* ENHANCED DOCTOR MANAGEMENT FUNCTIONS*/
void addDoctor()
{
    FILE *fp = fopen("doctor.txt", "a");
    struct Doctor d;
    int ch;

    if(fp == NULL) {
        printf("Error: Could not open database file!\n");
        return;
    }

    d.id = generateDoctorID(); // 1. Auto Generate ID
    printf("\n[System] Auto-Generated Doctor ID: %d\n", d.id);

    printf("Enter Name (Use_Underscores): "); // 2. Read Name
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = 0;

    selectDepartment(d.department);// 3. Guided Department Menu

    printf("Enter Visiting Fee: "); // 4. Fees & Shift Time
    scanf("%f", &d.fee);

    printf("Enter Shift/Time (e.g., 09:00-14:00): ");
    scanf("%s", d.time);

    fprintf(fp, "%d %s %s %.2f %s\n", d.id, d.name, d.department, d.fee, d.time); // Save
    fclose(fp);

    printf("\n Success: Doctor %s added under ID %d!\n", d.name, d.id);
}
void editDoctor()
{
    doctorList();

    FILE *fp = fopen("doctor.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Doctor d;
    int id, found = 0, ch;

    if(fp == NULL || temp == NULL) {
        printf("Error: Database files missing!\n");
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }
    printf("\nEnter Doctor ID to edit from the list above: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
    {
        if(d.id == id)
        {
            found = 1;
            printf("\n--- Editing Doctor ID: %d (%s) ---\n", d.id, d.name);

            printf("Enter new name (Use_Underscores): ");
            while((ch = getchar()) != '\n' && ch != EOF);
            fgets(d.name, sizeof(d.name), stdin);
            d.name[strcspn(d.name, "\n")] = 0;

            selectDepartment(d.department);

            printf("Enter new fee: ");
            scanf("%f", &d.fee);

            printf("Enter new time: ");
            scanf("%s", d.time);
        }
        fprintf(temp, "%d %s %s %.2f %s\n", d.id, d.name, d.department, d.fee, d.time);
    }

    fclose(fp);
    fclose(temp);

    remove("doctor.txt");
    rename("temp.txt", "doctor.txt");

    if(found)
        printf("\n Success: Doctor records updated!\n");
    else
        printf("\n Error: Doctor ID %d not found.\n", id);
}

void deleteDoctor()
{
    doctorList();

    FILE *fp = fopen("doctor.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Doctor d;
    int id, found = 0;

    if(fp == NULL || temp == NULL) {
        printf("Error: Database files missing!\n");
        if(fp) fclose(fp);
        if(temp) fclose(temp);
        return;
    }

    printf("\nEnter Doctor ID to DELETE from the list above: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
    {
        if(d.id != id)
        {
            fprintf(temp, "%d %s %s %.2f %s\n", d.id, d.name, d.department, d.fee, d.time);
        }
        else
        {
            found = 1; // Skips writing to file, effectively deleting them
        }
    }

    fclose(fp);
    fclose(temp);

    remove("doctor.txt");
    rename("temp.txt", "doctor.txt");

    if(found)
        printf("\n🗑️ Success: Doctor removed from the roster!\n");
    else
        printf("\n❌ Error: Doctor ID %d not found.\n", id);
}
/*APPOINTMENT FUNCTIONS*/

void bookAppointment()
{
    struct Patient p;
    struct Doctor d;
    int ch;

    FILE *fp = fopen("appointment.txt", "a");
    FILE *dfp = fopen("doctor.txt", "r");

    if(dfp == NULL)
    {
        printf("Doctor file missing!\n");
        if(fp) fclose(fp);
        return;
    }

    int found = 0;
    p.id = generateAppointmentID();
    printf("Auto Generated Appointment ID: %d\n", p.id);

    printf("Enter Name (Use_Underscores): ");
    while ((ch = getchar()) != '\n' && ch != EOF); // Fixed double getchar bug
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender: ");
    scanf("%s", p.gender);

    int dChoice;
    showDiseases();

    printf("Enter choice: ");
    scanf("%d", &dChoice);
    if(dChoice == 1)      strcpy(p.disease, "Medicine");
    else if(dChoice == 2) strcpy(p.disease, "Skin");
    else if(dChoice == 3) strcpy(p.disease, "Cardiology");
    else if(dChoice == 4) strcpy(p.disease, "Orthopedic");
    else if(dChoice == 5) strcpy(p.disease, "Dental");
    else                  strcpy(p.disease, "Unknown");

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", p.date);

    /* FIND DOCTOR */
    while(fscanf(dfp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
    {
        if(strcmp(p.disease, d.department) == 0)
        {
            strcpy(p.doctor, d.name);
            strcpy(p.time, d.time);
            found = 1;
            break;
        }
    }
    fclose(dfp);

    if(found == 0)
    {
        printf("No doctor found for this disease!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%d %s %d %s %s %s %s %s\n",
            p.id, p.name, p.age, p.gender,
            p.disease, p.doctor, p.date, p.time);

    fclose(fp);

    printf("\nAppointment Booked Successfully!\n");
    printf("Doctor Assigned: %s\n", p.doctor);
    printf("Time: %s\n", p.time);
}

void viewAppointment()
{
    struct Patient p;
    FILE *fp = fopen("appointment.txt", "r");

    if(fp == NULL)
    {
        printf("No appointments found!\n");
        return;
    }

    printf("\n================ APPOINTMENT LIST ================\n");

    while(fscanf(fp, "%d %s %d %s %s %s %s %s",
                 &p.id, p.name, &p.age, p.gender,
                 p.disease, p.doctor, p.date, p.time) != EOF)
    {
        printf("\nID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\nDate: %s\nTime: %s\n",
               p.id, p.name, p.age, p.gender,
               p.disease, p.doctor, p.date, p.time);
    }

    fclose(fp);
}

int generateAppointmentID()
{
    FILE *fp = fopen("appointment.txt", "r");
    struct Patient p;
    int max = 0;

    if(fp == NULL)
        return 1;

    while(fscanf(fp, "%d %s %d %s %s %s %s %s",
                 &p.id, p.name, &p.age, p.gender,
                 p.disease, p.doctor, p.date, p.time) != EOF)
    {
        if(p.id > max)
        {
            max = p.id;
        }
    }

    fclose(fp);
    return max + 1;
}

void cancelAppointment()
{
    struct Patient p;
    FILE *fp = fopen("appointment.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;

    if(fp == NULL)
    {
        printf("No appointment records found!\n");
        if(temp) fclose(temp);
        return;
    }

    printf("Enter Appointment ID to cancel: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %d %s %s %s %s %s",
                 &p.id, p.name, &p.age, p.gender,
                 p.disease, p.doctor, p.date, p.time) != EOF)
    {
        if(p.id == id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d %s %d %s %s %s %s %s\n",
                    p.id, p.name, p.age, p.gender,
                    p.disease, p.doctor, p.date, p.time);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("appointment.txt");
    rename("temp.txt", "appointment.txt");

    if(found == 1)
        printf("Appointment cancelled successfully!\n");
    else
        printf("Appointment ID not found!\n");
}

/* DIAGNOSTIC FUNCTIONS*/

void diagnosticList()
{
    FILE *fp = fopen("diagnostic.txt", "r");
    char test[50];
    int price;

    if(fp == NULL)
    {
        printf("No diagnostic data found!\n");
        return;
    }

    printf("\n------ DIAGNOSTIC FACILITIES ------\n");

    while(fscanf(fp, "%s %d", test, &price) != EOF)
    {
        printf("Test: %s\tPrice: %d Tk\n", test, price);
    }

    fclose(fp);
}

/*BILLING FUNCTIONS*/

void generateBill()
{
    struct Bill b;
    struct Patient p;
    struct Doctor d;

    FILE *fp = fopen("bill.txt", "a");
    FILE *ap = fopen("appointment.txt", "r");

    if(ap == NULL)
    {
        printf("Appointment file not found!\n");
        if(fp) fclose(fp);
        return;
    }

    int apptID, found = 0;

    printf("\nEnter Bill ID: ");
    scanf("%d", &b.billID);

    printf("Enter Appointment ID: ");
    scanf("%d", &apptID);

    while(fscanf(ap, "%d %s %d %s %s %s %s %s",
                 &p.id, p.name, &p.age, p.gender,
                 p.disease, p.doctor, p.date, p.time) != EOF)
    {
        if(p.id == apptID)
        {
            strncpy(b.patientName, p.name, sizeof(b.patientName));
            strncpy(b.doctorName, p.doctor, sizeof(b.doctorName));
            found = 1;
            break;
        }
    }
    fclose(ap);

    if(found == 0)
    {
        printf("Appointment not found!\n");
        fclose(fp);
        return;
    }

    printf("Enter Diagnostic Fee: ");
    scanf("%f", &b.testFee);

    FILE *dfp = fopen("doctor.txt", "r");
    b.doctorFee = 0.0;

    if (dfp != NULL) {
        while(fscanf(dfp, "%d %s %s %f %s", &d.id, d.name, d.department, &d.fee, d.time) != EOF)
        {
            if(strcmp(d.name, p.doctor) == 0)
            {
                b.doctorFee = d.fee;
                break;
            }
        }
        fclose(dfp);
    }

    b.totalFee = b.doctorFee + b.testFee;
    fprintf(fp, "%d %s %s %.2f %.2f %.2f\n",
            b.billID, b.patientName, b.doctorName,
            b.doctorFee, b.testFee, b.totalFee);

    fclose(fp);

    printf("\n====================================\n");
    printf("        BILL GENERATED SUCCESSFULLY\n");
    printf("====================================\n");
    printf("Patient Name : %s\n", b.patientName);
    printf("Doctor Name  : %s\n", b.doctorName);
    printf("Doctor Fee   : %.2f\n", b.doctorFee);
    printf("Test Fee     : %.2f\n", b.testFee);
    printf("Total Fee    : %.2f\n", b.totalFee);
}

void viewBill()
{
    struct Bill b;
    FILE *fp = fopen("bill.txt", "r");

    if(fp == NULL)
    {
        printf("No bills found!\n");
        return;
    }

    printf("\n================ BILL RECEIPT LIST ================\n");

    while(fscanf(fp, "%d %s %s %f %f %f",
                 &b.billID, b.patientName, b.doctorName,
                 &b.doctorFee, &b.testFee, &b.totalFee) != EOF)
    {
        printf("\n----------------------------------\n");
        printf("Bill ID      : %d\n", b.billID);
        printf("Patient Name : %s\n", b.patientName);
        printf("Doctor Name  : %s\n", b.doctorName);
        printf("Doctor Fee   : %.2f\n", b.doctorFee);
        printf("Test Fee     : %.2f\n", b.testFee);
        printf("TOTAL BILL   : %.2f\n", b.totalFee);
    }

    printf("\n==============================================\n");
    fclose(fp);
}

/*ADMIN FUNCTIONS*/

int passwordCheck()
{
    FILE *fp = fopen("admin.txt", "r");
    int pass, input;

    if(fp == NULL)
    {
        printf("Admin file missing! Defaulting access.\n");
        return 1;
    }

    if(fscanf(fp, "%d", &pass) != 1) {
        pass = 1234;
    }
    fclose(fp);

    printf("\nEnter Admin Password: ");
    scanf("%d", &input);

    if(input == pass)
    {
        printf("Login Successful!\n");
        return 1;
    }
    else
    {
        printf("Wrong Password!\n");
        return 0;
    }
}

void adminPanel()
{
    int choice;

    if(passwordCheck() == 0)
    {
        return;
    }

    while(1)
    {
        printf("\n------ ADMIN PANEL ------\n");
        printf("1. Add Doctor\n");
        printf("2. Edit Doctor\n");
        printf("3. Delete Doctor\n");
        printf("4. View Appointments\n");
        printf("5. View Bills\n");
        printf("6. Back\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)      addDoctor();
        else if(choice == 2) editDoctor();
        else if(choice == 3) deleteDoctor();
        else if(choice == 4) viewAppointment();
        else if(choice == 5) viewBill();
        else if(choice == 6) break;
        else                 printf("Invalid choice!\n");
    }
}

#endif
