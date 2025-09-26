GDExample Node (extends Sprite2D)

Base idea:
It behaves like a normal Sprite2D but adds motion, rotation, pulsing, and signals so it can interact with other nodes.

Features:

Motion Path – The sprite orbits around a center point using adjustable amplitudes and speeds for X and Y.

Auto-Rotate – Rotates at a set degrees-per-second value.

Pulse Scale – Optionally grows and shrinks in size in a smooth wave pattern.

Editor Properties:

center, amplitude_x, amplitude_y, speed_x, speed_y → control the motion.

auto_rotate_speed_deg → controls rotation.

pulse_enabled, pulse_speed, pulse_amount → control the pulse effect.

ping_interval → sets how often the node emits a signal.

Signals:

example_ping(elapsed) → emitted every ping_interval seconds.

Public Method:

on_external_ping(msg, strength) → can be called by other nodes’ signals; makes the sprite flash, adjust rotation speed, and toggle pulsing.
