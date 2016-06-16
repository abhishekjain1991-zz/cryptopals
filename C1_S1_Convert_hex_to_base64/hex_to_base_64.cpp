#include "hex_to_base_64.h"
#include <string.h>
#include <stdint.h>
#include <cstring>
#include <iostream>

using namespace std;

//Function for converting base 64 integer to correct representation
char hexbase_int_to_64base_repr(int b64){
    if(b64>=0 && b64<=25){
    //if value between 0 to 25 convert into char between A and Z
        return((char)(b64+65));
    }else if (b64>=26 && b64 <=51){
    //if value between 26 to 51 convert into char between a and z
        return ((char)(b64+97-26));
    }else if (b64 == 62){
        return '+';
    }else if (b64 == 63){
        return '/';
    }else{
        //if value between 52 to 61 convert into char between 0 and 9
        return (char)(b64-52+48);
    }
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
        dest[i] = hexbase_int_to_64base_repr(decimal_array[i]);
    }
    dest[++b64_array_element_count] = '\0';
}

int main(){
    char abcd[500] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char cdef[500] = "";
    hex_to_64(abcd,cdef);    
    cout<<cdef; 
    return 0;
}
