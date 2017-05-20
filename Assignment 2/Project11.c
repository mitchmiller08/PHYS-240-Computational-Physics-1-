#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Project 1.1
//Mitchell Miller PHYS 240 2/12/10

//**          Initial conditions file format:         **\\
//**                                                  **\\ 
//**  Position in angstroms *TAB* Potential in joules **\\
//**  Position in angstroms *TAB* Potential in joules **\\

//**              
//**               |                                   |
//**               | 2 * m        2                    |
//**     Psi(dz) = |--------- (dz)  * ( V(dz) - E ) + 2 |
//**               |       2                           |
//**               |(h_bar)                            |
      
int main(){
	  //Initialize variables
	  double zInitial[100];	                  //Change '100' to number of initial conditions
	  double V_zInitial[100];                 //Change '100' to number of initial conditions
	  int i=0;                                //Counter
	  //int n=0;
	  double psi0=0,psi1=1,psi2=0;            //Values for Psi_n, Psi_n-1, and Psi_n-2
	  double z=0,V_z=0,dz=0;                  
	  double e_0=1.602186e-19;                //Charge of electron
	  double dE=1e-3*e_0;                     //Energy step size
	  //float dummy=1;
	  double E,E_soln;
	  double hbar=1.05459e-34;           
	  double m=9.109534e-31;                  //Mass of electron
	  memset(zInitial,'\0',100);              //Change '100' to number of initial conditions
	  memset(V_zInitial,'\0',100);            //Change '100' to number of initial conditions
	  double Y1=1,Y2=1;
      FILE *file;
	  FILE *outfile;
	  FILE *solnfile;
	  outfile = fopen("Project 11.txt","w");  
	  solnfile = fopen("Project 11_soln.txt","w");
	
	  //Begin reading file
	  file = fopen("InitialConditions_11.txt", "r");   //Specify path for initial conditions file
	  char line[200], *end;
	  while(fgets(line, sizeof line, file) != NULL){
    		//Store initial condistions from file to array
            zInitial[i] = atof(strtok(line, "\t"));
    		V_zInitial[i] = atof(strtok(NULL, "\t"));
    		printf("z_i = %f, V(z)_i = %f\n", zInitial[i], V_zInitial[i]);
    		i++;
	  }
	  
	  //Calculate odd parity solutions
	  for(E=0; E<e_0;E=E+dE){
            psi1=1;
            psi0=0;
            for(i=0;i<100;i++){
                z = zInitial[i]*1e-10;
                V_z = V_zInitial[i];
                dz = (zInitial[i+1]-zInitial[i])*1e-10;
                psi2 = (2*m*(dz/hbar)*(dz/hbar)*(e_0*V_z-E)+2)*psi1-psi0;       //Calculate next term
                psi0 = psi1;
                psi1 = psi2;
            }
      printf("E=%fmeV psi(inf)=%f\n", E/(1e-3*e_0),psi2);
      Y2 = psi2;
      if(Y1*Y2<0){
            E_soln = fabs(Y1)*dE/(fabs(Y1)+fabs(Y2))+E-dE;
            fprintf(solnfile,"E_odd = %lf meV\n",E_soln/(1e-3*e_0));
            }
      Y1=Y2;
      fprintf(outfile, "{%f,%e},",E/(1e-3*e_0),psi2);
      }
      
	  fprintf(outfile,"\n\n\n");
	  
	  //Calculate even parity solutions
	  V_z = V_zInitial[0];
	  dz = (zInitial[1]-zInitial[0])*1e-10;
	  Y1=1;
	  for(E=0; E<e_0;E=E+dE){
            psi1=(m*(dz/hbar)*(dz/hbar)*(e_0*V_z-E)+1);
            psi0=1;
            for(i=0;i<100;i++){
                z = zInitial[i]*1e-10;
                V_z = V_zInitial[i];
                dz = (zInitial[i+1]-zInitial[i])*1e-10;
                psi2 = (2*m*(dz/hbar)*(dz/hbar)*(e_0*V_z-E)+2)*psi1-psi0;       //Calculate next term
                psi0 = psi1;
                psi1 = psi2;
            }
      printf("E=%fmeV psi(inf)=%f\n", E/(1e-3*e_0),psi2);
      Y2 = psi2;
      if(Y1*Y2<0){
            E_soln = fabs(Y1)*dE/(fabs(Y1)+fabs(Y2))+E-dE;
            fprintf(solnfile,"E_even = %lf meV\n",E_soln/(1e-3*e_0));
            }
      Y1=Y2;
      fprintf(outfile, "{%f,%e},",E/(1e-3*e_0), psi2);
      }
	  
	  
	  printf("Press Enter to Exit");
	  getchar();
	  fclose(file);
		
}
