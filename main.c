#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "fp_analyzer.h"

int main(int argc, char*argv[]){
    if (argc > 1 && strcmp(argv[1], "special") == 0){
        print_special();
        return EXIT_SUCCESS;
    }
    puts("Please enter a floating-point number or q to quit.");
    printf("> ");
    FP_TYPE value;
    while(scanf("%"INPUT_FORMAT, &value)){
        Converter converter;
        converter.f = value;
        printf("%.6"INPUT_FORMAT"\n", value);
        print_components(converter);
        print_reconstitution(converter);
        printf("> ");
    }
    return EXIT_SUCCESS;
}
