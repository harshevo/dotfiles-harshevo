#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILE "/home/harshevo/brightness_control.txt"

// Function to send a notification
void notify(const char *message) {
  char command[256];
  snprintf(command, sizeof(command), "notify-send \"%s\"", message);
  system(command);
}

// Function to write a value to the temporary file
void write_tmp_bg(const char *file_path, int value) {
  FILE *file = fopen(file_path, "w");
  if (file == NULL) {
    notify("Failed to open file for writing.");
    return;
  }
  fprintf(file, "%d\n", value);
  fclose(file);
}

// Function to read the brightness value from the temporary file
int read_tmp_bg(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  if (file == NULL) {
    notify("Failed to open file for reading.");
    return -1;
  }

  int value;
  if (fscanf(file, "%d", &value) != 1) {
    fclose(file);
    notify("Failed to read value from file.");
    return -1;
  }

  fclose(file);
  return value;
}

// Function to increase brightness
void inc_bg() {
  int init_value = read_tmp_bg(TEMP_FILE);
  if (init_value == -1) {
    return;
  }

  int curr_value = 2;
  if (init_value <= 90) {
    curr_value = init_value + 9;
    write_tmp_bg(TEMP_FILE, curr_value);
  } else {
    return;
  }

  // Set brightness using ddcutil
  char command[256];
  snprintf(command, sizeof(command), "ddcutil setvcp 10 %d --display 1",
           curr_value);
  int result = system(command);

  if (result == 0) {
    char notify_message[64];
    snprintf(notify_message, sizeof(notify_message), "Brightness set to - %d",
             curr_value);
    notify(notify_message);
  } else {
    notify("Failed to set brightness.");
  }
}

int main() {
  inc_bg();
  return 0;
}

