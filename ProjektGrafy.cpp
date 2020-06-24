#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;

LARGE_INTEGER freq, starting, ending;
double mikrosekundy;
fstream plik;
bool wersja_deweloperska;
bool problem;
/*
Program mierzy czas wykonania wlasnorzecznie zaimplementowanych algorytmow Prima, Kruskala, Dijkstry, Bellmana-Forda
na zadanym przez uzytkownika grafie (bez uzycia STL).
*/
inline double stoptimer(){
			    QueryPerformanceCounter(&ending);
                mikrosekundy = ((ending.QuadPart - starting.QuadPart)*1000000.0) / freq.QuadPart;
                cout << endl << "Czas trwania: " << setprecision(9) << mikrosekundy << endl;
                if(!wersja_deweloperska)getche();
                return mikrosekundy;
                }
struct lista_jednokierunkowa_dane{
    int wierzcholek;
    int waga;
    lista_jednokierunkowa_dane *nastepny;
    ~lista_jednokierunkowa_dane(){delete nastepny;}
};
struct lista_jednokierunkowa{
    lista_jednokierunkowa_dane *head;
    lista_jednokierunkowa_dane *temp1;
    int rozmiar;
    lista_jednokierunkowa(){
        rozmiar=0;
        head=NULL;
        }
    ~lista_jednokierunkowa(){delete head;}
	void dodaj_wierzcholek(int punkt, int ciezar){
        temp1 = head;
        head = new lista_jednokierunkowa_dane;
        head->wierzcholek = punkt;
        head->waga = ciezar;
        head->nastepny = temp1;
        rozmiar++;
	}
    int na_pozycji(int pozycja, bool b=true){
	    temp1 = head;
	    for(int i=0; i<pozycja; i++){
            temp1=temp1->nastepny;
	    }
        if(b)return temp1->wierzcholek; else return temp1->waga;
    }
    bool wyszukaj(int wierzcholek){
    for(int i=0; i<rozmiar; i++){
        if (na_pozycji(i)==wierzcholek) return true;
    }
    return false;
    }
	void wyswietl(){
	    cout << endl;
	    temp1 = head;
	    for (int i=0; i<rozmiar; i++){
            cout << temp1->wierzcholek << ", ";
            cout << temp1->waga << " | ";
            temp1=temp1->nastepny;
	    }
	}
};

class grafy{
protected:
    int krawedzie;
    int wierzcholki;
    float gestosc;
    string typ;
    virtual double Prima(int poczatek) = 0;
    virtual double Kruskala() = 0;
    virtual double Dijkstry(int poczatek) = 0;
    virtual double Forda_Bellmana(int poczatek) = 0;
    virtual void wyswietl() = 0;
public:
    void menuX(){
        int zmienna;
	    plik.open("czasy.txt", ios::in | ios::out | ios::app);
	    if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
	    do{
        system("CLS");
        cout << "Wybierz operacje:" << endl;
        cout << "1 - algorytm Prima" << endl;
        cout << "2 - algorytm Kruskala" << endl;
        cout << "3 - wyswietl reprezentacje grafu" << endl;
        switch (getche()){
        case 49:
            cout << "Wybierz poczatkowy wierzcholek: ";
            cin >> zmienna;
            if(zmienna>=wierzcholki || zmienna<0) {cout << "Nie ma takiego wierzcholka!"; getche(); break;}
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+Prima(zmienna);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << Prima(zmienna);
            plik << endl << "---Koniec Pomiaru--- " << typ << ", algorytm Prima, liczba wierzcholkow: ";
            plik << wierzcholki << ", gestosc: " << gestosc << endl;
            break;
        case 50:
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+Kruskala();
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << Kruskala();
            plik << endl << "---Koniec Pomiaru--- " << typ << ", algorytm Kruskala, liczba wierzcholkow: ";
            plik << wierzcholki << ", gestosc: " << gestosc << endl;
            break;
        case 51:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
	}
    void menuY(){
        int zmienna;
	    plik.open("czasy.txt", ios::in | ios::out | ios::app);
	    if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
	    do{
        system("CLS");
        cout << "Wybierz operacje:" << endl;
        cout << "1 - algorytm Dijkstry" << endl;
        cout << "2 - algorytm Forda-Bellmana" << endl;
        cout << "3 - wyswietl reprezentacje grafu" << endl;
        switch (getche()){
        case 49:
            cout << "Wybierz poczatkowy wierzcholek: ";
            cin >> zmienna;
            if(zmienna>=wierzcholki || zmienna<0) {cout << "Nie ma takiego wierzcholka!"; getche(); break;}
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+Dijkstry(zmienna);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << Dijkstry(zmienna);
            plik << endl << "---Koniec Pomiaru--- " << typ << ", algorytm Dijkstry, liczba wierzcholkow: ";
            plik << wierzcholki << ", gestosc: " << gestosc << endl;
            break;
        case 50:
            cout << "Wybierz poczatkowy wierzcholek: ";
            cin >> zmienna;
            if(zmienna>=wierzcholki || zmienna<0) {cout << "Nie ma takiego wierzcholka!"; getche(); break;}
            if(wersja_deweloperska){
                double srednia=0;
                for (int i=0; i<100; i++){
                    srednia=srednia+Forda_Bellmana(zmienna);
                }
                srednia=srednia/100.00;
                plik << srednia;
            } else plik << Forda_Bellmana(zmienna);
            plik << endl << "---Koniec Pomiaru--- " << typ << ", algorytm Forda-Bellmana, liczba wierzcholkow: ";
            plik << wierzcholki << ", gestosc: " << gestosc << endl;
            break;
        case 51:
            wyswietl();
            break;
        case 27:
            plik.close();
            return;
        }
    }while(1);
    }
};

class graf_listowy : public grafy{ //lista nastepnikow
    lista_jednokierunkowa *graf;
    double Prima(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        lista_jednokierunkowa rozpinajace[wierzcholki];
        int indeks_rozp=0;
        int koniec;
        int mini=0;
        bool uzyte_wierzcholki[wierzcholki];
        for(int i=0; i<wierzcholki; i++) uzyte_wierzcholki[i]=false;
        int ilosc_uzytych_wierzcholkow=0;
        uzyte_wierzcholki[poczatek]=true;
        ilosc_uzytych_wierzcholkow++;
        while(ilosc_uzytych_wierzcholkow!=wierzcholki){
            for(int i=0; i<wierzcholki; i++){
                if(!uzyte_wierzcholki[i]) continue;
                for(int j=0; j<graf[i].rozmiar; j++){
                    if(!uzyte_wierzcholki[graf[i].na_pozycji(j)] && (mini == 0 || graf[i].na_pozycji(j, false)<mini)){
                        mini=graf[i].na_pozycji(j, false); koniec=graf[i].na_pozycji(j); poczatek=i;
                    }
                }
            }//tu wybrano juz krawedz o najmniejszej wadze
            rozpinajace[poczatek].dodaj_wierzcholek(koniec, mini);
            rozpinajace[koniec].dodaj_wierzcholek(poczatek, mini);
            ilosc_uzytych_wierzcholkow++;
            uzyte_wierzcholki[koniec]=true;
            mini=0;
        }
        wynik=stoptimer();
	    cout << endl;
		for (int i=0; i<wierzcholki; i++){
            cout << i <<" wierzcholek: ";
			rozpinajace[i].wyswietl();
			cout << endl;
		}
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Kruskala(){
        QueryPerformanceCounter(&starting);
        double wynik;
        lista_jednokierunkowa rozpinajace[wierzcholki];
        int mini=0;
        int poczatek;
        int koniec;
        bool *uzyte_wierzcholki = new bool[wierzcholki];
        int ilosc_uzytych_krawedzi=0;
        int posortowane[3][krawedzie];
        for(int i=0; i<3; i++){
            for(int j=0; j<krawedzie; j++){
                posortowane[i][j]=-1;
            }
        }
        int podgrafy[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            podgrafy[i]=i;
        }
        bool p=false;
        int ostatni=-1;
        int k=0;
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<graf[i].rozmiar; j++){
                if(graf[i].na_pozycji(j)>i){ //nie zostana wziete pod uwage krawedzie-petle
                    for(k=0; posortowane[0][k]>-1; k++){
                        if(posortowane[2][k]>graf[i].na_pozycji(j, false)){
                            for(int m=ostatni; m>=k; m--){
                                posortowane[0][m+1]=posortowane[0][m];
                                posortowane[1][m+1]=posortowane[1][m];
                                posortowane[2][m+1]=posortowane[2][m];
                            }
                            posortowane[0][k]=i;
                            posortowane[1][k]=graf[i].na_pozycji(j);
                            posortowane[2][k]=graf[i].na_pozycji(j, false);
                            p=true;
                            break;
                        }
                    }
                    if(!p){
                        posortowane[0][ostatni+1]=i;
                        posortowane[1][ostatni+1]=graf[i].na_pozycji(j);
                        posortowane[2][ostatni+1]=graf[i].na_pozycji(j, false);
                    }
                    ostatni++;
                    p=false;
                }
            }
        }
        int y=0;
        int pomoc;
        while(ilosc_uzytych_krawedzi!=wierzcholki-1){
                poczatek=posortowane[0][y];
                koniec=posortowane[1][y];
                mini=posortowane[2][y];
                if(podgrafy[poczatek]!=podgrafy[koniec]){
                    pomoc=podgrafy[koniec];
                    for(int i=0; i<wierzcholki; i++){
                        if(podgrafy[i]==pomoc) podgrafy[i]=podgrafy[poczatek];
                    }
                    rozpinajace[poczatek].dodaj_wierzcholek(koniec, mini);
                    rozpinajace[koniec].dodaj_wierzcholek(poczatek, mini);
                    ilosc_uzytych_krawedzi++;
            }
            y++;
        }
        wynik=stoptimer();
        cout << endl;
	    for (int i=0; i<wierzcholki; i++){
            cout << i <<" wierzcholek: ";
			rozpinajace[i].wyswietl();
            cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Dijkstry(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        bool nieprzetworzone[wierzcholki];
        int d[wierzcholki];
        bool d_nieskonczonosc[wierzcholki];
        int p[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            nieprzetworzone[i]=true;
            d_nieskonczonosc[i]=true;
            p[i]=-1;
        }
        d[poczatek]=0;
        d_nieskonczonosc[poczatek]=false;
        int mini;
        int mini_wierzcholek;
        int ilosc_uzytych_wierzcholkow=0;
        int sasiad;
        int waga_krawedzi;
        while(ilosc_uzytych_wierzcholkow<wierzcholki){
        mini=-1;
        for(int i=0; i<wierzcholki; i++){
            if(nieprzetworzone[i] && !d_nieskonczonosc[i] && (mini==-1 || d[i]<mini)){
                mini=d[i];
                mini_wierzcholek=i;
            }
        }
        nieprzetworzone[mini_wierzcholek]=false;
        ilosc_uzytych_wierzcholkow++;
        for(int i=0; i<graf[mini_wierzcholek].rozmiar; i++){
            sasiad=graf[mini_wierzcholek].na_pozycji(i);
            waga_krawedzi=graf[mini_wierzcholek].na_pozycji(i, false);
            if(waga_krawedzi<0) {cout << "Znaleziono ujemna wartosc wagi! Ten algorytm nie zadziala!"; wynik=stoptimer(); getche(); return wynik;}
            if(d_nieskonczonosc[sasiad] || d[sasiad]>d[mini_wierzcholek]+waga_krawedzi){
                d[sasiad]=d[mini_wierzcholek]+waga_krawedzi;
                d_nieskonczonosc[sasiad]=false;
                p[sasiad]=mini_wierzcholek;
            }
        }
        }
        wynik=stoptimer();
        cout << "   Wierzcholek  Koszt  Poprzednik" << endl;
	    for (int i=0; i<wierzcholki; i++){
            printf("%9d %9d %9d", i, d[i], p[i]);
            cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Forda_Bellmana(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        int tablica_krawedzi[3][krawedzie];
        int d[wierzcholki];
        bool d_nieskonczonosc[wierzcholki];
        int p[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            d_nieskonczonosc[i]=true;
            p[i]=-1;
        }
        d[poczatek]=0;
        d_nieskonczonosc[poczatek]=false;
        int indeks=0;
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<graf[i].rozmiar; j++){
                tablica_krawedzi[0][indeks]=i;
                tablica_krawedzi[1][indeks]=graf[i].na_pozycji(j);
                tablica_krawedzi[2][indeks]=graf[i].na_pozycji(j, false);
                indeks++;
            }
        }
        for(int e=0; e<krawedzie; e++){
            if(d_nieskonczonosc[tablica_krawedzi[1][e]] || d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                d[tablica_krawedzi[1][e]]=d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e];
                p[tablica_krawedzi[1][e]]=tablica_krawedzi[0][e];
            }
        }//wydzielilem to z ponizszej petli, bo w kolejnych obiegach dla grafu spojnego, ktory jest tu gwarantowany, nie trzeba sprawdzac d_nieskonczonosc
        for(int h=0; h<wierzcholki-2; h++){
            for(int e=0; e<krawedzie; e++){
                if(d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                    d[tablica_krawedzi[1][e]]=d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e];
                    p[tablica_krawedzi[1][e]]=tablica_krawedzi[0][e];
                }
            }
        }
        for(int e=0; e<krawedzie; e++){
            if(d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                cout << "Znaleziono ujemny cykl! Ten algorytm nie zadziala!";
                wynik=stoptimer();
                getche();
                return wynik;
            }
        }
        wynik=stoptimer();
        cout << "   Wierzcholek  Koszt  Poprzednik" << endl;
	    for (int i=0; i<wierzcholki; i++){
            printf("%9d %9d %9d", i, d[i], p[i]);
            cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    void wyswietl(){
	    cout << endl;
		for (int i=0; i<wierzcholki; i++){
            cout << i <<" wierzcholek: ";
			graf[i].wyswietl();
			cout << endl;
		}
		getch();
	}
public:
    graf_listowy(){
        typ="lista nastepnikow";
        int i, wierzcholek, waga;
        string tekst;
        plik.open("graf.txt");
        if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
        getline(plik, tekst, ' ');
        istringstream(tekst) >> krawedzie;
        getline(plik, tekst, '\n');
        istringstream(tekst) >> wierzcholki;
        gestosc = 2*krawedzie/(float)(wierzcholki*(wierzcholki-1))*100;
        graf = new lista_jednokierunkowa[wierzcholki];
        for(int j=0; j<krawedzie; j++){
            getline(plik, tekst, ' ');
            istringstream(tekst) >> i;
            getline(plik, tekst, ' ');
            istringstream(tekst) >> wierzcholek;
            getline(plik, tekst, '\n');
            istringstream(tekst) >> waga;
            graf[i].dodaj_wierzcholek(wierzcholek, waga);
            if(!problem && i!=wierzcholek) graf[wierzcholek].dodaj_wierzcholek(i, waga);
        }
        for(int i=0; i<wierzcholki; i++) if(graf[i].head==NULL) {cout << "Graf nie jest spojny! Zmien dane w pliku!"; getche(); _Exit(0);}
        plik.close();
    }
    graf_listowy(int w, float g){
        int pierwszy_w;
        int drugi_w;
        int waga;
        typ="lista nastepnikow";
        wierzcholki = w;
        gestosc = g;
        krawedzie = g*w*(w-1)/200;
        graf = new lista_jednokierunkowa[wierzcholki];
        for(int j=0; j<w-1; j++){
            waga=rand()%krawedzie+1;
            graf[j].dodaj_wierzcholek(j+1, waga);
            if(!problem) graf[j+1].dodaj_wierzcholek(j, waga);
        }//tu graf jest juz spojny
        for(int j=w-1; j<krawedzie; j++){
            pierwszy_w=rand()%wierzcholki;
            drugi_w=rand()%wierzcholki;
            waga=rand()%krawedzie+1;
            graf[pierwszy_w].dodaj_wierzcholek(drugi_w, waga);
            if(!problem && pierwszy_w!=drugi_w) graf[drugi_w].dodaj_wierzcholek(pierwszy_w, waga);
        }
    }
    ~graf_listowy(){delete [] graf;}
};

class graf_macierzowy : public grafy{ //macierz incydencji
    char **graf;
    int *wagi;
    double Prima(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        char rozpinajace[wierzcholki][wierzcholki-1];
        int indeks_rozp=0;
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<wierzcholki-1; j++){
                rozpinajace[i][j]=0;
            }
        }
        int rozpinajace_krawedzie[wierzcholki];
        int koniec;
        int mini=0;
        int krawedz;
        bool uzyte_krawedzie[krawedzie];
        for(int i=0; i<krawedzie; i++) uzyte_krawedzie[i]=false;
        bool uzyte_wierzcholki[wierzcholki];
        for(int i=0; i<wierzcholki; i++) uzyte_wierzcholki[i]=false;
        int ilosc_uzytych_wierzcholkow=0;
        uzyte_wierzcholki[poczatek]=true;
        ilosc_uzytych_wierzcholkow++;
        while(ilosc_uzytych_wierzcholkow!=wierzcholki){
            for(int i=0; i<wierzcholki; i++){
                if(!uzyte_wierzcholki[i]) continue;
                for(int j=0; j<krawedzie; j++){
                    if(uzyte_krawedzie[j]) continue;
                    if(graf[i][j]==1){
                        if(mini!=0){
                            if(wagi[j]<mini) {mini=wagi[j]; krawedz=j; poczatek=i;}
                        } else {mini=wagi[j]; krawedz=j; poczatek=i;}
                    }
                }
            }//tu wybrano juz krawedz o najmniejszej wadze
            for(int i=0; i<wierzcholki; i++){
                if(graf[i][krawedz]==1 && !uzyte_wierzcholki[i]){
                    ilosc_uzytych_wierzcholkow++;
                    rozpinajace[i][indeks_rozp]=1;
                    rozpinajace[poczatek][indeks_rozp]=1;
                    rozpinajace_krawedzie[indeks_rozp]=mini;
                    uzyte_wierzcholki[i]=true;
                    indeks_rozp++;
                    break;
                }
            }//tu juz dodalismy uzyty wierzcholek
            uzyte_krawedzie[krawedz]=true;
            mini=0;
            poczatek=-1;
        }
        wynik=stoptimer();
        cout << endl;
        for (int j=0; j<wierzcholki-1; j++){
			printf(" %9d", rozpinajace_krawedzie[j]);
		}
		cout << endl << endl;
	    for (int i=0; i<wierzcholki; i++){
		for (int j=0; j<wierzcholki-1; j++){
			printf(" %9d", rozpinajace[i][j]);
		}
		cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Kruskala(){
        QueryPerformanceCounter(&starting);
        double wynik;
        char rozpinajace[wierzcholki][wierzcholki-1];
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<wierzcholki-1; j++){
                rozpinajace[i][j]=0;
            }
        }
        int rozpinajace_krawedzie[wierzcholki-1];
        int podgrafy[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            podgrafy[i]=i;
        }
        int mini;
        int poczatek;
        int koniec;
        int posortowane[3][krawedzie];
        for(int i=0; i<3; i++){
            for(int j=0; j<krawedzie; j++){
                posortowane[i][j]=-1;
            }
        }
        bool p=false;
        int ostatni=-1;
        int k=0;
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<krawedzie; j++){
                if(graf[i][j]!=0){
                    for(int g=i+1; g<wierzcholki; g++){ //g=i+1 i takie zagnie¿d¿enie pêtli wyklucza wpisanie krawedzi-petli
                        if(graf[g][j]!=0){
                            for(k=0; posortowane[0][k]>-1; k++){
                                if(posortowane[2][k]>wagi[j]){
                                    for(int m=ostatni; m>=k; m--){
                                        posortowane[0][m+1]=posortowane[0][m];
                                        posortowane[1][m+1]=posortowane[1][m];
                                        posortowane[2][m+1]=posortowane[2][m];
                                    }
                                    posortowane[0][k]=i;
                                    posortowane[1][k]=g;
                                    posortowane[2][k]=wagi[j];
                                    p=true;
                                    break;
                                }
                            }
                            if(!p){
                                posortowane[0][ostatni+1]=i;
                                posortowane[1][ostatni+1]=g;
                                posortowane[2][ostatni+1]=wagi[j];
                            }
                            ostatni++;
                            p=false;
                        }
                    }
                }
            }
        }
        int ilosc_uzytych_krawedzi=0;
        int y=0;
        int pomoc;
        while(ilosc_uzytych_krawedzi!=wierzcholki-1){
            if(posortowane[0][y]!=posortowane[1][y]){
                poczatek=posortowane[0][y];
                koniec=posortowane[1][y];
                mini=posortowane[2][y];
                if(podgrafy[poczatek]!=podgrafy[koniec]){
                    pomoc=podgrafy[koniec];
                    for(int i=0; i<wierzcholki; i++){
                        if(podgrafy[i]==pomoc) podgrafy[i]=podgrafy[poczatek];
                    }
                    rozpinajace[poczatek][ilosc_uzytych_krawedzi]=1;
                    rozpinajace[koniec][ilosc_uzytych_krawedzi]=1;
                    rozpinajace_krawedzie[ilosc_uzytych_krawedzi]=mini;
                    ilosc_uzytych_krawedzi++;
                }
            }
            y++;
        }
        wynik=stoptimer();
        cout << endl;
        for (int j=0; j<wierzcholki-1; j++){
			printf(" %9d", rozpinajace_krawedzie[j]);
		}
		cout << endl << endl;
	    for (int i=0; i<wierzcholki; i++){
		for (int j=0; j<wierzcholki-1; j++){
			printf(" %9d", rozpinajace[i][j]);
		}
		cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Dijkstry(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        bool nieprzetworzone[wierzcholki];
        int d[wierzcholki];
        bool d_nieskonczonosc[wierzcholki];
        int p[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            nieprzetworzone[i]=true;
            d_nieskonczonosc[i]=true;
            p[i]=-1;
        }
        d[poczatek]=0;
        d_nieskonczonosc[poczatek]=false;
        int mini;
        int mini_wierzcholek;
        int ilosc_uzytych_wierzcholkow=0;
        bool b;
        while(ilosc_uzytych_wierzcholkow<wierzcholki){
        mini=-1;
        b=true;
        for(int i=0; i<wierzcholki; i++){
            if(nieprzetworzone[i] && !d_nieskonczonosc[i] && (mini==-1 || d[i]<mini)){
                mini=d[i];
                mini_wierzcholek=i;
            }
        }
        nieprzetworzone[mini_wierzcholek]=false;
        ilosc_uzytych_wierzcholkow++;
        for(int i=0; i<krawedzie; i++){
            if(wagi[i]<0) {cout << "Znaleziono ujemna wartosc wagi! Ten algorytm nie zadziala!"; wynik=stoptimer(); getche(); return wynik;}
            if(graf[mini_wierzcholek][i]>0){
                for(int j=0; j<wierzcholki && b; j++){
                    if(graf[j][i]<0 && (d_nieskonczonosc[j] || d[j]>d[mini_wierzcholek]+wagi[i])){
                        d[j]=d[mini_wierzcholek]+wagi[i];
                        d_nieskonczonosc[j]=false;
                        p[j]=mini_wierzcholek;
                        b=false;
                    }
                }
                b=true;
            }
        }
        }
        wynik=stoptimer();
        cout << "   Wierzcholek  Koszt  Poprzednik" << endl;
	    for (int i=0; i<wierzcholki; i++){
            printf("%9d %9d %9d", i, d[i], p[i]);
            cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    double Forda_Bellmana(int poczatek){
        QueryPerformanceCounter(&starting);
        double wynik;
        int tablica_krawedzi[3][krawedzie];
        int d[wierzcholki];
        bool d_nieskonczonosc[wierzcholki];
        int p[wierzcholki];
        for(int i=0; i<wierzcholki; i++){
            d_nieskonczonosc[i]=true;
            p[i]=-1;
        }
        d[poczatek]=0;
        d_nieskonczonosc[poczatek]=false;
        for(int i=0; i<krawedzie; i++){
            tablica_krawedzi[0][i]=-1; // zeby wykryc petle
            tablica_krawedzi[2][i]=wagi[i];
            for(int j=0; j<wierzcholki; j++){
                if(graf[j][i]==1) tablica_krawedzi[0][i]=j;
                if(graf[j][i]==-1) tablica_krawedzi[1][i]=j;
            }
            if(tablica_krawedzi[0][i]==-1) tablica_krawedzi[0][i]=tablica_krawedzi[1][i]; //dla petli
        }
        for(int e=0; e<krawedzie; e++){
            if(d_nieskonczonosc[tablica_krawedzi[1][e]] || d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                d[tablica_krawedzi[1][e]]=d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e];
                p[tablica_krawedzi[1][e]]=tablica_krawedzi[0][e];
            }
        }//wydzielilem to z ponizszej petli, bo w kolejnych obiegach dla grafu spojnego, ktory jest tu gwarantowany, nie trzeba sprawdzac d_nieskonczonosc
        for(int h=0; h<wierzcholki-2; h++){
            for(int e=0; e<krawedzie; e++){
                if(d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                    d[tablica_krawedzi[1][e]]=d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e];
                    p[tablica_krawedzi[1][e]]=tablica_krawedzi[0][e];
                }
            }
        }
        for(int e=0; e<krawedzie; e++){
            if(d[tablica_krawedzi[1][e]]>d[tablica_krawedzi[0][e]]+tablica_krawedzi[2][e]){
                cout << "Znaleziono ujemny cykl! Ten algorytm nie zadziala!";
                wynik=stoptimer();
                getche();
                return wynik;
            }
        }
        wynik=stoptimer();
        cout << "   Wierzcholek  Koszt  Poprzednik" << endl;
	    for (int i=0; i<wierzcholki; i++){
            printf("%9d %9d %9d", i, d[i], p[i]);
            cout << endl;
	    }
		if(!wersja_deweloperska)getch();
        return wynik;
    }
    void wyswietl(){
        cout << endl;
        for (int j=0; j<krawedzie; j++){
			printf(" %9d", wagi[j]);
		}
		cout << endl << endl;
	    for (int i=0; i<wierzcholki; i++){
		for (int j=0; j<krawedzie; j++){
			printf(" %9d", graf[i][j]);
		}
		cout << endl;
	    }
		getch();
	}
public:
    graf_macierzowy(){
        typ="macierz incydencji";
        int poczatkowy, koncowy, waga;
        string tekst;
        plik.open("graf.txt");
        if (!plik.is_open()) {cout << "Nie udalo sie otworzyc pliku!" << endl; _Exit(0);}
        getline(plik, tekst, ' ');
        istringstream(tekst) >> krawedzie;
        getline(plik, tekst, '\n');
        istringstream(tekst) >> wierzcholki;
        gestosc = 2*krawedzie/(float)(wierzcholki*(wierzcholki-1))*100;
        graf = new char*[wierzcholki];
        for(int j=0; j<wierzcholki; j++) graf[j] = new char[krawedzie];
        for(int j=0; j<wierzcholki; j++){
            for(int i=0; i<krawedzie; i++){
                graf[j][i]=0;
            }
        }
        wagi = new int[krawedzie];
        for(int j=0; j<krawedzie; j++){
            getline(plik, tekst, ' ');
            istringstream(tekst) >> poczatkowy;
            getline(plik, tekst, ' ');
            istringstream(tekst) >> koncowy;
            getline(plik, tekst, '\n');
            istringstream(tekst) >> waga;
            wagi[j] = waga;
            graf[poczatkowy][j] = 1;
            if(problem) graf[koncowy][j]=-1; else graf[koncowy][j]=1;
        }
        bool spojnosc=true;
        char spojne=0;
        for(int i=0; i<wierzcholki; i++){
            for(int j=0; j<krawedzie; j++){
                if(graf[i][j]!=0) spojne++;
            }
            if(spojne==0) spojnosc=false;
            spojne=0;
        }
        if(!spojnosc) {cout << "Graf nie jest spojny! Zmien dane w pliku!"; getche(); _Exit(0);}
        plik.close();
    }
    graf_macierzowy(int w, float g){
        typ="macierz incydencji";
        int waga;
        gestosc = g;
        wierzcholki = w;
        krawedzie = g*w*(w-1)/200;
        graf = new char*[wierzcholki];
        for (int j=0; j<wierzcholki; j++){
            graf[j] = new char[krawedzie];
        }
        for(int j=0; j<wierzcholki; j++){
            for(int i=0; i<krawedzie; i++){
                graf[j][i]=0;
            }
        }
        wagi = new int[krawedzie];
        for(int k=0; k<w-1; k++){
            waga=rand()%krawedzie+1;
            wagi[k]=waga;
            graf[k][k]=1;
            if(problem) graf[k+1][k]=-1; else graf[k+1][k]=1;
        }//tu graf jest juz spojny
        for(int k=w-1; k<krawedzie; k++){
            waga=rand()%krawedzie+1;
            wagi[k]=waga;
            graf[rand()%wierzcholki][k]=1;
            if(problem) graf[rand()%wierzcholki][k]=-1; else graf[rand()%wierzcholki][k]=1;
        }
    }
    ~graf_macierzowy(){
        for (int i=0; i<wierzcholki; i++){
            delete [] graf[i];
        }
        delete [] graf;
        delete [] wagi;
    }
};
graf_listowy *a;
graf_macierzowy *b;
void menu0();
void menu1();
void menu0(){
    do{
        system("CLS");
        cout << "Witaj! Program podaje czas trwania algorytmow grafowych w MIKROSEKUNDACH. " << endl
        << "Wersja deweloperska oblicza sredni czas, wykonujac 100 razy zadana operacje," << endl
        << "a wynik zapisuje do pliku czasy.txt" << endl
        << "Jaka wersje programu chcesz wlaczyc i jaki problem chcesz rozwiazac??" << endl;
        cout << "1 - Wyznaczanie minimalnego drzewa rozpinajacego, wersja normalna" << endl;
        cout << "2 - Wyznaczanie minimalnego drzewa rozpinajacego, wersja deweloperska" << endl;
        cout << "3 - Wyznaczanie najkrotszej sciezki w grafie, wersja normalna" << endl;
        cout << "4 - Wyznaczanie najkrotszej sciezki w grafie, wersja deweloperska" << endl;
        switch (getche()){
        case 49:
            problem=false;
            wersja_deweloperska=false;
            menu1();
            break;
        case 50:
            problem=false;
            wersja_deweloperska=true;
            menu1();
            break;
        case 51:
            problem=true;
            wersja_deweloperska=false;
            menu1();
            break;
        case 52:
            problem=true;
            wersja_deweloperska=true;
            menu1();
            break;
        case 27:
            return;
        }
    }while(1);
}
void menu1(){
    int w;
    float g;
    do{
        system("CLS");
        cout << "Wczytaj graf:" << endl;
        cout << "1 - z pliku graf.txt, lista nastepnikow" << endl;
        cout << "2 - losowe dane, lista nastepnikow" << endl;
        cout << "3 - z pliku graf.txt, macierz incydencji" << endl;
        cout << "4 - losowe dane, macierz incydencji" << endl;
        switch (getche()){
        case 49:
            a = new graf_listowy();
            if(!problem) a->menuX(); else a->menuY();
            delete a;
            break;
        case 50:
            cout << "Podaj ilosc wierzcholkow: ";
            cin >> w;
            if(w<2) {cout << "I jakiego rozwiazania sie spodziewasz?!" << endl; getche(); break;}
            cout << "Podaj gestosc: ";
            cin >> g;
            if(g*w*(w-1)/200<w-1){cout << "Za mala gestosc, zeby utworzyc graf spojny." << endl; getche(); break;}
            a = new graf_listowy(w, g);
            if(!problem) a->menuX(); else a->menuY();
            delete a;
            break;
        case 51:
            b = new graf_macierzowy();
            if(!problem) b->menuX(); else b->menuY();
            delete b;
            break;
        case 52:
            cout << "Podaj ilosc wierzcholkow: ";
            cin >> w;
            if(w<2) {cout << "I jakiego rozwiazania sie spodziewasz?!" << endl; getche(); break;}
            cout << "Podaj gestosc: ";
            cin >> g;
            if(g*w*(w-1)/200<w-1){cout << "Za mala gestosc, zeby utworzyc graf spojny." << endl; getche(); break;}
            b = new graf_macierzowy(w, g);
            if(!problem) b->menuX(); else b->menuY();
            delete b;
            break;
        case 27:
            return;
        }
    }while(1);
}
int main(){
    QueryPerformanceFrequency(&freq);
    menu0();
	return 0;
}
