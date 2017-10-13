#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

int josephus_bit(int people);
int josephus(int people);
int next_alive(int group[], int people, int starting_seat);

int main()
{
    int people = 0;

    printf("JOSEPHUS PROBLEM\n\n");
    printf("How many people are in the \"game\": ");
    scanf("%d", &people);

    printf("Number of the winning seat is (step-by-step method): %d\n", josephus(people));
    printf("Number of the winning seat is (bitwise method): %d\n", josephus_bit(people));

    return 0;
}

/*  Bitwise solution of Josephus problem
 *  Return the winner position from 1. If there are more people given that it can handle, return 0;
 */
int josephus_bit(int people)
{
    uint8_t group = 0;              // 1 for alive, 0 for dead person in binary
    uint8_t counter = 0;            // counts the loop

    if (people > sizeof(group) * 8) { // if there are more people than it can be handled, return 0
        return 0;
    } else {
        // set the init value of the group according to the number of the people
        group = pow(2, people) - 1;
printf("\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(group));

        while (group > 1) {             // (The last bit is always 1) While there are more people than 1
            group = (group >> 1) + pow(2, people - 1); // that person remain alive, put it at the beginning bit, according to the number of people
            counter++;
            counter %= people;
//            count(counter, people, group);
printf("\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(group));

            while (group % 2 == 0) {    // find the next alive person (to kill)
                group >>= 1;
                counter++;
                counter %= people;
//                count(counter, people, group);
printf("\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(group));
            }
            group--;                    // then set the last bit to 0 (kill him)
printf("\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(group));
            while (group % 2 == 0) {    // find the next alive person (who can kill somebody)
                group >>= 1;
                counter++;
                counter %= people;
//                count(counter, people, group);
printf("\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(group));
            }
        }
    }
    return ((counter + 1) % 8);
}

/*  Step-by-step solution, gives back the nr. of the winning seat from 1
 *
 */
int josephus(int people)
{
    int group[people];  //1 is alive, 0 is dead
    int seat = 0;
    int n = 0;
    int step = 0;

    for (int i = 0; i < people; i++)
        group[i] = 1;

    do {
        step++;
        seat = n;
        n = next_alive(group, people, seat);
        if (n != seat) {
            group[n] = 0;
            n = next_alive(group, people, seat);
            //n = next_alive(group, people, seat);
        }
        printf("After the %d. step:\t", step);
        for (int i = 0; i < people; i++)
            printf("%d", group[i]);
        printf("\n");
    } while (n != seat);

    return seat + 1;
}

// gives back the next alive person's seat in the array (for josephus() )
int next_alive(int group[], int people, int starting_seat)
{
    int i = starting_seat;
    do {
        if (i == people - 1) {
            i = 0;
        } else {
            i++;
        }
    } while (group[i] == 0 && i != starting_seat);

    return i;
}


