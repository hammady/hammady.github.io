#include <stdio.h>

#define INPUT_FILENAME "trig.txt"

/* A program to classify angle quadrants read from a file */
int main(void)
{
	/* Declare variables */
	FILE *file_in;
	int angle, read_items;
	int q1, q2, q3, q4, total;
	float dummy;

	/* Open input file for reading */
	file_in = fopen(INPUT_FILENAME, "r");
	if (!file_in)
	{
		/* Error while opening file:
		   Display an error and exit with a non-zero value */
		printf("Error reading input file. Aborting\n");
		return (1);
	}
	
	/* Read angle values from input file */
	q1 = q2 = q3 = q4 = 0;
	while (!feof(file_in))
	{
		/* read next angle and skip the next 3 float values */
		read_items = fscanf(file_in, "%d, %f, %f, %f", &angle, &dummy, &dummy, &dummy);

		if (read_items > 0)
		{
			/* process angle assuming the input file is correct (angles in range 0..359) */
			if (angle >= 0 && angle < 90)
			{
				q1++;
			}
			else if (angle >= 90 && angle < 180)
			{
				q2++;
			}
			else if (angle >= 180 && angle < 270)
			{
				q3++;
			}
			else
			{
				q4++;
			}
		}
	}

	/* Calculate total by adding all quadrant angles */
	total = q1 + q2 + q3 + q4;

	/* Detect if the file was empty */
	if (total == 0)
	{
		/* Display a warning message */
		printf("Warning: input file is empty\n");
	}
	else
	{
		/* Display results */
		printf("Total number of angles: %d\n", total);
		printf("Angles between 0 and 89 degrees: %d\n", q1);
		printf("Angles between 90 and 179 degrees: %d\n", q2);
		printf("Angles between 180 and 269 degrees: %d\n", q3);
		printf("Angles between 270 and 359 degrees: %d\n", q4);
	}

	/* Close file and exit gracefully */
	fclose(file_in);
	return (0);
}
