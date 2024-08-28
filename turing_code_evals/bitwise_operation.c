#include<stdio.h>

int main()
{
    unsigned int num; 
    int pos;      
    
    printf("Enter the number (in hexadecimal format): ");
    scanf("%X", &num); 
    
    printf("Enter the position: ");
    scanf("%d", &pos); 
    
    int res = num + ((1 << pos) );

    printf("Result: %d\n", res);

    return 0;
}
