/* includes and macro definitions */
#include <stdio.h>
#define PI 3.14159265
#define THRESHOLD 0.0001

/* function prototypes */
float power(float base, int exp);
float factorial(int n);
float cosine(int angle_degrees);
float cosine_nonrecursive(float x);
float cosine_series(float x, int n);
void test();

/* a program to calculate the cosine value for an angle recursively using Tailor series
   cos(x) = 1 - (x^2)/(2!) + (x^4)/(4!) - (x^6)/(6!) ... */
int main(void)
{
	/* declare variables */
	int angle;
	float result;

	/* (optional) perform our tests */
	test();

	/* get a single value from user */
	printf("Please enter the whole value for an angle [0..359]: ");
	scanf("%d", &angle);

	/* is the angle out of range? */
	if (angle < 0 || angle > 359)
	{
		/* display an error message and exit with non-zero value */
		printf("You have entered an angle out of my range, bye bye!\n");
		return (1);
	}

	/* calculate the cosine of the angle */
	result = cosine(angle);

	/* display the result */
	printf("The approximate cosine value for angle %d is %8.6f\n", angle, result);

	/* exit gracefully */
	return (0);
}

/* a function to raise a floating-point number to an integer power */
float power(float base, int exp)
{
	if (base == 0)
		return (0);
	else if (exp == 0)
		return (1);
	else
		return (base * power(base, exp - 1));
}

/* a function to calculate the factorial value of a number */
float factorial(int n)
{
	if (n <= 1)
		return (1);
	else
		return (n * factorial(n - 1));
}

/* a function to calculate the cosine value of an angle in degrees */
float cosine(int angle_degrees)
{
	/* declare variables */
	float x, result;

	/* convert angle to radians */
	x = angle_degrees * PI / 180;

	/* compute cosine using the non-recursive version */
	result = cosine_nonrecursive(x);
	
	/* (optional: uncomment to enable) compute cosine again using the recursive version */
	//result = cosine_series(x, 0);
	
	/* return the result */
	return (result);
}

float cosine_nonrecursive(float x)
{
	/* declare variables */
	float result = 0, term;
	int n = 0;
	
	/* do while loop to gradually fix the value of cosine up to predefined accuracy */
	do {
		/* calculate the absolute value for the current term */
		term = power(x, n) / factorial(n);
		
		if ((n / 2) % 2 == 1)
		{
			/* odd term */
			result += term;
			/* notice the shorthand operator += equivalent to result = result + term */
		}
		else {
			/* even term */
			result -= term;
			/* notice the shorthand operator -= equivalent to result = result - term */
		}
		
		/* increment counter by 2 */
		n += 2;
		
	} while (term <= THRESHOLD);
}

float cosine_series(float x, int n)
{
	/* declare variables */
	float term;

	/* calculate the absolute value for the current term */
	term = power(x, n) / factorial(n);

	/* is the term too small? */
	if (term <= THRESHOLD)
	{
		/* yes, ignore its small value and return 0 instead */
		return (0);
	}
	else
	{
		/* no, check if it should be positive (even term) or negative (odd term)
		   we say odd and even based on zero-based numbering of the series terms */
		if ((n / 2) % 2 == 1)
		{
			/* odd term: negate */
			term = -term;
		}

		/* recursively call this function by incrementing the power by 2 and adding the result */
		return (term + cosine_series(x, n + 2));
	}
}

/* (optional) a function that will test our 3 core functions with several inputs */
void test() {
	int i;

	/* test power function */
	printf("Power test:\n");
	printf("==========:\n");
	for(i = 0; i < 5; i++)
		printf("2.0^%d = %f\n", i, power(2.0, i));

	/* test factorial function */
	printf("Factorial test:\n");
	printf("==============:\n");
	for(i = 0; i < 5; i++)
		printf("%d! = %f\n", i, factorial(i));

	/* test cosine function */
	printf("Cosine test:\n");
	printf("===========:\n");
	for(i = 0; i < 9; i++)
		printf("cosine(%d * 45) = %f\n", i, cosine(i * 45));
}
