#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int training[6][4] = { {0,0,0,0},{0,0,1,0},{0,1,0,0},{1,0,1,1},{1,1,0,1},{1,1,1,1} };
int i = 0, j = 0;
float weights[3] = {0,0,0};
float r = 0;
float sum = 0, pred = 0, cost = 0, err = 0;
float learningRate = -0.1;
float dc_dw1 = 0, dc_dw2 = 0, dc_dw3 = 0, sig = 0;
float eSum = 0;

//function to generate random numbers
int randNum(int range)
{
    srand(time(0));
    r = rand() % range;
    return r;
}

void sums(int i)
{
    sum = 0;
    for(j = 0; j < 3; j++)
    {
        //sum
        sum = sum + (training[i][j] * weights[j]);
    }
}

void prediction()
{
    pred = 0;

    //prediction with normalizing function
    pred = 1 / (1 + exp(-sum));
}

void errorCalc(int i)
{
    err = 0;

    //error
    err = training[i][3] - pred;
}

void calcGradient()
{
    for(int I = 0; I < 6; I++)
    {
        sums(I);
        prediction();
        errorCalc(I);

        sig = 1 / (1 + exp(-sum));

        dc_dw1 = dc_dw1 + (err * sig * (1 - sig) * training[I][0]);
        dc_dw2 = dc_dw2 + (err * sig * (1 - sig) * training[I][1]);
        dc_dw3 = dc_dw3 + (err * sig * (1 - sig) * training[I][2]);
    }
}

void correctWeights()
{
    weights[0] -= dc_dw1 * learningRate;
    weights[1] -= dc_dw2 * learningRate;
    weights[2] -= dc_dw3 * learningRate;
}

void test(int x1, int x2, int x3)
{
    //sum
    sum = 0;
    sum = weights[0] * x1 + weights[1] * x2 + weights[2] * x3;
    //predict the new output
    prediction();
    if( pred > 0.5)
        cout<<"1"<<endl;
    else
        cout<<"0"<<endl;
}

int main()
{
    //random weights assignment
    weights[0] = randNum(100)/100.0;
    weights[1] = randNum(100)/100.0;
    weights[2] = randNum(100)/100.0;

    for(int k = 0; k < 100; k++)
    {
        cost = 0;
        //forward
        for(int m = 0; m < 6; m++)
        {
            sums(m);
            prediction();
            errorCalc(m);
            cost = cost + pow(err,2);
        }

        //backward
        calcGradient();
        correctWeights();

    }

    test(1,0,0);
    test(0,1,1);


//    cout<<weights[0]<<" "<<weights[1]<<" "<<weights[2]<<endl;
//    cout<<cost;

    return 0;
}
