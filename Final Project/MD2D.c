/* This program implements molecular dynamics in a two-dimensional box of argon atoms. The atoms are placed in a face-centered-cubic 
lattice. Potenial energy and kinetic energy are also calculated in this dynamic system. Conservation of energy should occur since forces at
the cutoff radius are small. Energy is plotted against final temperature in order to find the heat of condensation of Argon. */


#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>



/*
Ndimension: dimension of box (1D, 2D, 3D)
Natom : number of argon atoms
x[Natom]: array of x positions argon atoms 
y[Natom]: array of y positions argon atoms 
vx[Natom]: array of velocities in the x direcition for argon atoms 
vy[Natom]: array of velocities in the y direcition for argon atoms 
fx[Natom][2]: array of forces in the x direction for argon atoms at t([Natom][t1]) and t+1([Natom][t2])
fx[Natom][2]: array of forces in the y direction for argon atoms at t([Natom][t1]) and t+1([Natom][t2])
t : time
h : time step
Nstep: number of time steps
T_final: final temperature
T_initial: initial temperature
L : size of the box
KE : kinetic energy
PE : potential energy
radius2 - square of the radius of argon
r2Cut: square of the cutoff radius; where potential is assumed to be 0 due to its distance
*/

#define Ndimension 2
#define Natom 1000
#define h 0.004
#define Nstep 1000
#define radius2 1.1225      /*chosen to be where the minimum of the potential occurs*/


#define drand48 1.0/RAND_MAX*rand    /*random number generator needed for initial velocities using Gaussian velocity distribution*/
#define srand48 srand



double forces(int t, double L, double x[], double y[], double fx[][], double fy[][]);


double sign(double a, double b); 

int main()
{
	
	int t;
	double x[Natom], y[Natom];
	double vx[Natom], vy[Natom];
	double fx[Natom][2], fy[Natom][2];
	double L = floor(pow(Natom+0.0, 1.0/(Ndimension +0.0))); 
	double T_final;
	double hOver2 = h/2.0;
	double KE, PE;	
	int i, j, k;
	int t1, t2, t_temp;
	int stop;
	
	FILE *output1, *output2, *output3;
	output1 = fopen("C:\\MD2D.txt", "w");    /* holds kinetic energy, potential energy, total energy, and final temperature*/
	
	output2 = fopen("C:\\2DInitialpositions.txt", "w"); /* initial x and y positions of argon atoms*/
	
	output3 = fopen("C:\\2DFinalpositions.txt", "w");   /*x and y positions of argon atoms after system equilibrated*/

	
	

    srand48(time(NULL));
	
	double T_initial = 9;
	
	t1 = 0;    /* time1= t([Natom][t1])*/
	t2 = 1;    /* time2= t+1([Natom][t2])*/
	

	i=0;

	stop = 0;
	for(k=0; k<=5*L; k+=5)
	{	
	for(j=0; j<=5*L; j+=5)
	{
		                                        /*initialize positions of argon atoms*/
		x[i] = j;
		y[i] = k;

		
		/*initialize velocities with a Gaussian velocity distribution; only part of molecular dynamics to depend on chance; 
		uses random number generator*/
		
		
		vx[i]=((drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48())/(20.))-0.5;
				
		vx[i] = 20*vx[i] * sqrt(T_initial);                                    /*scale velocities to initial temperature*/
		
		
		vy[i]=((drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48()
				+drand48()+drand48()+drand48()+drand48()+drand48())/(20.))-0.5;
				
		vy[i] = 20*vy[i] * sqrt(T_initial);                                     /*scale velocities to initial temperature*/
		
		

		
		if(i >= Natom-1)                                                        /*determine if another atom is to be added*/
		{
			stop = 1;
			break;			
		}
		
		fprintf(output2, "%f\t%f\n", x[i], y[i]);
		i++;
				
		
				
	}
	
	
	if(stop == 1)
     {
            break;
            
     }
     
	}
	

	KE = 0.0; 
	for(i = 0; i < Natom; i++)
	{
		KE = KE+(vx[i]*vx[i] + vy[i]*vy[i])/2.0; 
		
		
	}
	T_final = 2.0*KE / (3.0*Natom);
	PE = forces(t1, L, x, y, fx, fy);
	
	
	

	fprintf(output1, "%d\t%f\t%f\t%f\t%f\n", t, PE, KE, PE+KE, T_final);
	

/*main for loop; the values of energies and final temperature determined for each time step*/

	for(t = 0; t < Nstep; t++)
	{
		printf("%d\n", t);
		
		/* for time1*/
		
		
		for( i = 0; i < Natom; i++ )
		{
			
			x[i] = x[i] + h*(vx[i] + hOver2*fx[i][t1]);  /*advance with velocity-verlet algorithm*/
			y[i] = y[i] + h*(vy[i] + hOver2*fy[i][t1]);
			
			
			/* equilibrated positions: must check with periodic boundary conditions*/
			
			
			if (x[i] <= 0.0) 
               x[i] = x[i] + L;
               
			if (x[i] >= L)  
               x[i] = x[i] - L;
			
            if (y[i] <= 0.0) 
               y[i] = y[i] + L;
               
			if (y[i] >= L)  
               y[i] = y[i] - L;
			
		fprintf(output3, "%f\t%f\n", x[i], y[i]);	
		}
		
		/*for time2*/
		
	
		PE = forces(t2, L, x, y, fx, fy);
		
		
		KE = 0.0; 
		for(i = 0; i < Natom; i++)
		{ 
			vx[i] = vx[i] + hOver2 * (fx[i][t1] + fx[i][t2]);   /*advance with velocity-verlet algorithm*/
			vy[i] = vy[i] + hOver2 * (fy[i][t1] + fy[i][t2]);
			KE = KE + (vx[i]*vx[i] + vy[i]*vy[i])/2.0; 
			
		
		}
		T_final = 2.0*KE / (3.0*Natom);                /*final temperature of system*/
		

		
		fprintf(output1, "%d\t%f\t%f\t%f\t%f\n", t, PE, KE, PE+KE, T_final);
		
		t_temp = t1;
		t1 = t2;
		t2 = t_temp;
		
		
	}


	fprintf(output1, "\n%f\n", T_final);
	
	
	
	fclose(output1);
	fclose(output2);
	fclose(output3);

	


   
	
	return 0;
}

/* forces function calculates PE and forces for each time step at a given initial temperature*/


double forces(int t, double L, double x[Natom], double y[Natom], double fx[Natom][2], double fy[Natom][2])
{
	int i, j;
	double r2, inverse_r2=0, r2Cut, dx, dy;
	double f_ij_x, f_ij_y;
	
	r2Cut = 9.0;          /*cutoff radius where potential is 0*/
	
	
	/*initialize potentials and forces*/
		
	double PE = 0.0;
	for (i=0; i<Natom; i++)
	{
		fx[i][t] = 0.0;
		fy[i][t] = 0.0;
	}
	
	for(i = 0; i<Natom; i++)
	{
	for(j = i+1; j<Natom; j++)
	{
		dx = x[i]-x[j];   /*distance between centers of two atoms*/
		dy = y[i]-y[j];
		
		if(fabs(dx) > 0.50*L)           /*minimum image criterium*/
		{
			dx = dx - sign(L,dx);
		}
		if(fabs(dy) > 0.50*L)             /*minimum image criterium*/
		{
			dy = dy - sign(L,dy);
		}
		
		r2 = dx*dx + dy*dy;
				
		
		if(r2 < r2Cut)     /*cut off conditions*/
		
		{
              if(r2==0.)   /* if two atoms are overlapping, force atoms apart to a random location*/
              {
                       
               dx= dx*sqrt(radius2)*cos(drand48());
               dy= dy*sqrt(radius2)*cos(drand48());
               
               r2=radius2;
        
                       
               }
              
			else      /*ensure the distance between atoms larger than the radius of one atom*/
			{
				dx = dx*sqrt(radius2/r2);         
				dy = dy*sqrt(radius2/r2);         
				r2=radius2;                   
				
	
          }

         /*uses the Lennard-Jones potential
          u(r) = 4*(1/r**12 - 1/r**6) */
			         
			
			inverse_r2 = 1.0/r2;   
			f_ij_x =  48.0 * (pow(inverse_r2, 3) - 0.5) * pow(inverse_r2, 4)*dx;
			fx[i][t] = fx[i][t] + f_ij_x;
			fx[j][t] = fx[j][t] - f_ij_x;
			
			f_ij_y =  48.0 * (pow(inverse_r2, 3) - 0.5) * pow(inverse_r2, 4)*dy;
			fy[i][t] = fy[i][t] + f_ij_y;
			fy[j][t] = fy[j][t] - f_ij_y;
			
			PE = PE + 4.0 * pow(inverse_r2,3) * ( pow(inverse_r2,3) - 1.0);
		}
	}
	
}	
	
	return (PE);	
}


/*sign function necessary for forces function to calculate forces and PE*/

double sign(double a, double b)
{
	if(b >= 0.0)
	{
		return abs(a);
	}
	else
	{
		return -abs(a);
	}
}   
