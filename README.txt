-----------------------------------------------------------------------
Wizytowka Studenta

Wiktor Franus

-----------------------------------------------------------------------
Krotki opis problemu

Najkrótsza droga w mieście

Dany jest raster MxN o polach białych i czarnych. Opracować algorytm,
który znajdzie najkrótszą drogę z białego pola A do białego pola B, pod
warunkiem, że mozna się poruszać jedynie w pionie i w poziomie omjając
przy tym pola czarne. Przy generacji danych należy zwrócić uwagę, aby z
każdego pola białego można było się potencjalnie przedostać do dowolnego
innego pola o tym kolorze. Porównać czas obliczeń i wyniki różnych metod.

-----------------------------------------------------------------------
Informacja o mozliwych poleceniach w programie

Aby wyświetlić pomoc należy ruchomić program z parametrem -h.

Program należy uruchomić podając numer trybu jako pierwszy parametr.

Dostępne są 3 tryby uruchomienia:
1. Ręczne wczytywanie rastra.
2. Automatyczne generowanie rastra o zadanych parametrach.
3. Jak w trybie 2 + pomiary czasu wykonania dla każdego algorytmu.

Domyślnie program wyświetla okno z obrazkiem przedstawiającym znalezioną
ścieżkę (osobno dla każdego algorytmu). Można wyłączyć rysowanie urucha-
miając program z flagą -nd. Użycie tej flagi jest zalecane, gdy algorytmy
operują na rastrach o dużych rozmiarach (powyżej 40x40).

Program po utworzeniu okienka z obrazem czeka aż użytkownik zamknie to okno
(przy uzyciu myszki lub klawiszy ESC lub q) i dopiero wtedy kontynuuje swoje
działanie.
-----------------------------------------------------------------------
Konwencja we/wy

1. Należy podać kolejno:
    - szerokość rastra
    - wysokość rastra
    - wartości wszystkich pól rastra, wg konwencji:
        * 1 to bole białe, 0 pole czarne
        * liczby należy wpisywać wierszami, oddzielając każdą liczbę spacją
        * każdy wiersz powinien znajdować się w osobnej linii (Enter po
          każdym wierszu)
    - współrzędne x i y punktu startowego (białe pole, x-wiersz, y-kolumna)
      oddzielone spacją.
2. Należy podać:
    - liczbę testów
    - dla każdego testu:
        * szerokość rastra
        * wysokość rastra
        * pożądaną ilość pól białych (wierzchołków grafu)
        * pożądaną ilość połączeń między tymi polami (krawędzi grafu).
3. Tak samo jak w trybie 2.

Ścieżka znaleziona na rastrze wyświetlana jest przy pomocy biblioteki
CImg na ekran. W trybie 3 wyniki pomiarów prezentowane są w tabelach.

-----------------------------------------------------------------------
Krotki opis rozwiazania

Problem został rozwiązany przy użyciu 3 znanych algorytmów: przeszukiwania wszerz (BFS),
algorytmu Dijkstry oraz algorytmu A*.

Raster reprezentowany jest w programie przez dwuwymiarową, dynamicznie alokowaną tablicę
wypełnioną zeroma i jedynkami.

Odtworzenie znalezioniej ścieżki jest możliwe dzięki zapamiętywaniu wskazania na poprzednika
dla każdego pola rastra.

Wyświetlanie okna z obrazem przedstawiającym raster oraz znalezioną drogę zostało zrealizowane
przy użyciu biblioteki CImg składającej się z jednego pliku nagłówkowego, który został
dołączony do projektu.

-----------------------------------------------------------------------
Przewodnik po plikach zrodlowych

Raster.hpp - zawiera deklarację klasy reprezentującej raster

AlgorithmBase.hpp - zawiera deklaracje klas bazowych dla algorytmów przeszukiwania

BFS.hpp - zawiera deklarację klasy reprezentującej algorytm BFS wraz z implementacją funkcji
        przeszukującej

Dijkstra.hpp - zawiera deklarację klasy reprezentującej algorytm Dijkstry wraz z implementacją funkcji
        przeszukującej

A_star.hpp - zawiera deklarację klasy reprezentującej algorytm A* wraz z implementacją funkcji
        przeszukującej

draw.hpp - zawiera funkcję odpowiedzialną za rysowanie i wyświetlanie obrazu

AlgorithmBase.cpp - zawiera definicje metod klas bazowych dla algorytmów przeszukiwania

Raster.cpp -  zawiera definicje metod klasy reprezentującej raster

main.cpp - zawiera funkcję main wywołującą poszczególne tryby programu

-----------------------------------------------------------------------
Informacje dodatkowe :

Do generacji losowego wypełnienia rastra (przy ograniczeniach podanych w założeniach)
użyto zmodyfikowanej wersji algorytmu DFS z backtrackingiem.
