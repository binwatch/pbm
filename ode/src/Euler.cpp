#include <cmath>
#include <matplot/matplot.h>

int main() {

    double xc = 0, yc = 0;
    std::vector<double> theta = matplot::linspace(0, 2 * matplot::pi);

    matplot::figure();

    matplot::title("Inaccuracy of Euler Method");

    for (double r = 1.0; r < 5.0; r += 0.5) {
        std::vector<double> x =
            matplot::transform(theta, [=](auto theta) { return r * cos(theta) + xc; } );
        std::vector<double> y =
            matplot::transform(theta, [=](auto theta) { return r * sin(theta) + yc; } );
        matplot::plot(x, y, "k");
        matplot::hold(matplot::on);
    }
    
    double speed = 2.0;
    double a = matplot::pi / 2.0;
    double b = 2.0 * matplot::pi;

    for (double h = 0.05; h <= 0.3; h += 0.05) {
        std::vector<double> x;
        std::vector<double> y;
        double phi = matplot::pi;
        x.push_back(-1.0);
        y.push_back(0.0);
        for (int cnt = 0; cnt <= 50; cnt ++) {
            double vphi = phi - a;
            double vx = speed * cos(vphi);
            double vy = speed * sin(vphi);
            double nx = x[cnt] + h * vx;
            double ny = y[cnt] + h * vy;
            phi = atan(ny/nx);
            if (nx < 0.0) phi += matplot::pi;
            else if (ny < 0.0) phi += b;
            x.push_back(nx);
            y.push_back(ny);
        }
        auto p = matplot::plot(x, y);
        p->line_width(2);
        matplot::hold(matplot::on);
    }

    matplot::hold(matplot::off);
    matplot::axis(matplot::equal);

    matplot::save("img/Inaccuracy.png");

    return 0;
}