#ifdef DOUBLE
#define FP_TYPE double
#define INT_TYPE long
#define INT_FORMAT 1ul
#define INPUT_FORMAT "lf"
#define EXPONENT_LENGTH 11
#define MANTISSA_LENGTH 52
#define BIAS 1023
#define BITS_PER_TYPE 64
#else
#define FP_TYPE float
#define INT_TYPE int
#define INT_FORMAT 1u
#define INPUT_FORMAT "f"
#define EXPONENT_LENGTH 8
#define MANTISSA_LENGTH 23
#define BIAS 127
#define BITS_PER_TYPE 32
#endif

#define SIGN_LENGTH 1

struct Components{
    unsigned INT_TYPE mantissa : MANTISSA_LENGTH;
    unsigned int exponent : EXPONENT_LENGTH;
    unsigned int sign : SIGN_LENGTH;
};

typedef union Converter{
    FP_TYPE f;
    unsigned INT_TYPE u;
    struct Components components;
} Converter;

void print_bits(unsigned INT_TYPE u, int length);

void print_components(Converter c);

void print_normalized(Converter c);

void print_denormalized(Converter c);

FP_TYPE power_of_2(int exponent);

void print_reconstitution(Converter c);

void print_special();

