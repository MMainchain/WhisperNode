class Bouton {

    public: 
        Bouton(int myPin);
        int getNumber();
        void check();

    
    private: 
        int count;
        int myPin;
        int lastState;
        int lastPressedTime;

};