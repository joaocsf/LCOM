#include <minix/drivers.h>
#include "timer.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv) {

	sef_startup();
	printf("Lab2: Timer.\n");

	if (argc == 1) {
		print_usage(argv);
		return 0;
	} else {
		proc_args(argc, argv);
	}
	return 0;
}

static void print_usage(char *argv[]) {
	printf(
			"Usage: one of the following:\n"
					"\t service run %s -args \"testsquare <decimal number>\" \n"
					"\t service run %s -args \"testconfig <decimal number>\" - to blank screen \n"
					"\t service run %s -args \"testint <decimal number>\" \n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[]) {

	unsigned long freq,time,timer;

	//timer_test_square()
	if (strncmp(argv[1], "testsquare", strlen("testsquare")) == 0) {
		if (argc != 3) {
			printf("timer: wrong no of arguments for test of timer_test_square() \n");
			return 1;
		}
		if ((freq = parse_ulong(argv[2], 10)) == ULONG_MAX)
			return 1;

		printf("timer:: timer_test_square( %d )\n", freq);
		if(timer_test_square(freq)!=0){
			printf("timer::timer_test_square Error!\n");
			return 1;
		}
		return 0;

	//timer_test_config()
	} else if (strncmp(argv[1], "testconfig", strlen("testconfig")) == 0) {
		if (argc != 3) {
			printf("timer: wrong no of arguments for test of timer_test_config() \n");
			return 1;
		}
		if ((timer = parse_ulong(argv[2], 10)) == ULONG_MAX)
			return 1;

		printf("timer:: timer_test_config( %d )\n", timer);
		if(timer_test_config(timer)!=0){
			printf("timer::timer_test_config Error!\n");
			return 1;
		}

		return 0;

	//timer_test_int()
	} else if (strncmp(argv[1], "testint", strlen("testint")) == 0) {
		if (argc != 3) {
			printf("timer: wrong no of arguments for test of timer_test_int() \n");
			return 1;
		}
		if ((time = parse_ulong(argv[2], 10)) == ULONG_MAX)
			return 1;

		printf("timer:: timer_test_int(%lu)\n",(unsigned) time);
		if(timer_test_int(time) != 0){
			printf("timer::timer_test_int Error!\n");
			return 1;
		}
		return 0;
	} else {
		printf("timer: non valid function \"%s\" to test\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtoul(str, &endptr, base);

	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtol");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ulong: no digits were found in %s \n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

static long parse_long(char *str, int base) {
	char *endptr;
	unsigned long val;

	val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return LONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_long: no digits were found in %s \n", str);
		return LONG_MAX;
	}

	/* Successful conversion */
	return val;
}
