#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>

uint8_t hex_to_byte(unsigned char h1, unsigned char h2){
    int answer = 0;

    if('A' <= h1 && h1 <= 'F'){
        answer += (h1 - 55) * 16;
    }
    else if ('a' <= h1 && h1 <= 'f'){
        answer += (h1 - 87) * 16;
    }
    else if('0' <= h1 && h1 <= '9'){
        answer += (h1 - 48) * 16;
    }

    if('A' <= h2 && h2 <= 'F'){
        answer += (h2 - 55);
    }
    else if ('a' <= h2 && h2 <= 'f'){
        answer += (h2 - 87);
    }
    else if ('0' <= h2 && h2 <= '9'){
        answer += (h2 - 48);
    }

    return answer;
}

void hexstr_to_hash(char hexstr[], unsigned char hash[32]){
    int hex_index = 0;
    for(int i = 1; i < strlen(hexstr); i += 2){
        hash[hex_index] = hex_to_byte((unsigned char) hexstr[i-1], (unsigned char) hexstr[i]);
        hex_index++;
    }
}

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

int8_t crack_password(char password[], unsigned char given_hash[]){
    if(check_password(password, given_hash)){
        return 1;
    }

    for(int i = 0; i < strlen(password); i++){
        if(!( ('a' <= password[i] && password[i] <= 'z') || ('A' <= password[i] && password[i] <= 'Z') )){
            continue;
        }

        char original_character = password[i];

        if('a' <= password[i] && password[i] <= 'z'){
            password[i] = password[i] - 32;
        }
        else if('A' <= password[i] && password[i] <= 'Z'){
            password[i] = password[i] + 32;
        }

        if(check_password(password, given_hash)){
            return 1;
        }

        password[i] = original_character;
    }
    return 0;
}

int main(){

    printf("%d\n", hex_to_byte('c', '8'));
    char hexstr[] = "a1b2c3";
    unsigned char hash[32];
    hexstr_to_hash(hexstr, hash);
    
    for (size_t i = 0; i < strlen(hexstr)/2; i++) {
        printf("0x%02x ", hash[i]); 
    }
    printf("\n");



    char hash_as_hexstr[] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256 hash for "password"
    unsigned char given_hash[32];
    hexstr_to_hash(hash_as_hexstr, given_hash);
    printf("%d\n", check_password("password", given_hash));



    char password[] = "paSsword";
    char hash_as_hexstrr[] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256 hash of "password"
    unsigned char given_hashh[32];
    hexstr_to_hash(hash_as_hexstrr, given_hashh);
    int8_t match = crack_password(password, given_hashh);
    printf("%d\n", match);
    printf("%s\n", password);


    return 0;
}