#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Parte 1: escreva aqui as classes Astronauta, Voo e Agencia.

class Astronauta{
    private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
     Astronauta(string cpf, string nome, int idade){
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = true;
        this->disponivel = true;
    }
    string getCpf(){
        return cpf;
    }
    string getNome(){
        return nome;
    }
    int getIdade(){
        return idade;
    }

    bool estaVivo(){
        return vivo;
    }

    bool estaDisponivel(){
        return disponivel;
    }

    void embarcar(){
        disponivel = false;
    }     // fica indisponivel
    void desembarcar(){
        if(vivo){
            disponivel = true;
        }
    }  // volta a ficar disponivel, se estiver vivo
    void morrer(){
        vivo = false;
    }
};


class Voo {
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo){
        this->codigo = codigo;
        this->estado = "Planejado";
        cpfs = {};
    }

    int getCodigo(){
        return codigo;
    }

    string getEstado(){
        return estado;
    }

    int getQuantidadeAstronautas(){
        return cpfs.size();
    }

    string getCpf(int posicao){
       return cpfs[posicao];
    }
    // ```text: planejado, em curso, finalizado com sucesso, finalizado com explosao
    
    bool temAstronauta(string cpf){
        for (int i = 0; i < cpfs.size(); i++){
            if (cpf == cpfs[i]){
                return true;
            }
        }

        return false;
    }

    void adicionarAstronauta(string cpf){
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf){
        for (int i = 0; i <cpfs.size(); i++){
            if (cpfs[i] == cpf){
                cpfs.erase(cpfs.begin() + i);
                break;
            }
        }
        return false;
        // remover se tiver na dentro 
    } 
     // false se o CPF nao estava no voo
    void lancar(){
        estado = "Em Curso";
    }

    void explodir(){
        estado = "Finalizado com explosao";
    }
    void finalizar(){
        estado = "Finalizado com sucesso";
    }
};

class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf){
        for(int i = 0; i < astronautas.size(); i++){
            if (astronautas[i].getCpf() == cpf){
                return i;
            }
        }
     return -1;
    }   

    int buscarVoo(int codigo){
    for (int i = 0; i < voos.size(); i++){
        if (voos[i].getCodigo() == codigo){
            return i;
        }
    }
    return -1;
}          

public:
    void agencia(){
         astronautas = {};
         voos = {};
    }
    void cadastrarAstronauta(string cpf, string nome, int idade){
        astronautas.emplace_back(cpf, nome, idade);
    }
    void cadastrarVoo(int codigo){
        voos.emplace_back(codigo);
    }
    void adicionarAstronauta(string cpf, int codigo){
        int posicao_ast = buscarAstronauta(cpf);
        int posicao_voo = buscarVoo(codigo);
        if ((posicao_ast >= 0) && (posicao_voo >= 0)){
            voos[posicao_voo].adicionarAstronauta(cpf);
        }
    }
    void removerAstronauta(string cpf, int codigo){
         int posicao_ast = buscarAstronauta(cpf);
        int posicao_voo = buscarVoo(codigo);
        if ((posicao_ast >= 0) && (posicao_voo >= 0)){
            voos[posicao_voo].removerAstronauta(cpf);
        }
    }
    void lancarVoo(int codigo){
        int pos_voo = buscarVoo(codigo);
        if (pos_voo < 0){
            return; // nao é um voo cadastrado
        }
        Voo voo = voos[pos_voo];
        bool vivos = true;
        bool disponivel = true;
        for (int i = 0; i < voo.getQuantidadeAstronautas(); i++){
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf); 
            Astronauta astronauta = astronautas[pos_astro];
            if (!astronauta.estaVivo()){
                vivos = false;
            }
            if (!astronauta.estaDisponivel()){
                disponivel = false;
            }
    }

    if (vivos && disponivel){
        voo.lancar();
         for (int i = 0; i < voo.getQuantidadeAstronautas(); i++){
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf); 
            Astronauta astronauta = astronautas[pos_astro];
            astronauta.embarcar();
         }
    }
}
    void explodirVoo(int codigo){
        int pos_voo = buscarVoo(codigo);
        if (pos_voo < 0){
            return; // nao é um voo cadastrado
        }
        Voo voo = voos[pos_voo];
        voo.explodir();
         for (int i = 0; i < voo.getQuantidadeAstronautas(); i++){
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf); 
            Astronauta astronauta = astronautas[pos_astro];
            astronauta.morrer();
    }
 }
    void finalizarVoo(int codigo){
        int pos_voo = buscarVoo(codigo);
        if (pos_voo < 0){
            return; // nao é um voo cadastrado
        }
        Voo voo = voos[pos_voo];
        voo.finalizar();
         for (int i = 0; i < voo.getQuantidadeAstronautas(); i++){
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf); 
            Astronauta astronauta = astronautas[pos_astro];
            astronauta.desembarcar();
    }
    }
    void listarVoos(){

    }
    void listarMortos();
};

// Depois, em cada comando, apague a linha do cout com "TODO" e descomente
// a chamada ao metodo da Agencia.

int main() {
    // TODO: criar a Agencia aqui, por exemplo:  Agencia agencia;
    string comando;

    while (cin >> comando) {   // le uma palavra; para no FIM ou quando a entrada acaba
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);   // o nome vem por ultimo e pode ter espacos
            cout << "TODO " << comando << endl;
            // TODO: agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            cout << "TODO " << comando << endl;
            // TODO: agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            cout << "TODO " << comando << endl;
            // TODO: agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            cout << "TODO " << comando << endl;
            // TODO: agencia.listarMortos();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}

