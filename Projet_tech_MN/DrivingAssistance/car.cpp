#include "car.h"
#define NB_POINTS 4

Car::Car()
{
}

void Car::principalTrajectoryAnalysis(){

    // getting the splinters
    Spline principalTrajectory1;
    Spline principalTrajectory2;
    Spline principalTrajectory;

    //CvMat *samplePoints = cvCreateMat(numSamples, 2, CV_32FC1);

    int imax = _splinters.size();
    int nbpoints = 4;
    float points[nbpoints][2];
    //CvMat *FourSplinesPoints = cvCreateMat(matimg.height, matimg.width, matimg.type);

    principalTrajectory1 = _splinters.back();
    _splinters.pop_back();
    principalTrajectory2 = _splinters.back();
    _splinters.pop_back();

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
    _splinters.push_back(principalTrajectory1);
    _splinters.push_back(principalTrajectory2);
    _splinters.push_back(principalTrajectory);

}

