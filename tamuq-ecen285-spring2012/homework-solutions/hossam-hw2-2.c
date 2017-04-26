//
//  hossam-hw2-2.c
//  
//
//  Created by Hossam Hammady on 3/8/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* Program to compute the day of week for given date. */
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Delcare variables
    int k, m, y;    // input variables
    int M, Y, C;    // calculated variables
    float x;        // temporary variable
    int w;          // desired day of week
    
    // Get & validate user input
    
    // get day
    printf("Please enter day of month (1..31): ");
    scanf("%d", &k);
    if (k < 1 || k > 31) {
        printf("Error: invalid day\n");
        return (1);
    }

    // get month
    printf("Please enter month (1..12): ");
    scanf("%d", &m);
    if (m < 1 || m > 12) {
        printf("Error: invalid month\n");
        return (1);
    }

    // get year
    printf("Please enter year (zero or positive): ");
    scanf("%d", &y);
    if (y < 0) {
        printf("Error: invalid year\n");
        return (1);
    }
    
    // inputs ready, lets calcualte other variables
    if (m >= 3) {
        M = m - 2;
        Y = y % 100;    // remainder of division is always integer
        C = y / 100;    // both operands are integers so it is integer division
    }
    else {
        M = m + 10;
        Y = (y - 1) % 100; // remainder of division is always integer
        C = (y - 1) / 100; // both operands are integers so it is integer division
    }
    
    // ready to calculate day of week w
    x = k + floor(2.6 * M - 0.2) - 2 * C + Y + Y / 4 + C / 4;
    // note that floor is emulated by dividing 2 integers resulting in integer
    // floor returns float, so x is the sum of some integers and a float
    // this sum will result in a floating point number
    w = (int) x % 7;
    // we do typecasting to convert x to integer then take the remainder by 7
    if (w < 0) w += 7;
    // previous line is needed if w is negative, should add 7 to make it positive
    // that was not stated in the assignment, but found on Wikipedia
    // http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gaussian_algorithm
    
    // Print the result properly
    
    // print month name (there is a better way using arrays, but that's not covered yet)
    switch (m) {
        case 1:
            printf("January");
            break;
        case 2:
            printf("February");
            break;
        case 3:
            printf("March");
            break;
        case 4:
            printf("April");
            break;
        case 5:
            printf("May");
            break;
        case 6:
            printf("June");
            break;
        case 7:
            printf("July");
            break;
        case 8:
            printf("August");
            break;
        case 9:
            printf("September");
            break;
        case 10:
            printf("October");
            break;
        case 11:
            printf("November");
            break;
        case 12:
            printf("December");
            break;
    }
    
    // print day of month, year, some text
    printf(" %d, %d is a ", k, y);
    
    // print day name (there is a better way using arrays, but that's not covered yet)
    switch (w) {
        case 0:
            printf("Sunday");
            break;
        case 1:
            printf("Monday");
            break;
        case 2:
            printf("Tuesday");
            break;
        case 3:
            printf("Wednesday");
            break;
        case 4:
            printf("Thursday");
            break;
        case 5:
            printf("Friday");
            break;
        case 6:
            printf("Saturday");
            break;
        default:
            printf("[something went wrong]");
    }

    // the final dot and new line
    printf(".\n");
    
    // exit normally
    return (0);
    
}
