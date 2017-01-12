#include <stdio.h>
#include <math.h>

int add_together(int x, int y) {
	int result = x + y;
	return result;
}

typedef struct {
	float x;
	float y;
} point;

int main(int argc, char** argv) {
	int added = add_together(10, 18);

	point p;
	p.x = 0.1;
	p.y = 10.0;

	float length = sqrt(p.x * p.x + p.y * p.y);

	int x = 0;
	if (x > 10 && x < 100) {
		puts("x is greater than 10 and less than 100!");
	}
	else {
		puts("x is less than 11 or greater than 99!");
	}

	int i = 10;
	while (i > 0)
	{	
		puts("Look Iteration");
		i = i - 1;
	}

	for (int i = 0; i < 10; i++) {
		puts("Loop Iteration");
	}


	return 0;
}

