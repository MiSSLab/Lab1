#include <iostream>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

void average(mpz_t* array, int size, mpf_t result){
    mpz_t sum;
    mpf_t mpzsize;

    mpz_init(sum);
    mpf_init(mpzsize);
    mpf_set_si(mpzsize, size);

    for(int i=0;i<size;i++){
        mpz_add(sum, sum, array[i]);
    }

    mpf_set_z(result, sum);
    mpf_div(result, result, mpzsize);

    mpz_clear(sum);
    mpf_clear(mpzsize);
}

void variance(mpz_t* array, mpf_t average, int size, mpf_t result){

}

void period(mpz_t* array, int size, mpf_t result){

}

int main() {

    FILE * pFile;
    const int d = 16;
    long long int num_count;
    mpf_t result;
    cout.precision(16);

    // 2^24 numbers
    mpz_t* numbers = new mpz_t[16777216];
    mpf_init(result);

    pFile = fopen ("MS/d2" , "r");

    if(pFile == NULL){
        cout << "Could not open file" << endl;
        return 0;
    }

    while(mpz_inp_str(numbers[num_count], pFile, 10)){
        num_count++;
    }

    average(numbers, d, result);

    cout << result << endl;

    mpf_clear(result);

    return 0;
}