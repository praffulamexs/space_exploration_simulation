#include "../../headers/all_imports.h"
#include "../../headers/classes/species_attributes.h"

SpeciesAttributes::SpeciesAttributes() {
    this->diplomacy = rand() % 100 + 1;
    this->trading = rand() % 100 + 1;
}

int SpeciesAttributes::get_diplomacy_score() {
    return this->diplomacy;
}

int SpeciesAttributes::get_trading_score() {
    return this->trading;
}
