#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    double height;
};

int main(){

    struct Person person1 = { "John", 25, 1.75 };

    printf("Person1\n");
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %f\n", person1.height);

    printf("Memomry address:\n");
    printf("name; %p\nage: %p\nheigh: %p\n", person1.name, &person1.age, &person1.height);

    char *pName = person1.name;
    int *pAge = &person1.age;
    double *pHeight = &person1.height;

    printf("Pointers memory address:\n");
    printf("name; %p\nage: %p\nheigh: %p\n", pName, pAge, pHeight);

    printf("Deref pointers:\n");
    printf("name; %s\nage: %d\nheigh: %f\n", pName, *pAge, *pHeight);  
}