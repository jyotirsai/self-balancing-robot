

class Motor {
    private:
        #define AIN1 7 // AIN1 pin on motor driver connects to D7 on arduino
        #define PWMA_LEFT 5 // PWMA pin -> D5
        #define BIN1 12 // BIN1 -> D12
        #define PWMB_RIGHT 6 // PWMB -> D6
        #define STBY_PIN 8 // STBY -> D8

    public:
        void pinInit(); // assign pins
        void Forward(int speed); // move forward
        void Reverse(int speed); // move in reverse

};
