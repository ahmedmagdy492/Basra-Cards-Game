#pragma once

enum ScreenMode {
  MenuScreen,
  PlayScreen,
  HowToPlayScreen,
  PauseScreen
};

typedef enum ScreenMode ScreenMode;

static void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* utoa(uint8_t num, char* buffer) {
  int i = 0, base = 10;

    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    while (num != 0) {
        int rem = num % base;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    buffer[i] = '\0'; // Null-terminate the string

    reverse(buffer, i);

    return buffer;
}
