#include "hex_to_base_64.h"
#include <string.h>
#include <stdint.h>
#include <cstring>
#include <iostream>

using namespace std;

//Function to convert hex to base 64 integer
int hex_to_base_int(uint16_t hex){

}
//Function for converting base 64 integer to correct representation
char hexbase_int_to_64base_repr(uint16_t b64){

}

//Function to convert char to int
int  c_to_int (char hex_c){
   if(hex_c >= 'a' && hex_c <= 'f'){
      return int(hex_c - 'a')+10;
   }
  return int(hex_c - '0');
}

//Function to convert hex encoded string to base 64 encoded string
void hex_to_64 (char *src, char *dest){
    int src_len = strlen(src);
    int decimal_array [1000] = {0};
    
    //create an array of elements containg values in the range 0-63

    int hex_array_element_count = 0;
    int b64_array_element_count = 0;
    while(*src != '\0'){
        if(*(src+1) == '\0'){
            //if this is the last character in the string just store this 
            decimal_array[b64_array_element_count++] = c_to_int(*src);
            src++;
        } else if (*(src+2) == '\0'){
            //if this is the second last character in the string get 6 bits from this and the last
            //character and then last two bits of the last character act as one whole integer
            decimal_array[b64_array_element_count] = c_to_int(*src)<<2;
            decimal_array[b64_array_element_count++] |= (c_to_int(*(src+1)) & 0x0c) >> 2;
            decimal_array[b64_array_element_count++] = (c_to_int(*(src+1)) & 0x03);
            src = src+2;
        }else{
            //if there are 2 more characters after this convert 3 hex intergers to 2 base 64 integers
            decimal_array[b64_array_element_count] = c_to_int(*src)<<2;
            decimal_array[b64_array_element_count++] |= (c_to_int(*(src+1)) & 0x0c) >> 2;
            src++;
            decimal_array[b64_array_element_count] = (c_to_int(*src) & 0x03)<<4;
            decimal_array[b64_array_element_count++] |= (c_to_int(*(src+1)) & 0x0f);
            
            src = src+2;
        }
    }
    for(int i=0;i<b64_array_element_count;i++){
        cout<<decimal_array[i]<<" ";
    }
}

int main(){
    char abcd[7] = "49276d";
    hex_to_64(abcd,NULL);    
    return 0;
}
