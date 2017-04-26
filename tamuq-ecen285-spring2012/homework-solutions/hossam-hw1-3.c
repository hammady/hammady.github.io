//
//  hossam-hw1-3.c
//  
//
//  Created by Hossam Hammady on 3/8/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* Program to calculate values of acute angles in right-angled triangle. */
#include <stdio.h>
#include <math.h>

int main(void) {
    
    // Declare variables
    float b, h, alpha_r, alpha_d, beta_d;
    
    // Initialize base and height
    b = 10; h = 20;
    
    // Compute alpha & beta
    alpha_r = atan(b / h);   // get the arc tan
    alpha_d = alpha_r * 180 / M_PI; // M_PI is defined in math.h
    beta_d = 90 - alpha_d;
    
    // Print result
    printf("alpha = %5.2f\nbeta = %5.2f\n", alpha_d, beta_d);

    // Exit program normally
    return(0);
    
}