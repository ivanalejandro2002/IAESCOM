#ifndef arbolnodo_cabecera
#define arbolnodo_cabecera
#include <vector>
#include <iostream>
using namespace std;
struct arbol;
struct elementos{
    arbol *sig;
    int prioridad;
};
bool operator < (elementos a, elementos b){
    return a.prioridad<b.prioridad;
}
struct arbol{
    int estado;
    arbol *padre;
    vector<arbol *> hijos;
    vector<elementos> prioridades;
    arbol(int v,arbol *papacito):padre(papacito),estado(v),hijos({}),prioridades({}){};
    arbol *agrega(int transicion){
        arbol *nuevo = new arbol(transicion,this);
        hijos.push_back(nuevo);
        return nuevo;
    }
    void respuesta(){
        if(this==nullptr)return;
        cout<<"["<<estado/1000<<","<<(estado/100)%10<<","<<(estado/10)%10<<","<<estado%10<<"]";
        this->padre->respuesta();
    }
};
#endif