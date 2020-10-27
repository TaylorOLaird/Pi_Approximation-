#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define radius 10000
// center (0,0)
#define PI 3.141592

long timediff(clock_t t1, clock_t t2) {
	long elapsed;
	elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
	return elapsed;
}

float randomNum(int seed) {
	float ret_num, sign;
	srand(time(0) + seed);
	ret_num = rand() % (radius + 1);
	sign = rand() % 2; // 0 -> -num: 1 -> +num
	if (sign == 0)
		ret_num = ret_num * (-1);

	return ret_num;
}

void approx_pi() {
	clock_t start, end;
	long elapsed;
	float circle_count = 0, total = 0, pi, temp_x, temp_y;
	float new_diff = 0, rec_pi = 0, rec_diff = 0;
	int seed = 1;

	start = clock();
	while (1) {
		total ++;
		temp_x = randomNum(seed++);
		temp_y = randomNum(seed++);

		if ((float)radius * (float)radius > temp_x * temp_x + temp_y * temp_y)
			circle_count ++;

		pi = (float)4 *((circle_count)/(total));
		rec_diff = abs(PI * 1000000 - rec_pi * 1000000);
		new_diff = abs(PI * 1000000 - pi * 1000000); // int conversion

		if(new_diff < rec_diff) {
			rec_pi = pi;
			printf("%f\n", rec_pi);
		}
		if (rec_diff == 0) {
			break;
		}
	}

	end = clock();
	elapsed = timediff(start, end);
	printf("It took %d data points and %ld milliseconds to approximate pi to six dicimal places\n", (int)total, elapsed);
}

int main(int argc, char const *argv[]) {
	approx_pi();
	return 0;
}