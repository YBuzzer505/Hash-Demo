#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Convert one hex digit to int
int hexDigitToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    c = toupper(c);
    return 10 + (c - 'A');
}

int main() {
    char password[100];
    printf("Enter your password: ");
    scanf("%99s", password);

    // Convert password to hex string
    char hexStr[200] = "";
    for (int i = 0; i < strlen(password); i++) {
        char buf[3];
        sprintf(buf, "%02X", (unsigned char)password[i]);
        strcat(hexStr, buf);
    }

    printf("Password in hex: %s\n", hexStr);

    // Some Ai (GPT)
    
    // Each 3 hex digits = 1 pixel
    int numPixels = (strlen(hexStr) + 2) / 3; // round up
    int width = numPixels;
    int height = 1;

    FILE *f = fopen("password.ppm", "w");
    if (!f) {
        printf("Error: could not create image\n");
        return 1;
    }

    // PPM header
    fprintf(f, "P3\n%d %d\n255\n", width, height);

    // Process hex string in chunks of 3
    for (int i = 0; i < strlen(hexStr); i += 3) {
        char h1 = hexStr[i];
        char h2 = (i + 1 < strlen(hexStr)) ? hexStr[i+1] : '0';
        char h3 = (i + 2 < strlen(hexStr)) ? hexStr[i+2] : '0';

        int r = hexDigitToInt(h1) * 16; // scale 0–15 → 0–240
        int g = hexDigitToInt(h2) * 16;
        int b = hexDigitToInt(h3) * 16;

        fprintf(f, "%d %d %d ", r, g, b);
    }

    fprintf(f, "\n");
    fclose(f);

    printf("Image saved as password.ppm\n");
    return 0;
}
