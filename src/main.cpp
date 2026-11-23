#include <iostream>

#include "analytics.hpp"
#include "barrier_pricer.hpp"
#include "hedging.hpp"

int main() {
    BarrierParams p;
    Grid g(p, 400, 400);
    std::vector<double> u = payoff(p, g);

    // quick check the grid looks right
    std::cout << "dx = " << g.dx << ", dtau = " << g.dtau << "\n";
    std::cout << "u at Smax = " << u[g.M] << "\n";

    // Phase 1: pricer
    // Phase 2: convergence study
    // Phase 3: Greeks profile
    // Phase 4: hedging sim
    // Phase 5: near-barrier breakdown
    // Phase 6: wrong-vol experiment
    // Phase 7: CFL demo

    return 0;
}
