#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <iomanip>

using namespace std;

void adjust_zeros(mpf_t number, string* result, int precision){

	char* buffer = new char[300];
	int n = gmp_sprintf(buffer, "%.*Ff", precision, number);

	int index = n;
	bool doRemove = true;

	while(doRemove){
		if(buffer[index-1] == '0'){
			index--;
		}else{
			doRemove = false;
		}

	}
	if(buffer[index-1] == '.'){
		index--;
	}
	buffer[index+1] = '\n';
	(*result).assign(buffer, index);

}
void average(mpf_t *array, int size, mpf_t mpf_size, mpf_t result) {

    for (int i = 0; i < size; i++) {
        mpf_add(result, result, array[i]);
    }

    mpf_div(result, result, mpf_size);
}

void variance_period(mpf_t *array, int size, mpf_t mpf_size, mpf_t average, mpf_t variance, mpf_t period) {

    mpf_t temp, square;
    mpf_init(temp);
    mpf_init(square);
    int periodLen = 0;

    for (int i = 0; i < size; i++) {
        // variance
        mpf_sub(temp, array[i], average);
        mpf_pow_ui(square, temp, 2);
        mpf_add(variance, variance, square);

        //period
        if (i != 0) {
            if (periodLen != 0) {
                if (mpf_cmp(array[i], array[i % periodLen]) != 0) {
                    periodLen = i;
                }
            } else if (mpf_cmp(array[i], array[0]) == 0) {
                periodLen = i;
            }
        }
    }

    if (periodLen == 0) {
        periodLen = size;
    }

    mpf_set_si(period, periodLen);
    mpf_div(variance, variance, mpf_size);

}

int main() {

    const int d = 16;
    long long int num_count;
    mpf_t num_count_mpf;
    mpf_t average_result, variance_result, period_result;

    // 2^24 numbers
    mpf_t *numbers = new mpf_t[16777216];
    for (int i = 0; i < 16777216; i++) {
        mpf_init(numbers[i]);
    }

    mpf_init(average_result);
    mpf_init(variance_result);
    mpf_init(period_result);
    mpf_init(num_count_mpf);
    num_count = 0;

    while (cin >> numbers[num_count]) {
        num_count++;
    }

    mpf_set_si(num_count_mpf, num_count);
    average(numbers, num_count, num_count_mpf, average_result);
    variance_period(numbers, num_count, num_count_mpf, average_result, variance_result, period_result);

    string* adjusted = new string();
    adjust_zeros(average_result, adjusted, 5);
    cout << *adjusted << endl;

    adjust_zeros(variance_result, adjusted, 5);
    cout << *adjusted << endl;

//    cout << setiosflags(ios::fixed);
   // cout << fixed << setprecision(5) << average_result << endl;
//    cout << setprecision(5) << variance_result << endl;

//    gmp_printf (" %.*Ff \n", d, average_result);
//    gmp_printf (" %.*Ff \n", d, variance_result);

    cout << setprecision(0) << period_result << endl;

    mpf_clear(average_result);
    mpf_clear(variance_result);
    mpf_clear(period_result);

    return 0;
}
