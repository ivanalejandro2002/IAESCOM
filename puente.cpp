#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> menor(32,INT_MAX);
vector<int> origen(32,0);
vector<int> tiempos= {1,2,5,10};
void busca(vector<int> &tiempos, int mascarita,int t,int padre){
    //cout<<mascarita<<","<<t<<","<<padre<<"\n";
    menor[mascarita] = min(menor[mascarita],t);
    origen[mascarita] = padre;
    bool x = (mascarita & (1<<4));
    int nuevamascara;
    bool pi,pj;
    int extra;
    if(!x){
        for(int i=0;i<4;i++){
            for(int j = i;j<4;j++){
                extra = 0;
                nuevamascara = (mascarita^(1<<4));
                pi = !(mascarita & (1<<i));
                pj = !(mascarita & (1<<j));
                if(pi && pj){
                    if(i!=j){
                        extra=max(extra,tiempos[i]);
                        extra=max(extra,tiempos[j]);
                    }else{
                        extra= max(extra,tiempos[i]);
                    }
                }else{
                    if(pi)extra=max(extra,tiempos[i]);
                    if(pj)extra=max(extra,tiempos[j]);
                }
                //cout<<tiempos[i]<<","<<tiempos[j]<<"\n";
                //cout<<pi<<","<<pj<<","<<i<<","<<j<<"::"<<extra<<"\n";
                nuevamascara |= (1<<i);
                nuevamascara |= (1<<j);
                //cout<<pi<<","<<pj<<"::"<<nuevamascara<<"\n";
                if(!(pi || pj))continue;

                if(menor[nuevamascara]>t+extra)busca(tiempos,nuevamascara,t+extra,mascarita);
            }
        }
    }else{
        for(int i=0;i<4;i++){
            for(int j = i;j<4;j++){
                nuevamascara = (mascarita^(1<<4));
                pi = (mascarita & (1<<i));
                pj = (mascarita & (1<<j));
                int extra = 0;
                if(pi && pj){
                    if(pi!=pj){
                        extra=max(extra,tiempos[i]);
                        extra=max(extra,tiempos[j]);
                    }else{
                        extra= max(extra,tiempos[i]);
                    }
                }else{
                    if(pi)extra=max(extra,tiempos[i]);
                    if(pj)extra=max(extra,tiempos[j]);
                }
                nuevamascara &= ~(1<<i);
                nuevamascara &= ~(1<<j);
                //cout<<pi<<","<<pj<<"::"<<nuevamascara<<"\n";
                if(!(pi || pj))continue;
                if(menor[nuevamascara]>t+extra)busca(tiempos,nuevamascara,t+extra,mascarita);
            }
        }
    }
}
int main(){
    vector<int> tiempos= {1,2,5,10};
    int mascarita = 0;
    menor[0] = 0;
    busca(tiempos,mascarita,0,-1);
    int actual = 31;
    vector<int> datos;
    for(int i=0;i<32;i++){
        cout<<i<<"::"<<menor[i]<<","<<origen[i]<<"\n";
    }
    while(actual>0){
        datos.push_back(actual);
        actual = origen[actual];
    }
    datos.push_back(0);
    reverse(datos.begin(),datos.end());
    for(auto z:datos){
        cout<<z<<",";
    }
    cout<<"\n";
    for(int i=1;i<datos.size();i++){
        int w = datos[i-1]^datos[i];
        int x = datos[i-1]&(1<<4);
        if(!x){
            cout<<"Las personas con tiempo: ";
            bool algun = 0;
            for(int i=0;i<4;i++){
                if((w&(1<<i))){
                    if(algun)cout<<"y ";
                    cout<<tiempos[i]<<" ";
                    algun = 1;
                }
            }
            cout<<"cruzan el puente\n";
        }else{
            cout<<"Las personas con tiempo: ";
            bool algun = 0;
            for(int i=0;i<4;i++){
                if((w&(1<<i))){
                    if(algun)cout<<"y ";
                    cout<<tiempos[i]<<" ";
                    algun = 1;
                }
            }
            cout<<"regrezan el al inicio\n";
        }
    }
}