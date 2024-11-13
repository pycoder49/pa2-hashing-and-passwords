#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <assert.h>
#include <ctype.h>

// Milestone 1 part 1
uint8_t hex_to_byte(unsigned char h1, unsigned char h2){
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

// Milestone 1 part 2
void hexstr_to_hash(char hexstr[], unsigned char hash[32]){
    int hex_index = 0;
    for(int i = 1; i < strlen(hexstr); i += 2){
        hash[hex_index] = hex_to_byte((unsigned char) hexstr[i-1], (unsigned char) hexstr[i]);
        hex_index++;
    }
}

// Milestone 2
int8_t check_password(char password[], unsigned char given_hash[32]){
    unsigned char hash[32];
    SHA256(password, strlen(password), hash);

    for(int i = 0; i < 32; i++){
        if(hash[i] != given_hash[i]){
            return 0;
        }
    }
    return 1;
}

// Milestone 3
int8_t crack_password(char password[], unsigned char given_hash[]){
    if(check_password(password, given_hash)){
        return 1;
    }

    for(int i = 0; i < strlen(password); i++){
        char original_character = password[i];

        if(isdigit(original_character)){
            // run  a check with all numbres from 0-9
            for(int j = 0; j < 10; j++){
                password[i] = '0' + j;

                if(check_password(password, given_hash)){
                    return 1;   //success in finding a single digit variation
                }
            }
        }
        else if('a' <= original_character && original_character <= 'z'){
            password[i] -= 32;
        }
        else if('A' <= original_character && original_character <= 'Z'){
            password[i] += 32;
        }

        if(check_password(password, given_hash)){
            return 1;   //success
        }
        
        //if no checks pass, then replace the target character with original character
        password[i] = original_character;
    }

    return 0;
}


// main function
int main(int argc, char** argv){

    if (argc < 2) {
        printf("Error: Not enough arguments provided\n");
        printf("Correct way to input: %s <hex hash>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) != 64) {
        printf("Error: The hash must be exactly 64 hex characters long.\n");
        return 1;
    }

    unsigned char hash[32];
    hexstr_to_hash(argv[1], hash);

    char password[128];

    // keeps asking user for input until they press CTRL+D
    while (fgets(password, sizeof(password), stdin) != NULL) {
        if (password[strlen(password) - 1] == '\n') {
            password[strlen(password) - 1] = '\0';
        }

        if (crack_password(password, hash)) {
            printf("Found password: SHA256(%s) = %s\n", password, argv[1]);
            return 0;
        }
    }
    
    // prints this out when they give up
    printf("Did not find a matching password\n");

    return 0;
}