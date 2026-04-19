#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Gör första bokstaven av namn stor, resten små
void storBokstav(char *s)
{
    s[0] = toupper(s[0]); // Gör första bokstaven stor

    for (int i = 1; s[i] != '\0'; i++) // Loopar igenom namnen efter första index / bokstav, slutar vid '\0'
    {
        s[i] = tolower(s[i]); // Gör resten av bokstäverna små
    }
}

// Funktion som kollar om sträng är alphabetic 0-127 ascii
int bokstavAZ(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        // Om namnet inte är alphabetic returnera 0
        if (!(isalpha(s[i])))
        {
            return 0;
        }
    }
    return 1;
}

// Läser in namn och resultat + Räkna summan och medelvärde
void namnOchProv(float medel[5], char namn[5][11], int prov[5][13], float *total)
{
    for (int i = 0; i < 5; i++) // For loop för 5 elever
    {
        scanf("%10s", namn[i]); // Spara namn med max 10 tecken

        if (!bokstavAZ(namn[i])) // Om namnet inte är gilltigt / alphabetic
        {
            exit(0); // Avsluta program
        }

        storBokstav(namn[i]); // Gör till stor bokstav

        int summa = 0;

        // For loop för 13 provresultat per elev
        for (int j = 0; j < 13; j++)
        {
            scanf("%d", &prov[i][j]); // Spara värdet
            summa += prov[i][j];      // Summera poängen
        }

        medel[i] = (float)summa / 13; // Räkna medelvärdet
        *total += medel[i];           // Spara till Total
    }
}

// Retunerar ording för högst medelvärde
int ordningMedel(float medel[5])
{
    // Börja med första eleven
    int maxIndex = 0;
    float max = medel[0];

    for (int i = 1; i < 5; i++)
    {
        if (medel[i] > max) // Leta efter högre medelvärde än max
        {                   // Om medelvärdet hittar större, uppdatera till max
            max = medel[i];
            maxIndex = i; // Uppdatera index
        }
    }
    return maxIndex; // Retunera nya index med högst värde
}

// Skriv ut elever under max medelvärdet
void elevMedel(char namn[5][11], float medel[5], float gruppMedel, int maxIndex)
{
    for (int i = 0; i < 5; i++)
    {
        if (i != maxIndex && medel[i] < gruppMedel) // Hitta elever under Max medelvärdet
        {
            printf("%s\n", namn[i]); // Skriv ut namn
        }
    }
}

int main()
{
    // NamnochProv variablar
    char namn[5][11];
    int prov[5][13];
    float medel[5];
    float total = 0;

    namnOchProv(medel, namn, prov, &total); // Kalla på Namn och prov och ge dem värderna

    int maxIndex = ordningMedel(medel); // Hitta bästa eleven
    float gruppMedel = total / 5;       // Räkna eleverna medelvärde

    printf("%s\n", namn[maxIndex]);               // Skriv ut bästa eleven
    elevMedel(namn, medel, gruppMedel, maxIndex); // Skriv ut dem under bästa eleven

    return 0;
}
