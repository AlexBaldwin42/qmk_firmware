#!/usr/bin/env python3
"""
Dual-sensor trackball geometry model.

Frame: ball centre at origin. X = right, Y = forward (away from user), Z = up.
A sensor sits on the ball surface at unit direction n from the centre and looks
inward along -n.

theta = polar angle from the BOTTOM pole (-Z).  theta=0 is directly under the
        ball (the conventional single-sensor position); theta=90 is the equator.
phi   = azimuth from +Y (forward) toward +X (right).

Measurement model
-----------------
Surface velocity at the sensor point:  v = omega x (R n)
The sensor reports v projected onto its two in-plane axes (u, v) with
(u, v, n) right-handed.  Using the scalar triple product:

    m_u = u . (omega x R n) = R omega . (n x u) = R omega . v_hat
    m_v = v . (omega x R n) = R omega . (n x v) = -R omega . u_hat

so each sensor contributes two rows of a 4x3 matrix A, and m = A omega.

Key structural result (verified numerically below):

    A^T A = R^2 (2I - n1 n1^T - n2 n2^T)

This depends ONLY on the sensor positions n1, n2 -- not on the mounting
rotation psi about n.  So placement can be designed before the mounting
angles are ever measured.
"""

import numpy as np

R = 1.0  # ball radius; scales everything uniformly, irrelevant for conditioning


def n_hat(theta_deg, phi_deg):
    t, p = np.radians(theta_deg), np.radians(phi_deg)
    return np.array([np.sin(t) * np.sin(p), np.sin(t) * np.cos(p), -np.cos(t)])


def tangent_basis(n, psi_deg=0.0):
    """Orthonormal (u, v) spanning the tangent plane, rotated by psi about n."""
    ref = np.array([0.0, 0.0, 1.0])
    if abs(np.dot(ref, n)) > 0.99:
        ref = np.array([0.0, 1.0, 0.0])
    u = np.cross(ref, n)
    u /= np.linalg.norm(u)
    v = np.cross(n, u)
    c, s = np.cos(np.radians(psi_deg)), np.sin(np.radians(psi_deg))
    return c * u + s * v, -s * u + c * v


def build_A(sensors):
    """sensors: list of (theta, phi, psi). Returns 4x3 (or 2N x 3)."""
    rows = []
    for theta, phi, psi in sensors:
        n = n_hat(theta, phi)
        u, v = tangent_basis(n, psi)
        rows.append(R * v)       # row for the u-axis reading
        rows.append(-R * u)      # row for the v-axis reading
    return np.array(rows)


def metrics(sensors):
    A = build_A(sensors)
    AtA = A.T @ A
    inv = np.linalg.inv(AtA)
    # noise gain per axis: std of estimated omega_j for unit iid measurement noise
    gains = np.sqrt(np.diag(inv))
    return {
        "cond": np.linalg.cond(A),
        "gain_x": gains[0],
        "gain_y": gains[1],
        "gain_z": gains[2],   # <-- the scroll channel
        "pinv": np.linalg.pinv(A),
        "A": A,
    }


def separation(theta, alpha):
    """Angular separation gamma between two sensors at polar theta, azimuth +-alpha."""
    n1, n2 = n_hat(theta, -alpha), n_hat(theta, +alpha)
    return np.degrees(np.arccos(np.clip(np.dot(n1, n2), -1, 1)))


# ---------------------------------------------------------------- sanity checks
print("=" * 74)
print("STRUCTURAL CHECKS")
print("=" * 74)

# 1. A^T A is independent of mounting rotation psi
s_a = [(60, -55, 0), (60, +55, 0)]
s_b = [(60, -55, 37), (60, +55, -12)]   # same placement, wild mounting rotations
d = np.abs(build_A(s_a).T @ build_A(s_a) - build_A(s_b).T @ build_A(s_b)).max()
print(f"A^T A invariant to mounting rotation psi:      max diff = {d:.2e}")

# 2. closed form A^T A = R^2 (2I - n1 n1^T - n2 n2^T)
n1, n2 = n_hat(60, -55), n_hat(60, +55)
closed = R**2 * (2 * np.eye(3) - np.outer(n1, n1) - np.outer(n2, n2))
print(f"closed form matches numeric:                   max diff = "
      f"{np.abs(build_A(s_a).T @ build_A(s_a) - closed).max():.2e}")

# 3. antipodal placement is singular (shared blind axis)
anti = [(90, 0, 0), (90, 180, 0)]
print(f"antipodal (equator, 180 deg apart) cond(A):    {np.linalg.cond(build_A(anti)):.3e}  <- singular")

# 4. single sensor under the ball cannot see yaw at all
one = [(0, 0, 0)]
A1 = build_A(one)
print(f"single sensor at bottom pole, yaw column norm: {np.linalg.norm(A1[:, 2]):.2e}  <- blind to yaw")

# ------------------------------------------------------------------- the sweep
print()
print("=" * 74)
print("SWEEP  (yaw noise gain -- LOWER IS BETTER; this is the scroll channel)")
print("=" * 74)
print(f"{'theta':>6} {'alpha':>6} {'gamma':>7} {'cond':>7} {'gain_x':>8} {'gain_y':>8} {'gain_z':>8}")
print("-" * 74)

best = None
for theta in [30, 40, 45, 50, 55, 60, 65, 70, 75, 80, 90]:
    for alpha in [30, 45, 55, 60, 75, 90]:
        s = [(theta, -alpha, 0), (theta, +alpha, 0)]
        m = metrics(s)
        g = separation(theta, alpha)
        flag = ""
        if m["cond"] < 10 and m["gain_z"] < 1.0:
            flag = "  *"
            if best is None or m["gain_z"] < best[1]["gain_z"]:
                best = ((theta, alpha), m)
        print(f"{theta:>6} {alpha:>6} {g:>7.1f} {m['cond']:>7.2f} "
              f"{m['gain_x']:>8.3f} {m['gain_y']:>8.3f} {m['gain_z']:>8.3f}{flag}")

print()
print("* = well-conditioned AND yaw noise gain < 1.0")
print(f"\nBest yaw channel in sweep: theta={best[0][0]}, alpha=+-{best[0][1]}, "
      f"gain_z={best[1]['gain_z']:.3f}")

# --------------------------------------------------- mechanically-realistic pick
print()
print("=" * 74)
print("CANDIDATE GEOMETRIES")
print("=" * 74)

candidates = {
    "A  equator-ish, wide      (theta=75, alpha=+-60)": (75, 60),
    "B  balanced               (theta=65, alpha=+-65)": (65, 65),
    "C  shallower, wider       (theta=55, alpha=+-80)": (55, 80),
    "D  conventional depth     (theta=35, alpha=+-90)": (35, 90),
    "E  single-sensor depth    (theta=20, alpha=+-90)": (20, 90),
}
for name, (theta, alpha) in candidates.items():
    m = metrics([(theta, -alpha, 0), (theta, +alpha, 0)])
    print(f"{name}")
    print(f"     gamma={separation(theta, alpha):5.1f} deg   cond={m['cond']:5.2f}   "
          f"noise gain  x={m['gain_x']:.3f}  y={m['gain_y']:.3f}  z={m['gain_z']:.3f}")

# ------------------------------------------------------- firmware constants
print()
print("=" * 74)
print("FIRMWARE CONSTANTS  for candidate B (theta=65, alpha=+-65, psi=0)")
print("=" * 74)
theta, alpha = 65, 65
m = metrics([(theta, -alpha, 0), (theta, +alpha, 0)])
P = m["pinv"]
print("omega = P @ [s0_u, s0_v, s1_u, s1_v]")
print()
labels = ["omega_x (cursor R)", "omega_y (cursor F)", "omega_z (SCROLL) "]
for i, lab in enumerate(labels):
    print(f"  {lab}: [{P[i,0]:+.5f} {P[i,1]:+.5f} {P[i,2]:+.5f} {P[i,3]:+.5f}]")

print()
print("Q16 fixed point (int32 accumulate, >>16 at the end):")
for i, lab in enumerate(labels):
    q = [int(round(x * 65536)) for x in P[i]]
    print(f"  {lab}: {{{q[0]:+7d}, {q[1]:+7d}, {q[2]:+7d}, {q[3]:+7d}}}")

print()
print("Structure check -- is the naive sum/difference a good approximation?")
for i, lab in enumerate(labels):
    r = P[i]
    sym = np.allclose(r[:2], r[2:], atol=0.05)
    anti = np.allclose(r[:2], -r[2:], atol=0.05)
    kind = "SUM (common mode)" if sym else ("DIFFERENCE (antisym)" if anti else "mixed")
    print(f"  {lab}: {kind}")
