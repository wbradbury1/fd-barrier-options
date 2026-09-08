# FD Barrier Options + Delta-Hedging

**Build in progress**

This is a down-and-out barrier call pricer built on a log-transformed Black–Scholes PDE (using a Crank–Nicolson scheme with Rannacher start-up smoothing).

This project implements the numerical methods I analysed in [`essay.pdf`](./essay.pdf) where I compared Forward Euler, Backward Euler, Crank–Nicolson and Rannacher smoothing schemes for the barrier option PDE. This includes convergence behaviour, positivity/monotonicity, and start-up oscillation behaviour near the payoff kink. The essay is the theory; this repo will be the from-scratch C++ implementation of the schemes and the experiments that go with it, plus a few extensions beyond the essay such as a delta-hedging simulation, a near-barrier breakdown, and a wrong-vol P&L check (see roadmap below).

## Build and requirements

MSYS2 UCRT64 toolchain (`g++`, `gdb` on PATH).


```
g++ -std=c++17 -O2 -Wall -Wextra src/main.cpp -o main.exe
./main.exe
```

Writes CSVs to `output/`.

## Roadmap plan

1. **Pricer.** Log-space PDE, Crank–Nicolson, Rannacher, Thomas solver, barrier BC;
   read price + delta + gamma off the grid.
2. **Convergence study.** Max-norm error vs closed form; check against the rates in the essay (~2.4–3.0 over M=N=50→400).
3. **Greeks profile.** Delta and gamma across spot.
4. **Hedging simulation.** GBM paths, discrete delta-hedge, P&L distribution vs rebalancing frequency.
5. **Near-barrier breakdown.** Spot ladder S0 → B at fixed frequency, using std/premium as the metric.
6. **Wrong-vol experiment.** Systematic P&L bias when hedge vol ≠ realised vol.
7. **CFL demo.** Forward Euler just below and above `dt = dx²/(2a)`, showing why implicit schemes win here.

## Layout

| File | Purpose |
|------|---------|
| `main.cpp` | Driver — runs all experiments, writes CSVs |
| `barrier_pricer.hpp` | PDE solver (CN + Rannacher + Thomas + barrier BC) |
| `analytics.hpp` | Black–Scholes closed form, Greeks |
| `hedging.hpp` | Delta-hedging simulation, GBM paths |
| `plot.py` | Plotting |
| `essay.pdf` | Coursework essay this project implements |

## Technical notes

- Log transform (`x = ln S`) turns the Black–Scholes PDE into a constant-coefficient
  convection–diffusion–reaction equation.
- Rannacher smoothing: two half-step Backward Euler starts before switching to full Crank–Nicolson —
  kills the O(1) start-up oscillation from the payoff kink.
- Thomas (tridiagonal) solver: O(n) Gaussian elimination for the implicit systems each step.
- CFL stability limit for forward Euler: amplification factor G(π) = 1 − 4a·dt/dx² must stay ≥ −1,
  giving dt ≤ dx²/(2a); implicit methods sidestep this entirely.
- Near-barrier breakdown: leverage (delta·S/premium → ∞ as price → 0 at the barrier) plus knock-out
  gap risk means std/premium is the right hedging-error metric, not raw std.
  For a regular (non-reverse) barrier with B < K, the gamma spike sits near the strike, not at B.
- Discrete-monitoring gap: continuous-monitoring price vs a discretely-monitored simulation shows a
  systematic negative bias near the barrier.
- Wrong-vol P&L: a short option position loses money when realised vol exceeds implied
  (gamma cost outweighs theta income).
