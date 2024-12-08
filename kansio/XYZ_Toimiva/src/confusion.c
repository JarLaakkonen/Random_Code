#include <zephyr/kernel.h>
#include <math.h>
#include "confusion.h"
#include "keskipisteet.h"
#include "adc.h"
#include <time.h>

/* 
  K-means algorithm should provide 6 center points with
  3 values x,y,z. Let's test measurement system with known
  center points. I.e. x,y,z are supposed to have only values
  1 = down and 2 = up
  
  CP matrix is thus the 6 center points got from K-means algoritm
  teaching process. This should actually come from include file like
  #include "KmeansCenterPoints.h"
  
  And measurements matrix is just fake matrix for testing purpose
  actual measurements are taken from ADC when accelerator is connected.
*/ 
// Tänne se data jota kerättiin
int CP[6][3]={
	                     {1,0,0},
						 {2,0,0},
						 {0,1,0},
						 {0,2,0},
						 {0,0,1},
						 {0,0,2}
};

int measurements[6][3]={
	                     {1,0,0},
						 {2,0,0},
						 {0,1,0},
						 {0,2,0},
						 {0,0,1},
						 {0,0,2}
};
int TheData[3];
int CM[6][6]= {0};
int RandoData[6][100][3];

                                 // tulostetaan Confusion matrix??!
void printConfusionMatrix(void)
{
	printk("Confusion matrix = \n");
	printk("   cp1 cp2 cp3 cp4 cp5 cp6\n");
	for(int i = 0;i<6;i++)
	{
		printk("cp%d %d   %d   %d   %d   %d   %d\n",i+1,CM[i][0],CM[i][1],CM[i][2],CM[i][3],CM[i][4],CM[i][5]);
	}
}
                                          
void randomdata(void){
   printk("Make your own implementation for this function if you need this\n");
       /*
     Eli kun teen randomi arvot value
    Se mikä asento + 1900-2025 / -1268-1381
        1450,1700
        1450-1700       0-5
    */
    int max[6][3]={
        {2025,1800,1800},
        {1381,1800,1800},
        {1800,2025,1800},
        {1800,1381,1800},
        {1800,1800,2025},
        {1800,1800,1381},
    };

    int min[6][3]={
        {1900,1430,1430},
        {1268,1430,1430},
        {1430,1900,1430},
        {1430,1268,1430},
        {1430,1430,1900},
        {1430,1430,1268},
    };

    for (int B=0;B<6;B++){
    //    printk("Debug Arvot %d\n",B);
        for (int K=0;K<100;K++){

            for (int C=0;C<3;C++){
                RandoData[B][K][C]= min[B][C] + rand() % (max[B][C] - min[B][C] + 1);
        //        printk(" %d, ",RandoData[B][K][C]);
            }
        //      printk("\n");
        }
    }
    //printk("Hello World!\n");
    //    printk("%d\n",keskipisteet[0][0]);

    return;
}

void CaclOneAndUpdConfMatrix(int direction){
  //  printk("Debug dir %d\n",direction);
    // Mitä tämä tekee ottaa arrayn
    int LePoint=0;

    if (direction ==-1){
        for (int B=0; B<6; B++){
        for (int A=0; A<100; A++){
            LePoint=MinValCalc(RandoData[B][A][0],RandoData[B][A][1],RandoData[B][A][2]);

            CM[B][LePoint]++;

        }
        }
    }
    else{
   //     printk("jotain\n");
        LePoint=MinValCalc(TheData[0],TheData[1],TheData[2]);
        CM[direction][LePoint]++;


    }
}

int MinValCalc(int Mx, int My, int Mz){
//   printk("Make your own implementation for this function if you need this\n");
    int arvo[6];
    int Test=0;
    int Value=0;
  //  printk("Debug X arvo = %d\nDebug Y Arvo = %d \nDebug Z arvo = %d \n",Mx,My,Mz);
    for (int i=0; i<6;i++){
        arvo[i]=sqrt((pow(keskipisteet[i][0]-Mx,2))+ (pow(keskipisteet[i][1]-My,2)) + (pow(keskipisteet[i][2]-Mz,2)));

    }
    Test=arvo[0];
 //   printk("%d",arvo[0]);
    for (int K=0;K<6;K++){
  //      printk("Loop toimii");
        if (Test>=arvo[K]){
       //     printk("Debug Test on = %d ja arvo on = %d\n" ,Test,arvo[K]);
            Test=arvo[K];
            Value=K;

        }
    }
 //   printk("Pienin etaisyys on =%d ja sen omistaja = %d",Test,Value);
    return Value;
}
void DatHandler( int X, int Y,int Z){
    TheData[0]=X;
    TheData[1]=Y;
    TheData[2]=Z;
}




void resetConfusionMatrix(void)
{
	for(int i=0;i<6;i++)
	{ 
		for(int j = 0;j<6;j++)
		{
			CM[i][j]=0;
		}
	}
}

