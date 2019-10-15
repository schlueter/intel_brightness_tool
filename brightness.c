#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /* Collect some info from the status files */
    FILE *max_brightness_file;
    FILE *brightness_file_read;
    int max_brightness;
    int brightness;
    brightness_file_read = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
    if (brightness_file_read == NULL) {
        printf("Error accessing the brightness interface");
        exit(1);
    }
    max_brightness_file = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
    if (max_brightness_file == NULL) {
        printf("Error accessing the max brightness interface");
        exit(1);
    }
    fscanf(max_brightness_file, "%i", &max_brightness);
    fscanf(brightness_file_read, "%i", &brightness);

    fclose(brightness_file_read);
    fclose(max_brightness_file);

    int desired_brightness;
    if (argc == 2) {
        desired_brightness = atoi(argv[1]);
        printf("Desired brightness is %i\n", desired_brightness);
    } else if (argc < 2 || argc > 2) {
        printf("Usage: brightness N\n\nN may be any value between 0 and %i\n", max_brightness);
        exit(0);
    }

    /* Escalate priviledges to obtain write access to the brightness interface */
    int calling_uid = setuid(0);
    if (calling_uid == -1) {
        printf("Error encountered while escalating priviledges, not continuing.");
        exit(1);
    }

    /* Set desired brightness */
    FILE *brightness_file_write = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
    if (brightness_file_write == NULL) {
        printf("Error accessing the brightness interface");
        exit(1);
    }

    fprintf(brightness_file_write, "%i", desired_brightness);

    fclose(brightness_file_write);
}
