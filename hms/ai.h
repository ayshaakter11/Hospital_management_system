#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================
 U TI*LITY METHODS
 =================================================== */

static inline void toLowerCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static inline int matchKeywords(const char *input, const char *keywords[], int size)
{
    for (int i = 0; i < size; i++) {
        if (strstr(input, keywords[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

static inline void clearBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/* ===================================================
 M AI*N FEAT: ADVANCED CONVERSATIONAL THERAPIST
 =================================================== */

static inline void aiPsychologist()
{
    char input[256];
    srand(time(NULL));

    // Dynamic Time-of-Day Greeting
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);
    const char *greeting = "Hello";
    if (timeinfo != NULL) {
        if (timeinfo->tm_hour < 12) greeting = "Good morning";
        else if (timeinfo->tm_hour < 17) greeting = "Good afternoon";
        else greeting = "Good evening";
    }

    printf("\n====================================================================\n");
    printf("                  🧠 AI THERAPIST CONSULTATION ROOM\n");
    printf("====================================================================\n");
    printf("  Disclaimer: This interface provides simulated emotional support.\n");
    printf("  It is NOT a replacement for qualified mental health treatment.\n");
    printf("====================================================================\n\n");

    printf("Therapist: %s. Please, take a seat. What's occupying your thoughts?\n", greeting);
    printf("(Type 'exit' or 'bye' when you are finished with our session.)\n");

    clearBuffer();

    /* ================= SYSTEM KEYWORDS ================= */
    const char *helloKeys[] = {"hello", "hi", "hey", "good morning", "good evening", "greetings"};
    int helloSize = sizeof(helloKeys) / sizeof(helloKeys[0]);

    const char *thanksKeys[] = {"thanks", "thank you", "appreciate it"};
    int thanksSize = sizeof(thanksKeys) / sizeof(thanksKeys[0]);

    const char *anxietyKeys[] = {"anxious", "anxiety", "panic", "fear", "scared", "worry", "nervous", "overthinking", "restless", "paranoia"};
    int anxietySize = sizeof(anxietyKeys) / sizeof(anxietyKeys[0]);

    const char *depressionKeys[] = {"sad", "depressed", "lonely", "hopeless", "worthless", "empty", "crying", "miserable", "grief", "numb"};
    int depressionSize = sizeof(depressionKeys) / sizeof(depressionKeys[0]);

    const char *burnoutKeys[] = {"tired", "exhausted", "burnout", "stress", "overworked", "pressure", "exam", "workload", "drained", "stuck"};
    int burnoutSize = sizeof(burnoutKeys) / sizeof(burnoutKeys[0]);

    const char *suicideKeys[] = {"suicide", "kill myself", "end my life", "self harm", "die", "want to sleep and never wake up"};
    int suicideSize = sizeof(suicideKeys) / sizeof(suicideKeys[0]);

    const char *exitKeys[] = {"exit", "bye", "goodbye", "see ya", "quit"};
    int exitSize = sizeof(exitKeys) / sizeof(exitKeys[0]);

    const char *medicalKeys[] = {"fever", "cough", "pain", "cancer", "sick", "doctor", "headache", "stomach", "bleed", "injury", "hurt physical"};
    int medicalSize = sizeof(medicalKeys) / sizeof(medicalKeys[0]);

    const char *questionKeys[] = {"what", "how", "why", "help", "advice", "do next", "should i"};
    int questionSize = sizeof(questionKeys) / sizeof(questionKeys[0]);

    /* ================= RESPONSE MATRICES ================= */

    while (1)
    {
        printf("\nYou: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = 0;
        toLowerCase(input);

        // 1. Blank entry check must happen first
        if (strlen(input) == 0 || strcmp(input, " ") == 0) {
            printf("\nTherapist: I'm right here whenever you are ready to speak.\n");
            continue;
        }

        // 2. SEAMLESS EXIT DECORATION
        if (matchKeywords(input, exitKeys, exitSize))
        {
            printf("\nTherapist: Thank you for allowing me into your mental space today.\n");
            printf("Please be gentle with yourself. Take care until our next session.\n\n");
            break;
        }

        // 3. EMERGENCY REDIRECT TRIGGER
        if (matchKeywords(input, suicideKeys, suicideSize))
        {
            printf("\nTherapist: I'm concerned about your safety.\nYou deserve support, and talking with a trusted person or emergency service right now could make a big difference.\n");
            printf("Your life matters immensely. Please immediately call an emergency helpline or talk to a real professional.\n");
            printf("You do not have to carry this crushing weight alone.\n");
            continue;
        }

        // 4. PHYSICAL MEDICAL SYMPTOM DETECTOR
        if (matchKeywords(input, medicalKeys, medicalSize))
        {
            printf("\nTherapist: It sounds like you are experiencing a physical medical issue or ailment.\n");
            printf("While I can support your emotional state, please use our main menu to 'Book an Appointment'\n");
            printf("with one of our specialized doctors right away to address this properly.\n");
            continue;
        }

        // 5. CONVERSATIONAL INTERACTIONS (GREETINGS/THANKS)
        if (matchKeywords(input, helloKeys, helloSize))
        {
            printf("\nTherapist: Hello. I'm glad you stopped by. How are you feeling today?\n");
        }
        else if (matchKeywords(input, thanksKeys, thanksSize))
        {
            printf("\nTherapist: You're welcome. I'm always here to listen.\n");
        }

        // 6. EMOTIONAL PROFILE COMPREHENSION
        else if (matchKeywords(input, anxietyKeys, anxietySize))
        {
            printf("\nTherapist: It sounds like your thoughts are running fast, trying to shield you from everything at once.\n");
            printf("When an anxious storm hits, the body forgets it's safe. Let's ground ourselves.\n");
            printf("Can you focus on one physical object in your room right now and describe it to me?\n");
        }
        else if (matchKeywords(input, depressionKeys, depressionSize))
        {
            printf("\nTherapist: I can hear a profound heavy-heartedness in your message. It is completely okay to not feel okay.\n");
            printf("Sadness has a way of convincing us to isolate ourselves. Is there a trusted person you feel safe reaching out to today?\n");
        }
        else if (matchKeywords(input, burnoutKeys, burnoutSize))
        {
            printf("\nTherapist: You are pouring from an completely empty cup. Pushing past your energy reserves causes deep exhaustion.\n");
            printf("You have structural permission to pause today. What is one small demand you can safely pull off your schedule right now?\n");
        }

        // 7. TARGETED FALLBACKS
        else if (matchKeywords(input, questionKeys, questionSize))
        {
            const char *questionReplies[] = {
                "That's a meaningful question. Finding the next step usually starts with identifying exactly what feels overwhelming right now. Can you tell me what's on your mind?",
                "I'm here to help you unpack that. Where do you feel like you want to start?",
                "Figuring out what to do can feel dizzying. Let's take a step back—what's happening around you right now?",
                "We can figure that out together. Tell me a bit more about the situation you are facing."
            };
            printf("\nTherapist: %s\n", questionReplies[rand() % 4]);
        }
        else
        {
            const char *vagueReplies[] = {
                "I hear you. Tell me more about what's on your mind.",
                "I'm paying close attention. Please go on.",
                "I understand. What else are you experiencing right now?",
                "Thank you for sharing that. Let's explore that a bit deeper if you're comfortable."
            };
            printf("\nTherapist: %s\n", vagueReplies[rand() % 4]);
        }
    }
}

#endif
