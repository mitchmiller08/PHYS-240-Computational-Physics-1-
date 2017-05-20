#include <math.h>

//Exerciese 2.2.2
//Mitchell Miller


int main() {
    //Intialize variables
    double JUp[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double JDown[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int L=0;
    double x=0.1;
    int numberOfLoops=25;
    int XCount=0;
    int XLoops=3;
    int N=2;
    double n=2;
    double scale=0;
    double error=0;
    
    
    //Change values of x
    for(XCount=0; XCount<XLoops; XCount++){
        JUp[0] = sin(x)/x;
        JUp[1] = sin(x)/pow(x,2) - cos(x)/x;
        printf("J_0(%lf) Upward = %.10lf \n", x, JUp[0]);
        printf("J_1(%lf) Upward = %.10lf \n", x, JUp[1]);
        n = 2;
        //Fill array for values of J_0 to J_24 upwardly
        for(N=2; N<numberOfLoops; N++){
            JUp[N] = ((2*n-1)/x) * JUp[N-1] - JUp[N-2];
            printf("J_%i(%lf) Upward = %e \n", N, x, JUp[N]);
            n = n + 1;
        }
        //Set variables for downward recursion     
        n = 22;
        N = 2;
        JDown[24] = 1;
        JDown[23] = 1;
        for(N=22; N>=0; N--){
            JDown[N] = ((2*n+3)/x) * JDown[N+1] - JDown[N+2];
            n = n - 1;
        }
        //Scale values to known set
        scale = (sin(x)/x)/JDown[0];
        for(N=0; N<numberOfLoops; N++){
            JDown[N] = JDown[N] * scale;
            printf("J_%i(%lf) Downward = %e \n", N, x, JDown[N]);
        }
        x = x*10;
    }
    //Calculate relative error
    printf("Select value for X = ");
    scanf("%lf", &x);
    for(N=0; N<numberOfLoops; N++){
        error = fabs(JUp[N]-JDown[N]) / (fabs(JUp[N]) + fabs(JDown[N]));
        printf("L = %i \t J_%i(%.1lf)Up=%lf\t J_%i(%.1lf)Down=%lf\t Error = %e \n", N, N, x, JUp[N], N, x, JDown[N], error);
    }
    printf("Press Enter to Exit");
    getchar();
    getchar();
}
