#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char Kelimeler[100][100], t[100];
int ifc=0;
    char search[20];
    int searcher=0;
    int ctrl;
    int ccc = 0;
int control();
int main(){
    //Step 1: We transferred the requested file to the array named maintxt
    char ch;
    char file_name[20];
    printf("Enter your file name: ");
    scanf("%s", file_name);
    printf("You use:  %s.\n\n", file_name);
    char maintxt[1000][100];
    int a;
    int sayac=0;
    int b=0;
    char eklenecekKelime[30];
    FILE *file;
    file=fopen(file_name,"r+");
    if(file == NULL)
    {
    printf("Input File Could Not Be Opened!\n");
    exit(1);
    }
    a=0;
    // printf("*******************************************************************\n");
    // printf("*********************Your maintxt is here**************************\n");
    // printf("*******************************************************************\n");
    while(b != EOF)
    {
        b = fscanf(file,"%s",eklenecekKelime);
        strcpy(maintxt[a],eklenecekKelime);
        sayac++;
        // printf("\n%s",maintxt[a]);
        a++;
    }
    fclose(file);
    // printf("\n******************************************************************\n");
    // printf("********************Your main txt is done**************************\n");
//Step 2: We transferred the ignore list to the array named ignoreList
	char ignoreList[1000][100];
    int x=0;
    int counter=0;
    int y=0;
    char addword[20];
    FILE *file_pointer;
    file_pointer=fopen("ignoreList.txt","r");
    if(file_pointer == NULL)
    {
    printf("Input File Could Not Be Opened!\n");
    exit(1);
    }
    x=0;
    // printf("\n*******************************************************************\n");
    // printf("******************your ignore list is here*************************\n");
    // printf("******************************************************************\n");
    while(y != EOF)
    {
        y = fscanf(file_pointer,"%s",addword);
        strcpy(ignoreList[x],addword);
        counter++;
        // printf("\n%s",ignoreList[x]);
        x++;
    }
    fclose(file_pointer);
//Step 3: address the words on the ignorelist
    // printf("********************************************************************\n");
    // printf("*********************your ignore list is done***********************\n");
    int m=0,n=0;
    char cleanList[300][100];
    int sonuc;
    int finder=0;
    // printf("*******************************************************************\n");
    // printf("**********************Your cleanList is here*************************\n");
    // printf("******************************************************************\n");
    for(m=0; m<sayac;m++)
    {
        finder=0;
        for(n=0; n<counter; n++)
        {
            sonuc= strcmp(maintxt[m],ignoreList[n]);
            if (sonuc == 0 || !strcmp(maintxt[m],".")|| !strcmp(maintxt[m],",") )
            {
                finder=1;
            }
        }
        if (finder==0)
        {
            ifc++;
            strcpy(cleanList[ifc],maintxt[m]);
        }
    }
    // for(m=0; m<ifc; m++)
    // {
    //     printf(" %s \n",cleanList[m]);
    // }
//Step 4: Order the words.
    // printf("*******************************************************************");
    // printf("\n*****************ORDER OF WORDS HERE*********************\n");
    // printf("******************************************************************\n");
    for (x = 0; x < ifc; x++)
        {strcpy(Kelimeler[x],cleanList[x]);}
    for (x = 1; x < 100; x++)
    {
        for (y = 1; y < ifc; y++)
        {
            if (strcmp(Kelimeler[y - 1], Kelimeler[y]) > 0)
            {
                strcpy(t, Kelimeler[y - 1]);
                strcpy(Kelimeler[y - 1], Kelimeler[y]);
                strcpy(Kelimeler[y], t);
            }
        }
    }
    // for (x = 0; x < ifc; x++)
    // {
    //     printf("\n%s", Kelimeler[x]);
    // }
    printf("*******************************************************************");
    printf("\n*****************FREQUENCY OF WORDS HERE*********************\n");
    printf("******************************************************************\n");

    FILE *wordfile;
    wordfile = fopen("word.txt", "w");
    char freq[100];
    int value1 = 0,value2 = 0;
    int frequency_counter = 1;
    int que=0;
    int cikar = 0;
    for(value1=0; value1<ifc; value1++)
    {
        frequency_counter = 1;
        cikar = 0;
        for (value2 = value1 + 1; value2 < ifc; value2++)
        {
            int frequency = strcmp(Kelimeler[value1], Kelimeler[value2]);
            if (frequency == 0)
            {
                frequency_counter++;
            }
        }
        value1 += frequency_counter - 1;
        printf("%d: %s\n", frequency_counter, Kelimeler[value1]);
        fprintf(wordfile, "%s,%d\n", Kelimeler[value1], frequency_counter);
        que++;
    }
    fclose(wordfile);
    int makecontrol = 0;
    // printf("%d  %d", ccc,ifc);
    do
    {
        searcher = 0;
        makecontrol = 0;
        ccc = 0;
        printf("\nEnter the word you want to search:\nEnter 0 to exit ");
        scanf("%s",search);
        if (strcmp(search,"0") == 0){break;}
         makecontrol = control();
        if (makecontrol == 1)
        {
            printf("The word you are looking for is exist in the txt file\n");
        }
        else
        {
            printf("The word you are looking for is not exist in the txt file\n");
        }
    }
    while(1);

    printf("exited the search engine\n");
}
//Step 5: Check if the desired word exists
int control()
{
    if (ccc == ifc || searcher == 1)
    {
        return searcher;
    }
    if (strcmp(Kelimeler[ccc], search))
    {
        ccc++;
        control();
    }
    else
    {
        searcher = 1;
    }
    return searcher;
}