#include <iostream>
#include <vector>
#include <algorithm>
#include "arbol.cpp"
using namespace std;
vector<int> inicial={4,3,2,1};
vector<int> meta = {1,2,3,4};
int costo(vector<short> &actual){
    int total = 0;
    int xfact = 1;
    for(int i=meta.size()-1;i>=0;i--){
        int j = 0;
        while(actual[j]!=inicial[i])j++;
        total+=xfact*abs(j-i);
        xfact*=meta.size();
    }
    return total;
}
bool busca(arbol *nodo,vector<bool> &vistos, int actual, int meta){
    bool encontrado = 0;
    if(actual==meta){
        nodo->respuesta();
        return 1;
    }
    vector<short> aux(4);
    aux[0] = actual/1000;
    aux[1] = (actual/100)%10;
    aux[2] = (actual/10)%10;
    aux[3] = (actual%10);
    arbol *sig;
    int v = aux[0]*1000+aux[1]*100+aux[2]+aux[3]*10;
    sig = nodo->agrega(v);
    swap(aux[2],aux[3]);
    nodo->prioridades.push_back({sig, costo(aux) });
    swap(aux[2],aux[3]);

    v = aux[0]*1000+aux[1]*10+aux[2]*100+aux[3];
    sig = nodo->agrega(v);
    swap(aux[1],aux[2]);
    nodo->prioridades.push_back({sig, costo(aux) });
    swap(aux[1],aux[2]);

    v = aux[0]*100+aux[1]*1000+aux[2]*10+aux[3];
    sig = nodo->agrega(v);
    swap(aux[0],aux[1]);
    nodo->prioridades.push_back({sig, costo(aux) });
    swap(aux[0],aux[1]);

    sort(nodo->prioridades.begin(),nodo->prioridades.end());

    for(auto z:nodo->prioridades){
        if(!vistos[z.sig->estado] && !encontrado){
            vistos[z.sig->estado]=1;
            encontrado|=busca(z.sig,vistos,z.sig->estado,meta);
        }
    }
    return encontrado;
}
void buscar(arbol *nodo, int actual, int meta){
    vector<bool> vistos(10001);
    vistos[actual]=1;
    busca(nodo,vistos,actual,meta);
}
void solve(){
    int hashinicio = inicial[0]*1000+inicial[1]*100+inicial[2]*10+inicial[3];
    int hashmeta = meta[0]*1000+meta[1]*100+meta[2]*10+meta[3];
    arbol *busqueda = new arbol(hashmeta,nullptr);
    buscar(busqueda,hashmeta,hashinicio);
}
int main(){
    solve();
}