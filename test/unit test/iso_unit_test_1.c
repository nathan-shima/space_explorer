#include <stdio.h>

int difficulty_tweak(void) {
    int difficulty;
    do {
        printf("please enter the difficulty (easy = 1, medium = 2, hard = 3) : ");
        scanf("%d", &difficulty);
    } while (difficulty < 1 || difficulty > 3);

    printf("difficulty = %d\n", difficulty);
    return difficulty;
}
void main(void) {
    difficulty_tweak();
    difficulty_tweak();
    difficulty_tweak();
}