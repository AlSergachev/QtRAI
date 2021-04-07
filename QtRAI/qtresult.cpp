#include "qtresult.h"

QtResult::QtResult(int const& N, vector <struct Point>& points, QWidget *parent) :
    QWidget(parent), ui(new Ui::QtResult)
{
    ui->setupUi(this);
    transformationOfAngle(N, points);

        // Ïåðåâîäèì èçìåðåííûå óãëû èç ãðàäóñîâ â ðàäèàíû
        translationDegToRad(N, rad_angle_meas, points, deg_rad);

        // Îïðåäåëÿåì èçìåðåííûå äèðåêöèîííûå óãëû
        setDirectionAngleMeas(alfa_meas, rad_angle_meas, points, PI);

        // Âû÷èñëÿåì ïðèáëèæåííûå êîîðäèíàòû îïðåäåëÿåìîé òî÷êè
        setApproximateCoordinates(x_0, y_0, alfa_meas, points);

        // Âû÷èñëÿåì äèðåêöèîííûå óãëû íà èñõîäíûå ïóíêòû è ðàñòîÿíèÿ äî íèõ
        setDirectionAngleCompEndDistance(N, x_0, y_0, directions, points, PI);

        // Âû÷èñëÿåì ñâîáîäíûå ÷ëåíû ïîïðàâîê
        setFreeMembers(N, free_members, rad_angle_meas, directions);

        // Âû÷èñëèì êîýôèöèåíòû óðàâíåíèÿ ïîïðàâîê
        setCoefficientsOfTheCorrectionsEquation(N, Ai, Bi, directions);

        // Ðåøèì íîðìàëüíûå óðàâíåíèÿ
        double delta_x(0), delta_y(0), D(0), VV(0), AA(0), BB(0);
        setFinalAmendments(N, delta_x, delta_y, D, AA, BB, VV, free_members, Ai, Bi, rad_deg);

        // Óðàâíåííûå êîîðäèíàòû
        equalized_x = x_0 + delta_x;
        equalized_y = y_0 + delta_y;

        // Îöåíêà òî÷íîñòè
        m_alfa = sqrt(abs(VV) / (N - 2));
        m_x = 1000 * m_alfa / sqrt(D / BB);
        m_y = 1000 * m_alfa / sqrt(D / AA);
        m_P = sqrt(m_x * m_x + m_y * m_y);

        ui->label_x->setText("X = " + QString::number(equalized_x, 'f', 3));
        ui->label_y->setText("Y = " + QString::number(equalized_y, 'f', 3));
        ui->label_mp->setText(QString::number(m_P, 'f', 2));
        ui->label_mx->setText(QString::number(m_x, 'f', 2));
        ui->label_my->setText(QString::number(m_y, 'f', 2));
        ui->label_mx_a->setText(QString::number(m_alfa, 'f', 2));
}

void QtResult::transformationOfAngle(int const& N, vector <struct Point>& points)
{
    for (int i = 0; i < N; i++)
    {
        points[i].deg_angle_meas = points[i].deg + (points[i].min / 60.) + (points[i].sec / 3600.);
    }

}

void QtResult::translationDegToRad(int const& N, vector<double>& rad_angle_meas, vector<Point>const& points, const double& deg_rad)
{
    for (int i = 0; i < N; i++)
    {
        rad_angle_meas.push_back(points[i].deg_angle_meas * deg_rad);
    }
}

void QtResult::setDirectionAngleMeas(vector<double>& alfa_meas, vector<double> rad_angle_meas, vector<Point>const& points, const double& PI)
{
    double ctg_angle1 = tan(PI / 2 - rad_angle_meas[1]);
    double ctg_angle2 = tan(PI / 2 - rad_angle_meas[2]);
    double numerator = (points[1].p_y - points[0].p_y) * ctg_angle1 + (points[0].p_y - points[2].p_y) * ctg_angle2 + (points[2].p_x - points[1].p_x);
    double denumerator = (points[1].p_x - points[0].p_x) * ctg_angle1 + (points[0].p_x - points[2].p_x) * ctg_angle2 - (points[2].p_y - points[1].p_y);
    alfa_meas.push_back(atan(numerator / denumerator));
    for (size_t i = 1; i < rad_angle_meas.size(); i++)
    {
        alfa_meas.push_back(alfa_meas[0] + rad_angle_meas[i]);
    }
}

void QtResult::setApproximateCoordinates(double& x_0, double& y_0, vector<double>& alfa_meas, vector<Point>const& points)
{
    double dx_p_t1 = (((points[0].p_x - points[1].p_x) * tan(alfa_meas[1]) - (points[0].p_y - points[1].p_y))) / (tan(alfa_meas[0]) - tan(alfa_meas[1]));
    double dx_p_t2 = (((points[0].p_x - points[1].p_x) * tan(alfa_meas[0]) - (points[0].p_y - points[1].p_y))) / (tan(alfa_meas[0]) - tan(alfa_meas[1]));
    double dy_p_t1 = dx_p_t1 * tan(alfa_meas[0]);
    double dy_p_t2 = dx_p_t2 * tan(alfa_meas[1]);
    double x1_0 = points[0].p_x + dx_p_t1;
    double x2_0 = points[1].p_x + dx_p_t2;
    double y1_0 = points[0].p_y + dy_p_t1;
    double y2_0 = points[1].p_y + dy_p_t2;
    x_0 = (x1_0 + x2_0) / 2;
    y_0 = (y1_0 + y2_0) / 2;
}

void QtResult::setDirectionAngleCompEndDistance(int const& N, double const& x_0, double const& y_0, vector<Directions>& directions, vector<Point>const& points, const double& PI)
{
    double z(0), dx(0), dy(0);
    Directions d;
    for (int i = 0; i < N; i++)
    {
        dx = points[i].p_x - x_0;
        dy = points[i].p_y - y_0;
        z = sqrt(pow(dx, 2) + pow(dy, 2));
        d.distance = z;
        double r = atan(abs(dy) / abs(dx));
        if (dx >=0 && dy >= 0) d.alfa_comp = r;
        else if (dx <= 0 && dy >= 0) d.alfa_comp = PI - r;
        else if (dx <= 0 && dy <= 0) d.alfa_comp = PI + r;
        else if (dx >= 0 && dy <= 0) d.alfa_comp = 2*PI - r;
        directions.push_back(d);
    }
}

void QtResult::setFreeMembers(int const& N, vector<double>& free_members, vector<double> const& rad_angle_meas, vector<Directions>const& directions)
{
    vector<double> rad_angle_comp;
    for (int i = 1; i < N; i++)
    {
        double beta = directions[i].alfa_comp - directions[0].alfa_comp;
        rad_angle_comp.push_back(beta);
    }
    for (int i = 0; i < N - 1; i++)
    {
        double l = rad_angle_comp[i] - rad_angle_meas[i + 1];
        free_members.push_back(l);
    }
}

void QtResult::setCoefficientsOfTheCorrectionsEquation(int const& N, vector<double>& Ai, vector<double>& Bi, vector<Directions> const& directions)
{
    vector<double> ai, bi;
    double sec_p(206265), d_ai(0), d_bi(0);
    for (int i = 0; i < N; i++)
    {
        d_ai = -sec_p * sin(directions[i].alfa_comp) / directions[i].distance;
        ai.push_back(d_ai);
    }
    for (int i = 0; i < N; i++)
    {
        d_bi = sec_p * cos(directions[i].alfa_comp) / directions[i].distance;
        bi.push_back(d_bi);
    }
    for (int i = 1; i < N; i++)
    {
        Ai.push_back(ai[0] - ai[i]);
    }
    for (int i = 1; i < N; i++)
    {
        Bi.push_back(bi[0] - bi[i]);
    }
}

void QtResult::setFinalAmendments(int const& N, double& delta_x, double& delta_y, double& D, double& AA, double& BB, double& VV, vector<double>& free_members, vector<double> const& Ai, vector<double> const& Bi, const double& rad_deg)
{
    double AB(0), L(0), BL(0), AL(0), LL(0);
    for (int i = 0; i < N - 1; i++)
    {
        AA += Ai[i] * Ai[i];
        AB += Ai[i] * Bi[i];
        BB += Bi[i] * Bi[i];
        L = (free_members[i] * rad_deg * 3600);
        AL += Ai[i] * L;
        BL += Bi[i] * L;
        LL += L * L;
    }
    D = (AA * BB - AB * AB);
    delta_x = (AB * BL - BB * AL) / D;
    delta_y = (AB * AL - AA * BL) / D;
    vector<double> amendments;
    for (int i = 0; i < N - 1; i++)
    {
        L = (free_members[i] * rad_deg * 3600);
        amendments.push_back(Ai[i] * delta_x + Bi[i] * delta_y + L);
        VV += amendments[i];
    }
}

QtResult::~QtResult()
{
    delete ui;
}
