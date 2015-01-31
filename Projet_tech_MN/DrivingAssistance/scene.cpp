#include "scene.h"

#define NB_SPLINES_MAX 10

Scene::Scene()
{

}

bool Scene::principalWayAnalysis(const CvMat *matimg, vector<Spline> *splinters,bool dispTraj){


    int nbsplines = splines.size();

    //get center of picture
    cv::Mat fromcvmat(matimg);
    int cx = (fromcvmat.cols)/2;

    Spline tempoSplines[NB_SPLINES_MAX];
    FLOAT  tempoSplineScore[NB_SPLINES_MAX];
    Line tempoLines[NB_SPLINES_MAX];
    FLOAT tempoLineScore[NB_SPLINES_MAX];


    // get all value of the vector
    int i = 0;
    int sum[NB_SPLINES_MAX];
    int iclosest[NB_SPLINES_MAX];
    int closestval[NB_SPLINES_MAX][2];

    while(nbsplines-1-i>=-1){
        iclosest[nbsplines-i]=5;
        closestval[nbsplines-i][0]=2000; //closest val and index
        i++;
    }

    i=0;

    int flag=0;
    int j=0;
    int flaggoingthrough = 0;


    while (splines.empty()!=true)
      {
        flaggoingthrough ++;
        tempoSplines[i] = splines.back();
        tempoSplineScore[i]= splineScores.back();
        tempoLines[i]= lanes.back();
        tempoLineScore[i]=lineScores.back();


        sum[i] =abs(tempoSplines[i].points[1].x+
                tempoSplines[i].points[2].x +
                tempoSplines[i].points[3].x +
                tempoSplines[i].points[0].x - cx*4) ;

        i++;
        splines.pop_back();
        splineScores.pop_back();
        lanes.pop_back();
        lineScores.pop_back();
      }

// sort from smallest to biggest gapt between center and splines


    for(i=0;i<nbsplines;i++){
        j=nbsplines-1; // for each splines
        flag=0;
        while(flag==0){
        // compare each sum with the array of closest val3
            if(sum[i]<closestval[nbsplines-1-j][0]) // from nbsplines to zero in the closest
            {
                for(flag = nbsplines-1;flag > nbsplines-1-j; flag-- ){  //shift the value of the index
                    closestval[flag][0]=closestval[flag-1][0];
                    closestval[flag][1]=closestval[flag-1][1];
                }
                closestval[nbsplines-1-j][0]=sum[i];
                closestval[nbsplines-1-j][1]=i;
                flag=15;

            }
            j--;
        }
    }

    for(i=0;i<nbsplines;i++){
        splines.push_back(tempoSplines[closestval[i][1]]);
        splineScores.push_back(tempoSplineScore[closestval[i][1]]);
        lanes.push_back(tempoLines[closestval[i][1]]);
        lineScores.push_back(tempoLineScore[closestval[i][1]]);
    }

    splinters->push_back(tempoSplines[closestval[0][1]]);
    splinters->push_back(tempoSplines[closestval[1][1]]);

return true;

}
