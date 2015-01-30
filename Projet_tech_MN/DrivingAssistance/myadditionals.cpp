#include "myadditionals.h"
//  This additional file bring the analysis of the principal way and principal trajectory.

//  Dans la seconde je souhaiterais crée un ensemble de 4 points (moyenne des 2 splines) pour ensuite les utiliser
//    pour créer une troisième spline représentant la trajectoire souhaitée par la fonction mcvFitBezierSpline() l.173 .
//  Mais il doit me manquer un paramètre indispensable au type CvMat et je ne trouve comment comment manipuler cet objet
//



/**
 * This function returns the principal Way Analysed
 * of the input image,
 * given the camera parameters.
 *
 * \param matimg the input image
 * \param lanes line vector saving all lines detected
 * \param lineScores
 * \param splines
 * \param splineScores
 * \param splinters getting just the first two principal lanes
 *
*/
bool principalWayAnalysis(const CvMat *matimg, vector<Line> *lanes,
                          vector<FLOAT>*lineScores,
                          vector<Spline> *splines, vector<FLOAT> *splineScores,
                          vector<Spline> *splinters){


    int nbsplines = splines->size();

    //get center of picture
    cv::Mat fromcvmat(matimg);
    int cx = (fromcvmat.cols)/2;

    Spline tempoSplines[nbsplines];
    FLOAT  tempoSplineScore[nbsplines];
    Line tempoLines[nbsplines];
    FLOAT tempoLineScore[nbsplines];


    // get all value of the vector
    int i = 0;
    int sum[nbsplines];
    int iclosest[nbsplines];
    int closestval[nbsplines][2];

    while(nbsplines-1-i>=-1){
        iclosest[nbsplines-i]=5;
        closestval[nbsplines-i][0]=2000; //closest val and index
        i++;
    }

    i=0;

    int flag=0;
    int j=0;
    int flaggoingthrough = 0;


    while (splines->empty()!=true)
      {
        flaggoingthrough ++;
        tempoSplines[i] = splines->back();
        tempoSplineScore[i]= splineScores->back();
        tempoLines[i]= lanes->back();
        tempoLineScore[i]=lineScores->back();


        sum[i] =abs(tempoSplines[i].points[1].x+
                tempoSplines[i].points[2].x +
                tempoSplines[i].points[3].x +
                tempoSplines[i].points[0].x - cx*4) ;

        i++;
        splines->pop_back();
        splineScores->pop_back();
        lanes->pop_back();
        lineScores->pop_back();
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
        splines->push_back(tempoSplines[closestval[i][1]]);
        splineScores->push_back(tempoSplineScore[closestval[i][1]]);
        lanes->push_back(tempoLines[closestval[i][1]]);
        lineScores->push_back(tempoLineScore[closestval[i][1]]);
    }
    splinters->push_back(tempoSplines[closestval[0][1]]);
    splinters->push_back(tempoSplines[closestval[1][1]]);


    //principalTrajectoryAnalysis(splinters);

    return 0;

    }




/**
 * This function returns the Principal Trajectory Analysis
 * of the input Lanes, creating another third spline
 *
 * \param splinters input vector of 2 Splines
 *
*/

bool principalTrajectoryAnalysis(vector<Spline> *splinters){

// getting the splinters
    Spline principalTrajectory1;
    Spline principalTrajectory2;
    Spline principalTrajectory;

    //CvMat *samplePoints = cvCreateMat(numSamples, 2, CV_32FC1);

    int imax = splinters->size();
    int nbpoints = 4;
    float points[nbpoints][2];
    //CvMat *FourSplinesPoints = cvCreateMat(matimg->height, matimg->width, matimg->type);

    principalTrajectory1 = splinters->back();
    splinters->pop_back();
    principalTrajectory2 = splinters->back();
    splinters->pop_back();

    // averaging all the points
    for(int i=0;i<nbpoints;i++){


        points[i][0]=(principalTrajectory1.points[i].x+ principalTrajectory2.points[i].x)/2;
        points[i][1]=(principalTrajectory1.points[i].y+ principalTrajectory2.points[i].y)/2;



    }


    CvMat *samplePoints = cvCreateMat(nbpoints, 2, CV_32FC1);

    for (int j=0; j<nbpoints; j++) //numSamples
    {
      //points into cvmat samplePoints
      CV_MAT_ELEM(*samplePoints, float, j, 0) = points[j][0];
      CV_MAT_ELEM(*samplePoints, float, j, 1) = points[j][1];
    }
    //SHOW_MAT(samplePoints,"oui");

    //create a new spline for the trajectory
    principalTrajectory= mcvFitBezierSpline(samplePoints,3);
    splinters->push_back(principalTrajectory1);
    splinters->push_back(principalTrajectory2);
    splinters->push_back(principalTrajectory);

    return 0;
}



