#include <iostream>
#include <array>
#include <fstream>

const int TMAX = 5;
using Tab_tirage = std::array <int, TMAX>;

struct date {
    int jours;
    int mois;
    int annee;
    date * suivant;
};
using liste_date = date *;


struct noeud {
    Tab_tirage tab_tirage;   //mon nom de var tab_tirage est mal choisit car 1 seul tableau par noeud -> jaurai du l'apeller 'tirage'
    liste_date liste;
    noeud * sag;
    noeud * sad;
};
using historique = noeud *;


//Question 2
void affichage_date(date date_saisie) {
    std::cout << date_saisie.jours << "-" << date_saisie.mois << "-" << date_saisie.annee << std::endl;
}

void affichage_liste_date(liste_date liste) {
    if (liste != nullptr) {
        affichage_date(*liste);
        affichage_liste_date(liste->suivant);
    };
}


liste_date init_liste_date() {
    liste_date liste;
    liste = nullptr;
    return liste;
}

void saisie_date(date & date1) {
    std::cout << "Saisir l'année de la date : ";
    std::cin >> date1.annee;
    std::cout << "Saisir le mois de la date : ";
    std::cin >> date1.mois;
    std::cout << "Saisir le jour de la date : ";
    std::cin >> date1.jours;
}

historique init_histoique() {
    historique hist = new noeud;
    hist->liste = init_liste_date();
    hist->sag = nullptr;
    hist->sad = nullptr;
    return hist;
}


int ordre_date(date date1, date date2) {
    if (date1.annee < date2.annee) return -1;
    else if (date1.annee > date2.annee) return 1;
    else {
        if (date1.mois < date2.mois) return -1;
        else if (date1.mois > date2.mois) return 1;
        else {
            if (date1.jours < date2.jours) return -1;
            else if (date1.jours > date2.jours) return 1;
        };
    };
    return 0;
}


int ordre_tirage(Tab_tirage tab1, Tab_tirage tab2) {
    for (int i = 0; i < 5; ++i) {
        if (tab1[i] < tab2[i]) return -1;
        else if (tab1[i] > tab2[i]) return 1;
        //On continue de parcourir les deux tirages pour comparer leur valeurs tant qu'elles ne sont pas égales
    };
    return 0;
}


void ajout_date(liste_date & liste, date date_saisie) {
    if (liste == nullptr) {
        liste = new date;
        liste->jours = date_saisie.jours;
        liste->mois = date_saisie.mois;
        liste->annee = date_saisie.annee;
        liste->suivant = nullptr;
    }
    else ajout_date(liste->suivant, date_saisie);
}



//QUESTION 4
void ajout_tirage(historique & hist, date date_saisie, Tab_tirage tirage_saisie) {
    if (hist == nullptr) {
        hist = init_histoique();
        ajout_date(hist->liste, date_saisie);
        hist->tab_tirage = tirage_saisie;
        hist->sag = nullptr;
        hist->sad = nullptr;
    }
    else if (ordre_tirage(tirage_saisie, hist->tab_tirage) == -1) ajout_tirage(hist->sag, date_saisie, tirage_saisie);
    else if (ordre_tirage(tirage_saisie, hist->tab_tirage) == 0) ajout_tirage(hist->sad, date_saisie, tirage_saisie);
    else ajout_date(hist->liste, date_saisie);
}


//QUESTION 5
void ajout_fichier(std::string fic, historique & hist) {
    std::ifstream var_flux;
    var_flux.open(fic);
    if (var_flux.is_open()) {
        std::cout << "Ouverture du fichier réussit." << std::endl;
        int elt;
        int indice_tab = 0;
        Tab_tirage tab_saisie;
        while(var_flux.good()) {
            
        }
    }
    else std::cout << "Echec de l'ouverture du fichier de données." << std::endl;
}


int main() {
    std::string fichier_data = "fake_loto.txt";

    /*
    date date1;
    date date2;
    saisie_date(date1);
    saisie_date(date2);

    liste_date listeDate = init_liste_date();
    ajout_date(listeDate, date1);
    ajout_date(listeDate, date2);
    std::cout << "Affichage de la liste date : ";
    affichage_liste_date(listeDate);
    */
    return 0;
}