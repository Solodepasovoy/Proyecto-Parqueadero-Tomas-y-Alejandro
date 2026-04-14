#include <iostream>
#include <fstream>
using namespace std;

char MostrarElMenu(string NombreParq, int precio){
    char opcion;

    cout<<"Bienvenido a "<<NombreParq<<"!\n";
    cout<<"Cobramos $"<<precio<<" COP por minuto dentro del parqueadero\n";
    cout<<"Que desearía hacer?"<<endl;
    cout<<endl;
    cout << "v - ver lista de parqueaderos y disponibilidad\n";
    cout <<"a - agregar nuevo carro al parqueadero\n";
    cout <<"s - sacar un carro del parqueadero\n";
    cout <<"p - consultar placa y en que espacio del parqueadero esta\n";
    cout <<"c - consultar el valor total del parqueadero para cierta placa (se actualiza cada minuto)\n";
    cout <<"s - salir\n";

    cin>>opcion;
    return opcion;
}

bool CrearParqueadero(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero, reinicie el codigo\n";
        return false;
    } else {
        archivo << "Inaccesible;ENTRADA;";
        for (int i = 0; i < 4; i++){
            archivo << "Inaccesible;Inaccesible;Parking;";
        }
        archivo << "Inaccesible;SALIDA;\n";

        for (int k = 0; k < 2; k++){
            for (int i = 0; i < 6 ;i++){
                archivo << "Parking;Via;";
                for (int j = 0; j < 4; j++){
                    archivo << "Parking;Parking;Via;";
                }
                archivo << "Parking;Via\n";
            }
            archivo<<"Parking;";
            for (int i = 0; i < 15; i++){
                archivo<<"Via;";
            }
            archivo<<endl;
        }
        cout << "El parqueadero ha sido creado con exito y se guardo como Parking.csv\n";
        return true;
    }
}

int main(){
CrearParqueadero("Parking.csv");
MostrarElMenu("Parqueadero Skibidi", 200);
}