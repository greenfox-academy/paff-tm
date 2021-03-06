#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
int num_of_elements (int array[]);
void print_array (int array[]);
*/

int main()
{
    int nr_of_items = 0;
    do {
        printf("Please add the highest number to check if it is a prime (min 2): ");
        scanf("%d", &nr_of_items);
        nr_of_items -= 1;
    } while (nr_of_items < 1);

    uint8_t is_prime[nr_of_items]; // 1 if the n + 2 is prime, 0 if not prime

    //fill is_prime with 1s
    for (int i = 0; i < nr_of_items; i++)
        is_prime[i] = 1;

    for (int i = 0; i < nr_of_items; i++) {
        for (int j = i + (i + 2); j < nr_of_items; j = j + (i + 2)){
            is_prime[j] = 0;
        }
    }

    //print the prime numbers
    for (int i = 0; i < nr_of_items; i++) {
        if (is_prime[i] == 1) {
            printf("%d\t", i + 2);
        }
    }

    return 0;
}

/*
int num_of_elements (int array[])
{
    return (sizeof(array) / sizeof(array[0]));
}
void print_array (int array[])
{
    printf("%d ", sizeof(array));
    printf("%d ", sizeof(array[0]));
    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
        printf("%d ", array[i]);
}
*/
