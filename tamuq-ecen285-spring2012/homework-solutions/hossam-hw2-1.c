//
//  hossam-hw2-1.c
//  
//
//  Created by Hossam Hammady on 3/8/12.
//  Copyright (c) 2012 Texas A&M University at Qatar. All rights reserved.
//

/* Program to determine if a letter is vowel or consonant. */
#include <stdio.h>

int main(void)
{
    // Declare variables
    char ch;
    
    // input character
    printf("Please enter a letter: ");
    scanf("%c", &ch);
    
    // check letter
    if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
        // character is either small or capital letter, check vowel/consonant
        switch (ch) {
            case 'a': case 'A':
            case 'e': case 'E':
            case 'i': case 'I':
            case 'o': case 'O':
            case 'u': case 'U':
                printf("Letter %c is vowel\n", ch);
                break;
            default:
                printf("Letter %c is consonant\n", ch);
        }
        // we are done, exit normally
        return (0);
    }
    else {
        // print error and indicate that in program exit code
        printf("Error: %c is not a letter\n", ch);
        return (1);
    }
}
