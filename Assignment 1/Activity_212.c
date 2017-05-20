#include <stdio.h>
#include <math.h>

//Exerciese 2.1.2 #1
//Mitchell Miller
int main() {
    //Initialize variables
    double a=0;
    double b=0;
    double c=0;
    double positiveX1=0;
    double negativeX1=0;
    double positiveX2=0;
    double negativeX2=0;
    
    //Get values from user
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    printf("c = ");
    scanf("%lf",&c);
    
    //Calculate quadratics
    positiveX1 = (-b + sqrt((b * b) - (4*a*c))) / (2*a);
    negativeX1 = (-b - sqrt((b * b) - (4*a*c))) / (2*a);
    positiveX2 = (-2*c) / (b + sqrt((b * b) - (4*a*c)));
    negativeX2 = (-2*c) / (b - sqrt((b * b) - (4*a*c)));

    //Display results
    printf("X_1, X_2, X'_1, X'_2 \n");
    printf("%e, %e, %e, %e \n", positiveX1, negativeX1, positiveX2, negativeX2);

    printf("Press enter to exit \n");
    getchar();
    getchar();
    return 0;
}
