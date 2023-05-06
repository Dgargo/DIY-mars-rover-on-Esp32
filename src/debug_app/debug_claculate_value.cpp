
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "debug_app/debug_claculate_value.h"


/**
 * @brief  To print information for debugging purposes
 * 
 * This function allows for the output of information about variables to the serial port,
 * 
 * which can be useful for further analysis and debugging.
 * 
 * @param name_function The name of the function where the debug_print function is called
 * @param data_arr an array that contains the values ​​of the variables to output to the port
 * @param num_data the number of variables in the array
 * @param data_arr_name  an array of variable names
 *
 */
void debug_print(const char* name_function, const int  data_arr[],size_t num_data,String data_arr_name[])
{
 Serial.println(name_function);
 for(int i = 0 ;i<num_data;i++)
 {
    Serial.printf("%s : %d \n",data_arr_name[i],data_arr[i]);
 }
 Serial.println("___________________________________"); 
}

/**
 * @brief check input parametrs 
 * 
 * This function validates the input parameters to ensure that they are correct and within the specified range.
 * 
 * The first and second parameters after the "number" parameter determine the range size.
 * 
 * With the first parameter indicating the minimum value and the second parameter indicating the maximum value.
 * 
 * @param number the number of parameters
 * @param ... unlimited number of parameters
 *
 * @return true - verification successful 
 * @return false - verification failed
 */
bool check_input_parameters(int number,...)
{
  va_list args;
    va_start(args, number);
    int min = va_arg(args, int);
    int max = va_arg(args, int);
    for (int i = 0; i < number-2; i++) {
        int num = va_arg(args, int);
        if (num < min || num > max) {
            va_end(args);
            return false;
        }
    }
    va_end(args);
    return true;
}