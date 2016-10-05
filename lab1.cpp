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

void variance_period(mpf_t* array, int size, mpf_t mpf_size, mpf_t average, mpf_t variance, mpf_t period){

    mpf_t temp;
    mpf_init(temp);

    for(int i=0;i<size;i++){

        mpf_sub(temp, array[i], average);
        mpf_pow_ui(temp, temp, 2);
        mpf_add(variance, variance, temp);
    }

    mpf_clear(temp);

    mpf_div(variance, variance, mpf_size);

}
void period(mpf_t* array, int size, mpf_t sizempf, mpf_t period){

	int periodLen = 1;
	for(int i=1;i<size;i++)
	{
		if(array[i]!=array[i%(periodLen-1)]){
			periodLen++;
		}else{
			periodLen=i;
		}
	}
//	mpf_set_si(period, periodLen);
}

int main() {

    const int d = 16;
    long long int num_count;
    mpf_t num_count_mpf;
    mpf_t average_result, variance_result, period_result;
    cout.precision(d);
    ios::sync_with_stdio(false);

    // 2^24 numbers
    mpf_t* numbers = new mpf_t[16777216];
    for(int i=0;i<16777216;i++){
        mpf_init(numbers[i]);
    }

    mpf_init(average_result);
    mpf_init(variance_result);
    mpf_init(period_result);
    mpf_init(num_count_mpf);
    num_count = 0;

    while(cin >> numbers[num_count]){
	    num_count++;
    }
    
   // while(gmp_scanf("%Ff", numbers[num_count]) != EOF){
   //     num_count++;
   // }
   
    mpf_set_si(num_count_mpf, num_count);
    average(numbers, num_count, num_count_mpf, average_result);
    variance_period(numbers, num_count, num_count_mpf, average_result, variance_result, period_result);
    period(numbers, num_count, num_count_mpf, period_result);

    cout << average_result << endl;
    cout << variance_result << endl;
    cout << period_result << endl;

    mpf_clear(average_result);
    mpf_clear(variance_result);
    mpf_clear(period_result);

    return 0;
}
