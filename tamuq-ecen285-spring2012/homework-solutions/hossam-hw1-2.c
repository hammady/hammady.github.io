//
//  hossam-hw1-2.c
//  
//
//  Created by Hossam Hammady on 3/8/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* Program to calculate the surface area of a cylinder. */
#include <stdio.h>
#define PI 3.1416

int main(void) {
	
    // Declare radius and area variables
    float r, h, area;
	
    // Initialize radius and height
    r = 5.0;
    h = 10.0;
	
    // Compute surface area
    area = 2 * PI * r * h;
	
    // Print result
    printf("Radius = %5.2f\nHeight = %5.2f\nSurface Area = %5.2f\n", r, h, area);
    
    // Exit program normally
    return(0);
    
}