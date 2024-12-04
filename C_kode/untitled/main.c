#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Keskipisteet.h>
static const int CP[6][3] = {
    {1971, 1618, 1638},
    {1356, 1639, 1682},
    {1659, 1929, 1656},
    {1657, 1285, 1639},
    {1676, 1613, 1960},
    {1650, 1620, 1324},
    };

int CM[6][6]= {0};
// data handelr laittaa datan
int TheData[3];
int RandoData[6][100][3];
void printConfusionMatrix(void)
{
    printf("Confusion matrix = \n");
    printf("   cp1 cp2 cp3 cp4 cp5 cp6\n");
    for(int i = 0;i<6;i++)
    {
        printf("cp%d %d   %d   %d   %d   %d   %d\n",i+1,CM[i][0],CM[i][1],CM[i][2],CM[i][3],CM[i][4],CM[i][5]);
    }
}
            // tällä LAKSETAAN ANTAA ASENNON
int MinValCalc(int Mx, int My, int Mz){
    int arvo[6];
    int Test=0;
    int Value=0;
  //  printf("Debug X arvo = %d\nDebug Y Arvo = %d \nDebug Z arvo = %d \n",Mx,My,Mz);
    for (int i=0; i<6;i++){
        arvo[i]=sqrt((pow(keskipisteet[i][0]-Mx,2))+ (pow(keskipisteet[i][1]-My,2)) + (pow(keskipisteet[i][2]-Mz,2)));

    }
    Test=arvo[0];
 //   printf("%d",arvo[0]);
    for (int K=0;K<6;K++){
  //      printf("Loop toimii");
        if (Test>=arvo[K]){
       //     printf("Debug Test on = %d ja arvo on = %d\n" ,Test,arvo[K]);
            Test=arvo[K];
            Value=K;

        }
    }
 //   printf("Pienin etaisyys on =%d ja sen omistaja = %d",Test,Value);
    return Value;
}






void CaclOneAndUpdConfMatrix(int direction){
    printf("paska dir %d\n",direction);
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
        printf("jotain\n");
        LePoint=MinValCalc(TheData[0],TheData[1],TheData[2]);
        CM[direction][LePoint]++;


    }

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
                      // tehdää Randomi data , joka on aikalailla samanlainan kuin oikea data
void randomdata(){
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
    //    printf("Debug Arvot %d\n",B);
        for (int K=0;K<100;K++){

            for (int C=0;C<3;C++){
                RandoData[B][K][C]= min[B][C] + rand() % (max[B][C] - min[B][C] + 1);
        //        printf(" %d, ",RandoData[B][K][C]);
            }
        //      printf("\n");
        }
    }
    //printf("Hello World!\n");
    //    printf("%d\n",keskipisteet[0][0]);

    return;
}

                    // Lasketaan lyhin matka ja tuodaan sen asennon numero vain
void DatHandler( int X, int Y,int Z){
    TheData[0]=X;
    TheData[1]=Y;
    TheData[2]=Z;
}


int main()
{
    srand(time(NULL));
    randomdata();
    //int (*pRD)[6][100][3]=&RandoData;
    int direction=3;

    int x =1900;
    int y =1500;
    int z =1500;
    DatHandler(x,y,z);
     CaclOneAndUpdConfMatrix(direction);
    printConfusionMatrix();
    /*
    resetConfusionMatrix();
      srand(time(NULL));
      randomdata();
      CaclOneAndUpdConfMatrix(direction);
    printConfusionMatrix();
      resetConfusionMatrix();
   // printf("Debug MinValCalc tulos =  %lf\n",paska);
*/
    return 0;

}


