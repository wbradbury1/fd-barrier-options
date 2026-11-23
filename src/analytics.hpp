#pragma once

// closed form stuff, only used to check the FD numbers against
//
// - normal cdf
// - black-scholes call (sanity check before the barrier one)
// - down-and-out call, method of images (essay sec 5.1)
// - exact values on the grid nodes at tau = T for the max-norm error
// - delta/gamma closed form later for the greeks check
