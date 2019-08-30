#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFSIZE (64)

int get_msr_value(uint64_t* reg_value) {
  const char* cmd = "rdmsr -u 0x1FC";
  char cmd_buf[BUFSIZE];

  FILE* fp;

  if ((fp = popen(cmd, "r")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  cmd_buf[strcspn(fgets(cmd_buf, BUFSIZE, fp), "\n")] = 0;
  *reg_value = atoi(cmd_buf);

  if (pclose(fp)) {
    printf("Command not found or exited with error status\n");
    return -1;
  }

  return 0;
}

int main(void) {
  const char* cmd = "wrmsr -a 0x1FC";
  char* concat_cmd;
  int ret;
  uint64_t* reg_value = &(uint64_t){0};

  if ((ret = get_msr_value(reg_value))) {
    return ret;
  }

  printf("Old register value: %lu\n", *reg_value);

  *reg_value = *reg_value & 0xFFFFFFFE;  // clear bit 0

  printf("New register value: %lu\n", *reg_value);

  if (asprintf(&concat_cmd, "%s %i", cmd, *reg_value) == -1)
    return -1;

  printf("Executing: %s\n", concat_cmd);

  system(concat_cmd);
  free(concat_cmd);

  return 0;
}
