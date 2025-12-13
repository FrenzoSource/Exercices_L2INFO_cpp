#include <iostream>
#include <array>
#include <fstream>

const int TMAX = 100;
using Tab_string = std::array <std::string, TMAX>;
using Tab_int = std::array <int, TMAX>;



struct ArbreTab {
    int  n;
    int racine;   //compris entre 1 et n
    Tab_string tab_etiquette;           //tableau de chaine de caractères 
    Tab_int tab_gauche;                 //tableau d'entiers
    Tab_int tab_droite;
    Tab_int tab_pere;
};



ArbreTab construire_arbre(std::string fic) {
    ArbreTab arbre;
    std::ifstream var_flux;         //variable de flux pour l'ouverture du fichier
    var_flux.open(fic);
    if (var_flux.is_open()) {
        std::cout << "Ouverture du fichier de données réussit." << std::endl;
        
        var_flux >> arbre.n;
        var_flux >> arbre.racine;
        int indice = arbre.racine;
        while(var_flux.good()) {
            var_flux >> arbre.tab_etiquette[indice];
            var_flux >> arbre.tab_gauche[indice];
            var_flux >> arbre.tab_droite[indice];
            ++indice;
        };


        //on remplit tab_pere avec les informations que l'on vient d'obtenir
        arbre.tab_pere[1] = 0;
        for (int i = 1; i <= arbre.n; ++i) {
            for (int gauche = 1; gauche <= arbre.n; ++gauche) {
                if (arbre.tab_gauche[gauche] == i) {
                    arbre.tab_pere[i] = gauche;
                };
            };
            for (int droite = 1; droite <= arbre.n; ++droite) {
                if (arbre.tab_droite[droite] == i) {
                    arbre.tab_pere[i] = droite;
                };
            };
        };
    }
    else std::cout << "Echec de l'ouverture du fichier texte." << std::endl;
    return arbre;
}


void affichage_etiquette(ArbreTab arbre) {
    std::cout << "Affichage des etiquettes de l'arbre :" << std::endl;
    for (int i = 1; i <= arbre.n; ++i) {
        std::cout << arbre.tab_etiquette[i] << " ";
    };
}

void affichage_peres(ArbreTab arbre) {
    std::cout << "Affichage du tableau père de l'arbre :" << std::endl;
    for (int i = 1; i <= arbre.n; ++i) {
        std::cout << arbre.tab_pere[i] << " ";
    };
}


int profondeur_noeud(ArbreTab arbre, int indice) {
    int profondeur = 0;

    while (indice != arbre.racine && indice != 0) {
        indice = arbre.tab_pere[indice];
        ++profondeur;
    }

    return profondeur;
}






int main() {
    std::string fichier_data = "usine1.txt";

    ArbreTab arbre = construire_arbre(fichier_data);
    //affichage_etiquette(arbre);
    //affichage_peres(arbre);
    std::cout << "Profondeur de depot_c : " << profondeur_noeud(arbre, 7);
    return 0;
}

