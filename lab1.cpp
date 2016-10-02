#include <iostream>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

void average(mpf_t* array, int size, mpf_t mpf_size, mpf_t result){

    for(int i=0;i<size;i++){
        mpf_add(result, result, array[i]);
    }

    mpf_div(result, result, mpf_size);
}

void variance(mpf_t* array, int size, mpf_t mpf_size, mpf_t average, mpf_t result){

    mpf_t temp;
    mpf_init(temp);

    for(int i=0;i<size;i++){

        mpf_sub(temp, array[i], average);
        mpf_pow_ui(temp, temp, 2);
        mpf_add(result, result, temp);
    }

    mpf_clear(temp);

    mpf_div(result, result, mpf_size);

}

void period(mpf_t* array, int size, mpf_t result){

}

int main() {

    FILE * pFile;
    const int d = 16;
    long long int num_count;
    mpf_t num_count_mpf;
    mpf_t average_result, variance_result, period_result;
    cout.precision(d);

    // 2^24 numbers
    mpf_t* numbers = new mpf_t[16777216];
    for(int i=0;i<16777216;i++){
        mpf_init(numbers[i]);
    }

    mpf_init(average_result);
    mpf_init(variance_result);
    mpf_init(period_result);

    pFile = fopen ("MiSSLab1/r1" , "r");

    if(pFile == NULL){
        cout << "Could not open file" << endl;
        return 0;
    }

    while(mpf_inp_str(numbers[num_count], pFile, 10)){
        num_count++;
    }
    mpf_set_si(num_count_mpf, num_count);

    average(numbers, num_count, num_count_mpf, average_result);
    variance(numbers, num_count, num_count_mpf, average_result, variance_result);

    cout << average_result << endl;
    cout << variance_result << endl;
    cout << period_result << endl;

    mpf_clear(average_result);
    mpf_clear(variance_result);
    mpf_clear(period_result);

    return 0;
}