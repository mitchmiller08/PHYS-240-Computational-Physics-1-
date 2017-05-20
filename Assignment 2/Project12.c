#include <stdio.h>
#include <math.h>

//Project 1.2
//Mitchell Miller PHYS 240 2/12/10

//**              
//**               |                                   |
//**               | 2 * m        2                    |
//**     Psi(dz) = |--------- (dz)  * ( V(0) - E ) + 2 |
//**               |       2                           |
//**               |(h_bar)                            |

//Define constants
#define hbar 1.05459e-34
#define m 9.109534e-31
#define e_0 1.602186e-19

int main(){
    //Intialize variables
    FILE *file;
    file = fopen("Project 12.txt", "w");
    float dE=1e-3*e_0;                                 //Energy step size
    float dz=1e-10;                                    //Postion step size
    float E;                                           //Energy
    float psi0,psi1,psi2;                              //Psi_n, Psi_n-1, and Psi_n-2
    float z;                                           //Position
    
    //Begin "shooting method"
    for(E=0; E < e_0; E += dE){
             psi0=1e-10;
             psi1=1e-10*pow(2.71828183,dz*pow(2*m*(dz*5e-6-E)/(hbar*hbar),0.5));
             for(z = dz; z < 100e-10; z += dz){
                   //Calculate next value
                   psi2 = (2*m*(dz/hbar)*(dz/hbar)*(dz*1e-10-E)+2)*psi1-psi0;
                   psi0 = psi1;
                   psi1 = psi2;
             }
             printf("E=%f meV psi(infinity)=%f \n", E/(1e-3*e_0), psi2);
             fprintf(file, "{%f,%f},", E/(1e-3*e_0), psi2);
    }
    printf("Press Enter to Exit");
    getchar();
}
