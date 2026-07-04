#include <stdio.h>

typedef struct s_animal {
    char    *(*speak)(void);  // pointeur vers la fonction "comportement"
    char    *name;
} t_animal;

char *dog_speak(void) { return "Woof"; }
char *cat_speak(void) { return "Meow"; }

t_animal make_dog(void) {
    t_animal a;
    a.speak = dog_speak;
    a.name = "Dog";
    return a;
}

t_animal make_cat(void) {
    t_animal a;
    a.speak = cat_speak;
    a.name = "Cat";
    return a;
}

void make_it_speak(t_animal a) {
    printf("%s\n", a.speak()); // ne sait pas si c'est un chien ou un chat
}

int main(void) {
    make_it_speak(make_dog());
    make_it_speak(make_cat());
}
