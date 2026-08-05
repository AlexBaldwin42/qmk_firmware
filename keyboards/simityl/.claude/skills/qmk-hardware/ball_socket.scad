// ============================================================================
// Dual-sensor trackball socket  --  55mm SlimBlade-size ball, two PMW3389s
//
// Coordinate convention matches the geometry model:
//   theta = polar angle from the ball's BOTTOM pole (0 = directly under the
//           ball, 90 = equator)
//   phi   = azimuth from +Y (straight forward, away from user) toward +X (right)
//
// Placement transform for anything on the ball surface at (theta, phi):
//     rotate([0,0,-phi]) rotate([theta,0,0]) translate([0,0,-(r + offset)])
//   ...with the part built pointing +Z (toward the ball centre).
//
// !!! EVERY DIMENSION MARKED  <MEASURE>  IS A PLACEHOLDER. Verify against the
// !!! real parts before printing anything you intend to keep.
// ============================================================================

// ---------------------------------------------------------------- ball ------
ball_d          = 55.0;   // SlimBlade ball. <MEASURE> yours -- nominal only
ball_clear      = 0.6;    // radial air gap, ball to cup wall

// ------------------------------------------------------------- supports -----
// Following the SlimBlade's proven approach: 3 point supports.
n_supports      = 3;
support_theta   = 38;     // polar angle of the support ring
support_phi0    = 60;     // azimuth of first support (rotate to dodge sensors)
btu_body_d      = 7.938;  // <MEASURE> 5/16" BTU body
btu_ball_d      = 4.763;  // <MEASURE> 3/16" rolling ball
btu_depth       = 8.0;    // <MEASURE> press-fit bore depth
btu_proud       = 1.2;    // how far the BTU ball stands above the cup surface

// --------------------------------------------------------------- sensors ----
// LAYOUT: "asym"  = pole + equator   (Kensington-style, if FCC photos confirm)
//         "sym"   = symmetric pair   (theta=80, alpha=+-45)
// Both satisfy the 90-degree separation optimum. See the qmk-hardware skill.
layout          = "asym";

sym_theta       = 80;     // used when layout == "sym"
sym_alpha       = 45;

asym_pole_theta = 0;      // used when layout == "asym"
asym_eq_theta   = 85;     // push toward 90 as the shell allows
asym_eq_phi     = 0;      // phi=0 is +Y = FAR side, away from the hand.
                          // (phi=180 is the near side -- where fingers live.)

// PROVEN value from Alex's working Top55mmTrackball, measured in Fusion:
// 2.96mm from the *PCB face* to the ball surface. The lens protrudes into that
// gap. Do NOT "correct" this to the 2.4mm datasheet figure -- that spec is
// lens-bottom-to-surface, and this working part already settles the question.
lens_standoff   = 2.96;   // PCB face to ball surface
lens_bore_d     = 12.0;   // <MEASURE> clear aperture through to the ball
lens_body_w     = 19.0;   // <MEASURE> lens assembly footprint
lens_body_h     = 21.0;   // <MEASURE>
lens_body_t     = 3.5;    // <MEASURE> lens thickness below the PCB

pcb_w           = 21.0;   // <MEASURE> BastardKB sensor PCB
pcb_h           = 24.0;   // <MEASURE>
pcb_t           = 1.6;
pcb_clear       = 0.3;
screw_d         = 2.2;    // M2 clearance
screw_spacing_x = 15.0;   // <MEASURE> sensor PCB mounting holes
screw_spacing_y = 18.0;   // <MEASURE>

// ------------------------------------------------------------------ cup -----
rim_theta       = 62;     // cup wall stops here. MUST clear the sensors --
                          // see the conflict check echoed at render time.
wall            = 3.0;
base_z          = -34;    // flat underside of the block
block_xy        = 74;     // outer footprint (trim into your shell later)

// ------------------------------------------------------------- rendering ----
show_ball       = false;  // ghost ball + sensor axes for inspection
$fn             = 96;

r  = ball_d / 2;
rc = r + ball_clear;

// ============================================================================
// derived sensor list: [theta, phi, label]
// ============================================================================
sensors =
  layout == "sym"
    ? [ [sym_theta, -sym_alpha, "S0 sym-left"],
        [sym_theta, +sym_alpha, "S1 sym-right"] ]
    : [ [asym_pole_theta, 0,            "S0 pole"],
        [asym_eq_theta,   asym_eq_phi,  "S1 equator"] ];

// --- geometry report + conflict checks --------------------------------------
function nvec(t, p) = [ sin(t)*sin(p), sin(t)*cos(p), -cos(t) ];

sep = acos( max(-1, min(1,
        nvec(sensors[0][0], sensors[0][1]) * nvec(sensors[1][0], sensors[1][1])
      )));

echo(str("=== layout: ", layout));
echo(str("  sensor 0: theta=", sensors[0][0], " phi=", sensors[0][1]));
echo(str("  sensor 1: theta=", sensors[1][0], " phi=", sensors[1][1]));
echo(str("  angular separation = ", sep, " deg   (90 is optimal)"));
echo(str("  cup rim at theta=", rim_theta));

// A sensor buried below the rim is occluded by the cup wall.
for (s = sensors)
  if (s[0] > 0 && s[0] > rim_theta)
    echo(str("  NOTE: ", s[2], " at theta=", s[0],
             " sits ABOVE the rim (theta=", rim_theta,
             ") -- needs a turret or a rim cutout."));

if (abs(sep - 90) > 15)
  echo(str("  WARNING: separation ", sep,
           " deg is far from the 90 deg optimum -- conditioning degrades."));

// ============================================================================
// modules
// ============================================================================

// Place a child on the ball surface at (theta, phi), `off` beyond the surface.
module at_ball(theta, phi, off = 0) {
  rotate([0, 0, -phi])
    rotate([theta, 0, 0])
      translate([0, 0, -(r + off)])
        children();
}

// Negative volume for one sensor: lens bore + lens body + PCB recess + screws.
module sensor_cut(theta, phi) {
  at_ball(theta, phi, lens_standoff) {
    // clear optical path up to the ball
    translate([0, 0, -0.01]) cylinder(d = lens_bore_d, h = lens_standoff + 0.5);
    // lens body
    translate([0, 0, -lens_body_t])
      cube([lens_body_w, lens_body_h, lens_body_t + 0.02], center = true);
    // PCB recess
    translate([0, 0, -lens_body_t - (pcb_t + pcb_clear)/2])
      cube([pcb_w + pcb_clear*2, pcb_h + pcb_clear*2, pcb_t + pcb_clear],
           center = true);
    // exit slot for the ZIF flex -- just the cable, not the whole PCB
    translate([0, 0, -lens_body_t - pcb_t - 10])
      cube([12, pcb_h + pcb_clear*2, 20], center = true);
    // mounting screws
    for (sx = [-1, 1], sy = [-1, 1])
      translate([sx*screw_spacing_x/2, sy*screw_spacing_y/2, -lens_body_t - 12])
        cylinder(d = screw_d, h = 24);
  }
}

module support_cuts() {
  for (i = [0 : n_supports - 1])
    at_ball(support_theta, support_phi0 + i * 360/n_supports,
            -(btu_ball_d/2 - btu_proud))
      translate([0, 0, -btu_depth])
        cylinder(d = btu_body_d, h = btu_depth + 0.01);
}

// Seat + the clearance column above it.
// The ball lifts straight out for any rim_theta < 90 (the ball's cross-section
// at the rim plane only shrinks as it rises). rim_theta > 90 would trap it.
module cup_cavity() {
  sphere(r = rc);                               // spherical seat
  translate([0, 0, -rc*cos(rim_theta)])         // straight column, no flare --
    cylinder(r = rc, h = rc + 12);              // a cone here eats the block
}

// Solid material to host a sensor that sits above the cup rim.
// Hulls the sensor mounting pad back down onto the block, so the pocket has
// something to be cut out of. This is the piece that fights fingers and
// collects lint -- keep it as slim and as far from the hand as possible.
module sensor_pad(theta, phi) {
  depth = lens_body_t + pcb_t + 8;
  at_ball(theta, phi, lens_standoff)
    translate([0, 0, -depth/2])
      cube([pcb_w + wall*2, pcb_h + wall*2, depth], center = true);
}

module turret(theta, phi) {
  drop = 45;   // enough to always reach the block top
  intersection() {
    // vertical buttress: the sensor pad swept straight down
    hull() {
      sensor_pad(theta, phi);
      translate([0, 0, -drop]) sensor_pad(theta, phi);
    }
    // never extend below the block underside
    translate([-block_xy, -block_xy, base_z])
      cube([block_xy*2, block_xy*2, -base_z + 40]);
  }
}

module socket() {
  block_top = -r*cos(rim_theta) + 2;
  difference() {
    union() {
      // outer block -- boolean this into the real shell later
      translate([-block_xy/2, -block_xy/2, base_z])
        cube([block_xy, block_xy, block_top - base_z]);
      // turrets for any sensor above the rim
      for (s = sensors) if (s[0] > rim_theta) turret(s[0], s[1]);
    }
    cup_cavity();
    support_cuts();
    for (s = sensors) sensor_cut(s[0], s[1]);
  }
}

// ============================================================================
// output
// ============================================================================
socket();

if (show_ball) {
  %sphere(r = r);                                   // ghost ball
  for (s = sensors)                                 // sensor optical axes
    color("red") at_ball(s[0], s[1], lens_standoff)
      cylinder(d = 1.2, h = r, center = false);
  for (i = [0 : n_supports - 1])                    // support directions
    color("blue") at_ball(support_theta, support_phi0 + i*360/n_supports)
      cylinder(d = 1.0, h = r*0.5);
}
