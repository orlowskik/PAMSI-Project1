#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>


/*
    Klasa definiujaca pakiet danych dla wyznaczonego zadania.
*/
class Package{
    private:    

        long unsigned int position; // pozycja pakietu
        char data;                  // przechowywany znak

    public:     // Interfejs publiczy klasy
        Package() {position = 0;data = ' ';};   // konstruktor klasy

        const int pos() const {return position;};     // Funkcja zwracajaca pozycje. Tylko do odczytu.
        const char show_data() const {return data;};   // Funkcaj zwracajaca dane. Tylko do odczytu.

        /*
            Funkcja zmieniajaca wartosci pol prywatnych.
            [in] char& c             - znak do wpisania
            [in] long unsigned int a - pozycja znaku

            [out] - brak. Funkcja void; 
        */
        void add_data(char& c, long unsigned int a) {data = c; position = a;};
        
        bool operator < (const Package& b) const; // Komparator pakietow 
        bool operator > (const Package& b) const; // Komparator pakietow
};


/*  
    Klasa definiujaca wezel listy dwukierunkowej przechowywujacej pakiety.
*/
class DNode{
    private:
        Package elem;   // Przechowywany pakiet
        DNode* next;    // Wskaznik do nastepnego wezla
        DNode* prev;    // Wskaznik do poprzedniego wezla
        friend class DLinkedList;

    public: // Interfejs klasy
        DNode(){next = nullptr;prev = nullptr ;elem = Package();};   //Konstruktor klasy ustawiajacy wzkazniki na NULL (ochrona przed zrzutem pamieci)
        DNode(const Package& e){next = nullptr;prev = nullptr ; elem = e;}; //Konstruktor parametryczny klasy


        const Package& getElement() const {return elem;}; // Funkcja zwracajaca element. Tylko do odczytu.
        DNode* getNext() const{return next;};             // Funkcja zwracajaca kolejny wezel. Tylko do odczytu.
        DNode* getPrev() const{return prev;};             // Funkcja zwracajaca poprzedni wezel. Tylko do odczytu.

        void setElem(Package newElem){elem = newElem;};   // Funkcja zmieniajaca wartosc elementu
        void setNext(DNode& newN){next = &newN;};         // Funkcja zmieniajaca wskaznik na kolejny wezel
        void setPrev(DNode& newP){prev = &newP;};         // Funkcja zmieniajaca wskaznik na poprzedni element
};

/*
    Klasa definiujaca dwukierunkowa liste, wykorzystujaca klase DNode. 
*/
class DLinkedList{
    private:
        DNode* head; // Wskaznik na pierwszy element
        DNode* tail; // Wskaznik na ostatni element

    public: // Interfejs klasy
        DLinkedList(){head = nullptr; tail = nullptr; }; // Konstruktor klasy.Ochrona przed zrzutem pamieci
        // Destruktor klasy. Zwalnia pamiec od poczatku listy 
        ~DLinkedList(){
            while(!empty()){
                removeFront();
            }
            delete head;delete tail;};


        bool empty() const {if(head == nullptr) return 1; return 0;}; // Funkcja sprawdzajaca, czy lista jest pusta
        const DNode& front() const {return *head;};  // Funkja zwracajaca pierwszy wezel. Tylko do odczytu
        const DNode& end()   const {return *tail;};  // Funkcja zwracajaca ostatni wezel. Tylko do odczytu
        void addFront(const Package& e);             // Funkcja dodajaca element na poczatek listy
        void addEnd(const Package& e);               // Funkcja dodajaca element na koniec listy
        void removeFront();                          // Funkca usuwajaca pierwszy element 
        void removeEnd();                            // Funkca usuwajaca ostatni element
        void removeElement(DNode* elem);             // Funkca usuwajaca wskazany element

};

/*
    Klasa abstrakcyjna opisujaca interfejs kolejki priorytetowej.
    Stworzona jako szablon, w celu uniwersyfikacji przechowywanych wartosci.
*/
template <typename TYPE>
class Prio_Queue{
    public:
        // Podstawowy interfejs kolejki priorytetowej jako funkcje wirtualne.
        virtual void insert(int k, TYPE element) = 0;
        virtual TYPE Min() const = 0;
        virtual TYPE removeMin() = 0;
        virtual bool isEmpty() = 0;
};


/*
    Szablon klasy wezla listy jednokierunkowej.
    Przechowuje dane oraz ich klucze (wagi).
*/
template <typename TYPE>
class PNode{
    private:
        int key;              // Priorytet danych
        TYPE data;            // Przechowywane dane
        PNode<TYPE>* next;    // Wskaznik na kolejny wezel
    public:
        // Iterfejs publiczny wezla
        PNode(){key = 0; data = TYPE(); next = nullptr;} //Konstruktor klasy. Ochrona przed zrzutem pamieci

        const TYPE& getElement() const {return data;};  // Funkcja zwracajaca dane. Tylko do odczytu
        int getKey() const {return key;};               // Funkcja zwracajaca klucz. Tylko do odczytu
        PNode<TYPE>* getNext() const{return next;};     // Funkcja zwracajaca kolejny wezel. Tylko do odczytu

        void setElem(TYPE newElem){data = newElem;};    // Funkcja zmieniajaca wartosc danych
        void setKey(int k){key = k;};                   // Funkcja zmieniajaca wartosc klucza
        void setNext(PNode<TYPE>& newN){next = &newN;}; // Funkcja zmieniajaca kolejny wezel 
};



/*
    Szablon klasy listy jednokierunkowej bedacej klasa pochodna Prio_Queue.
    Implementacja kolejki priorytetowej.
*/
template <typename TYPE>
class PrioList : public Prio_Queue<TYPE>{
    private:
        PNode<TYPE>* head;   // Wskaznik na pierwszy element
    public:
        PrioList(){head = nullptr;};  // Konstruktor listy. Ochrona przed zrzutem pamieci
        // Destruktor listy. zwalnia pamiec od poczatku listy, az bedzie pusta.
        ~PrioList(){
            PNode<TYPE>*tmp = head;
            while(head != nullptr){
                tmp = head;
                head = tmp->getNext();
                delete tmp;
            }
        }

        // Definicja interfejsu kolejki priorytetowej
        void insert(int k, TYPE element);
        TYPE Min() const;
        TYPE removeMin();
        bool isEmpty();
};


/*
    Funkcja dodajaca element do listy.
    Wartosci:
        [in] int k        - klucz danych
        [in] TYPE element - dane przechowywane w liscie
        [out] - brak
    Funkcja dodaje element na miejsce zgodne z jego kluczem.
    Wezel o najmniejszym kluczu jest przechowywany na poczatku   
*/
template <typename TYPE>
void PrioList<TYPE>::insert(int k, TYPE element){
    // Tworzenie nowego wezla
    PNode<TYPE>* newEl = new PNode<TYPE>();
    PNode<TYPE>* tmp = head;
    newEl->setElem(element);
    newEl->setKey(k);

    if(isEmpty())       // Jezeli lista jest pusta wstawia element na poczatek
        head = newEl;
    else if(k <= head->getKey()){   // Wstawianie na poczatek listy (najmniejsza wartosc klucza)
        newEl->setNext(*head);
        head = newEl;
    }
    else{       // Pzypadek poszukiwania miejsca
        if(tmp->getNext() != nullptr){          // Jezeli jest wiecej niz 1 element
            while(tmp->getNext()->getKey() < k ){   // Porownanie wartosci kluczy
                tmp = tmp->getNext();           
                if(tmp->getNext() == nullptr)       // Jezeli pszeszukana cala lista
                    break;
            }
            newEl->setNext(*(tmp->getNext()));   // Ustawienie kolejnego wezla dla nowego 
        }
        tmp->setNext(*newEl);       // Wstawienie nowego wezla w odpowiednie miejsce
    }
}

//Sprawdzenie czy kolejka jest pusta
template <typename TYPE>
bool PrioList<TYPE>::isEmpty(){
    if(head == nullptr)
        return true;
    return false;
}

/*
    Zwrocenie elementu o najmniejszym kluczu. Tylko do odczytu.
    !!!!!
    Warunek poczatkowy:
        Lista nie jest pusta
    !!!!!!!
*/
template <typename TYPE>
TYPE PrioList<TYPE>::Min() const{
    if(! (head == nullptr))
        return head->getElement();
    else
        return TYPE();
}

/*
    Zwrocenie elementu o najmniejszym kluczu i usuniecie go z listy.
    !!!!!!!!!!!
    Warunek poczatkowy:
        Lista nie jest pusta
    !!!!!!!!!!!!
*/
template <typename TYPE>
TYPE PrioList<TYPE>::removeMin(){
    TYPE element = TYPE();
    if(!isEmpty()){
        PNode<TYPE>* tmp = head;
        element = head->getElement();
        head = head->getNext();
        delete tmp;
    }
    return element;
}









