#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define INPUT_FILENAME "angles.txt"
#define OUTPUT_FILENAME "trig.txt"

/* function prototypes */
int normailze_angle(int angle);

/* A program to compute trigonometric functions for angles read from a file */
int main(void)
{
	/* Declare variables */
	FILE *file_in, *file_out;
	int angle;
	float radians;
	float s, c, t;
	int angle_count, read_items;

	/* Open input file for reading */
	file_in = fopen(INPUT_FILENAME, "r");
	if (!file_in)
	{
		/* Error while opening file:
		   Display an error and exit with a non-zero value */
		printf("Error reading input file. Aborting\n");
		return (1);
	}
	
	/* Open output file for writing */
	file_out = fopen(OUTPUT_FILENAME, "w");
	if (!file_out)
	{
		/* Error while opening file:
		   Display an error and exit with a non-zero value */
		printf("Error opening output file for writing. Aborting\n");

		/* cleanup */
		fclose(file_in);
		return (1);
	}

	/* Read angle values from input file */
	angle_count = 0;
	while (!feof(file_in))
	{
		/* read next angle */
		read_items = fscanf(file_in, "%d", &angle);

		if (read_items > 0)
		{
			/* increment angle_count */
			angle_count++;

			/* process angle */
			angle = normailze_angle(angle);
			radians = angle * PI / 180;
			s = sin(radians);
			c = cos(radians);
			t = s / c;
			fprintf(file_out, "%d, %6.4f, %6.4f, %6.4f\n", angle, s, c, t);
		}
	}

	/* Detect if the file was empty */
	if (angle_count == 0)
	{
		/* Display a warning message */
		printf("Warning: input file is empty\n");
	}

	/* Close files and exit gracefully */
	fclose(file_in);
	fclose(file_out);
	return (0);
}

/* a function that will normalize an angle by confining it to the range 0..359 */
int normailze_angle(int angle)
{
	/* declare and initialize normalized angle to original angle */
	int normalized = angle;

	/* keep on subtracting 360 until it is below 360 */
	while (normalized >= 360)
		normalized -= 360;

	/* keep on adding 360 until it is non-negative */
	while (normalized < 0)
		normalized += 360;

	return (normalized);
}
