/*
 * CS 261 PA0: Intro project
 *
 * Name: 
 */

#include "p0-intro.h"

#include <math.h>

int add_abs (int num1, int num2)
{
    int sum = abs(num1) + abs(num2);
    return sum;
}

void add_ptr (int num1, int num2, int *ans)
{
    if(ans != NULL){

         int temp = num1 + num2;
         *ans = temp;
    }
}

int factorial (int num)
{
    int value = 1;

	for(int i  =  1; i <= num; i++){
	    value = value * i;
    }
    return value;
}

bool is_prime (int num)
{
    // zero or one cannot be prime
    if(num == 0 || num == 1){
        return false;
    }
    //Actual checker starts at 2 in order to see if prime
    for (int i = 2; i < num; i++) {
        if (num % i == 0){
            return false;
         }
    }
    return true; 
}

vector_t add_vec (vector_t v1, vector_t v2)
{
    vector_t value;
    value.x = v1.x + v2.x;
    value.y = v1.y + v2.y;
    
    return value;
}

double dot_prod_vec (vector_t v1, vector_t v2)
{
    vector_t value;
    value.x = v1.x * v2.x;
    value.y = v1.y * v2.y;
    return value.x + value.y;
}

//Add the array together
int sum_array (int *nums, size_t n)
{
    int sum = 0;
   
    for(int i = 0; i < n; i++){
          sum = sum + nums[i];
    }
    return sum;
}

//Find the greatest common denominator
int gcd (int num1, int num2)
{
    if(num1 < 0){
        num1 = num1 * -1;
    }
      if(num2 < 0){
        num2 = num2 * -1;
    }

    int gcd;
    if( num1 == 0 && num2 == 0){
        return 0;
    } else if( num1 == 0 ){
        return num2;
    } else if( num2 == 0 ){
        return num1;
    } else if( num1 == 1 && num2 == 1){
        return 1;
    }
    for(int i=1; i <= num1 && i <= num2; i++)
    {
        if(num1 % i == 0 && num2 % i == 0){
            gcd = i;
    }
    }
    return gcd;
}

void sort_array (int *nums, size_t n)
{  
    int temp;
    for (int i = 0; i < n; i++) {     
        for (int j = i + 1; j < n; j++) {     
           if(nums[i] > nums[j]) {   
            // Got TA help because I forgot about temp variable storage 
               temp = nums[i];    
               nums[i] = nums[j];    
               nums[j] = temp;    
            }
        }
    }
}

