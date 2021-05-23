class mpu {
    public:
        void init(); // initializes mpu
        void retrieveData(); // retrieves raw accelerometer data
        void processData(); // processes raw accelerometer data

    public:
        double ax_raw, ay_raw, az_raw; // store raw accelerometer data
        double ax_g, ay_g, az_g; // stores g-forces
        double angleX, angleY, angleZ; // stores angles
};
