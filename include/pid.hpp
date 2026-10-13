enum PID {
	LATERAL,
	ANGULAR,
	CORECTER,
	CASCADE
};

void drivePID(double inches);

void cascadePID(double inches);

void PID_tuning(PID type);

