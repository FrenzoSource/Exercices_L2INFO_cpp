#include <iostream>
#include <string>
#include <fstream>

//QUESTION 1
struct occMot {
    int occurences;
    std::string mot;
    bool occupe;
    int suiv = -1;
};

struct tableHachage {
    occMot * T;
    int m;    //m zone primaire de hachage
    int pos_libre;
};


//QUESTION 2
tableHachage init_table(int taille) {
    tableHachage table;
    table.m = taille;
    table.pos_libre = (taille * 1.15) - 1;
    table.T = new occMot [table.pos_libre];
    //initialisation des alvéoles occmots
    for (int i = 0; i < table.pos_libre; ++i) {
        table.T[i].occupe = false;
        table.T[i].occurences = 0;
    };
    return table;
}

//QUESTION 3
int hachageBernstein(std::string mot, int m) {    //m est le facteur de compression
    int hash = 5381;
    for (unsigned int i = 0; i < mot.length(); ++i) {
        hash = (33 * hash + int(mot[i])) % m;
    };
    return hash;
}


//QUESTION 4
void ajout(tableHachage & table, std::string mot) {
    int i = hachageBernstein(mot, table.pos_libre);
    if (table.T[i].occupe) {    // la case contient deja un mot
        if (table.T[i].mot == mot) ++table.T[i].occurences;
        else {     // le mot est different de celui de la case
            while (table.T[i].suiv >= 0) {
                i = table.T[i].suiv;
            };
            table.T[i].suiv = table.pos_libre;
            i = table.pos_libre;
            table.T[i].mot = mot;
            table.T[i].occurences += 1;
            table.T[i].occupe = true;
        };
    }
    else {      //la case est vide 
        table.T[i].mot = mot;
        table.T[i].occupe = true;
        table.T[i].occurences = 1;
    };
    while (table.pos_libre >= 0 && table.T[table.pos_libre].occupe) --table.pos_libre;
}


//suplement
void affichage(tableHachage table) {
    std::cout << "Affichage des mots de notre table de hachage : " << std::endl;
    for (int i = 0; i < table.pos_libre; ++i) {
        std::cout << "mot indice " << i << ":" << table.T[i].mot << "  occurences:"<< table.T[i].occurences << std::endl;
    };
}


//QUESTION 5
void ajout_fichier(std::string fic, tableHachage & table) {
    std::ifstream var_flux;
    var_flux.open(fic);
    if (var_flux.is_open()) {
        std::cout << "Ouverture du fichier réussit." << std::endl;
        std::string mot;
        var_flux >> mot;
        while (var_flux.good()) {
            ajout(table, mot);
            var_flux >> mot;
        };
    }
    else std::cout << "Echec de l'ouverture du fchier de données." << std::endl;
}




int main() {
    std::string fichier_data = "bouledesuif.txt";
    int zone_primaire;    // zone primaire est la taile de notre table sans la réserve
    std::cout << "Saisir la taille de la zone primaire de la table de hachage : ";
    std::cin >> zone_primaire;
    tableHachage table = init_table(zone_primaire);

    /*     patie test pour question 4
    std::cout << "hachage de bernstein pour mot = hello: " << hachageBernstein("hello", table.pos_libre) << std::endl;
    std::cout << "hachage de bernstein pour mot = holla: " << hachageBernstein("holla", table.pos_libre) << std::endl;
    std::cout << "hachage de bernstein pour mot = bonjour: " << hachageBernstein("bonjour", table.pos_libre) << std::endl;
    ajout(table, "hello");
    ajout(table, "hello");
    ajout(table, "holla");
    ajout(table, "bonjour");
    */
    
    

    ajout_fichier(fichier_data, table);
    affichage(table);


    return 0;
}