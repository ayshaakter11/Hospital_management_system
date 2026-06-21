#ifndef HOSPITAL_H
#define HOSPITAL_H
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char name[50];
    int age;
} patient;

static inline void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static inline int matchKeywords(const char *input, const char *keywords[], int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(input, keywords[i]) != NULL) {
            return 1; 
        }
    }
    return 0;
}
 
static inline void addPatient() {
    FILE *fp = fopen("patients.text", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    patient p;
    printf("enter patient id: ");
    scanf("%d", &p.id);
    printf("enter name: ");
    scanf(" %[^\n]", p.name); 
    printf("Enter Age: ");
    scanf("%d", &p.age);
    fprintf(fp, "%d|%s|%d\n", p.id, p.name, p.age);
    fclose(fp);
    printf("Patient added successfully!\n\n");
}

static inline void viewpatients() {
    FILE *fp = fopen("patients.text", "r");
    if (fp == NULL) {
        printf("\nNo patient records found yet! Add a patient first.\n\n");
        return;
    }
    patient p;
    printf("\n=== PATIENT RECORDS ===\n");
    printf("%-5s %-20s %-5s\n", "ID", "Name", "Age");
    printf("-------------------------------\n");
    while (fscanf(fp, "%d|%49[^|]|%d\n", &p.id, p.name, &p.age) == 3) {
        printf("%-5d %-20s %-5d\n", p.id, p.name, p.age);
    }
    printf("===============================\n\n");
    fclose(fp);
}

// THE NATURAL HUMAN PSYCHOLOGIST INTERFACE
static inline void aiPsychologist() {
    char input[256];
    printf("\n======================================================\n");
    printf("🧠 AI THERAPIST CONSULTATION ROOM\n");
    printf("======================================================\n");
    printf("Hello. Please, take a seat. Tell me what's on your mind today.\n");
    printf("(Type 'exit' whenever you feel ready to stop our session.)\n\n");
    
    while (getchar() != '\n'); 

    const char *anxietyKeys[] = {
        "anxious", "anxiety", "panic", "fear", "scared", "dread", "worry", "worried", "nervous", 
        "shaking", "palpitations", "sweating", "overthinking", "uneasy", "restless", "paranoia", 
        "paranoid", "phobia", "chest tightness", "hyperventilating", "apprehensive", "tense", "jitters"
    };
    int anxietySize = sizeof(anxietyKeys) / sizeof(anxietyKeys[0]);

    const char *depressionKeys[] = {
        "sad", "depressed", "depression", "lonely", "alone", "empty", "hopeless", "worthless", 
        "crying", "miserable", "unhappy", "grief", "grieving", "mourning", "numb", "darkness", 
        "isolated", "isolation", "despair", "gloomy", "heavy hearted", "pessimistic"
    };
    int depressionSize = sizeof(depressionKeys) / sizeof(depressionKeys[0]);

    const char *burnoutKeys[] = {
        "burnout", "burnt out", "tired", "exhausted", "fatigue", "sleepy", "no energy", "drained", 
        "overworked", "stress", "stressed", "pressure", "overwhelmed", "deadline", "exam", "exams", 
        "study", "coding", "workload", "cannot cope", "heavy load", "burdened", "stuck", "procrastinating"
    };
    int burnoutSize = sizeof(burnoutKeys) / sizeof(burnoutKeys[0]);

    const char *traumaKeys[] = {
        "trauma", "ptsd", "flashback", "nightmare", "abuse", "abusive", "toxic", "hurt", "broken", 
        "betrayed", "betrayal", "divorce", "breakup", "rejected", "rejection", "abandoned", "guilt", 
        "ashamed", "regret", "haunted", "past", "childhood", "scars", "harassment", "bullying"
    };
    int traumaSize = sizeof(traumaKeys) / sizeof(traumaKeys[0]);

    const char *angerKeys[] = {
        "angry", "anger", "furious", "mad", "rage", "irritated", "annoyed", "frustrated", "frustration", 
        "bitter", "resentful", "hate", "hating", "jealous", "envy", "agitated", "snapping", "lost temper"
    };
    int angerSize = sizeof(angerKeys) / sizeof(angerKeys[0]);

    while(1) {
        printf("\nYou: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        input[strcspn(input, "\n")] = 0; 
        toLowerCase(input);              

        if (strcmp(input, "exit") == 0) {
            printf("\nTherapist: Thank you for opening up to me today. Take care of yourself until our next session.\n\n");
            break;
        }

        // Direct, human responses without technical data dumps
        if (matchKeywords(input, anxietyKeys, anxietySize)) {
            printf("\nTherapist: It sounds like your mind is racing and trying to protect you from everything at once.\n");
            printf("When panic sets in, your body forgets it is safe. Let's pause together right now.\n");
            printf("Look around the room and focus on the physical objects around you. Take a slow, deep breath.\n");
        } 
        else if (matchKeywords(input, depressionKeys, depressionSize)) {
            printf("\nTherapist: I hear how heavy things feel for you right now, and it's okay to not be okay.\n");
            printf("Depression has a way of making us want to isolate, but please remember you don't have to carry this completely alone.\n");
            printf("Try to do just one small thing for yourself today, even if it's just opening a window for some fresh air.\n");
        } 
        else if (matchKeywords(input, burnoutKeys, burnoutSize)) {
            printf("\nTherapist: You are pushing yourself incredibly hard, and it makes complete sense that you feel drained.\n");
            printf("Burnout happens when we forget that our energy is finite. You cannot pour from an empty cup.\n");
            printf("Give yourself permission to stop working for the rest of today. The work can wait; your health cannot.\n");
        } 
        else if (matchKeywords(input, traumaKeys, traumaSize)) {
            printf("\nTherapist: That sounds deeply painful, and I am so sorry you have had to carry that weight.\n");
            printf("The past can leave deep echoes that make the present moment feel unsafe or fragile.\n");
            printf("Please be gentle with yourself. Healing isn't a race, and honoring your feelings is the first step.\n");
        } 
        else if (matchKeywords(input, angerKeys, angerSize)) {
            printf("\nTherapist: I can feel the intense frustration in what you're dealing with. It's completely valid to feel angry.\n");
            printf("Often, anger is just a shield protecting a part of us that is actually feeling hurt, exhausted, or unfair treatment.\n");
            printf("Take a step back from the situation for a few minutes. Let the immediate physical rush pass before you react.\n");
        } 
        else {
            printf("\nTherapist: I see. Tell me more about that. How long have you been carrying these feelings?\n");
        }
    }
}

#endif
