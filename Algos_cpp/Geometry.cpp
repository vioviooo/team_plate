#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const double PI = acos(-1.0);
const double eps = 1e-9;
const double INF = 1e18;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";


//Для работы с double
//В теории можно запариться с переопределением операторов
//Но так можно запутаться, думаю
double d_equal(const double a, const double b) {
	if (abs(a - b) < eps)
		return true;
	return false;
}
bool d_less(double a, double b) {
	if (!d_equal(a, b)) {
		return a < b;
	}
	else
		return false;
}
bool d_greater(double a, double b) {
	if (!d_equal(a, b)) {
		return a > b;
	}
	else
		return false;
}

//Angle normalization - нормализация/нормировка угла. 5pi == pi, например
//[mn,mx) - диапазон значений.
double norm_angle(double angle, double mn = 0, double mx = 2 * PI) {
	if (!d_equal(mx - mn, 2 * PI)) {
		//Если промежуток меньше 2PI, то в нормализации нет смысла
		return INF;
	}
	if (d_greater(angle, mx) || d_equal(angle, mx)) {//if(angle>=mx), короче
		int k = (angle - mx) / (2 * PI);
		angle = angle - k * 2 * PI;
		if (d_greater(angle, mx) || d_equal(angle, mx))
			angle -= 2 * PI;
	}
	if (d_less(angle, mn)) {
		int k = (mn - angle) / (2 * PI);
		angle = angle + k * 2 * PI;
		if (d_less(angle, mn))
			angle += 2 * PI;
	}
	return angle;
}
//Перевод градусы <-> радианы
double deg2rad(double angle) {
	return angle * PI / 180.0;
}
double rad2deg(double angle) {
	return angle / PI * 180.0;
}

//-------------------------------------------------------------------------------
//Нахождение полярного угла по координатам точки (угол между вектором (x,y) и Ох))
// 
//x = r*cos(angle)						   y.     .(x,y)
//y = r*sin(angle)							.	.
//atan2 -> (-PI,PI] -> нужна нормировка		. . angle
//angle = norm_angle(atan2(y,x))		   0. .	. .	. . . .x
//r = cos(angle) / x
//-------------------------------------------------------------------------------

//Структура двумерный вектор
struct vec2d {
	double x, y;

	vec2d(double _x, double _y) : x(_x), y(_y) {}
	vec2d() : x(0), y(0) {};

	//----------------------------------------------------
	//Перегрузка операторов
	friend vec2d operator + (vec2d& a, vec2d& b) {
		return vec2d(a.x + b.x, a.y + b.y);
	}
	friend vec2d operator - (vec2d& a, vec2d& b) {
		return vec2d(a.x - b.x, a.y - b.y);
	}
	friend bool operator == (vec2d& a, vec2d& b) {
		return d_equal(a.x, b.x) && d_equal(a.y, b.y);
	}
	friend vec2d operator *(vec2d& a, double b) {
		return vec2d(a.x * b, a.y * b);
	}
	friend vec2d operator *(double b, vec2d& a) {
		return vec2d(a.x * b, a.y * b);
	}
	//----------------------------------------------------

	//Скалярное произведение
	//dot(a,b) == len(a) * len(b) * cos(angle(a,b)) == формула ниже
	static double dot(vec2d& a, vec2d& b) {
		return a.x * b.x + a.y * b.y;
	}
	//Векторное произведение для 2д векторов (лишь скалярная длина)
	//Вспоминаем детерминант 2х2 ну или 3х3 с нулями
	//Площадь параллелограмма, образуемого этими векторами
	//cross(a,b) == len(a) * len(b) * sin(angle(a,b)) == формула ниже
	static double cross(vec2d& a, vec2d& b) {
		return a.x * b.y - a.y * b.x;
	}
	//Длина вектора. Выражение через скалярное произведение
	//Оттуда следует нужна формула по теореме Пифагора, если присмотреться
	static double len(vec2d& a) {
		return sqrt(dot(a, a));
	}
	//Угол между векторами. Выражение через скалярное произведение
	static double angle(vec2d& a, vec2d& b) {
		double phi = acos(dot(a, b) / (len(a) * len(b)));
		return norm_angle(phi);
	}
};
//Структура простой точки, не засоряю перегрузкой операторов
struct Point {
	double x, y;
	static double distance(Point& a, Point& b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	static double equal(Point& a, Point& b) {
		return d_equal(a.x, b.x) && d_equal(a.y, b.y);
	}
};

//Структура прямой
struct Line {
	double a, b, c;
	vec2d napr;//направляющий вектор
	vec2d norm;//нормаль

	Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) 
	{
		makevecs();
	};
	Line(const Point& first, const Point& second) {
		//Общее уравнение
		a = second.y - first.y;
		b = -(first.x - second.x);
		c = -a * first.x - first.y * b;
		makevecs();
	}
private:
	void makevecs() {
		napr = vec2d(-b, a);
		norm = vec2d(a, b);
	}
public:
	//Проверка параллельности двух прямых
	bool is_parallel(const Line& first, const Line& second) {
		return d_equal(first.a * second.b, second.a * first.b);
	}
	double distance(const Point& point, const Line& line) {
		//взять точку на прямой, найти вторую по направляющему вектору
		//по площади параллелограмма найти высоту
		//это и есть искомое расстояние



	}
	//расстояние между двумя прямыми
	double distance(const Line& first, const Line& second) {
		//Приравнять коэффициенты a и b
		//формула на http://www.cleverstudents.ru/line_and_plane/distance_between_parallel_lines.html


	}


};
//Площадь многоугольника по точкам на плоскости
//По алгоритму шнурования (Гаусса)
double square(vector<Point>& dots) {
	double res = 0;
	int n = dots.size();
	for (int i = 1; i < n; i++) {
		res += (dots[i - 1].x - dots[i].x) * (dots[i].y + dots[i - 1].y);
	}
	res += (dots[n - 1].x - dots[0].x) * (dots[n - 1].y + dots[0].y);
	cout << abs(res) / 2;
}

//СЛАУ 2х2 (в частности пересечения прямых)
Point SolveEq2XY(double a, double b, double e, double c, double d, double f) {
	//ax + by = e;
	//cx + dy = f
	double determinant = a * d - b * c;
	if (determinant != 0) {
		double x = (e * d - b * f) / determinant;
		double y = (a * f - e * c) / determinant;
		return { x,y };
	}
	else
		return { INF, INF };
	//По правилу Крамера 


}


void solve()
{
    // let's go kid
	cout << norm_angle(5 * PI) << ' ';
	cout << norm_angle(7 * PI) << ' ';
	cout << norm_angle(-3 * PI / 2) << ' ';
	cout << norm_angle(0) << ' ';
	cout << norm_angle(PI) << ' ';
	cout << norm_angle(5.0 / 2.0 * PI) << ' ';
	cout << norm_angle(2 * PI) << ' ';
	//
	cout << '\n';
	//
	cout << rad2deg(norm_angle(5 * PI, 2 * PI, 4 * PI)) << ' ';
	cout << rad2deg(norm_angle(7 * PI, PI / 2.0, 5.0 / 2.0 * PI)) << ' ';
	cout << rad2deg(norm_angle(-3 * PI / 2.0, -2 * PI, 0)) << ' ';
	cout << rad2deg(norm_angle(0, -5.0 / 2.0 * PI, -PI / 2.0)) << ' ';
	cout << rad2deg(norm_angle(PI, 31 * PI, 33 * PI)) << ' ';
	cout << rad2deg(norm_angle(5.0 / 2.0 * PI, 0, 2 * PI)) << ' ';
	cout << rad2deg(norm_angle(2 * PI)) << ' ';
	cout << '\n';
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    SPEEDTEST_START
    solve();
    SPEEDTEST_STOP
}