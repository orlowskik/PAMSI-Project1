#include<iostream>
#include<stdio.h>
#include<fstream>
#include<cstdlib>

#include"structures.h"



/*
    Funkcaj inicjujaca wiadomosc
    Parametry;
        [in] DLinkedList& list - lista, na ktora ma zostac wpisana wiadomosc
*/
bool init_message(DLinkedList& list){
    FILE* file;
    Package tmp;
    char c;
    long unsigned int i = 0;
    int los;


    file = fopen("send.txt","r");  // Plik, z ktorego czytana jest wiadomosc
    
    srand(time(NULL));             // LOsowanie potrzebne do imitacji przesylania pakietow w dowolnej kolejnosci      
    do
    {
        c = fgetc(file);         // Pobiera kolejny znak z wiadomosci
        if(c == EOF) break;      // Nie zapisuje warosci EOF
        tmp.add_data(c,i);       // TWorzenie paczki
        if(rand() % 2)           // Losowanie liczby 0 lub 1
            list.addFront(tmp);  // Dla 1 wstaw na poczatek
        else
            list.addEnd(tmp);    // Dla 0 wstaw na koniec
        ++i;
    }
    while (c != EOF);
    std::cout << i << std::endl;  // Pokazanie ilosci znakow (pomocniczo do okreslenia zlozonosci)
    
    fclose(file);         
    list.removeFront();
    
    return 1;
}







int main(){
    DLinkedList list;
    PrioList<char> r_mess;     // Zdefiniowanie szablonu dla listy (implementacji ADT)
    std::fstream writefile;    // Plik, z pszeslana wiadomoscia
    std::fstream checkfile;    // Plik pomocniczy pokazujacy, ze wiadomosc byla nieposortowana
    char c; 

    init_message(list);         // Inicjacja wiadomosci do listy

    writefile.open("receive.txt",std::ios::out);
    checkfile.open("encrypted.txt",std::ios::out);
    
    while(!list.empty()){
        r_mess.insert(list.front().getElement().pos(),list.front().getElement().show_data()); // Dodawanie danych do kolejki priorytetowej
        checkfile << list.front().getElement().show_data();  // Sprawdzanie losowej wiadomosci
        list.removeFront();  // usuniecie znaku z listy
    }
    while(!r_mess.isEmpty()){       // Zwracanie najmniejsego elementu i umieszczanie go w pliku 
        c = r_mess.removeMin();
        writefile << c;             // Po zakonczeniu wiadomosc powinna byc kopia oryginalu
    }
    writefile.close();
    checkfile.close();


    std::cout << "End Of Program\n";

    return 0;
}



