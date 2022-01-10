/*bibliotheques***************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
/*definitions*****************************/
#define alpha 1
#define betan 2
#define betap 3
#define endm 40
#define endli 28
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define OK 13
#define BACK 8
#define menuc 11
#define begin 6
#define SPACE 32

typedef struct
{
    int NUMERO_ATOMIQUE;
    char SYMBOLE[10],ETAT;
    float MAR;
}ELEMENT_ATM;

typedef struct LISTE_ATM LISTE_ATM;
struct LISTE_ATM
{
    ELEMENT_ATM X;
    LISTE_ATM*next;
};

typedef LISTE_ATM * LISTE;

typedef struct
{
    LISTE T[7][18];
} TAB, * ELEMENT_TAB;

typedef enum
{
    FALSE,TRUE
}boolean;

/*prototypes***********************************/
void color(char); //permet de changer la couleur de l'atome selon son etat (solide ou gaz ou liquide ou synthetique)
ELEMENT_ATM * finder_Name(ELEMENT_TAB E, char * s); // permet de retourner l'atome recherché par son nom
boolean finder_list(LISTE l, ELEMENT_ATM X); // permet de determiner si un atome existe ou pas dans une liste chainée, TRUE s'il existe sinon FALSE
LISTE inserer(LISTE l, LISTE e); // permet d'inserer un atome dans une liste chainée
LISTE finder(ELEMENT_TAB E, int n, int *i, int *j); // permet de trouver et retourn l'atome recherché et stock dans i et j ses coordonnées
ELEMENT_TAB chargement_du_TP(); //importation du tableau periodique du fichier TAP.txt
LISTE Gaz(ELEMENT_TAB E); // retourne une liste chainée de gaz
LISTE  Lourds(ELEMENT_TAB  E); // retourne une liste chainée des atomes lourds
LISTE  Instables(ELEMENT_TAB  E); // retourne une liste chainée des atomes instables
LISTE  Radioactifs(ELEMENT_TAB  E); // retourne la liste des atomes radioactifs
double  Ar(ELEMENT_TAB  E,  char  *  s); // retourne la masse atomique d'un element
double M_C8H10N4O2(ELEMENT_TAB  E); // retourn la masse d'une molecule de cafeine
double n_C8H10N4O2(ELEMENT_TAB E); // retourne le nombre de mole dans 10g de cafeine
double M(ELEMENT_TAB E,char * molecule); // retourne la masse atomique d'une molecule donnée
void afficher_liste(LISTE G, int i, int j, int w); // affiche une liste chainée dans  un emplacement precis et limité
void afficher(ELEMENT_TAB t); // pour afficher le tableau periodique
ELEMENT_ATM  noyauFils(  ELEMENT_ATM  X,  ELEMENT_TAB  E,  int type_radio ); // pour la radioactivité
void menu(); // pour afficher un menu est des grilles
int choix(); // faire un choix
void information_atm(ELEMENT_ATM * atm); // j'affiche des informations sur un atome
int length(LISTE c); // la taille d'une liste chainée
void effacer(int x,int y,int longueur,int largeur); // pour effacer u bloc dans la console
int rise(ELEMENT_ATM *X,int x,int y); // pour afficher l'element indiqué par l'utilisateur en jaune
void case0(ELEMENT_TAB E); // si l'utilisateur choisi le choix 0
void case1to4(LISTE L); // # # # # # # # # # # # # # # un choix de 1 a 4
void case5(ELEMENT_TAB E); // # # # # # # # # # # # # le choix 5
void case7(ELEMENT_TAB E); // # # # # # # # # # # # #  le choix 7
void affichagecase8n6(LISTE l,char*s,double m); // affichage des informations sur la molecule dans le choix 8 ou 6
void case8n6(ELEMENT_TAB E,char *s); // # # # # # # # # # # # #  le choix 8 ou 6
void affichagecase9(int i); // des affichage du choix 9
void afficheratm(ELEMENT_ATM *X,int i,int j); // affichage d'un atome
void case9(ELEMENT_TAB E); // # # # # # # # # # # # #  le choix 9

/*fonctions***********************************/
void color(char e)
{
    switch(e)
    {
        case 'G': textcolor(LIGHTGREEN); break;
        case 'L': textcolor(LIGHTRED); break;
        case 'S': textcolor(WHITE); break;
        case 'Y': textcolor(LIGHTCYAN); break;
    }
}

ELEMENT_ATM * finder_Name(ELEMENT_TAB E, char *s)
{
    int i,j; // permet le parcour de la matrice
    LISTE a; // utilisé pour le parcour des listes chainées de la matrice
    for(i=0;i<7;i++)
    {
        for(j=0;j<18;j++)
        {
            a=E->T[i][j]; // l'initialiser a la tête de la liste chainée dans une case [i][j] de la matrice
            while(a!=NULL)
            {
                if(strcmp(a->X.SYMBOLE,s) == 0) // si le nom de l atome recherché s et le nom de l'atome ou pointe a
                    return &a->X; // je retourne l'atome
                a=a->next; //sinon je passe au bloc suivant
            }
        }
    }
    return NULL;// et si l'atome n'existe pas il retourne NULL
}

boolean finder_list(LISTE l, ELEMENT_ATM X)
{
    while(l!=NULL) // boucle pour le parcour de la liste chainée
    {
        if(l->X.NUMERO_ATOMIQUE==X.NUMERO_ATOMIQUE) // si les nbr atomiques sont identiques
            return TRUE; // je retourn TRUE
        l=l->next; //sinon je passe au bloc suivant
    }
    return FALSE; // si l'atome n'existe pas je retourn FALSE
}

LISTE inserer(LISTE l, LISTE e)
{
    LISTE t=malloc(sizeof(LISTE_ATM)); // créer le bloc ou je vais copier l atome
    t->X=e->X; // copier les informations
    t->next=l; // le bloc pointe sur la tete de la liste chainée
    return t; // retourner la nouvelle tete
}

LISTE finder(ELEMENT_TAB E, int n /*nbr atomique qu'on cherche*/, int *i, int *j)
{
    LISTE a; // a pour parcourir la liste
    for(*i=0;*i<7;(*i)++)
    {
        for(*j=0;*j<18;(*j)++)
        {
            a=E->T[*i][*j];
            while(a!=NULL)
            {
                if(a->X.NUMERO_ATOMIQUE==n) // si les nbrs atomiques sont identiques
                    return a; // je retourne l'atome
                a=a->next; // sinon je passe au bloc suivant
            }
        }
    }
    return NULL; // s'il n'existe pas on retourne NULL
}

ELEMENT_TAB chargement_du_TP()
{
    LISTE e;
    ELEMENT_TAB tp = malloc(sizeof(TAB));
    int i, j=0, c=0;
    FILE * f = fopen("TAP.txt","r");
    if(f == NULL) // si le fichier n'existe pas il sort du programme
        exit(1);
    fseek(f,SEEK_SET, 0); // je me le curseur dans le fichier à l'origine
    while(j < 7)
    {
        e = malloc(sizeof(LISTE_ATM)); // je crée un atome
        fscanf(f,"%d %d %s %c %f",&i,&e->X.NUMERO_ATOMIQUE,&e->X.SYMBOLE,&e->X.ETAT,&e->X.MAR); //je lis les informations de l atome du fichier
        while(c<=i)
        {
            tp->T[j][c++]=NULL;
        }// permet d'initialiser une case par NULL (c = i) et si la case n'est pas censée etre remplie (c < i) je l'initialise par NULL et je le depasse
        e->next=tp->T[j][i];
        tp->T[j][i]=e;
        // 2 instructions pour inserer dans la liste chainée
        if(i==17)
        {
           j++;
           c = 0;
        }//si i == 17 cad la prochaine insertion sera dans la ligne prochaine  donc la ligne s'incremente et et c se reinitialise
    }
    fclose(f);
    return tp; //on retourne la matrice
}

LISTE Gaz(ELEMENT_TAB E)
{
    LISTE gaz=NULL,a;
    int i,j;
    for(i=0;i<7;i++)
    {
        for(j=0;j<18;j++)
        {
            a = E->T[i][j];
            while(a!=NULL)
            {
                if(a->X.ETAT=='G') // si l'etat de l'atome est "gaz" je l'insere dans la liste
                {
                    gaz=inserer(gaz,a);
                }
                a=a->next;
            }
        }
    }
    return gaz;
}

LISTE  Lourds(ELEMENT_TAB  E)
{
    LISTE lourds=NULL,a;
    int i,j;
    for(i=0;i<7;i++)
    {
        for(j=0;j<18;j++)
        {
            a = E->T[i][j];
            while(a!=NULL)
            {
                if(a->X.NUMERO_ATOMIQUE>104) //si le nbre atomique > 104 je l'insere dans liste des elements lourds
                {
                    lourds=inserer(lourds,a);
                }
                a=a->next;
            }
        }
    }
    return lourds;
}

LISTE  Instables(ELEMENT_TAB  E)
{
    int i,j;
    LISTE instables=NULL,a;
    for(i=0;i<7;i++)
    {
        for(j=0;j<18;j++)
        {
            a = E->T[i][j];
            while(a!=NULL)
            {
                if(((int)(a->X.MAR*1000)%1000)==0)// s'il y a des nbres avant la virgule j'insere l'element dans la liste des elements instables
                    instables = inserer(instables,a);
                a=a->next;
            }
        }
    }
    return instables;
}

LISTE  Radioactifs(ELEMENT_TAB  E)
{
    LISTE radioda=NULL,a;
    int i,j;
    //Inserer les atomes 43 61
    radioda=inserer(radioda,finder(E,43,&i,&j));
    radioda=inserer(radioda,finder(E,61,&i,&j));
    //insere l'element 84 et obtenir ses coordonées pour inserer touts les elments qui le suivent
    radioda=inserer(radioda,finder(E,84,&i,&j));
    j++;
    while(i<7)
    {
        while(j<18)
        {
            a = E->T[i][j];
            while(a!=NULL)
            {
                radioda=inserer(radioda,a); // inserer un element dans la liste
                a=a->next;
            }
            j++;
        }
        i++;
        j=0;
    }
    return radioda;
}

double  Ar(ELEMENT_TAB  E,  char  *  s)
{
    ELEMENT_ATM * a;
    a = finder_Name(E, s); // je cherche l'element
    if(a != NULL) //si l'element existe
           return a->MAR; // je retourne sa masse atomique
    return 0; //sinon je retourne 0
}

double M_C8H10N4O2(ELEMENT_TAB  E)
{
   return 8*Ar(E,"C") + 10*Ar(E,"H") + 4*Ar(E,"N") + 2*Ar(E,"O");
}

double n_C8H10N4O2(ELEMENT_TAB E)
{
    return 10 / M_C8H10N4O2(E);
}

double M(ELEMENT_TAB E,char * molecule)
{
    int i=0,c,l;
    char s[7];
    double m=0,a;
    while(molecule[i]!='\0')
    {
        c=l=0;
        s[0]='\0';
        while(molecule[i]<'0' || molecule[i]>'9') // tant que le caractere different d'un chiffre
        {
            s[l++]=molecule[i];
            s[l]='\0'; //stocker un caractere dans une chaine de caractere
            i++;
            if(molecule[i]=='\0' || (molecule[i]>='A' && molecule[i]<='Z'))// si je suis à la fin de la chaine de caractere ou le caractere  est majuscule(cad un nouveau atome)
            {
                c=1; // car il n'y a pas dinformation sur le nombres de cette atome donc le nombre de fois dont il se repete est 1
                break;
            }
        }
        while(molecule[i]>='0' && molecule[i]<='9') // tant que le caractere est un chiffre
        {
            c = (c*10) + molecule[i] - '0'; //je forme le nombre de fois de repetition
            i++;
        }
        a = Ar(E,s); // je stock la valeur de la masse atomique dans a
        if(a==0) // si a = 0 donc un element dans cette molecule est inexistent dans le tableau periodique
            return 0;
        m = m + (double)c * a; // je calcule la masse de la molecule
    }
    return m;
}

void afficher_liste(LISTE G,int i,int j,int w)
{
    int k = 0;
    while(G!=NULL)
    {
               //i et j les points de reference
               // w est l'extremité droite de la cosnole à ne pas depasser
               //k*5 est l espace entre 2 atomes
               //(k*5)%(w-i) pour ne jamais depassé w
               //(k*5)%(w-i) s'il depasse w on revient a l a ligne mais je ne depasse pas l'extremité gauche ce qui explique " + i"
        gotoxy((k * 5) % (w - i) + i,j + (k * 5) / (w - i));
        color(G->X.ETAT); // donner une couleur a l'atome selon son etat
        cprintf("%s",G->X.SYMBOLE);
        G=G->next;
        k++;
    }
}

void afficher(ELEMENT_TAB t)
{
    int i,j;
    LISTE a;
    for(i=0;i<7;i++)
    {
        for(j=0;j<18;j++)
        {
            if(t->T[i][j]!=NULL)
            {
                gotoxy(j*5+begin,i+1);
                color(t->T[i][j]->X.ETAT);
                cprintf("%s",t->T[i][j]->X.SYMBOLE);
            }
        }
    }
    //afficher les lanthanides****************
    i++;
    gotoxy(5+begin,i+1);printf("lanthanides: ");
    a=t->T[5][2];
    j=0;
    while(a!=NULL)
    {
        gotoxy(j*5+18+begin,i+1);
        color(a->X.ETAT);
        cprintf("%s",a->X.SYMBOLE);
        j++;
        a=a->next;
    }
    //afficher les actinides****************
    i++;
    j=0;
    gotoxy(5+begin,i+1);printf("actinides: ");
    a=t->T[6][2];
    while(a!=NULL)
    {
        gotoxy(j*5+18+begin,i+1);
        color(a->X.ETAT);
        cprintf("%s",a->X.SYMBOLE);
        j++;
        a=a->next;
    }
    //afficher la legende ******************
    i=i+3;
    gotoxy(5,i); textcolor(WHITE); cprintf("%c",178);
    printf(": Solide");
    gotoxy(24,i); textcolor(LIGHTRED); cprintf("%c",178);
    printf(": Liquide");
    gotoxy(44,i); textcolor(LIGHTGREEN); cprintf("%c",178);
    printf(": Gaz");
    gotoxy(64,i); textcolor(LIGHTCYAN); cprintf("%c",178);
    cprintf(": Synthetique");
    i++;
    for(j=1;j<=100;j++)
    {
        gotoxy(j,i);printf("_");
    }
    printf("\n");
}

ELEMENT_ATM  noyauFils(  ELEMENT_ATM  X,  ELEMENT_TAB  E,  int type_radio )
{
    int i,j;
    ELEMENT_ATM Y;
    LISTE a;
    if((X.NUMERO_ATOMIQUE<=2 && type_radio==alpha) || (X.NUMERO_ATOMIQUE==1 && type_radio==betap) || (X.NUMERO_ATOMIQUE==118 && type_radio==betan))
        return X;
    else if(type_radio==alpha)
    {
        a=finder(E,X.NUMERO_ATOMIQUE-2,&i,&j);
        Y = a->X;
        Y.MAR = X.MAR - 4;
    }
    else if(type_radio==betap)
    {
        a=finder(E,X.NUMERO_ATOMIQUE-1,&i,&j);
        Y = a->X;
        Y.MAR = X.MAR;
    }
    else
    {
        a=finder(E,X.NUMERO_ATOMIQUE+1,&i,&j);
        Y = a->X;
        Y.MAR = X.MAR;
    }
    return Y;
}

void menu()
{
    int i;
    gotoxy(5,15); textcolor(YELLOW); cprintf("Menu: ");
    gotoxy(endm+5,15); textcolor(YELLOW); cprintf("Execution: ");
    gotoxy(1,17); printf("0* Informations sur les atomes.");
    printf("\n1* La liste des gaz.");
    printf("\n2* La liste des atomes lourds.");
    printf("\n3* La liste des atomes instables.");
    printf("\n4* La liste des atomes radioactifs.");
    printf("\n5* La masse atomique d'un element.");
    printf("\n6* La masse molaire du cafeine.");
    printf("\n7* Le nombre de moles de cafeine (10g).");
    printf("\n8* La masse molaire d'une molecule.");
    printf("\n9* La radioactivitee.");
    printf("\n10* Quitter.");
    for(i=1;i<=99;i++)
    {
        gotoxy(i,endli);printf("_");
    }
    for(i=1;i<=endli;i++)
    {
        gotoxy(100,i);printf("|");
    }
    for(i=14;i<=endli;i++)
    {
        gotoxy(endm,i);printf("|");
    }
}

int choix()
{
    static int i;
    menu();
    while(1)
    {
        fflush(stdin);
        gotoxy(1,17+i);
        switch(getch())//choisir avec les fleches et pour executer il faut clicker sur "entrer"
        {
            case UP: i=(i+menuc-1)%menuc; break;
            case DOWN: i=(i+1)%menuc; break;
            case OK: return i;
        }
    }
}

void information_atm(ELEMENT_ATM *atm)
{
   gotoxy(endm+3,17);printf("Atome: ");
   gotoxy(endm+20,17);color(atm->ETAT);cprintf("%s",atm->SYMBOLE);
   gotoxy(endm+3,20);printf("Num.atm.:");
   gotoxy(endm+20,20); printf("%d",atm->NUMERO_ATOMIQUE);
   gotoxy(endm+3,23);printf("M.Atm:");
   gotoxy(endm+20,23); printf("%d g/mol",(int)(atm->MAR+0.5)/*j'arrondit*/);
   gotoxy(endm+3,26);printf("Etat: ");
   gotoxy(endm+20,26);
   switch(atm->ETAT)
   {
       case 'G': printf("Gaz"); break;
       case 'L': printf("Liquide"); break;
       case 'S': printf("Solide"); break;
       case 'Y': printf("Synthetique"); break;
   }
}

int length(LISTE c)
{
    if(c==NULL)
        return 0;
    return 1+length(c->next);
}

void effacer(int x,int y,int longueur,int largeur)
{  // x et y les coordonées d'origine dans la console
   // longeur et la largeur dimension du bloc à effacer
    int i,j;
    for(i=0;i<longueur;i++)
    {
        for(j=0;j<largeur;j++)
        {
            gotoxy(x+j,y+i);textcolor(BLACK);cprintf("%c",178);
        }
    }
}

int rise(ELEMENT_ATM *X,int x,int y)
{
    int g;
    gotoxy(x,y);
    textcolor(YELLOW);
    cprintf("%s",X->SYMBOLE);
    gotoxy(x,y);
    g=getch();
    gotoxy(x,y);
    color(X->ETAT);
    cprintf("%s",X->SYMBOLE);
    return g;
}

void case0(ELEMENT_TAB E)
{
    static int i,j,z,k;
    boolean b=TRUE, v=FALSE; //v indique s'il est au milieu d'une liste chainée ou non, FALSE si le pointeur est dans la tete d'une case de la matrice sinon TRUE
    int g,c;
    LISTE a;
    while(b)
    {
        for(c=0,a= E->T[i][j];c<z;c++,a=a->next); //pour parcourir la liste chainée jusqu'a ou l'utilisateur pointe
        information_atm(&a->X); // afficher les info sur l'atome
        fflush(stdin);

        if(v)
            g=rise(&a->X,z*5+18+begin,k+9);
        else
            g=rise(&a->X,j*5+begin,i+1);
        switch(g)
        {
            // (x + 1)% k : x s'incremente et revient a 0 quand elle depasse k-1
            // (x + k - 1)% k : x se decremente et revient a k-1 quand elle depasse 0
            case UP:  do{ i=(i+6)%7; }while(E->T[i][j]==NULL); break;
            case DOWN: do{ i=(i+1)%7; }while(E->T[i][j]==NULL); break;
            case LEFT: if(v){z=(z+14)%15; break;} do{ j=(j+17)%18; }while(E->T[i][j]==NULL); break;
            case RIGHT: if(v){z=(z+1)%15; break;} do{ j=(j+1)%18; }while(E->T[i][j]==NULL); break;
            case OK: if(!v && (i==5 || i==6) && j==2){ k=i/6; z=0; v=TRUE;} break; // si le curseur est sur La ou Ac et l'utilisateur clique sur entrer l'utilisateur parcourt les listes des actinides ou des lanthanides
            case BACK: if(v){z=0; v=FALSE; break;} b = FALSE; break; // retour en arriere
        }
        effacer(endm+1,17,10,40);
    }
}

void case1to4(LISTE L)
{
    LISTE a;
    int c,t=length(L),k=0;
    boolean b=TRUE;
    afficher_liste(L,endm + 1,17,100);
    while(b)
    {
        for(c=0,a=L;c<k;c++,a=a->next);
        c=rise(&a->X,(k*5)%(100-endm-1)+endm+1,17+(k*5)/(100-endm-1)); //meme logique de "afficher_liste()"
        gotoxy(k*5+endm+1,17);
        switch(c)
        {
            case LEFT: k=(k+t-1)%t; break;
            case RIGHT: k=(k+1)%t; break;
            case OK: effacer(endm+1,17,9,59); information_atm(&a->X); while(getch()!=BACK){} effacer(endm+3,17,10,40); afficher_liste(L,endm + 1,17,100); break;
            case BACK: b=FALSE; break;
        }
    }
}

void case5(ELEMENT_TAB E)
{
    char s[7];
    double ar;
    do{
        effacer(endm+1,18,9,50);
        gotoxy(endm+1,18);
        printf("Entrez le symbole de l'atome:");
        gotoxy(endm+10,20);
        scanf("%s",s);
        ar=Ar(E,s);
        gotoxy(endm+3,22);
        if(ar==0)
            printf("L'element %s est inexistant.",s);
        else
            printf("M(%s) = %.4f g/mol = %d g/mol",s,ar,(int)(ar+0.5));
        gotoxy(endm+15,25);
        printf("Clickez sur ESPACE pour reessayer.");
    }while(getch()==SPACE);
}

void case7(ELEMENT_TAB E)
{
    gotoxy(endm+3,18);
    printf("nombre de mole dans 10g de cafeine (C8H10N4O2):");
    gotoxy(endm+8,20);
    printf("Nm = %.3f mol ",n_C8H10N4O2(E));
    getch();
    effacer(endm+3,18,3,50);
}

void affichagecase8n6(LISTE l,char*s,double m)
{
    gotoxy(endm+3,17);
    printf("molecule: ");
    gotoxy(endm+15,17);
    printf("%s",s);
    gotoxy(endm+3,20);
    printf("composants: ");
    gotoxy(endm+3,24);
    printf("masse atomique:");
    gotoxy(endm+20,24);
    printf("%.2f g/mol",m);
    afficher_liste(l,endm+20,20,100);
}

void case8n6(ELEMENT_TAB E,char *s)
{
    int i=0,t=strlen(s),k;
    char a[7];
    double m;
    boolean b=TRUE;
    LISTE l=NULL,c;
    if(!strcmp(s,"C8H10N4O2"))
        m = M_C8H10N4O2(E);
    else
        m = M(E,s);
    if(m==0)
    {
        gotoxy(20+endm,20);
        printf("ERREUR");
        goto here;
    }
    while(i<t)
    {
       k=0;
       a[0]='\0';
       while( s[i]>='0' && s[i]<='9')
        i++;
        if(s[i]=='\0')
            break;
       while(s[i]<'0' || s[i]>'9')
       {
           a[k++]=s[i];
           a[k]='\0';
            i++;
           if(s[i]=='\0' || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9'))
                break;
       }
       c=malloc(sizeof(LISTE_ATM));
       c->X=*finder_Name(E,a);
       if(!finder_list(l,c->X))
       {
           c->next=l;
           l=c;
       }
    }
    affichagecase8n6(l,s,m);
    i=0;
    t=length(l);
    while(b)
    {
        for(k=0,c=l;k<i;k++,c=c->next);
        k=rise(&c->X,(i*5)%(100-endm-20)+endm+20,20+(i*5)/(100-endm-20));
        switch(k)
        {
            case LEFT:  i=(i+t-1)%t; break;
            case RIGHT: i=(i+1)%t; break;
            case OK: effacer(endm+3,17,9,50); information_atm(&c->X); while(getch()!=BACK); effacer(endm+3,17,10,40); affichagecase8n6(l,s,m); break;
            case BACK: b=FALSE; break;
        }
    }
    here:
}

void affichagecase9(int i)
{
    gotoxy(endm+40,15); textcolor(LIGHTRED); cprintf("type:");
    effacer(endm+41,16,1,10);
    gotoxy(endm+41,16);
    switch(i)
    {
        case alpha: printf("Alpha"); break;
        case betan: printf("Beta-"); break;
        case betap: printf("Beta+"); break;
    }
    gotoxy(endm+40,19); textcolor(LIGHTCYAN); cprintf("atm: ");
}

void afficheratm(ELEMENT_ATM *X,int i,int j)
{
    gotoxy(i-1,j-1);printf("%d",(int)(X->MAR+0.5));
    gotoxy(i-1,j+1);printf("%d",X->NUMERO_ATOMIQUE);
    gotoxy(i,j);printf("%s",X->SYMBOLE);
}

void case9(ELEMENT_TAB E)
{
    static int i,j=1;
    boolean b=TRUE,atm=FALSE;
    ELEMENT_ATM Y,X;
    char s[7];
    affichagecase9(i+1);
    while(b)
    {
        while(b && j==1)
        {
            gotoxy(endm+40,19); textcolor(YELLOW); cprintf("atm:");
            switch(getch())
            {
                case UP: j=0; break;
                case OK: effacer(endm+45,19,1,10); gotoxy(endm+45,19); scanf("%s",s); if(finder_Name(E,s)==NULL){effacer(endm+1,21,3,58); gotoxy(endm+5,22); printf("ERROR"); atm=FALSE; break;} effacer(endm+1,21,3,58); X=*finder_Name(E,s); atm=TRUE; Y = noyauFils(X,E,i+1); goto skip;
                case BACK: b=FALSE; break;
            }
            affichagecase9(i+1);
        }
        while(b && j==0)
        {
            gotoxy(endm+40,15); textcolor(YELLOW); cprintf("type:");
            switch(getch())
            {
                case LEFT: i=(i+2)%3; break;
                case RIGHT: i=(i+1)%3; break;
                case DOWN: j=1; break;
                case OK: if(!atm)break; effacer(endm+1,21,3,58); Y = noyauFils(X,E,i+1); goto skip;
                case BACK: b=FALSE; break;
            }
            affichagecase9(i+1);
        }
        if(FALSE)
        {
            skip:
            afficheratm(&X,endm+4,22); gotoxy(endm+8,22); printf(" =>"); afficheratm(&Y,endm+16,22); gotoxy(endm+20,22);
            if(X.NUMERO_ATOMIQUE!=Y.NUMERO_ATOMIQUE)
            {
                switch(i+1)
                {
                    case 1: printf("+"); afficheratm(&E->T[0][17]->X,endm+26,22); gotoxy(endm+32,22); printf("+  Gamma"); break;
                    case 2: printf("+"); printf("  Electron  +  Gamma  +  Antineutrino"); break;
                    case 3: printf("+"); printf("  Positron  +  Neutrino + Gamma"); break;
                }
            }
        }
    }
}

int main()
{
    int c;
    char s[70];
    ELEMENT_TAB E=chargement_du_TP();
    afficher(E);
    while((c=choix())!=10)
    {
        switch(c)
        {
            case 0: case0(E); break;
            case 1: case1to4(Gaz(E)); break;
            case 2: case1to4(Lourds(E)); break;
            case 3: case1to4(Instables(E)); break;
            case 4: case1to4(Radioactifs(E)); break;
            case 5: case5(E); break;
            case 6: case8n6(E,"C8H10N4O2"); break;
            case 7: case7(E); break;
            case 8: gotoxy(endm+3,17); printf("molecule: "); gotoxy(endm+15,17); scanf("%s",s); case8n6(E,s); break;
            case 9: case9(E); break;
        }
        effacer(endm+1,15,9,59);
    }
    return 0;
}

