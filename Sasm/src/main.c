#include "sat.h"

int main(int argc, char **argv)
{
	char buf[256], line[256];
	char add_mem[MEMORYSIZE];
	FILE *input, *output;
	int value, addr, line_cnt = 1;
	int err;
	int flag_err = 0;
	
	if (argc != 3) {
		perror("Incorrect arguments!\n");
		exit(1);
	}
	if (test_argv(argv) != 0) {
		perror("Incorrect arguments!\n");
		exit(1);
	}
	if ((output = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "Cannot open file:%s", argv[1]);
		exit(1);
	}
	if ((input = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "Cannot open file:%s", argv[2]);
		exit(1);
	}
	
	memset(add_mem, 0, MEMORYSIZE);
	memset(MemoryArray, 0, MEMORYSIZE * sizeof(int));
	while (fgets(line, 256, input)) {
		strcpy(buf, line);
		err = pars_line(buf, &addr, &value);
		if (err == 0) {
			if (add_mem[addr] == 0) {
				MemoryArray[addr] = value;
			}
			else {
				fprintf(stderr, "%d: Command with %d addres already exists\n%s",  line_cnt, addr, line);
				flag_err = 1;	
			}
		}
		else if (err < 0) {
			print_error(line, line_cnt, err);
			flag_err = 1;
		}
		line_cnt++;
	}
	if (flag_err == 0) {
		fwrite(MemoryArray, sizeof(*MemoryArray), MEMORYSIZE, output);
	}
	fclose(input);
	fclose(output);
	return 0;
}