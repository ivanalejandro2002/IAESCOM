#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#define MOD 1000000007
using namespace std;
typedef long long int ll;
struct RNG{
    ll semilla;
    ll azar(){
        semilla*=semilla;
        semilla%=MOD;
        semilla+=rand()%9999999;
        semilla*=semilla;
        semilla%=MOD;
        return semilla;
    }
}generator;
struct gato{
    vector<vector<int> > matrix;
    int tamano;
    bool turno;
    vector<bool> bot;
    bool termino;
    bool ganador;
    int libres;
    void imprime(){
        for(int i=0;i<tamano;i++){
            for(int j=0;j<tamano;j++){
                cout<<matrix[i][j];
            }
            cout<<"\n";
        }
    }
    void evalua(int y, int x){
        if(matrix[0][x]==matrix[1][x] && matrix[2][x] == matrix[1][x]){
            termino =1;
        }
        if(matrix[y][0]==matrix[y][1] && matrix[y][2] == matrix[y][1]){
            termino =1;
        }
        if(y == x){
            if(matrix[0][0] == matrix[1][1] && matrix[2][2]==matrix[1][1]){
                termino = 1;
            }
        }
        if(x+y == 2){
            if(matrix[0][2] == matrix[1][1] && matrix[2][0]==matrix[1][1]){
                termino = 1;
            }
        }
    }

    void azar(){
        int x;
        x = generator.azar();
        x%=libres;
        x++;
        int xpos,ypos;
        xpos=ypos=0;
        while(x>0){
            //cout<<"{"<<xpos<<","<<ypos<<"}";
            if(!matrix[ypos][xpos]){
                x--;
                //cout<<x<<",";
                if(x==0){
                    matrix[ypos][xpos] =(int)turno+1;
                    cout<<xpos+1<<","<<ypos+1<<"\n";
                    this->evalua(ypos,xpos);
                    return;
                }
            }
            xpos++;
            if(xpos==tamano){
                xpos=0;
                ypos = (ypos+1)%tamano;
            }
        }
    }

    void tirada(){
        int x,y;
        bool bandera = 0;
        while(!bandera){
            cin>>x>>y;
            x--;
            y--;
            if(x<0 || x>=tamano || y<0 || y>=tamano){
                cout<<"Error: No puedes colocar cosas fuera de la matriz\n";
            }else if(matrix[y][x]){
                cout<<"Error: No puedes colocar algo en una casilla ocupada\n";
            }else{
                matrix[y][x]=(int)(turno)+1;
                this->evalua(y,x);
                bandera = 1;
            }
        }
    }

    void juego(){
        while(!termino && libres>0){
            cout<<"Turno del jugador "<<(int)(turno+1)<<((bot[turno])?"(BOT):":":")<<"\n";
            this->imprime();
            if(bot[turno]){
                this->azar();
            }else{
                this->tirada();
            }
            if(termino){
                this->imprime();
                if(turno==0){
                    cout<<"Jugador 1 Gana\n";
                }else{
                    cout<<"Jugador 2 Gana\n";
                }
            }
            turno = !turno;
            libres--;
        }
        if(!termino){
            this->imprime();
            cout<<"EMPATE\n";
        }
    }
    gato(int n,bool uno,bool dos):libres(n*n),termino(0),turno(0),matrix(n+2,vector<int>(n+2)),tamano(n),bot({uno,dos}){};
};

int main(){
    srand(time(NULL));
    bool jugador1;
    bool jugador2;
    cin>>jugador1>>jugador2;
    gato juego(3,jugador1,jugador2);
    juego.juego();
}