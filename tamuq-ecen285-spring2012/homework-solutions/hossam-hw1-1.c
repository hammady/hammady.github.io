//
//  hossam-hw1-1.c
//  
//
//  Created by Hossam Hammady on 3/8/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* Program to calculate the average of 5 exam grades. */
#include <stdio.h>

int main(void) {
    
    // Declare variables
    int g1, g2, g3, g4, g5;
    float average;
    
    // Initialize grades
    g1 = 65, g2 = 90, g3 = 99, g4 = 70, g5 = 80;
    
    // Compute average
    average = (float) (g1 + g2 + g3 + g4 + g5) / 5;
    
    // Print result
    printf("Average = %5.2f\n", average);
	
    // Exit program normally
    return(0);
    
}