#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream> //solo para heapsort
#include <windows.h>
using namespace std;
//constantes del programa
const int size=15;
const int million=1000000;

//cronometro
/* retorna "a - b" en segundos */
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}


//get size of files
int sizes (int w)
{
  FILE * pFile;
  int size;
  if(w==0){
  	pFile=fopen("male.txt","rb");
  }
  if(w==1){
  	pFile=fopen("female.txt","rb");
  }
  if(w==2){
  	pFile = fopen ("surname.txt","rb");
  }
  if(w==3){
  	pFile = fopen("city.txt","rb");
  }
  if(w==4){
  	pFile = fopen("jobs.txt","rb");
  }
  if (pFile==NULL) perror ("Error opening file");
  else
  {
    fseek (pFile, 0, SEEK_END);   // non-portable
    size=ftell (pFile);
    fclose (pFile);
  }
  return size;
}
//size=
int male_size=sizes(0);
int female_size=sizes(1);
int surname_size=sizes(2);
int city_size=sizes(3);
int job_size=sizes(4);

struct date{
	int day;
	int month;
	int year;
};

struct reg{
	int code;
	char surname[size];
	char surname2[size];
	char name[size];
	char name2[size];
	char gender[size];
	char city[size];
	char country[size];
	char job[size];
	date bday;
}registry[million],aux,new_registry[million];



//Debemos crean una funcion para generar un numero random de 10 digitos.
//un random para decir si es masculino o femenino 
//otra funcion para tomar un nombre-apellido-ciudad de un archivo
//por ultimo generar una fecha de nacimiento random que tenga sentido

//funcion code
int code(int i)
{
	registry[i].code=rand() %9999999999 + 1000000000;
}

//gender funtion

int gender(int g, int i)
{
	if(g==0)
		{
			strcpy(registry[i].gender,"MASCULINO");
		}		
		else{
			strcpy(registry[i].gender,"FEMENINO");
		}
}

//take string from file funtion

int take_name(int g, int i)
{
	char caracter;
	int c=0;
	int pos;
	FILE *flujo; 
	if (g==0)
	{
		flujo=fopen("male.txt","rb");
		pos=rand() %male_size;
	}
	else{
		flujo=fopen("female.txt","rb");	
		pos=rand() %female_size;
	}
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].name);
	rewind(flujo);
	if (g==0){
		pos=rand() %male_size;	
	}
	else{
		pos=rand() %female_size;
	}
	c=0;
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].name2);
	fclose(flujo);
}

//Take surname

int take_surname(int i)
{	
	char caracter;
	int c=0;
	int pos;
	FILE *flujo;
	flujo=fopen("surname.txt","rb");
	pos=rand() %surname_size;
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].surname);
	rewind(flujo);
	pos=rand() %surname_size;
	c=0;
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].surname2);
	fclose(flujo);
}

//take city

int take_city(int i)
{
	char caracter;
	int c=0;
	int pos;
	FILE *flujo;
	flujo=fopen("city.txt","rb");
	pos=rand() %city_size;
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].city);
	fclose(flujo);
}

//take job

int take_job(int i)
{
	char caracter;
	int c=0;
	int pos;
	FILE *flujo;
	flujo=fopen("jobs.txt","rb");
	pos=rand() %job_size;
	fseek(flujo,pos-100,SEEK_SET);
	while(c!=10){
		caracter=fgetc(flujo);
		c=caracter;
	}
	fscanf(flujo,"%s",registry[i].job);
	fclose(flujo);
}

//set bday

int set_bday(int i)
{
	registry[i].bday.day=rand() %31 + 1;
	registry[i].bday.month=rand() %12 +1;
	registry[i].bday.year=rand() %50 + 1950;
}

//set country

int set_country(int i)
{
	strcpy(registry[i].country,"COLOMBIA");
}

//make 1 million data registry

int make_registry(int i)
{
	FILE *reg;
	reg=fopen("registry.txt","a");
	fprintf(reg,"%d\t",registry[i].code);
	fprintf(reg,"%-15.15s\t",registry[i].gender);
	fprintf(reg,"%-15.15s\t",registry[i].name);
	fprintf(reg,"%-15.15s\t",registry[i].name2);
	fprintf(reg,"%-15.15s\t",registry[i].surname);
	fprintf(reg,"%-15.15s\t",registry[i].surname2);
	fprintf(reg,"%-15.15s\t",registry[i].job);
	fprintf(reg,"%-15.15s\t",registry[i].city);
	fprintf(reg,"%-15.15s\t",registry[i].country);
	fprintf(reg,"%d/%d/%d  \n",registry[i].bday.day,registry[i].bday.month,registry[i].bday.year);
	fclose(reg);
}

int make_new_registry()
{
	FILE *reg;
	reg=fopen("new_registry.txt","a");
	for(int i=0;i<million;i++){
	fprintf(reg,"%d\t",new_registry[i].code);
	fprintf(reg,"%-15.15s\t",new_registry[i].gender);
	fprintf(reg,"%-15.15s\t",new_registry[i].name);
	fprintf(reg,"%-15.15s\t",new_registry[i].name2);
	fprintf(reg,"%-15.15s\t",new_registry[i].surname);
	fprintf(reg,"%-15.15s\t",new_registry[i].surname2);
	fprintf(reg,"%-15.15s\t",new_registry[i].job);
	fprintf(reg,"%-15.15s\t",new_registry[i].city);
	fprintf(reg,"%-15.15s\t",new_registry[i].country);
	fprintf(reg,"%d/%d/%d  \n",new_registry[i].bday.day,new_registry[i].bday.month,new_registry[i].bday.year);
	}
	fclose(reg);
	
}

//Algoritmo burbuja

void ordenacion_burbuja()
{
    int i,j, bandera;
    for(i=0;i<million;i++){
    	new_registry[i]=registry[i];
	}
    for(i=1; i<million; i++)   {
         bandera=0;         //inciamos la bandera en 0
         for(j=million-1; j>=i; j--)   {
                if(new_registry[j-1].code>new_registry[j].code)  {
                       aux=new_registry[j];
                       new_registry[j]=new_registry[j-1];
                       new_registry[j-1]=aux;
                       bandera=1; //si hubo cambio cambiamos la bandera a 1
               }
         }
         if (bandera==0)
        break; //si no hubo cambios entonces salir del for
    }
}

//algoritmo insercion

void ordenacion_insercion()
{
	int i,j;
    for(i=0;i<million;i++){
    	new_registry[i]=registry[i];
	}
	for (i=1; i<million; i++){
         aux = new_registry[i];
         j = i - 1;
         while ( (new_registry[j].code > aux.code) && (j >= 0) ){
		 		new_registry[j+1] = new_registry[j];	
				j--;
				new_registry[j+1] = aux;
			}
		}
}

//algoritmo quick

int pivot(int izq, int der)
{
    int i;
    int pivote, valor_pivote;

    pivote = izq;
    valor_pivote = new_registry[pivote].code;
    for (i=izq+1; i<=der; i++){
        if (new_registry[i].code < valor_pivote){
                pivote++;
                aux=new_registry[i];
                new_registry[i]=new_registry[pivote];
                new_registry[pivote]=aux;

        }
    }
    aux=new_registry[izq];
    new_registry[izq]=new_registry[pivote];
    new_registry[pivote]=aux;
    return pivote;
}

void quicksort(int izq, int der)
{
     int pivote;
     if(izq < der){
        pivote=pivot(izq, der);
        quicksort(izq, pivote-1);
        quicksort(pivote+1, der);
     }
}

//algoritmo shell

void shell() 
{ 
	int n=million;
	int inter=(n/2),i=0,j=0,k=0; 
    for(i=0;i<million;i++){
    	new_registry[i]=registry[i];
	}
	i=0;
	while(inter>0){ 
		for(i=inter;i<n;i++) 
		{		 
			j=i-inter; 
			while(j>=0) { 
				k=j+inter; 
				if(new_registry[j].code<=new_registry[k].code){ 
					j--; 
				}		 
				else{ 
					aux=new_registry[j]; 
					new_registry[j]=new_registry[k]; 
					new_registry[k]=aux; 
					j=j-inter; 
				}		 
			} 
		} 
		inter=inter/2; 
	} 
}  

//ordenamiento heap

void heapify(int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && new_registry[l].code > new_registry[largest].code)
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && new_registry[r].code > new_registry[largest].code)
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(new_registry[i], new_registry[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(n, largest);
    }
}
 
// main function to do heap sort
void heapsort(int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
 
    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(new_registry[0], new_registry[i]);
 
        // call max heapify on the reduced heap
        heapify(i, 0);
    }
}
 

//option menu

int option(int op){
	LARGE_INTEGER t_ini, t_fin;
  	double secs;
  	QueryPerformanceCounter(&t_ini);
	switch(op)
	{
		case 1:	
			ordenacion_burbuja();
			break;
		case 2:
			ordenacion_insercion();
			break;
		case 3:
    		for(int i=0;i<million;i++){
    			new_registry[i]=registry[i];
    		}
			quicksort(0,million);
			break;
		case 4:
			shell();
			break;
		case 5:
			for(int i=0;i<million;i++){
    			new_registry[i]=registry[i];
    		}
			heapsort(million);
   		    break;			
	}
	QueryPerformanceCounter(&t_fin);
	secs = performancecounter_diff(&t_fin, &t_ini); 
	printf("Tiempo requerido: %.16g seconds\n", secs);
}

//buscar

int buscar(int p1,int p2){
	for(;p1<=p2;p1++){
		printf("%d\t",new_registry[p1].code);
		printf("%-15.15s\t",new_registry[p1].gender);
		printf("%-15.15s\t",new_registry[p1].name);
		printf("%-15.15s\t",new_registry[p1].name2);
		printf("%-15.15s\t",new_registry[p1].surname);
		printf("%-15.15s\t",new_registry[p1].surname2);
		printf("%-15.15s\t",new_registry[p1].job);
		printf("%-15.15s\t",new_registry[p1].city);
		printf("%-15.15s\t",new_registry[p1].country);
		printf("%d/%d/%d  \n",new_registry[p1].bday.day,new_registry[p1].bday.month,new_registry[p1].bday.year);
	}
}
// main funtion

int main()
{
	srand(time(NULL));
	int g;
	int op,p1,p2;
	printf("Creando registro... por favor espere...\n\n");
	for(int i;i<million;i++){
		g=rand() %2;
		code(i);
		gender(g,i);
		take_name(g,i);
		take_job(i);
		take_surname(i); 
		take_city(i);
		set_country(i);
		set_bday(i);
		make_registry(i);
	}
	while(1){
	printf("\n\n");
	printf("Registro terminado, seleccione metodo de ordenamiento= \n");
	printf("1 - Burbuja\n");
	printf("2 - Insercion\n");
	printf("3 - Quick\n");
	printf("4 - Shell\n");
	printf("5 - Heap\n");
	printf("7. Continuar\n");
	printf("\n\nSeleccione una opcion= ");
	scanf("%d",&op);
	fflush(stdin);
	option(op);
	printf("Registro organizado... ");
	int n;
	printf("\nMenu:\n\n");
	printf("1. Buscar por posicion [int][int]\n");
	printf("2. Crear registro nuevo organizado\n");
	printf("3. Organizar mediante otro metodo\n");
	printf("\n\nSeleccione una opcion= ");
	scanf("%d",&n);
	fflush(stdin);
	switch(n){
		case 1: scanf("%d %d",&p1,&p2);
				fflush(stdin);
				buscar(p1,p2);
				break;
		case 2:	make_new_registry();
				printf("Nuevo registro creado... saliendo...");
				system("exit");
				break;
		}
	}
}
