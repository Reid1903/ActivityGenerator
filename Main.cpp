#include <iostream>
#include <vector>
#include <string.h>
#include "Generator.h"
#include <pthread.h>
#include <stdlib.h>


typedef struct{
    string esc;
    string doc; 
    string fecha;
    string TL;

}parametroL;

typedef struct{
    string esc;
    string doc; 
    string fecha;
    string TS;
    vector <string> x; 

}parametroS;

using namespace std;
void* laberintof(void* args)
{
    parametroL *l= (parametroL *) args; 
    laberinto s = laberinto(l->esc, l->doc, l->fecha, l-> TL);
    s.generar();
    cout<<"Laberinto generado bajo el nombre Laberinto.txt"<<endl;
    return NULL;
}

void* sopaf(void* args)
{
    parametroS *l= (parametroS *) args; 
    sopa s = sopa(l->esc, l->doc, l->fecha, l-> TS, l->x);
    s.generar();
    cout<<"Sopa de letras generado bajo el nombre de Sopa.txt"<<endl;
    return NULL;
}


int main()
{
    try{
    system("clear");
    int n;
    int matriz[40][30]; 
    pthread_t lab;
    pthread_t sop;
    string cad, escuela, docente;
    char ans;
    string TL = "Laberinto";
    string TS = "Sopa de letras"; 
    string fecha;
    vector <string> x;
    parametroS s;
    parametroL l;
    
    cout << "Bienvendido a ActivyGenerator"<<endl<<endl;
    cout << "Nombre de la escuela: "; getline(cin, escuela); 
    cout<<"Docente: "; getline(cin, docente); 
    cout<<"Fecha: "; getline(cin, fecha);
    cout<<endl;
    char r=' ';

    while(r!='4')
    {
    system("clear");
    cout<<"--------------Menú--------------"<<endl;
    cout<<"1. Crear un laberinto"<<endl;
    cout<<"2. Crear una sopa de letras"<<endl;
    cout<<"3. Crear ambas actividades"<<endl;
    cout<<"4. Finalizar programa"<<endl; 
    cout<<"--------------------------------"<<endl; 
    cin>>r;
    switch(r)
    {
    case '1':
        cout<<"Desea Añadir un título al laberinto (S/N) "; cin >>ans;   
        if(ans == 'S' || ans == 's')
        {   fflush(stdin);
            cout<<"Introducir el título"<<endl; getline(cin, TL);  
            
        }
        l.esc = escuela;
        l.doc = docente; 
        l.fecha = fecha;
        l.TL = TL; 
        pthread_create(&lab, NULL, laberintof, (void*) &l);
        pthread_join(lab, NULL);
        break;

        

    case '2':

        cout<<"Desea Añadir un título a la sopa de letra (S/N) "; cin >>ans;   
        if(ans == 'S' || ans == 's')
        {   fflush(stdin);
            cout<<"Introducir el título"<<endl; getline(cin, TS); 
            
        }
        cout<<endl;
        cout<<"¿Cuántas palabras quiere insertar en la sopa de letra? (Máximo 15) "<<endl; cin>>n; 
        if(n>15)
        {
            throw "Error: Inserto un numéro mayor a 15";
        }
        if(n<=0)
        {
            throw "Error: Inserto un número igual o mayor a cero";
        }
        cout<<"Introducir sus palabras. Las palabras deben de estar en Mayúscula y evite el uso de la tilde"<<endl;

        for(int i=0; i<n; i++)
        {
            cin>>cad; 
            x.push_back(cad);
        }

       
        s.esc = escuela; 
        s.doc = docente; 
        s.fecha = fecha;
        s.TS = TS;
        s.x= x;
        pthread_create(&sop, NULL, sopaf, (void *) &s);
        pthread_join(sop, NULL);
        break;

    case '3':
        cout<<"Desea Añadir un título al laberinto (S/N) "; cin >>ans;   
        if(ans == 'S' || ans == 's')
        {   fflush(stdin);
            cout<<"Introducir el título"<<endl; getline(cin, TL);  
            
        }

        cout<<"Desea Añadir un título a la sopa de letra (S/N) "; cin >>ans;   
        if(ans == 'S' || ans == 's')
        {   fflush(stdin);
            cout<<"Introducir el título"<<endl; getline(cin, TS); 
            
        }
        cout<<endl;

        cout<<"¿Cuántas palabras quiere insertar en la sopa de letra? (Máximo 12) "<<endl; cin>>n; 
        if(n>15)
        {
            throw "Error: Inserto un numéro mayor a 15";
        }
        if(n<=0)
        {
            throw "Error: Inserto un número igual o mayor a cero";
        }
        cout<<"Introducir sus palabras. Las palabras deben de estar en Mayúscula y evite el uso de la tilde"<<endl;

        for(int i=0; i<n; i++)
        {
            cin>>cad; 
            x.push_back(cad);
        }


       
        l.esc = escuela;
        l.doc = docente; 
        l.fecha = fecha;
        l.TL = TL; 
        s.esc = escuela; 
        s.doc = docente; 
        s.fecha = fecha;
        s.TS = TS;
        s.x= x;


        pthread_create(&lab, NULL, laberintof, (void*) &l);
        pthread_create(&sop, NULL, sopaf, (void *) &s);
        pthread_join(lab, NULL);
        pthread_join(sop, NULL);
        break;

        case '4': 
            cout<<"Programa finalizado"<<endl;
            break;

        default:
            cout<<"No es una opción valida"<<endl;
            break;
    }
    }
    }

    catch(const char* e)
    {
        cout << e << endl;
    }

    
}