#pragma once

// delta hedging sim, do this after the pricer is validated
//
// - GBM paths (exact log step, fixed seed so runs are repeatable)
// - rebalance at discrete times using grid delta (interpolate in S)
// - knock-out: stop hedging + unwind if path hits B
// - P&L at expiry -> std / premium as the metric
// - then: vary rebalance freq, S0 ladder towards B, wrong vol
