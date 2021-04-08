/*************************************************************************/
/*  Program testowy dla obiektu X oprogamowania SPSym                    */
/*************************************************************************/
#include "spsym.h"         	// Pomocnicze funkcje i deklaracje
#include <stdio.h>         	// Stadnardowe I/O

// --- Makrodefinicje dla obiektu X ---
#define T  X8

#define Z1 Y1
#define Z2 Y2
#define Z3 Y3
#define Z4 Y4
#define Z5 Y5
#define M  Y6
#define G1 Y7

// --- Zmienne u¿ytkownika ---
int licz = 0;                	// Licznik przerwañ
char czOtw, czZam;
int tim1 = 0; tim2 = 0; diod = 0;
char kier = 0, silnik;
char stan = 1;

void prolog(void)			// Inicjowanie programu (jednorazowo przy starcie)
{
    L1 = L2 = L3 = L4 = 0;         	// Zgaszenie LED-ów
}

void oblicz(void)			// Kod u¿ytkownika wykonywany cyklicznie
{
    /*L1=aK1; L2=aK2; L3=aK3; L4=aK4;

    if(aK1) Z1 = 1; else Z1 = 0;
    if(aK2) Z2 = 1; else Z2 = 0;
    if(aK3) Z3 = 1; else Z3 = 0;
    if(aK4) G1 = 1; else G1 = 0;
    if(aK4) M  = 1; else M  = 0;

    if(licz >= 12000) licz=0;

    AO[0] += 100; AO[1] += 200;
    AO[2] += 300; AO[3] += 400;
    AO[4] += 500; AO[5] += 600;
    AO[6] += 700; AO[7] = licz/100;
    */
    czOtw = aK3;
    czZam = aK4;

    switch (stan)
    {
        /*
            case 1: // Oczekiwanie
                L1=0; L2=0; L3=0; L4=0;
                if(aK1&&!pK1) { tim1=100; tim2=(100-tim1)/10+1; kier=1; silnik=1; stan=2; }	// Otwórz
                if(aK2&&!pK2) { tim1=100; tim2=tim1/10+1; kier=0; silnik=1; stan=3; }	// Zamknij
                break;
            case 2: // Otwieranie
                L1=1; L2=0; L4=0;
                if(czOtw) { silnik=0; stan=1; }	// Stop
                if(aK2&&!pK2) { tim1=100; tim2=(100-tim1)/10+1; kier=0; silnik=1; stan=3; }	// Zamknij
                if(!tim2) { L3=!L3; tim2=tim1/10+1; }
                break;
            case 3: // Zamykanie
                L1=0; L2=1; L3=0;
                if(czZam) { silnik=0; stan=1; }	// Stop
                if(aK1&&!pK1) { tim1=100; tim2=tim1/10+1; kier=1; silnik=1; stan=2; }	// Zamknij
                if(!tim2) { L4=!L4; tim2=(100-tim1)/10+1; }
                break;
        */
    case 1: // oczekiwanie na uruchomienie urz¹dzenia przyciskiem aK1
        L1 = 0; L2 = 0; L3 = 0; L4 = 0; L5 = 0;
        if (aK1) { tim1 = 50; tim2 = 5; stan = 2; L5 = 1; };
        break;
    case 2: // uruchamianie przy uzyciu aK1 dok³adnie 5s
        L1 = 0; L2 = 0; L3 = 0; L4 = 0;
        if (!aK1) { stan = 1; }
        else if (!tim1) { stan = 3; tim2 = 20; L5 = 1; }
        else if (!tim2) { L5 = !L5; tim2 = (tim1 > 30) ? 15 : 5; };
        break;
    case 3: // oczekiwanie na puszczenie K1
        L1 = 0; L2 = 1; L3 = 0; L4 = 0;
        if (!aK1) { stan = 4; }
        else if (!tim2) { L5 = 0; };
        break;
    case 4: // urz¹dzenie w³¹czone, roleta opuszczona
        L1 = 0; L2 = 1; L3 = 1; L4 = 0; L5 = 0;
        if (aK1) { tim1 = 50; stan = 5; tim2 = 5; L5 = 1; }
        else if (aK2) { tim1 = 20; stan = 7; };
        // @TODO stan dalszy
        break;
    case 5: //wy³¹czanie urz¹dzenia
        L1 = 0; L2 = 1; L3 = 0; L4 = 0;
        if (!aK1) { stan = 4; }
        else if (!tim1) { stan = 6; tim2 = 20; L5 = 1; }
        else if (!tim2) { L5 = !L5; tim2 = (tim1 > 30) ? 15 : 5; };
        break;
    case 6: // oczekiwanie na puszczenie aK1
        L1 = 0; L2 = 0; L3 = 0; L4 = 0;
        if (!aK1) { stan = 1; }
        else if (!tim2) { L5 = 0; };
        break;
    case 7: // aktywowaniie podnoszenia rolety
        L1 = 0; L2 = 1; L3 = 1;
        if (!tim1) { stan = 17; kier = 1; }
        else if (tim1 && !aK2) { stan = 4; };
        break;
    case 8: // podnoszenie rolety do aK3
        L1 = 1; L2 = 1; L3 = 1;
        if (aK3) { stan = 9; }
        else if (!tim2) {
            tim2 = 4;
            L4 = !L4;
        };
        break;
    case 9: // podnoszenie rolety do aK4
        L1 = 1; L2 = 1; L3 = 1; L4 = 1;
        if (aK4) { stan = 10; tim2 = 5; L4 = 0; }
        else if (aK2) { stan = 13; tim2 = 5; }
        else if (!tim2) {
            tim2 = 4;
            L4 = !L4;
        };
        break;
    case 10: // roleta podniesiona, oczekiwanie na akcjê
        L1 = 0; L2 = 1; L3 = 1;
        if (aK2) { stan = 15; tim1 = 20; }
        else if (!tim2) {
            L4 = !L4;
            if (diod >= 5) {
                tim2 = 30;
                diod = 0;
            }
            else {
                tim2 = 5;
                diod++;
            }
        };
        break;
    case 11: // opuszczanie rolety do aK4
        L1 = 1; L2 = 1; L3 = 1;
        if (!aK4) { stan = 12; }
        else if (!tim2) {
            tim2 = 3;
            L4 = !L4;
        };
        break;
    case 12: // opuszczanie rolety do aK3
        L1 = 1; L2 = 1; L3 = 1;
        if (!aK3) { stan = 4; }
        else if (aK2) { stan = 13; tim2 = 5; }
        else if (!tim2) {
            tim2 = 2;
            L4 = !L4;
        };
        break;
    case 13: // roleta zatrzymana, oczekiwanie na puszczenie aK2
        L1 = 0; L2 = 1; L3 = 1;
        if (!aK2) stan = 14;
        else if (!tim2) { L4 = !L4; tim2 = 5; };
        break;
    case 14: // roleta zatrzymana oczekiwanie na ponown¹ aktywacjê
        L1 = 0; L2 = 1; L3 = 1;
        if (aK2) { stan = 16; }
        else if (!tim2) { L4 = !L4; tim2 = 5; };
        break;
    case 15: // ponowne aktywowanie rolety
        L1 = 0; L2 = 1; L3 = 1; L4 = 1;
        if (tim1 && !aK2) { stan = 10; }
        else if (!tim1) { stan = 17; kier = 0; };
        break;
    case 16: //ponowne aktywowanie rolety, oczekiwanie na puszczenie aK2
        L1 = 0; L2 = 1; L3 = 1;
        if (!aK2 && kier == 0) { stan = 9; }
        else if (!aK2 && kier == 1) { stan = 12; }
        else if (!tim2) { L4 = !L4; tim2 = 5; };
        break;
    case 17: // aktywowanie rolety, oczekiwanie na puszczenie aK2
        L1 = 1; L2 = 1; L3 = 1;
        if (!aK2 && kier == 1) { stan = 8; }
        else if (!aK2 && kier == 0) { stan = 11; }
        //else if(!tim2) {L4=!L4; tim2=5;};
        break;

    }
    //AO[0] = tim2*5;
    //L5=!L5;
    printf(&stan, "%c");
    sprintf(buf, "K1=%dK2=%dK3=%dK4=%d    ", (int)aK1, (int)aK2, (int)aK3, (int)aK4);
    LCD_xy(1, 1); LCD_puts(buf);
    sprintf(buf, "L1=%dL2=%dL3=%dL4=%dL5=%d    ", (int)L1, (int)L2, (int)L3, (int)L4, (int)L5);
    LCD_xy(1, 2); LCD_puts(buf);

    if (tim1) --tim1;
    if (tim2) --tim2;
}

void przerwanie(void)      	// Obs³ugs przerwania od uk³adu czasowo-licznikowego
{
    licz++;
}

void komunikacja(void)		// Obs³uga komunikacji szeregowej
{}

#ifdef Symulator_PC
void wykres(void)			// Dane do tabeli i wykresu (dot. symulacji obiektu)
{
    aTab[0] = (int)(AI[0] / 10.0);
    aTab[1] = (int)(AI[1] / 5.0);
    aTab[2] = AI[7];
    aTab[3] = (int)(licz / 100.0);
    aTab[4] = AO[0];
    aTab[5] = AO[7];
    aTab[6] = -120;
    aTab[7] = 120;

    bTab[0] = (int)aK1;
    bTab[1] = (int)aK2;
    bTab[2] = (int)aK3;
    bTab[3] = (int)aK4;
    bTab[4] = (int)L1;
    bTab[5] = (int)L2;
    bTab[6] = (int)L3;
    bTab[7] = (int)L4;
    bTab[8] = Z3;
    bTab[9] = G1;
    bTab[10] = M;
    bTab[11] = 11;
    bTab[12] = 12;
    bTab[13] = 13;
    bTab[14] = 14;
    bTab[15] = 15;
}
#endif
