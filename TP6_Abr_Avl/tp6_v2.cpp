#include <iostream>
#include <array>



const int N1 = 10;
using Tab = std::array<int, N1>;

struct noeud {
    int val;
    int hauteur=-1;
    noeud * sag;
    noeud * sad;
};
using abr = noeud *;



void ajouter(abr & arbre, int elt) {
    if (arbre == nullptr) {
        arbre = new noeud;
        arbre->val = elt;
        arbre->sag = nullptr;
        arbre->sad = nullptr;
    }
    else if (arbre->val >= elt) ajouter(arbre->sag, elt);
    else ajouter(arbre->sad, elt);
}


abr generer(Tab tab, int n) {
    abr arbre = nullptr;
    for (int i = 0; i < n; ++i) {
        ajouter(arbre, tab[i]);
    };
    return arbre;
}


void affichage_infixe(abr arbre) {
    if (arbre != nullptr) {
        affichage_infixe(arbre->sag);
        std::cout << "Valeur du noeud : " << arbre->val << ", adr noeud : " << arbre << ", adr sag:" << arbre->sag << ", adr sad:" << arbre->sad << " hauteur :" << arbre->hauteur << std::endl;
        affichage_infixe(arbre->sad);
    };
}



bool recherche (int e, abr a) {
    if (a == nullptr) return false ;
    else if (a->val == e) return true ;
    else if (a->val > e) return recherche(e, a->sag) ;
    else return recherche (e, a->sad) ;
}



//version remplacement par le predecesseur
abr supprimer(abr a, int e) {
    if (a == nullptr)
        return nullptr;

    if (e < a->val) {
        a->sag = supprimer(a->sag, e);
    }
    else if (e > a->val) {
        a->sad = supprimer(a->sad, e);
    }
    else {
        // ==== NOEUD TROUVÉ ====

        // Cas 1 : feuille
        if (a->sag == nullptr && a->sad == nullptr) {
            delete a;
            return nullptr;
        }

        // Cas 2 : un seul fils
        if (a->sag == nullptr) {
            abr temp = a->sad;
            delete a;
            return temp;
        }
        if (a->sad == nullptr) {
            abr temp = a->sag;
            delete a;
            return temp;
        }

        // Cas 3 : deux fils -> chercher prédécesseur
        abr p = a->sag;
        while (p->sad != nullptr)
            p = p->sad;

        // Remplacer par le prédécesseur
        a->val = p->val;

        // Supprimer prédécesseur dans sag
        a->sag = supprimer(a->sag, p->val);
    }
    return a;
}


/*-------------------------------------------------version remplacement par le successeur---------------------------------------
abr supprimer(abr a, int e) {
    if (a == nullptr)
        return nullptr;

    if (e < a->val) {
        a->sag = supprimer(a->sag, e);
    }
    else if (e > a->val) {
        a->sad = supprimer(a->sad, e);
    }
    else {
        // ==== NOEUD TROUVÉ ====

        // Cas 1 : feuille
        if (a->sag == nullptr && a->sad == nullptr) {
            delete a;
            return nullptr;
        }

        // Cas 2 : un seul fils
        if (a->sag == nullptr) {
            abr temp = a->sad;
            delete a;
            return temp;
        }
        if (a->sad == nullptr) {
            abr temp = a->sag;
            delete a;
            return temp;
        }

        // Cas 3 : deux fils -> chercher successeur
        abr p = a->sad;
        while (p->sag != nullptr)
            p = p->sag;

        // Remplacer par le prédécesseur
        a->val = p->val;

        // Supprimer prédécesseur dans sad
        a->sad = supprimer(a->sad, p->val);
    }
    return a;
}
*/



int somme_inf(abr arbre, int elt) {
    if (arbre == nullptr) return 0;
    if (arbre->val > elt) return 0 + somme_inf(arbre->sag, elt);
    else  return arbre->val + somme_inf(arbre->sag, elt) + somme_inf(arbre->sad, elt);

    return 0;
}



//QUESTION 8
void fusionner(abr & arbre1, Tab tab2, int taille_tab) {
    for (int i = 0; i < taille_tab; ++i) {
        ajouter(arbre1, tab2[i]);
    };
    std::cout << "Fusion réussit." << std::endl;
    affichage_infixe(arbre1);
}

//QUESTION 9
int hauteur(abr a) {
    if (a == nullptr) return -1;
    return 1 + std::max(hauteur(a->sag), hauteur(a->sad));
}




bool est_equilibre(abr a) {
    if (a == nullptr) return true;

    int hauteur_g = hauteur(a->sag);
    int hauteur_d = hauteur(a->sad);

    int facteur = hauteur_d - hauteur_g;

    if (facteur < -1 || facteur > 1)
        return false;

    // Vérifie récursivement
    return est_equilibre(a->sag) && est_equilibre(a->sad);
}


//QUESTION 11
void maj_hauteur_noeud(abr & arbre) {
    arbre->hauteur = hauteur(arbre);
}

void maj_hauteur_abr(abr & arbre) {
    if (arbre != nullptr) {
        maj_hauteur_abr(arbre->sag);
        maj_hauteur_abr(arbre->sad);
        maj_hauteur_noeud(arbre);
    };
    std::cout << "Mise a jour des hauteurs terminée." << std::endl;
}





int main() {
    Tab tab1 = {5, 3, 7, 1, 8, 10, 9, 5, 7, 7};
    abr arbre1 = generer(tab1, 10);
    Tab tab2 = {15 , 10 , 26 , 7 , 9 , 23 , 13 , 26 , 10 , 26};
    Tab tab3 = {11 , 4 , 15 , 3 , 7 , 17 , 6 };
    abr arbre3 = generer(tab3, 7);
    
    maj_hauteur_abr(arbre1);
    std::cout << "Affichage infixe de l'arbre 1 : " << std::endl;
    affichage_infixe(arbre1);
    

    /*
    int rec1 = 10;
    std::cout << "Element " << rec1 << " présent ? " << std::boolalpha << recherche(rec1, arbre1) << std::endl;
    */
    /*
    arbre1 = supprimer(arbre1, 3);
    std::cout << "Affichage infixe de l'arbre 1 : " << std::endl;
    affichage_infixe(arbre1);
    */

    /* Question 7
    std::cout << "Somme total des valeurs inf ou egales a 5 : " << somme_inf(arbre1, 5) << std::endl;
    */
    std::cout << "Equilibre ?" << std::boolalpha << est_equilibre(arbre3)  << std::endl;
    /*
    fusionner(arbre1, tab2, 10);
    */
    
    return 0;
}