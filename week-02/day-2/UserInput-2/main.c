#include <stdio.h>
#include <string.h>

int main() {
    char buffer[255] = "";   // Buffer variable for user input

    //TODO:
    // Get the user's name with gets
    printf("Input your name: ");
    gets(buffer);

    //TODO:
    // Print it out with puts
    printf("Your name is: ");
    puts(buffer);

    //TODO:
    // Get the user's pet name with getch
    printf("Input your pet's name: ");
    int i = 0;
    do {
        buffer[i] = getch();
        printf("%c", buffer[i]);  //getch needs this to see what is typed
        i++;
    } while ((buffer[i-1] != '\r') && (i < 256));
    //with getchar I need to wait an \n value as enter
    //with getch I need to wait an \r value as enter
    buffer[i - 1] = '\0';  // close the string

    //TODO:
    // Print it out
    printf("\nYour pet's name is: %s", buffer);
    printf("\nLength of your pet's name is: %d", strlen(buffer));

    return 0;
}
