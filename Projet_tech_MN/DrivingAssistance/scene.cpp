#include "scene.h"
#define NB_SPLINES_MAX 10

Scene::Scene()
{

}

bool Scene::principalWayAnalysis(const CvMat *matimg, vector<Spline> *splinters,bool dispTraj){


    int nbsplines = _splines.size();

    //get center of picture
    cv::Mat fromcvmat(matimg);
    int cx = (fromcvmat.cols)/2 + 50;

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


    while (_splines.empty()!=true)
      {
        flaggoingthrough ++;
        tempoSplines[i] = _splines.back();
        tempoSplineScore[i]= _splineScores.back();
        tempoLines[i]= _lanes.back();
        tempoLineScore[i]=_lineScores.back();


        sum[i] =abs(tempoSplines[i].points[1].x+
                tempoSplines[i].points[2].x +
                tempoSplines[i].points[3].x +
                tempoSplines[i].points[0].x - cx*4) ;

        i++;
        _splines.pop_back();
        _splineScores.pop_back();
        _lanes.pop_back();
        _lineScores.pop_back();
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
        _splines.push_back(tempoSplines[closestval[i][1]]);
        _splineScores.push_back(tempoSplineScore[closestval[i][1]]);
        _lanes.push_back(tempoLines[closestval[i][1]]);
        _lineScores.push_back(tempoLineScore[closestval[i][1]]);
    }

    splinters->push_back(tempoSplines[closestval[0][1]]);
    splinters->push_back(tempoSplines[closestval[1][1]]);

return true;

}

