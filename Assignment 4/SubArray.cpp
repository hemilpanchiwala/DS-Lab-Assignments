/**
 * @file SubArray.cpp
 * @author Hemil Panchiwala
 * @brief This code prints the maximum subarray with given sum
 * @date 2019-09-03
 * 
 * 
 */
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <time.h>

using namespace std;

/**
 * @brief This function finds the largest subarray with the given sum using
 * unordered_map(hash map)
 * 
 * @return int 
 */
int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int N;
    cout<<"Enter the value of N: ";
    cin>>N;
    int a[N];
    for(int i=0;i<N;i++){
        cin>>a[i];
    }
    int n;
    cout<<"Enter the value of n: ";
    cin>>n;
    int maxLength = 0;
    int sum = 0;
    unordered_map<int, int> mp;
    int p=-1,q=-1;

    for(int i=0;i<N;i++){

        sum = sum + a[i];

        if(sum == n) {
            maxLength = i+1;
            p = 0;
            q = i;
        }

        if(mp.find(sum) == mp.end()) {

            mp.insert({sum, i});

        }

        if(mp.find(sum - n) != mp.end()) {

            int value = i - mp[sum-n];
            if(maxLength < value){
                maxLength = value;
                p = mp[sum-n]+1;
                q = i;
            }

        }

    }

    cout<<"Length of longest subarray is "<<maxLength<<endl;
    cout<<"Index from "<<p<<" to "<<q<<endl;

    end = clock();
  
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;

}