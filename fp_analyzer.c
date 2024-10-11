// Sara Rigatti - rigattis@bc.edu
// CSCI 2271
// Assignment PA3: Floating point analyzer
// Last modified: 10/7/2024

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "fp_analyzer.h"

void print_bits(unsigned INT_TYPE u, int length){
    unsigned INT_TYPE mask = INT_FORMAT << (length-1);
    while (mask){
        putchar(!!(u&mask)+'0');
        mask>>=1;
    }
    putchar('\n');
}

void print_components(Converter c){
    printf("All bits: ");
    print_bits(c.u, BITS_PER_TYPE);
    printf("Sign: ");
    print_bits(c.components.sign, SIGN_LENGTH);
    printf("Exponent: ");
    print_bits(c.components.exponent, EXPONENT_LENGTH);
    printf("Mantissa: ");
    print_bits(c.components.mantissa, MANTISSA_LENGTH);
}

void print_normalized(Converter c){
    int true_sign = 0;
    if(c.components.sign){
        true_sign = -1;
    }
    else{
        true_sign = 1;
    }

    int true_exponent = c.components.exponent-BIAS;
    
    FP_TYPE true_mantissa = (FP_TYPE)c.components.mantissa;
    for(int i = 0; i<MANTISSA_LENGTH; i++){
        true_mantissa/=2;
    }
    printf("Original value:\n");
    printf("(-1)^{%d} x (1 + %.6"INPUT_FORMAT") x 2^{%d - %d}\n", c.components.sign, true_mantissa, c.components.exponent, BIAS);
    true_mantissa+=1;
    printf("    = %d x %.6"INPUT_FORMAT" x 2^{%d}\n", true_sign, true_mantissa, true_exponent);
    float evaluated_exponent = power_of_2(true_exponent);
    if(true_sign==1){
        printf("    = %.6"INPUT_FORMAT" x %.0f\n", true_mantissa, evaluated_exponent);
    }
    else{
        printf("    = %d x %.6"INPUT_FORMAT" x %.0f\n", true_sign, true_mantissa, evaluated_exponent);
    }
    FP_TYPE v = true_sign * true_mantissa * evaluated_exponent;
    printf("    = %.45"INPUT_FORMAT"\n", v);

}

void print_denormalized(Converter c){
    int true_sign = 0;
    if(c.components.sign){
        true_sign = -1;
    }
    else{
        true_sign = 1;
    }
    int true_exponent = 1-BIAS;
    FP_TYPE true_mantissa = (FP_TYPE)c.components.mantissa;
    for(int i = 0; i<MANTISSA_LENGTH; i++){
        true_mantissa/=2;
    }
    printf("Original value:\n");
    printf("(-1)^{%d} x %.45"INPUT_FORMAT" x 2^{1 - %d}\n", c.components.sign, true_mantissa, BIAS);
    printf("    = %d x %.6"INPUT_FORMAT" x 2^{%d}\n", true_sign, true_mantissa, true_exponent);
    FP_TYPE evaluated_exponent = power_of_2(-1*true_exponent);
    FP_TYPE v = true_sign * true_mantissa * (1/evaluated_exponent);
    printf("    = %.45"INPUT_FORMAT" x 1/%.0f\n", (true_mantissa*true_sign), evaluated_exponent);
    printf("    = %.45"INPUT_FORMAT"\n", v);
}


FP_TYPE power_of_2(int exponent){
    FP_TYPE result = 1.0;
    if (exponent >= 0){
        while(exponent--){
            result*=2;
        }
    }
    else{
        exponent*=-1;
        while(exponent--){
            result/=2;
        }
    }
    return result;
}

void print_reconstitution(Converter c){
    if((c.components.mantissa == 0)&&(c.components.exponent==0)){
        if(c.components.sign){
            printf("Original value: -0.0\n");
            return;
        }
        else{
            printf("Original value: 0.0\n");
            return;
        }
    }
    if(c.components.exponent){
        print_normalized(c);
    }
    else{
        print_denormalized(c);
    }
}

void print_special(){
    union Converter special_values[4];
    special_values[0].f = 1.0/0.0;
    special_values[1].f = -1.0/0.0;
    special_values[2].f = NAN;
    special_values[3].f = -NAN;
    const char * special_names[4] = {"inf", "-inf", "nan", "-nan"};
    for(int i = 0; i<4; i++){
        printf("%s\n", special_names[i]);
        print_components(special_values[i]);
        printf("\n");
    }
}
