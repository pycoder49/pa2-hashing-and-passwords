#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

uint8_t hex_to_byte(unsigned char h1, unsigned char h2) {
    int answer = 0;

    // Check h1 for lower case, upper case, number
    if ('a' <= h1 && h1 <= 'f') {
        answer += 16 * (h1 - 'a' + 10);
    } else if ('A' <= h1 && h1 <= 'F') {
        answer += 16 * (h1 - 'A' + 10);
    } else if ('0' <= h1 && h1 <= '9') {
        answer += 16 * (h1 - '0');
    }

    // Check the same for h2
    if ('a' <= h2 && h2 <= 'f') {
        answer += (h2 - 'a' + 10);
    } else if ('A' <= h2 && h2 <= 'F') {
        answer += (h2 - 'A' + 10);
    } else if ('0' <= h2 && h2 <= '9') {
        answer += (h2 - '0');
    }

    return answer;
}

void hexstr_to_hash(char hexstr[], unsigned char hash[32]) {
    int hex_index = 0;
    for(int i = 1; i < strlen(hexstr); i += 2){
        hash[hex_index] = hex_to_byte((unsigned char) hexstr[i-1], (unsigned char) hexstr[i]);
        hex_index++;
    }
}

int main(int argc, char* argv[]) {
    // Testing hex_to_byte function
    assert(hex_to_byte('c', '8') == 200);
    assert(hex_to_byte('0', '3') == 3);
    assert(hex_to_byte('0', 'a') == 10);
    assert(hex_to_byte('1', '0') == 16);

    // Testing the second function
    char str[64] = "c803a10f";
    char str_as_hex[32];
    hexstr_to_hash(str, str_as_hex);
    for (int i = 0; i < strlen(str_as_hex); i++) {
        printf("0x%02x ", str_as_hex[i]);
    }
    printf("\n");

    return 0;
}