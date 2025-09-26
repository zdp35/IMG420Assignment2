#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/color.hpp>

namespace godot {

	class GDExample : public Sprite2D {
		GDCLASS(GDExample, Sprite2D)

	private:
		// Time
		double time_passed = 0.0;
		double ping_accumulator = 0.0;

		// Motion (feature already present, now editor-configurable)
		Vector2 center = Vector2(10.0, 10.0);
		double amplitude_x = 10.0;
		double amplitude_y = 10.0;
		double speed_x = 2.0;
		double speed_y = 1.5;

		// Feature 1: Auto-rotate (degrees per second)
		double auto_rotate_speed_deg = 45.0;

		// Feature 2: Pulse scale
		bool   pulse_enabled = false;
		double pulse_speed = 2.0;   // Hz-ish
		double pulse_amount = 0.2;   // scale delta

		// Signal timer
		double ping_interval = 1.0; // seconds

	protected:
		static void _bind_methods();

	public:
		GDExample();
		~GDExample();

		void _process(double delta) override;

		// --- Setters/Getters for editor-exposed properties ---
		void set_center(const Vector2& p_center);
		Vector2 get_center() const;

		void set_amplitude_x(double p_val);
		double get_amplitude_x() const;

		void set_amplitude_y(double p_val);
		double get_amplitude_y() const;

		void set_speed_x(double p_val);
		double get_speed_x() const;

		void set_speed_y(double p_val);
		double get_speed_y() const;

		void set_auto_rotate_speed_deg(double p_val);
		double get_auto_rotate_speed_deg() const;

		void set_pulse_enabled(bool p_val);
		bool get_pulse_enabled() const;

		void set_pulse_speed(double p_val);
		double get_pulse_speed() const;

		void set_pulse_amount(double p_val);
		double get_pulse_amount() const;

		void set_ping_interval(double p_val);
		double get_ping_interval() const;

		// --- Public method intended to be connected to OTHER nodes' signals ---
		// Example: connect a Button.pressed() -> call("on_external_ping", "Button", 1)
		void on_external_ping(const String& msg, int strength);
	};

} // namespace godot
