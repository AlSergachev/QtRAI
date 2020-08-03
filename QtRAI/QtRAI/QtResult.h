#pragma once

#include <QWidget>
#include "ui_QtResult.h"
#include <cmath>

using namespace std;

struct Point
{
    double p_x;
    double p_y;
    double deg_angle_meas;
    int deg;
    int min;
    double sec;
};

struct Directions
{
    double alfa_comp;
    double distance;
};

class QtResult : public QWidget
{
	Q_OBJECT

public:
    QtResult(int const& N, vector <struct Point>& points, QWidget* parent = Q_NULLPTR);
    ~QtResult();



    void transformationOfAngle(int const& N, vector <struct Point>& points);
    void translationDegToRad(int const& N, vector<double>& rad_angle_meas, vector<Point>const& points, const double& deg_rad);
    void setDirectionAngleMeas(vector<double>& alfa_meas, vector<double> rad_angle_meas, vector<Point>const& points, const double& PI);
    void setApproximateCoordinates(double& x_0, double& y_0, vector<double>& alfa_meas, vector<Point>const& points);
    void setDirectionAngleCompEndDistance(int const& N, double const& x_0, double const& y_0, vector<Directions>& directions, vector<Point>const& points, const double& PI);
    void setFreeMembers(int const& N, vector<double>& free_members, vector<double> const& rad_angle_meas, vector<Directions>const& directions);
    void setCoefficientsOfTheCorrectionsEquation(int const& N, vector<double>& Ai, vector<double>& Bi, vector<Directions> const& directions);
    void setFinalAmendments(int const& N, double& delta_x, double& delta_y, double& D, double& AA, double& BB, double& VV, vector<double>& free_members, vector<double> const& Ai, vector<double> const& Bi, const double& rad_deg);

private:
    Ui::QtResult ui;
    const double PI = 3.1415926535897932384626433832795;
    const double deg_rad = PI / 180;
    const double rad_deg = 180 / PI;
    vector<double> rad_angle_meas;
    vector<double> alfa_meas;
    vector<double> free_members;
    vector<double> Ai, Bi;
    vector<Directions> directions;
    double x_0 = 0,
        y_0 = 0,
        equalized_x = 0,
        equalized_y = 0,
        m_alfa = 0,
        m_x = 0,
        m_y = 0,
        m_P = 0;
};