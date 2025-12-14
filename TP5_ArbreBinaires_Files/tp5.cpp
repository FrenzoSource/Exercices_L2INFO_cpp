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




int profondeur_noeud(ArbreTab arbre, int indice) {
    int profondeur = 0;

    while (indice != arbre.racine && indice != 0) {
        indice = arbre.tab_pere[indice];
        ++profondeur;
    }

    return profondeur;
}





//QUESTION 4
void affichage_prefixe_tab(ArbreTab arbre, int indice_racine) {    //la racine est le noeud courant a afficher
    if (indice_racine == 0) return;      //si la racine est vide   ----->    indice==0 comme on commence a 1
    else {
        std::cout << "Etiquette : " << arbre.tab_etiquette[indice_racine] << "  etiquette_fg : " ;
        //<< arbre.tab_gauche[indice_racine] << "  etiquette_fd : " << arbre.tab_droite[indice_racine] << " "
        if (arbre.tab_gauche[indice_racine] != 0) std::cout << arbre.tab_etiquette[arbre.tab_gauche[indice_racine]] << " etiquette_fd : ";
        else std::cout << " *   etiquette_fd : ";

        if (arbre.tab_droite[indice_racine] != 0) std::cout << arbre.tab_etiquette[arbre.tab_droite[indice_racine]] << " pere : ";
        else std::cout << " *   pere : ";

        if (arbre.tab_pere[indice_racine] != 0) std::cout << arbre.tab_etiquette[arbre.tab_pere[indice_racine]] << " profondeur: ";
        else std::cout << " *   profondeur : ";

        std::cout << profondeur_noeud(arbre, indice_racine) << std::endl;

        //Parcours préfixe donc : affichage racine ---> sous arbre-gauche ----> sous arbre-droit
        affichage_prefixe_tab(arbre, arbre.tab_gauche[indice_racine]); 
        affichage_prefixe_tab(arbre, arbre.tab_droite[indice_racine]);
    };

}


void affichage_prefixe(ArbreTab arbre) {
    affichage_prefixe_tab(arbre, arbre.racine);
}




//PARTIE 2 REPRESENTATION CHAINEE D'UN ARBRE BINAIRE

//QUESTION 5
struct Noeud {
    std::string nom_lieu;
    Noeud * pere;
    Noeud * sag;
    Noeud * sad;
};
using ArbreBinaire = Noeud *;





//QUESTION 6
ArbreBinaire conversion_rec(ArbreTab abr_tab, int indice, Noeud * pere) {
    if (indice == 0) return nullptr;

    ArbreBinaire abr = new Noeud;
    abr->nom_lieu = abr_tab.tab_etiquette[indice];
    abr->pere = pere;

    abr->sag = conversion_rec(abr_tab, abr_tab.tab_gauche[indice], abr);
    abr->sad = conversion_rec(abr_tab, abr_tab.tab_droite[indice], abr);

    return abr;
}


void conversion(ArbreTab abr_tab, ArbreBinaire & abr_bin) {
    abr_bin = conversion_rec(abr_tab, abr_tab.racine, nullptr);
}






//QUESTION 7
bool estRacine (ArbreBinaire abr) {
    return abr->pere == nullptr; 
}

bool estFeuille (ArbreBinaire abr) {
    return abr->pere != nullptr && abr->sag == nullptr && abr->sad == nullptr ;
}


bool estNoeud (ArbreBinaire abr) {
    return abr->sag != nullptr && abr->sad != nullptr;
}

bool estFilsGauche (ArbreBinaire abr) {
    if (!estRacine(abr)) {
        ArbreBinaire abr_tmp = abr->pere;
        return abr_tmp->sag == abr;
    }
    else return false;
}

bool estFilsDroit (ArbreBinaire abr) {
    if (!estRacine(abr)) {
        ArbreBinaire abr_temp = abr->pere;
        return abr_temp->sad == abr;
    }
    else return false;
}



//SUPPLEMENT
void affichage_prefixe_bin(ArbreBinaire abr) {
    if (abr != nullptr) {
        std::cout << abr->nom_lieu << " ";
        affichage_prefixe_bin(abr->sag);
        affichage_prefixe_bin(abr->sad);
    };
}


//QUESTION 8
int calcul_feuille(ArbreBinaire abr) {
    if (!estFeuille(abr)) return calcul_feuille(abr->sag) + calcul_feuille(abr->sad);
    else return 1;
}




//QUESTION 9
void affichage_feuille(ArbreBinaire abr) {
    if (estFeuille(abr)) std::cout << abr->nom_lieu << " ";
    else {
        affichage_feuille(abr->sag);
        affichage_feuille(abr->sad);
    };
}



//QUESTION 10
int hauteur_arbre(ArbreBinaire abr) {
    if (abr==nullptr) return -1;
    else return 1 + std::max(hauteur_arbre(abr->sag), hauteur_arbre(abr->sad));
}


//QUESTION 11
ArbreBinaire recherche_etiquette(ArbreBinaire abr, std::string etiquette) {
    if (abr == nullptr) return nullptr;

    if (abr->nom_lieu == etiquette)
        return abr;

    ArbreBinaire res = recherche_etiquette(abr->sag, etiquette);
    if (res != nullptr)
        return res;

    return recherche_etiquette(abr->sad, etiquette);
}









int main() {
    std::string fichier_data = "usine1.txt";

    ArbreTab arbre = construire_arbre(fichier_data);
    //affichage_prefixe(arbre);

    ArbreBinaire arbre_bin;
    conversion(arbre, arbre_bin);
    //affichage_prefixe_bin(arbre_bin);
    
    //std::cout << "Nombre de feuilles de l'abre binaire : " << calcul_feuille(arbre_bin) << std::endl;
    //affichage_feuille(arbre_bin);

    std::cout << "Hauteur de l'arbre : " << hauteur_arbre(arbre_bin) << std::endl;

    return 0;
}

