#ifndef resource_class
#define resource_class

class Resource {
    private:
        int food;
        int fuel;
        int gold;
        int scrap_metal;
    
    public:
        Resource(int); // 0 -> SpaceShip,   1 -> Species,   2 -> Planet
        Resource(int, int, int, int);

        int get_food();
        int get_fuel();
        int get_gold();
        int get_scrap_metal();

        void getInfo();

        Resource* operator+(Resource*);
        Resource* operator-(Resource*);
};

#endif

