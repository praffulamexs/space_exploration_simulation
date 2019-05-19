#ifndef species_attributes_class
#define species_attributes_class

class SpeciesAttributes {
    protected:
        int diplomacy;
        int trading;

    public:
        SpeciesAttributes();

        int get_diplomacy_score();
        int get_trading_score();
};

#endif

