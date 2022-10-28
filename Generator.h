#include <ctime>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

class File{
private:
    string escuela;
    string docente;
    string fecha; 
public:
    File(string, string, string); 
    string getEscuela();
    string getDocente();
    string getFecha();
};

class laberinto : File 
{
    private:
        string titulo; 
        int matriz[40][30]; 
    
    public:
        laberinto(string, string, string, string); 
        void generar(); 
};

class sopa : File 
{
    private:
        string titulo;
        vector <string> x;
        char matriz[40][30]; 

    public: 
        sopa(string, string, string, string, vector <string>);
        void generar();
};

File :: File(string _esc, string _doc, string _fecha)
{
    escuela = _esc;
    docente = _doc; 
    fecha = _fecha; 
}

string File :: getEscuela()
{
    return escuela;
}

string File :: getDocente()
{
    return docente;
}

string File :: getFecha()
{
    return fecha; 
}

laberinto :: laberinto(string _esc, string _doc, string _fecha, string tl) : File(_esc, _doc, _fecha)
{
     titulo = tl; 
}

sopa :: sopa(string _esc, string _doc, string _fecha, string ts, vector <string> _x) :  File(_esc, _doc, _fecha)
{
    titulo = ts;
    x = _x;
}

void laberinto :: generar()
{
    int filas = 40; 
    int columnas = 30;
	ofstream archivo;
	archivo.open("Laberinto.txt", ios_base::out);
	
    if(archivo.fail()){
        cout << "El archivo no se puede abrir"<<endl;
    }

    float densidad =1;

	int FParedes = densidad*8; 
	densidad = filas*columnas*densidad / 4;

	//valores
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
				matriz[i][j] = 1;
			}
			else {
				matriz[i][j] = 0; 
			}
		}
	}
	//laberinto 
	srand(time(NULL));
	for (int i = 0; i < densidad; i++) {
		int x = rand() % (columnas - 4) + 2; // 2 18 
		x = (x / 2) * 2; 
		int y = rand()% (filas - 4) + 2;
		y = (y / 2) * 2;
		matriz[y][x] = 1; 
		for (int j = 0; j < FParedes; j++) {
			int mx[4] = { x,  x,  x + 2, x - 2 };
			int my[4] = { y + 2,y - 2, y ,  y };
			int r = rand() % 4;
			if (matriz[my[r]][mx[r]] == 0) {
				matriz[my[r]][mx[r]] = 1; 
				matriz[my[r] +( y - my[r])/2][mx[r]+(x- mx[r])/2] = 1;
			}
				
		}
	}
	archivo<<"Institución: "<<getEscuela()<<endl;
    archivo<<"Docente: "<<getDocente()<<endl;
    archivo<<"Fecha: "<<getFecha()<<endl;
    archivo<<titulo<<endl<<endl;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j] == 1) {
				char a = (char)35; 
				archivo<<a<<a; 
			}
			if(matriz[i][j] == 0) {
				archivo<<"  ";
			}
		}
		archivo<<endl; 
	}

	archivo.close();
} 

void sopa :: generar()
{
    ofstream archivo, res;
    archivo.open("Sopa.txt", ios_base::out);
    res.open("Respuesta.txt", ios_base::out);
	
    if(archivo.fail()){
        cout << "El archivo no se puede abrir"<<endl;
    }
    if(res.fail())
    {
        cout <<"No se puede abrir el código"<<endl;
    }

    memset(matriz,' ',sizeof(matriz));
    string cad; 
    int mx, my, dir, sizeC;
        
    
   srand (time(NULL));
    for(auto it = x.begin(); it != x.end(); it++)
    {
        
        int SePudo=0;
        cad = *it;
        sizeC = cad.size();

        while(SePudo==0)
        { 
            
            mx = rand() % 30;
            my = rand() % 20; 
            dir= rand() % 5;

            while(matriz[mx][my] != ' ')
            {
                mx = rand() % 30;
                my = rand() % 20; 
            }

            if(dir==0)
            {
                if(mx+1  >= sizeC)
                {
                    int c = 0;
                    int seRompio = 0;

                    for(int i = mx; i!=mx-sizeC; i--)
                    {
                    
                                seRompio=1;
                                break;   
                        
                            c++;
                    }

                    if(seRompio==0)
                    {
                        SePudo=1;
                        c=0;
                        for(int i = mx; i!=mx-sizeC; i--)
                        {
                            
                            matriz[i][my] = cad[c];

                            
                            c++;
                        }

                    }
                }
            }


            if(dir==1)
            {
                int auxX=mx;
                if(mx+1 >= sizeC && 20 - my >= sizeC)
                {
                    int c=0; 
                    int seRompio = 0;

                    for(int i = my; i< my + sizeC ; i++)
                    {
                        if(matriz[mx][i]!=' ')
                        {
                            
                                seRompio=1;
                                break;
                            
                            
                        }
                        mx--;
                        c++;
                    }
                    mx=auxX;
                    if(seRompio==0)
                    {
                        SePudo=1;
                        c=0;
                        for(int i = my; i< my + sizeC ; i++)
                        {
                            
                            matriz[mx][i] = cad[c];
                            c++;
                            mx--;
                        }
                    }
                }
            }

            if(dir == 2)
            {
                if(20 - my >= sizeC)
                {
                    int c = 0;
                    int seRompio = 0;
                    for(int i = my; i< my + sizeC ; i++)
                    {
                        if(matriz[mx][i]!=' ')
                        {
                           
                                seRompio = 1;
                                break;  
                        }  
                        
                        c++;
                    }


                    if(seRompio==0)
                    {
                        SePudo=1;
                        c=0;
                        for(int i = my; i< my + sizeC ; i++)
                        {
                            matriz[mx][i] = cad[c];
                            c++;
                        }
                    }
                }
            }

            if(dir==3)
            {
                int auxX=mx;
                if(30-mx >= sizeC && 20 - my >= sizeC)
                {
                    int c = 0;
                    int seRompio = 0;
                    for(int i = my; i< my + sizeC ; i++)
                    {
                        if(matriz[mx][i]!=' ')
                        {

                         
                                seRompio = 1;
                                break;
                            
                        }  
                        
                        mx++;
                        c++;
                    }

                    mx=auxX;
                    if(seRompio==0)
                    {
                        SePudo=1;
                        c=0;
                        for(int i = my; i< my + sizeC ; i++)
                        {
                            matriz[mx][i] = cad[c];
                            mx++;
                            c++;
                        }
                    }

                }

            }

            if(dir==4)
            {
                if(30-mx>=sizeC)
                {
                    int c=0;
                    int seRompio=0;
                    for(int i=mx; i<mx+sizeC; i++)
                    {
                        if(matriz[i][my]!=' ')
                        { 

                           
                                seRompio=1;
                                break;
                            
                        }
                        
                    }

                    if(seRompio==0)
                    {
                        SePudo=1;
                        c=0;
                        for(int i=mx; i<mx+sizeC; i++)
                        {
                            matriz[i][my]=cad[c];
                            c++;
                        }
                    }
                }

            }
        }

    }

    int c;
    archivo<<"Institución: "<<getEscuela()<<endl;
    archivo<<"Docente: "<<getDocente()<<endl;
    archivo<<"Fecha: "<<getFecha()<<endl;
    archivo<<titulo<<endl<<endl;
    res<<"Institución: "<<getEscuela()<<endl;
    res<<"Docente: "<<getDocente()<<endl;
    res<<"Fecha: "<<getFecha()<<endl;
    res<<titulo<<endl<<endl;

     for(int i=0; i<30; i++)
    {
    
        for(int j=0; j<20; j++)
        {
            
            res<<matriz[i][j]<<" ";
        }
        res<<endl;    
    }

    for(int i=0; i<30; i++)
    {
    
        for(int j=0; j<20; j++)
        {
            if(matriz[i][j]==' ')
            {
                c = 65 + rand() % 26; 
                char ch = (char) c; 
                matriz [i][j] = ch;
            }
            
            archivo<<matriz[i][j]<<" ";
        }
        archivo<<endl;    
    }
    archivo<<endl;

    
    for(auto it = x.begin(); it < x.end(); it++)
    {
        cad = *it;
        archivo<< cad<<endl;
    }

    res.close();
    archivo.close();
}









