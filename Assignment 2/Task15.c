#include <stdio.h>
#include <math.h>

//Task 1.5 (modified version of provided code)
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
    FILE *solnfile;
    file = fopen("Task 15.txt", "w");
    solnfile = fopen("Task 15_soln.txt","w");
    float dE=1e-3*e_0;                       //Energy step size
    float dz=1e-10;                          //Position step size
    float E;                                 //Energy
    float E_soln,Y1,Y2;
    float psi0,psi1,psi2;                    //Psi_n, Psi_n-1, and Psi_n-2
    float z;                                 //Position
    
    //Begin "shooting method"
    for(E=0; E < e_0; E += dE){
             psi0=1;
             psi1=(m*(dz/hbar)*(dz/hbar)*(e_0*(dz/100e-10)*(dz/100e-10)-E)+1);
             for(z = dz; z < 100e-10; z += dz){
                   //Calculate next value
                   psi2 = (2*m*(dz/hbar)*(dz/hbar)*(e_0*(z/100e-10)*(z/100e-10)-E)+2)*psi1-psi0;
                   psi0 = psi1;
                   psi1 = psi2;
             }
             printf("E=%f meV psi(infinity)=%f \n", E/(1e-3*e_0), psi2);
             fprintf(file, "{%f,%f},", E/(1e-3*e_0), psi2);
             Y2 = psi2;
             if(Y1*Y2<0){
                  E_soln = fabs(Y1)*dE/(fabs(Y1)+fabs(Y2))+E-dE;
                  fprintf(solnfile,"E = %lf meV\n",E_soln/(1e-3*e_0));
            }
            Y1=Y2;
    }
    printf("Press Enter to Exit");
    getchar();
}
