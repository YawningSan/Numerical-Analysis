#include <stdio.h>
int main(void) {
int n1, n2, n3, min;
printf("Enter n1:");
scanf("%d", &n1);
printf("Enter n2:");
scanf("%d", &n2);
printf("Enter n3:");
scanf("%d", &n3);
if( n1 < n2 )
if( n1 < n3 )
min = n1;
else
min = n3;
else
if( n2 < n3 )
min = n2;
else
min = n3;
printf("The smallest number is %d\n", min);
}