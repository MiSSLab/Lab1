#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

void print(mpf_class number, int precision){

	char* buffer = new char[300];
	int n = gmp_sprintf(buffer, "%.*Ff", precision, number.get_mpf_t());

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
    string result;
    result.assign(buffer, index);
    cout << result << endl;
}

int period(vector<mpz_class> numbers, int size){

    int periodLen = 0;

    for (int i = 0; i < size; i++) {
        if (i != 0) {
            if (periodLen != 0) {
                if(numbers[i] != numbers[i % periodLen]){
                    periodLen = i;
                }
            } else if (numbers[i] == numbers[0]) {
                periodLen = i;
            }
        }
    }

    if (periodLen == 0) {
        periodLen = size;
    }

    return periodLen;
}


int main(int argc, char* argv[]) {

    if(argc!= 2){
        return 1;
    }

    int d = atoi(argv[1]);

    mp_bitcnt_t prec = ceil(d * log(10)/log(2));
    mpf_set_default_prec(prec + 128);

    vector<mpz_class> numbers;
    mpz_class input;

    mpz_class sum, square_sum;

    while(cin >> input){
        sum = sum + input;
        numbers.push_back(input);
	    square_sum = square_sum + (input*input);
    }


    int size = numbers.size();
    int periodLen = period(numbers, size);

    mpq_class average(sum, size);
    mpq_class temp1(square_sum, size);
    mpq_class temp2(average*average);
    mpq_class variance(temp1-temp2);

    mpf_class average_float;
    average_float = average;
    mpf_class variance_float = variance;

    print(average_float, d);
    print(variance_float, d);
    cout << periodLen << endl;

    return 0;
}
