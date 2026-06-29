# Navya_ClimateControlProject
A temperature-based DC fan speed controller using Arduino Uno. Reads temperature via a sensor and controls fan speed with PWM. Fan stays OFF below 27°C, gradually increases speed up to 40°C where it hits maximum (PWM=255). Linear mapping formula used. Output printed every 500ms on Serial Monitor.
