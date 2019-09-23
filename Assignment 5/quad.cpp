/**
 * @file quad.cpp
 * @author Hemil Panchiwala
 * @brief This program performs the addition and multiplication of two polynomials
 * @date 2019-09-23
 * 
 * 
 */
#include <iostream>
#include <map> 
#include <time.h>
using namespace std;

/**
 * @brief This function performs the addition and multiplication
 * 
 * @return int 
 */
int main(){

    clock_t start, end;
    double cpu_time_used;

    start = clock();

	int coeff, pow;
	int max;
	map<int,int> eq1, eq2;

    int terms1, terms2;

	cout<<"Enter number of terms in first polynomial: ";
	cin>>terms1;
	cout<<"Enter the Coefficient and Power: "<<endl;
	for(int i=0; i<terms1; i++){
		cin>>coeff>>pow;
		eq1[pow]=coeff;
	}

	cout<<"Enter number of terms in second polynomial: ";
	cin>>terms2;
	cout<<"Enter the Coefficient and Power: "<<endl;
	for(int i=0; i<terms2; i++){
		cin>>coeff>>pow;
		eq2[pow]=coeff;
	}

	max = (terms1>terms2)?terms1:terms2;

    while(1){
        cout<<"Enter 1 to add: "<<endl;
        cout<<"Enter 2 to multiply: "<<endl;
        cout<<"Enter 3 to exit: "<<endl;
        int option;
        cin>>option;
        
        if(option == 1){
            cout<<"After addition: "<<endl;
            cout<<"Coefficients        Power"<<endl;

            for(int i=max-1;i>=0;i--){
                cout<<eq1[i]+eq2[i]<<"                   "<<i<<endl;
            }
        }else if(option == 2){
            cout<<"After multiplication: "<<endl;
            cout<<"Coefficients        Power"<<endl;

            for(int i=terms1+terms2-2; i>=0; i--){
                int temp = 0;
                for(int j=0; j<=i; j++){
                    temp += eq1[j]*eq2[i-j];
                }
                cout<<temp<<"                   "<<i<<endl;
            }
        }else if(option == 3){
            break;
        }else{
            cout<<"Enter valid option!!!"<<endl;
        }
    }

    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

	return 0;
}