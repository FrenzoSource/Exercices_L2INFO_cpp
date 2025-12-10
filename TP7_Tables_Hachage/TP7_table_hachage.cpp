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
    table.pos_libre = taille + (taille/100) * 15;

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
    int i = hachageBernstein(mot, table.m);
    if (table.T[i].occupe) {    // la case contient deja un mot
        if (table.T[i].mot == mot) ++table.T[i].occurences;
        else {     // le mot est different de celui de la première case
            while (table.T[i].suiv >= 0 && table.T[i].mot != mot) {
                //on doit verifier le cas ou si on croise le meme mot dans la case parcourut de notre tableau
                if (table.T[i].mot == mot)  {
                    ++table.T[i].occurences;
                    while (table.pos_libre >= 0 && table.T[table.pos_libre].occupe) --table.pos_libre;
                    return;
                }
                else i = table.T[i].suiv;
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
    std::cout << "Facteur de remplissage de la zone primaire : " << table.m << std::endl;
    std::cout << "Facteur de remplissage de la zone de reserve : 15%" << std::endl; 
    std::cout << "Facteur de remplissage total (zone primaire + zone total) : " << table.m + (table.m / 100) * 15 << std::endl;
}


//QUESTION 5
void ajout_fichier(std::string fic, tableHachage & table) {
    std::ifstream var_flux;
    var_flux.open(fic);
    if (var_flux.is_open()) {
        std::cout << "Ouverture du fichier réussit." << std::endl;
        std::string mot;
        var_flux >> mot;
        ajout(table, mot);
        while (var_flux.good()) {
            var_flux >> mot;
            ajout(table, mot);
        };
    }
    else std::cout << "Echec de l'ouverture du fchier de données." << std::endl;
}


//QUESTION 6
int occurence_mot(tableHachage & table, std::string mot) {
    /*Ici on recalcule la taille max de notre tableau car pos_libre que l'on utiliser pour la derniere case de libre de notrre tableau est modifié lors de l'ajout (voire derniere ligne question4) de valeur dans table de hachage*/
    int taille_tab = table.m + (table.m / 100) * 15;      // rappel: la taille est table.m
    for (int i = 0; i < taille_tab; ++i) {
        if (table.T[i].mot == mot) return table.T[i].occurences;
    };
    return 0;
}






int main() {
    std::string fichier_data = "bouledesuif.txt";
    std::string fic_data2 = "test.txt";
    int zone_primaire;    // zone primaire est la taille de notre table sans la réserve
    std::cout << "Saisir la taille de la zone primaire de la table de hachage : ";
    std::cin >> zone_primaire;

    tableHachage table = init_table(zone_primaire);


    ajout_fichier(fichier_data, table);
    affichage(table);

    std::string mot_rec;
    std::cout << "Saisir un mot a rechercher dans la table de hachage : ";
    std::cin >> mot_rec;
    std::cout << std::endl;
    std::cout << "Le mot " << mot_rec << " apparrait " << occurence_mot(table, mot_rec) << " fois." << std::endl;


    return 0;
}