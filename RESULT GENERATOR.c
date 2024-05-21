#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_STUDENTS 50

void Cover();
void Input();
void First();
void readData(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students);
void saveData(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], int Students);
void displayAllResults(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int Students);
void displayMeritList(int ID[], float CGPA[], int Students);
void displayGradeDistribution(float CGPA[], int Students);
void editStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int Students);
void deleteStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students);
void insertStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students);

int main() {
    Cover();
    First();
    return 0;
}

void Cover() {
    printf("            *********************************************************************\n");
    printf("            *********************************************************************\n");
    printf("            *****                                                           *****\n");
    printf("            ****                    RESULT  GENERATOR                        ****\n");
    printf("            *****                                                           *****\n");
    printf("            *********************************************************************\n");
    printf("            *********************************************************************\n\n\n\n\n\n");
}

void Input() {
    printf("            $$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Main Menu $$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("            Enter all students result --------------------------------- input [1]\n");
    printf("            See all student result ------------------------------------ input [2]\n");
    printf("            See student merit  list ----------------------------------- input [3]\n");
    printf("            See how many student got which grade ---------------------- input [4]\n");
    printf("            Edit a student record ------------------------------------- input [5]\n");
    printf("            Delete a student record ----------------------------------- input [6]\n");
    printf("            Insert a new student record ------------------------------- input [7]\n");
    printf("            Exit this loop -------------------------------------------- input [0]\n");
    printf("                                      Enter Input :");
}

void readData(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students) {
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("                                      ---------------------\n");
        printf("                                      | Error opening file! |\n");
        printf("                                      ---------------------\n");
        return;
    }
    else
    {
        printf("                                      ---------------------\n");
        printf("                                      | Student data open |\n");
        printf("                                      ---------------------\n");

    }


    int i = 0;
    while (fscanf(file, "%d %f %f %f %f %f %f", &ID[i], &MAT[i], &CSE[i], &CSE1[i], &PHY[i], &PHY1[i], &ENG[i]) != EOF) {
        float GMAT = 3 * MAT[i];
        float GCSE = 3 * CSE[i];
        float GCSE1 = 1 * CSE1[i];
        float GPHY = 3 * PHY[i];
        float GPHY1 = 1 * PHY1[i];
        float GENG = 1 * ENG[i];
        float Total = GMAT + GCSE + GCSE1 + GPHY + GPHY1 + GENG;
        CGPA[i] = Total / 12;
        i++;
    }

    *Students = i;
    fclose(file);
}

void saveData(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], int Students) {
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("                                      ---------------------\n");
        printf("                                      | Error opening file! |\n");
        printf("                                      ---------------------\n");
        return;
    }

    for (int i = 0; i < Students; i++) {
        fprintf(file, "%d %.2f %.2f %.2f %.2f %.2f %.2f\n", ID[i], MAT[i], CSE[i], CSE1[i], PHY[i], PHY1[i], ENG[i]);
    }

    fclose(file);
        printf("                                      ---------------------\n");
        printf("                                      | File Update Done ! |\n");
        printf("                                      ---------------------\n");
}

void displayAllResults(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int Students) {
    printf("    |-------------------------------------------------------------------------------------------|\n");
    printf("    |Student ID     MAT121      CSE122      CSE123      PHY123      PHY124      ENG123      CGPA|\n");
    for (int i = 0; i < Students; i++) {
        printf("    |212-15-%d    %.2f         %.2f        %.2f        %.2f       %.2f         %.2f       %.2f|\n", ID[i], MAT[i], CSE[i], CSE1[i], PHY[i], PHY1[i], ENG[i], CGPA[i]);
    }
    printf("    |-------------------------------------------------------------------------------------------|\n");

    printf("\n                                   Click enter to see the main menu");
    getch();
    system("cls");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void swapFloat(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}


int partition(int ID[], float CGPA[], int low, int high) {
    float pivot = CGPA[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        if (CGPA[j] >= pivot) {
            i++;
            swap(&ID[i], &ID[j]);
            swapFloat(&CGPA[i], &CGPA[j]);
        }
    }
    swap(&ID[i + 1], &ID[high]);
    swapFloat(&CGPA[i + 1], &CGPA[high]);
    return (i + 1);
}


void quickSort(int ID[], float CGPA[], int low, int high) {
    if (low < high) {

        int pi = partition(ID, CGPA, low, high);

        quickSort(ID, CGPA, low, pi - 1);
        quickSort(ID, CGPA, pi + 1, high);
    }
}

void displayMeritList(int ID[], float CGPA[], int Students) {
    quickSort(ID, CGPA, 0, Students - 1);

    printf("            Student ID                      CGPA\n");
    printf("        ------------------            ---------------\n");

    for (int i = 0; i < Students; ++i) {
        printf("            212-15-%d                      %.2f\n", ID[i], CGPA[i]);
    }
    printf("\n                                   Click enter to see the main menu");
    getch();
    system("cls");
}

void displayGradeDistribution(float CGPA[], int Students) {
    int A0 = 0, A = 0, A1 = 0, B0 = 0, B = 0, B1 = 0, C0 = 0, C = 0, D = 0, F = 0;

    for (int i = 0; i < Students; i++) {
        if (CGPA[i] == 4)
            A0++;
        else if (CGPA[i] >= 3.75)
            A++;
        else if (CGPA[i] >= 3.50)
            A1++;
        else if (CGPA[i] >= 3.25)
            B0++;
        else if (CGPA[i] >= 3.00)
            B++;
        else if (CGPA[i] >= 2.75)
            B1++;
        else if (CGPA[i] >= 2.50)
            C0++;
        else if (CGPA[i] >= 2.25)
            C++;
        else if (CGPA[i] >= 2.00)
            D++;
        else
            F++;
    }

    printf("                        Let's see how many students got how much CGPA\n");
    printf("                        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("                        |  %d Students got A+   | Their CGPA 4.00|\n", A0);
    printf("                        |  %d Students got A    | Their CGPA 3.75|\n", A);
    printf("                        |  %d Students got A-   | Their CGPA 3.50|\n", A1);
    printf("                        |  %d Students got B+   | Their CGPA 3.25|\n", B0);
    printf("                        |  %d Students got B    | Their CGPA 3.00|\n", B);
    printf("                        |  %d Students got B-   | Their CGPA 2.75|\n", B1);
    printf("                        |  %d Students got C+   | Their CGPA 2.50|\n", C0);
    printf("                        |  %d Students got C    | Their CGPA 2.25|\n", C);
    printf("                        |  %d Students got D    | Their CGPA 2.00|\n", D);
    printf("                        |  %d Students got F    | Their CGPA 0.00|\n", F);
    printf("                        |-----------------------------------------|\n");

    printf("\n                                   Click enter to see the main menu");
    getch();
    system("cls");
}

void editStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int Students) {
    int studentID, index = -1;
    printf("Enter the student ID to edit: ");
    scanf("%d", &studentID);

    for (int i = 0; i < Students; i++) {
        if (ID[i] == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Student ID not found.\n");
        return;
    }

    printf("Enter new marks for MAT, CSE, CSE1, PHY, PHY1, ENG: ");
    scanf("%f %f %f %f %f %f", &MAT[index], &CSE[index], &CSE1[index], &PHY[index], &PHY1[index], &ENG[index]);

    float GMAT = 3 * MAT[index];
    float GCSE = 3 * CSE[index];
    float GCSE1 = 1 * CSE1[index];
    float GPHY = 3 * PHY[index];
    float GPHY1 = 1 * PHY1[index];
    float GENG = 1 * ENG[index];
    float Total = GMAT + GCSE + GCSE1 + GPHY + GPHY1 + GENG;
    CGPA[index] = Total / 12;

    saveData(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, Students);
    printf("Student record updated successfully.\n");
}

void deleteStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students) {
    int studentID, index = -1;
    printf("Enter the student ID to delete: ");
    scanf("%d", &studentID);

    for (int i = 0; i < *Students; i++) {
        if (ID[i] == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("                                      ---------------------\n");
        printf("                                      | Student Not Found! |\n");
        printf("                                      ---------------------\n");
        return;
    }

    for (int i = index; i < *Students - 1; i++) {
        ID[i] = ID[i + 1];
        MAT[i] = MAT[i + 1];
        CSE[i] = CSE[i + 1];
        CSE1[i] = CSE1[i + 1];
        PHY[i] = PHY[i + 1];
        PHY1[i] = PHY1[i + 1];
        ENG[i] = ENG[i + 1];
        CGPA[i] = CGPA[i + 1];
    }

    (*Students)--;
    saveData(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, *Students);
        printf("                             ---------------------------------------\n");
        printf("                             | Student record deleted successfully |\n");
        printf("                             ---------------------------------------\n");
}

void insertStudent(int ID[], float MAT[], float CSE[], float CSE1[], float PHY[], float PHY1[], float ENG[], float CGPA[], int *Students) {
    if (*Students >= MAX_STUDENTS) {
        printf("     ------------------------------------------------------------------\n");
        printf("     | Cannot insert new student. Maximum number of students reached. |\n");
        printf("     ------------------------------------------------------------------\n");
        return;
    }

    int index = *Students;
    printf("first Enter student id then marks for MAT, CSE, CSE1, PHY, PHY1, ENG: ");
    scanf("%d %f %f %f %f %f %f", &ID[index], &MAT[index], &CSE[index], &CSE1[index], &PHY[index], &PHY1[index], &ENG[index]);

    float GMAT = 3 * MAT[index];
    float GCSE = 3 * CSE[index];
    float GCSE1 = 1 * CSE1[index];
    float GPHY = 3 * PHY[index];
    float GPHY1 = 1 * PHY1[index];
    float GENG = 1 * ENG[index];
    float Total = GMAT + GCSE + GCSE1 + GPHY + GPHY1 + GENG;
    CGPA[index] = Total / 12;
    (*Students)++;
    saveData(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, *Students);

        printf("     ------------------------------------------------------------------\n");
        printf("     |  New student record inserted successfully with ID: 212-15-%d   |\n", ID[index]);
        printf("     ------------------------------------------------------------------\n");
}

void First() {
    int input, ID[MAX_STUDENTS], Students = 0;
    float MAT[MAX_STUDENTS], CSE[MAX_STUDENTS], CSE1[MAX_STUDENTS], PHY[MAX_STUDENTS], PHY1[MAX_STUDENTS], ENG[MAX_STUDENTS], CGPA[MAX_STUDENTS];

    readData(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, &Students);

    while (1) {
        Input();
        scanf("%d", &input);
        system("cls");

        switch (input) {
            case 1:
                readData(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, &Students);
                break;
            case 2:
                displayAllResults(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, Students);
                break;
            case 3:
                displayMeritList(ID, CGPA, Students);
                break;
            case 4:
                displayGradeDistribution(CGPA, Students);
                break;
            case 5:
                editStudent(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, Students);
                break;
            case 6:
                deleteStudent(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, &Students);
                break;
            case 7:
                insertStudent(ID, MAT, CSE, CSE1, PHY, PHY1, ENG, CGPA, &Students);
                break;
            case 0:
                return;
            default:
                printf("Invalid input. Please try again.\n");
                printf("                            -----------------------------------\n");
                printf("                            | Invalid input. Please try again |\n");
                printf("                            -----------------------------------\n");
                break;
        }
    }
}
