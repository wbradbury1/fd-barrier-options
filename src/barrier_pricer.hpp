#pragma once

#include <cmath>
#include <vector>

// FD pricer for the down-and-out call
// log transform x = ln S so the PDE is constant coeff (essay eq 3.2):
//     u_tau = a u_xx + b u_x + c u,   a = sigma^2/2, b = r - sigma^2/2, c = -r
// domain [ln B, ln Smax], tau = time to maturity so payoff is the initial condition

struct BarrierParams {
    double K = 100.0;
    double B = 80.0;
    double r = 0.05;
    double sigma = 0.2;
    double T = 1.0;
    double Smax = 400.0;   // essay checked 200-800, 400 is fine
};

struct Grid {
    int M;        // space intervals, nodes 0..M
    int N;        // time steps
    double xmin, xmax, dx, dtau;
    std::vector<double> x;

    Grid(const BarrierParams& p, int M_, int N_) : M(M_), N(N_) {
        xmin = std::log(p.B);
        xmax = std::log(p.Smax);
        dx = (xmax - xmin) / M;
        dtau = p.T / N;
        x.resize(M + 1);
        for (int i = 0; i <= M; i++) x[i] = xmin + i * dx;
    }
};

// payoff at tau = 0, max(e^x - K, 0)
inline std::vector<double> payoff(const BarrierParams& p, const Grid& g) {
    std::vector<double> u(g.M + 1);
    for (int i = 0; i <= g.M; i++) u[i] = std::fmax(std::exp(g.x[i]) - p.K, 0.0);
    return u;
}
