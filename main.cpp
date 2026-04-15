#include <iostream>
#include <fstream>
using namespace std;

char opcion;

char MostrarElMenu(string NombreParq, int preciocarros, int preciomotos, int preciosbici){
    cout<<"Bienvenido a "<<NombreParq<<"!\n";
    cout<<"Cobramos  a carros $"<<preciocarros<<" COP/min, a motos "<<preciomotos<<" y a bicicletas "<<preciosbici<<".\n";
    cout<<"Que desearía hacer?"<<endl;
    cout<<endl;
    cout <<"m - presione m para ver este menu de nuevo";
    cout <<"v - ver lista de parqueaderos y disponibilidad\n";
    cout <<"c - agregar nuevo vehículo al parqueadero\n";
    cout <<"s - sacar un vehículo del parqueadero\n";
    cout <<"p - consultar placa/id y en que espacio del parqueadero esta\n";
    cout <<"d - consultar el valor del dinero total del parqueadero para cierto vehículo (se actualiza cada minuto)\n";
    cout <<"s - salir\n";
    cout <<"Opción: ";
    cin>>opcion;
    cout<<endl;
    return opcion;

}

bool CrearParqueaderoCarros(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de carros, reinicie el codigo\n";
        return false;
    } else {
        archivo << "Bloqueado;ENTRADA;";
        for (int i = 0; i < 4; i++){
            archivo << "Bloqueado;Bloqueado;Parking;";
        }
        archivo << "Bloqueado;SALIDA;\n";

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
        cout<<"El parqueadero de carros ha sido creado con exito.\n";
        return true;
    }
}

bool CrearParqueaderoMotos(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de motos, reinicie el codigo\n";
        return false;
    } else {
        archivo<<"Entrada;";
        for (int i = 0; i < 13; i++){
            archivo<<"Bloqueado;";
        }
        archivo<<"SALIDA;\n";
        
        for (int k = 0; k < 3; k++){
            for (int i = 0; i < 15; i++){
                archivo<<"Via;";
            }
            archivo<<endl;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 5; j++){
                    archivo<<"Via;Parking;Parking;";
                }
                archivo<<endl;
            }
        }
        cout<<"El parqueadero de motos ha sido creado con exito.\n";
        return true;
    }
}

bool CrearParqueaderoBicis(string ruta){
    ofstream archivo(ruta);
    if (!archivo.is_open()){
        cout<<"No se pude crear el parqueadero de bicicletas, reinicie el codigo\n";
        return false;
    } else {
        archivo<<"Entrada;";
        for (int i = 0; i < 13;i++){
            archivo<<"Bloqueado;";
        }
        archivo<<"Salida;";
        archivo<<endl;
        for (int i = 0; i < 15; i++){
            archivo<<"Via;";
        }
        archivo<<endl;
        for (int i = 0; i < 15; i++){
            archivo<<"Parking;";
        }
        cout << "El parqueadero de bicicletas ha sido creado con exito.\n";
        return true;
}
}

bool VerLista(){
return true;
}

bool AgregarVehiculo(){
return true;
}

bool SacarVehiculo(){
return true;
}

bool ConsultarPlaca(){
return true;
}

bool ConsultarValor(){
return true;
}

int main(){
bool regresarmenu = false;
CrearParqueaderoCarros("ParkingCarros.csv");
cout<<endl;
CrearParqueaderoMotos("ParkingMotos.csv");
cout<<endl;
CrearParqueaderoBicis("ParkingBicis.csv");
cout<<endl;

do{
cout<<endl;
MostrarElMenu("Parqueadero Skibidi",300,175,80);

if (opcion == 'm'){
regresarmenu = true;
}else if (opcion == 'v'){
    regresarmenu = false;
}else if (opcion == 'c'){
    regresarmenu = false;
} else if (opcion == 's'){
    regresarmenu = false;
} else if (opcion == 'p'){
    regresarmenu = false;
} else if (opcion == 'd'){
    regresarmenu = false;
} else if (opcion == 's'){
    regresarmenu = false;
    cout<<"Adios\n";
} else {
    cout<<"Ingrese un comando valido, regresando al menu\n";
    regresarmenu = true;
}
}while (regresarmenu == true);

return 0;
}