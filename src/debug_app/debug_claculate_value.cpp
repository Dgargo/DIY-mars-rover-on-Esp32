
#include <stdio.h>

#include "debug_app/debug_claculate_value.h"


//Prit data for debuging 
void debug_print(const char* name_function, const int  data_arr[],size_t num_data,String data_arr_name[])
{
 Serial.println(name_function);
 for(int i = 0 ;i<num_data;i++)
 {
    Serial.printf("%s : %d \n",data_arr_name[i],data_arr[i]);
 }
 Serial.println("___________________________________"); 
}
