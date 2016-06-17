#include "../header_files/hex_to_base_64.h"
#include <string.h>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <stdlib.h>  

using namespace std;


// Converts char to hex integers
int hex_decode(char hex_str_element){
    if (hex_str_element  >= 'a' && hex_str_element <= 'f'){
        return (int)((hex_str_element - 'a') + 10);
    }else{
        return (int)(hex_str_element - '0');
    }
}

//Converts integers to hex chars
char hex_encode(int hex_int){
    if (hex_int >= 10 && hex_int<=15){
        return char(hex_int - 10 + 'a');
    }else{
        return char(hex_int + '0');
    }
}
void fixed_xor(char *src1, char *src2, char *dest){
   int *x1 = (int*)calloc(strlen(src1),sizeof(int)); 
   int *x2 = (int*)calloc(strlen(src2),sizeof(int)); 
   int *out = (int*)calloc(strlen(src2),sizeof(int)); 
   int index = 0;
   int len = strlen(src1); 
   cout<<strlen(src1)<<endl;
   //decode both hex inputs
   while(index < len){
      x1[index] = hex_decode(*(src1++));
      x2[index++] = hex_decode(*(src2++));
   }
   index = 0;

   //calculate the xor
   while(index < len){
      out[index] = (x1[index]^x2[index])&0xff; 
      index++;
   }

   index = 0;
   //encode the output    
   while(index < len){
      dest[index] = hex_encode(out[index]); 
      index++;
   }
   dest[index] = '\0'; 
}
int main(){
    char hex_str1[500] = "1c0111001f010100061a024b53535009181c";
    char hex_str2[500] = "686974207468652062756c6c277320657965";
    char dest[500] = "";
    fixed_xor(hex_str1,hex_str2,dest);    
    cout<<dest; 
    return 0;
}
