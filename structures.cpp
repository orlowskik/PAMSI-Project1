#include "structures.h"

//Przeciazenie operatora porownujacego
bool Package::operator < (const Package& b) const{
    if(position < b.position)
            return true;
    return false;
}


//Przeciazenie operatora porownujacego
bool Package::operator > (const Package& b) const{
    if(position > b.position)
            return true;
    return false;
}


/*  
    Funkca dodajaca element na poczatek listy
    Parametry:
        [in] const Package& e - element do dodania
*/
void DLinkedList::addFront(const Package& e){
    DNode* tmp = new DNode; // Tworzy nowy wezel
    tmp->setElem(e);        // Ustawianie wartosci wezla
    if(empty()){            // Jezeli pusta ustawia poczatek i koniec na nowym elemencie
        tail = tmp;
    }
    else{                     // Ustawianie wskaznikow  
        head->setPrev(*tmp);
        tmp->setNext(*head);
    }
    head = tmp;
}


/*  
    Funkca dodajaca element na koniec listy
    Parametry:
        [in] const Package& e - element do dodania
*/
void DLinkedList::addEnd(const Package& e){
    DNode* tmp = new DNode; // Tworzenie nowego wezla
    tmp->setElem(e);        // Ustawianie wartosci wezla
    if(empty()){            // Jezeli pusta ustawia poczatek i koniec na nowym elemencie
        head = tmp;
    }
    else{                   // Wstawianie elementu na koniec listy
        tail->setNext(*tmp);
        tmp->setPrev(*tail);
    }
    tail = tmp;
}


/*
    Funkcja usuwajaca element z poczatku listy
*/
void DLinkedList::removeFront(){
    if(!empty()){               //Jezeli nie jest juz pusta
        DNode* tmpptr = head; 
        if(tail == head){       //Jezeli jest tylko jeden element 
            head = nullptr;
            tail = nullptr;
            delete tmpptr;
        }
        else{                   //Zmiana kolejnego wezla 
            head = head->next;
            head->prev = nullptr;
            delete tmpptr;     // Zwolnienie pamieci
        }
        
    }
    else{
        std::cout << "Lista jest pusta\n"; 
    }
}



/*
    Funkcja usuwajaca element z konca listy
*/
void DLinkedList::removeEnd(){
    if(!empty()){               // Jezeli nie jest juz pusta
        DNode* tmpptr = tail;  
        if(tail == head){      // Jezeli tylko jeden wezel
            head = nullptr;
            tail = nullptr;
            delete tmpptr;
        }
        else{                   // Zmiana przedostatniego wezla
            tail = tail->prev;
            tail->next = nullptr;
            delete tmpptr;      // Zwolnienie pamieci
        }
    }
    else{
        std::cout << "Lista jest pusta\n";
    }
}


/*
    Usuwanie podanego elementu
    Parametry:
        [in] DNode* elem - wezel przeznaczony do usuniecia
    !!!!!
    Warunek wstepny:
        Element musi nalezec do listy
    !!!!!
*/
void DLinkedList::removeElement(DNode* elem){
    if(empty()){            // Jezeli lista nie jest pusta
        std::cout << "Lista jest pusta\n";
    }
    else if(head == elem){  // Jezeli podano pierwszy element
        removeFront();
    }
    else if(tail == elem){ // Jezeli podana ostatni element
        removeEnd();
    }
    else{                // Zmiana wskaznikow elementow dookola
        elem->prev->setNext(*elem->next);
        elem->next->setPrev(*elem->prev);
        delete elem;     // Zwolnienie pamieci
    }
}



