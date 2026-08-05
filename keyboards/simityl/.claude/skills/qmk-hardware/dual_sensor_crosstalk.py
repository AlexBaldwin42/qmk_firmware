#!/usr/bin/env python3
"""
Cross-talk / bias analysis for the dual-sensor trackball.

Random noise (previous script) is NOT the thing that kills this design.
Systematic mismatch is: if the two sensors disagree slightly about scale or
orientation, pure ball ROLL leaks into the yaw estimate and the cursor
phantom-scrolls.  That is the failure mode users actually feel.

Two error sources modelled:

  1. CPI / gain mismatch  -- sensor 1 reads (1+eps) x truth.  Causes:
     unequal lens-to-ball standoff, part-to-part variation, surface quality.

  2. Mounting rotation error -- sensor 1 rotated by delta about its own
     normal relative to the assumed value.  Causes: assembly tolerance.

Metric: spurious omega_z produced per unit of genuine roll, i.e. the
phantom-scroll rate during ordinary cursor movement.
"""

import numpy as np

from dual_sensor_geometry import build_A, n_hat, tangent_basis, separation, metrics


def crosstalk_gain(theta, alpha, eps=0.05, delta_deg=3.0):
    """Return spurious-yaw-per-unit-roll for gain mismatch and rotation error."""
    sensors = [(theta, -alpha, 0.0), (theta, +alpha, 0.0)]
    A = build_A(sensors)
    Ainv = np.linalg.pinv(A)

    # --- 1. gain mismatch on sensor 1 (rows 2,3)
    S = np.diag([1.0, 1.0, 1.0 + eps, 1.0 + eps])
    E_gain = Ainv @ S @ A - np.eye(3)
    # spurious omega_z from unit omega_x / omega_y
    leak_gain = np.hypot(E_gain[2, 0], E_gain[2, 1])

    # --- 2. mounting rotation error on sensor 1
    A_true = build_A([(theta, -alpha, 0.0), (theta, +alpha, delta_deg)])
    E_rot = Ainv @ A_true - np.eye(3)
    leak_rot = np.hypot(E_rot[2, 0], E_rot[2, 1])

    return leak_gain, leak_rot


def yaw_signal_ratio(theta, alpha):
    """
    How large is the yaw channel relative to the cursor channels, for equal
    angular rates?  = ratio of column norms of A.  Higher is better: the yaw
    signal stands further above any fixed error floor.
    """
    A = build_A([(theta, -alpha, 0.0), (theta, +alpha, 0.0)])
    return np.linalg.norm(A[:, 2]) / np.linalg.norm(A[:, :2]) * np.sqrt(2)


print("=" * 86)
print("CROSS-TALK: spurious yaw per unit roll")
print("  eps   = 5% CPI mismatch between the two sensors")
print("  delta = 3 deg mounting rotation error on one sensor")
print("  'scroll @ 5%' = phantom scroll counts per 100 counts of cursor motion")
print("=" * 86)
print(f"{'theta':>6} {'alpha':>6} {'gamma':>7} {'yaw/cur':>8} "
      f"{'gain_z':>7} {'leak_5%':>8} {'leak_3deg':>10} {'scroll @5%':>11}")
print("-" * 86)

rows = []
for theta in [20, 30, 40, 50, 60, 70, 75, 80, 85, 90]:
    for alpha in [30, 45, 60]:
        lg, lr = crosstalk_gain(theta, alpha)
        m = metrics([(theta, -alpha, 0), (theta, +alpha, 0)])
        ysr = yaw_signal_ratio(theta, alpha)
        rows.append((theta, alpha, lg, lr, m, ysr))
        print(f"{theta:>6} {alpha:>6} {separation(theta,alpha):>7.1f} {ysr:>8.3f} "
              f"{m['gain_z']:>7.3f} {lg:>8.4f} {lr:>10.4f} {100*lg:>10.1f}%")

print()
print("=" * 86)
print("SWEET SPOT SEARCH  -- minimise the worst of {noise gains, cross-talk}")
print("=" * 86)
best = []
for theta in np.arange(45, 91, 2.5):
    for alpha in np.arange(25, 91, 2.5):
        m = metrics([(theta, -alpha, 0), (theta, +alpha, 0)])
        lg, lr = crosstalk_gain(theta, alpha)
        worst_noise = max(m["gain_x"], m["gain_y"], m["gain_z"])
        # combined score: noise must stay bounded, cross-talk minimised
        score = worst_noise + 4.0 * lg
        best.append((score, theta, alpha, m, lg, lr, worst_noise))

best.sort()
print(f"{'rank':>4} {'theta':>6} {'alpha':>6} {'gamma':>7} {'cond':>6} "
      f"{'gain_x':>7} {'gain_y':>7} {'gain_z':>7} {'leak_5%':>8}")
print("-" * 86)
for i, (sc, th, al, m, lg, lr, wn) in enumerate(best[:8]):
    print(f"{i+1:>4} {th:>6.1f} {al:>6.1f} {separation(th,al):>7.1f} {m['cond']:>6.2f} "
          f"{m['gain_x']:>7.3f} {m['gain_y']:>7.3f} {m['gain_z']:>7.3f} {lg:>8.4f}")

# ------------------------------------------------------------------ verdict
print()
print("=" * 86)
print("RETROFIT CHECK  -- can this work at conventional single-sensor depth?")
print("=" * 86)
for label, (th, al) in {
    "conventional cup depth (theta=20)": (20, 45),
    "shallow                (theta=35)": (35, 45),
    "recommended            (theta=75)": (75, 45),
    "theoretical optimum    (theta=90)": (90, 45),
}.items():
    m = metrics([(th, -al, 0), (th, +al, 0)])
    lg, lr = crosstalk_gain(th, al)
    print(f"{label}:  yaw noise gain {m['gain_z']:.3f}   "
          f"phantom scroll {100*lg:5.1f}% of cursor motion @ 5% CPI mismatch")

print()
print("Interpretation: 'phantom scroll X%' means that when the user moves the")
print("cursor 100 counts with a 5% sensor mismatch, X counts of unwanted scroll")
print("are generated.  Anything above a few percent needs an aggressive ratio")
print("gate to stay usable.")
