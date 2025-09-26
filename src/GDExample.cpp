#include "GDExample.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <cmath>

using namespace godot;

static constexpr double PI_CONST = 3.14159265358979323846;

void GDExample::_bind_methods() {
	// DO NOT bind virtuals like _process/_ready/etc.

	// Properties
	ClassDB::bind_method(D_METHOD("set_center", "center"), &GDExample::set_center);
	ClassDB::bind_method(D_METHOD("get_center"), &GDExample::get_center);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "motion/center"), "set_center", "get_center");

	ClassDB::bind_method(D_METHOD("set_amplitude_x", "value"), &GDExample::set_amplitude_x);
	ClassDB::bind_method(D_METHOD("get_amplitude_x"), &GDExample::get_amplitude_x);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motion/amplitude_x", PROPERTY_HINT_RANGE, "0,1000,0.1"), "set_amplitude_x", "get_amplitude_x");

	ClassDB::bind_method(D_METHOD("set_amplitude_y", "value"), &GDExample::set_amplitude_y);
	ClassDB::bind_method(D_METHOD("get_amplitude_y"), &GDExample::get_amplitude_y);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motion/amplitude_y", PROPERTY_HINT_RANGE, "0,1000,0.1"), "set_amplitude_y", "get_amplitude_y");

	ClassDB::bind_method(D_METHOD("set_speed_x", "value"), &GDExample::set_speed_x);
	ClassDB::bind_method(D_METHOD("get_speed_x"), &GDExample::get_speed_x);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motion/speed_x", PROPERTY_HINT_RANGE, "0,50,0.01"), "set_speed_x", "get_speed_x");

	ClassDB::bind_method(D_METHOD("set_speed_y", "value"), &GDExample::set_speed_y);
	ClassDB::bind_method(D_METHOD("get_speed_y"), &GDExample::get_speed_y);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motion/speed_y", PROPERTY_HINT_RANGE, "0,50,0.01"), "set_speed_y", "get_speed_y");

	ClassDB::bind_method(D_METHOD("set_auto_rotate_speed_deg", "value"), &GDExample::set_auto_rotate_speed_deg);
	ClassDB::bind_method(D_METHOD("get_auto_rotate_speed_deg"), &GDExample::get_auto_rotate_speed_deg);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "features/auto_rotate_speed_deg", PROPERTY_HINT_RANGE, "-1080,1080,1"), "set_auto_rotate_speed_deg", "get_auto_rotate_speed_deg");

	ClassDB::bind_method(D_METHOD("set_pulse_enabled", "value"), &GDExample::set_pulse_enabled);
	ClassDB::bind_method(D_METHOD("get_pulse_enabled"), &GDExample::get_pulse_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "features/pulse_enabled"), "set_pulse_enabled", "get_pulse_enabled");

	ClassDB::bind_method(D_METHOD("set_pulse_speed", "value"), &GDExample::set_pulse_speed);
	ClassDB::bind_method(D_METHOD("get_pulse_speed"), &GDExample::get_pulse_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "features/pulse_speed", PROPERTY_HINT_RANGE, "0,50,0.01"), "set_pulse_speed", "get_pulse_speed");

	ClassDB::bind_method(D_METHOD("set_pulse_amount", "value"), &GDExample::set_pulse_amount);
	ClassDB::bind_method(D_METHOD("get_pulse_amount"), &GDExample::get_pulse_amount);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "features/pulse_amount", PROPERTY_HINT_RANGE, "0,5,0.01"), "set_pulse_amount", "get_pulse_amount");

	ClassDB::bind_method(D_METHOD("set_ping_interval", "seconds"), &GDExample::set_ping_interval);
	ClassDB::bind_method(D_METHOD("get_ping_interval"), &GDExample::get_ping_interval);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "signals/ping_interval", PROPERTY_HINT_RANGE, "0.05,10,0.01"), "set_ping_interval", "get_ping_interval");

	// Public callable for external signals
	ClassDB::bind_method(D_METHOD("on_external_ping", "msg", "strength"), &GDExample::on_external_ping);

	// Signal
	ADD_SIGNAL(MethodInfo("example_ping", PropertyInfo(Variant::FLOAT, "elapsed")));
}

GDExample::GDExample() {
	// Ensure _process runs
	set_process(true);
}

GDExample::~GDExample() {
}

void GDExample::_process(double delta) {
	time_passed += delta;
	ping_accumulator += delta;

	// Motion
	const double x = center.x + amplitude_x * std::sin(time_passed * speed_x);
	const double y = center.y + amplitude_y * std::cos(time_passed * speed_y);
	set_position(Vector2(x, y));

	// Auto-rotate
	if (auto_rotate_speed_deg != 0.0) {
		set_rotation_degrees(get_rotation_degrees() + auto_rotate_speed_deg * delta);
	}

	// Pulse scale
	if (pulse_enabled) {
		const double s = 1.0 + pulse_amount * std::sin(2.0 * PI_CONST * pulse_speed * time_passed);
		set_scale(Vector2((float)s, (float)s));
	}

	// Emit periodic signal
	if (ping_interval > 0.0 && ping_accumulator >= ping_interval) {
		ping_accumulator = 0.0;
		emit_signal("example_ping", (double)time_passed);
	}
}

// Setters/Getters (unchanged)
void GDExample::set_center(const Vector2& p_center) { center = p_center; }
Vector2 GDExample::get_center() const { return center; }

void GDExample::set_amplitude_x(double p_val) { amplitude_x = p_val; }
double GDExample::get_amplitude_x() const { return amplitude_x; }

void GDExample::set_amplitude_y(double p_val) { amplitude_y = p_val; }
double GDExample::get_amplitude_y() const { return amplitude_y; }

void GDExample::set_speed_x(double p_val) { speed_x = p_val; }
double GDExample::get_speed_x() const { return speed_x; }

void GDExample::set_speed_y(double p_val) { speed_y = p_val; }
double GDExample::get_speed_y() const { return speed_y; }

void GDExample::set_auto_rotate_speed_deg(double p_val) { auto_rotate_speed_deg = p_val; }
double GDExample::get_auto_rotate_speed_deg() const { return auto_rotate_speed_deg; }

void GDExample::set_pulse_enabled(bool p_val) { pulse_enabled = p_val; }
bool GDExample::get_pulse_enabled() const { return pulse_enabled; }

void GDExample::set_pulse_speed(double p_val) { pulse_speed = p_val; }
double GDExample::get_pulse_speed() const { return pulse_speed; }

void GDExample::set_pulse_amount(double p_val) { pulse_amount = p_val; }
double GDExample::get_pulse_amount() const { return pulse_amount; }

void GDExample::set_ping_interval(double p_val) { ping_interval = p_val; }
double GDExample::get_ping_interval() const { return ping_interval; }

void GDExample::on_external_ping(const String& msg, int strength) {
	UtilityFunctions::print("[GDExample] on_external_ping from: ", msg, " strength: ", strength);
	set_modulate(Color(1.0, 0.9, 0.9, 1.0));
	auto_rotate_speed_deg += (double)strength * 10.0;
	if ((strength % 2) != 0) {
		pulse_enabled = !pulse_enabled;
	}
}
