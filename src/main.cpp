#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Parte 1: escreva aqui as classes Astronauta, Voo e Agencia.

class Astronauta
{
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

public:
    Astronauta(string cpf, string nome, int idade)
    {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        this->vivo = true;
        this->disponivel = true;
    }
    string getCpf()
    {
        return cpf;
    }
    string getNome()
    {
        return nome;
    }
    int getIdade()
    {
        return idade;
    }

    bool estaVivo()
    {
        return vivo;
    }

    bool estaDisponivel()
    {
        return disponivel;
    }

    void embarcar()
    {
        disponivel = false;
    } // fica indisponivel
    void desembarcar()
    {
        if (vivo)
        {
            disponivel = true;
        }
    } // volta a ficar disponivel, se estiver vivo
    void morrer()
    {
        vivo = false;
    }
};

class Voo
{
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo)
    {
        this->codigo = codigo;
        this->estado = "Planejado";
        cpfs = {};
    }

    int getCodigo()
    {
        return codigo;
    }

    string getEstado()
    {
        return estado;
    }

    int getQuantidadeAstronautas()
    {
        return cpfs.size();
    }

    string getCpf(int posicao)
    {
        return cpfs[posicao];
    }
    // ```text: planejado, em curso, finalizado com sucesso, finalizado com explosao

    bool temAstronauta(string cpf)
    {
        for (int i = 0; i < cpfs.size(); i++)
        {
            if (cpf == cpfs[i])
            {
                return true;
            }
        }

        return false;
    }

    void adicionarAstronauta(string cpf)
    {
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf)
    {
        for (int i = 0; i < cpfs.size(); i++)
        {
            if (cpfs[i] == cpf)
            {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }
        return false;
        // remover se tiver na dentro
    }
    // false se o CPF nao estava no voo
    void lancar()
    {
        estado = "Em Curso";
    }

    void explodir()
    {
        estado = "Finalizado com explosao";
    }
    void finalizar()
    {
        estado = "Finalizado com sucesso";
    }
};

class Agencia
{
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf)
    {
        for (int i = 0; i < astronautas.size(); i++)
        {
            if (astronautas[i].getCpf() == cpf)
            {
                return i;
            }
        }
        return -1;
    }

    int buscarVoo(int codigo)
    {
        for (int i = 0; i < voos.size(); i++)
        {
            if (voos[i].getCodigo() == codigo)
            {
                return i;
            }
        }
        return -1;
    }

public:
    void agencia()
    {
        astronautas = {};
        voos = {};
    }

    void cadastrarAstronauta(string cpf, string nome, int idade)
    {
        if (buscarAstronauta(cpf) == -1)
        {
            astronautas.emplace_back(cpf, nome, idade);
            cout << "OK: astronauta " << cpf << " cadastrado" << endl;
        }
        else
        {
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
        }
    }
    void cadastrarVoo(int codigo)
    {
        if (buscarVoo(codigo) == -1)
        {
            voos.emplace_back(codigo);
            cout << "OK: voo " << codigo << " cadastrado" << endl;
        }
        else
        {
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
        }
    }
    void adicionarAstronauta(string cpf, int codigo)
    {
        int posicao_ast = buscarAstronauta(cpf);
        if (posicao_ast == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        } 
        
        int posicao_voo = buscarVoo(codigo);
        if (posicao_voo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        Voo& voo = voos[posicao_voo];
        if (voo.getEstado() != "Planejado"){
            cout << "ERRO: voo " << codigo << "nao esta planejado" << endl;
            return;
        }
        Astronauta astronauta = astronautas[posicao_ast];
        if (!astronauta.estaVivo()){
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }
        if (voo.temAstronauta(cpf)){
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }
       
        voo.adicionarAstronauta(cpf);
        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
        
    }
    void removerAstronauta(string cpf, int codigo){
    
        int posicao_ast = buscarAstronauta(cpf);
        if (posicao_ast == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        int posicao_voo = buscarVoo(codigo);
        if (posicao_voo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        Voo& voo = voos[posicao_voo];
        if (voo.getEstado() != "Planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
      
        if (voo.removerAstronauta(cpf)){
             cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
        } else{
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
        }
        
    }
    void lancarVoo(int codigo)
    {

        int pos_voo = buscarVoo(codigo);
        if (pos_voo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        
        Voo& voo = voos[pos_voo];
        if (voo.getEstado() != "Planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if (voo.getQuantidadeAstronautas() == 0){
            cout << "ERRO: voo " << codigo  << " nao possui astronautas" << endl;

        }
        bool vivos = true;
        bool disponivel = true;
        for (int i = 0; i < voo.getQuantidadeAstronautas(); i++)
        {
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf);
            Astronauta astronauta = astronautas[pos_astro];
            if (!astronauta.estaVivo())
            {
                vivos = false;
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
            if (!astronauta.estaDisponivel())
            {
                disponivel = false;
                cout << "ERRO: astronauta " << cpf << " nao esta disponivel" << endl;
                return;
            }
        }

        if (vivos && disponivel)
        {
            voo.lancar();
            cout << "OK: voo " << codigo << " lancado" << endl;
            for (int i = 0; i < voo.getQuantidadeAstronautas(); i++)
            {
                string cpf = voo.getCpf(i);
                int pos_astro = buscarAstronauta(cpf);
                Astronauta astronauta = astronautas[pos_astro];
                astronauta.embarcar();
            }
        }
    }
    void explodirVoo(int codigo)
    {
        int pos_voo = buscarVoo(codigo);
        if (pos_voo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        Voo& voo = voos[pos_voo];
        if (voo.getEstado() != "Em curso"){
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        voo.explodir();
        cout << "OK: voo " << codigo << " explodiu" << endl;
        for (int i = 0; i < voo.getQuantidadeAstronautas(); i++)
        {
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf);
            Astronauta astronauta = astronautas[pos_astro];
            astronauta.morrer();
        }
    }
    void finalizarVoo(int codigo)
    {
        int pos_voo = buscarVoo(codigo);
        if (pos_voo < 0)
        {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl; 
            return; // nao é um voo cadastrado
        }
        Voo& voo = voos[pos_voo];
          if (voo.getEstado() != "Em curso"){
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        voo.finalizar();
        cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
        for (int i = 0; i < voo.getQuantidadeAstronautas(); i++)
        {
            string cpf = voo.getCpf(i);
            int pos_astro = buscarAstronauta(cpf);
            Astronauta astronauta = astronautas[pos_astro];
            astronauta.desembarcar();
        }
    }
    void listarVoos()
    {
        cout << "LISTA DE VOOS" << endl;
        cout << "== planejado ==" << endl;
        // Planejado
        //  to com dor de cabeça nessa parte
        int num_plan = 0;
        for (int i = 0; i < voos.size(); i++)
        {
            if (voos[i].getEstado() == "Planejado")
            {
                num_plan++;
                cout << "Voo " << voos[i].getCodigo() << ": ";
                if (voos[i].getQuantidadeAstronautas() > 0)
                {
                    int quant = voos[i].getQuantidadeAstronautas();
                    for (int j = 0; j < quant; j++)
                    {
                        string cpf = voos[i].getCpf(j);
                        int pos_astro = buscarAstronauta(cpf);
                        Astronauta astronauta = astronautas[pos_astro];
                        cout << astronauta.getCpf() << " " << astronauta.getNome();
                        if (j < quant - 1)
                        {
                            cout << ", ";
                        }

                        cout << endl;
                    }
                }
                else
                {
                    cout << "sem astronautas" << endl;
                }
            }
        }
        if (num_plan == 0)
        {
            cout << "(nenhum)" << endl;
        }

        // em curso
        cout << "== em curso ==" << endl;
        int num_curso = 0;
        for (int i = 0; i < voos.size(); i++)
        {
            if (voos[i].getEstado() == "Em Curso")
            {
                num_curso++;
                cout << "Voo " << voos[i].getCodigo() << ": ";
                if (voos[i].getQuantidadeAstronautas() > 0)
                {
                    int quant = voos[i].getQuantidadeAstronautas();
                    for (int j = 0; j < quant; j++)
                    {
                        string cpf = voos[i].getCpf(j);
                        int pos_astro = buscarAstronauta(cpf);
                        Astronauta astronauta = astronautas[pos_astro];
                        cout << astronauta.getCpf() << " " << astronauta.getNome();
                        if (j < quant - 1)
                        {
                            cout << ", ";
                        }
                    }
                }
                else
                {
                    cout << "sem astronautas";
                }
                cout << endl;
            }
            
        }
        if (num_curso == 0)
            {
                cout << "(nenhum)" << endl;
            }

        // finalizado com sucesso
        cout << "== finalizado com sucesso ==" << endl;
        int num_suc = 0;
        for (int i = 0; i < voos.size(); i++)
        {
            if (voos[i].getEstado() == "finalizado com sucesso")
            {
                num_suc = +1;
                cout << "Voo " << voos[i].getCodigo() << ": ";
                if (voos[i].getQuantidadeAstronautas() > 0)
                {
                    int quant = voos[i].getQuantidadeAstronautas();
                    for (int j = 0; j < quant; j++)
                    {
                        string cpf = voos[i].getCpf(j);
                        int pos_astro = buscarAstronauta(cpf);
                        Astronauta astronauta = astronautas[pos_astro];
                        cout << astronauta.getCpf() << " " << astronauta.getNome();
                        if (j < quant - 1)
                        {
                            cout << ", ";
                        }
                    }
                }
                else
                {
                    cout << "sem astronautas";
                }
                cout << endl;
            }
        }
        if (num_suc == 0)
            {
                cout << "(nenhum)" << endl;
            }
        // finalizado com explosao
        cout << "== finalizado com explosao ==" << endl;
        int num_exp = 0;
        for (int i = 0; i < voos.size(); i++)
        {
            if (voos[i].getEstado() == "finalizado com explosao")
            {
                num_exp = +1;
                cout << "Voo " << voos[i].getCodigo() << ": ";
                if (voos[i].getQuantidadeAstronautas() > 0)
                {
                    int quant = voos[i].getQuantidadeAstronautas();
                    for (int j = 0; j < quant; j++)
                    {
                        string cpf = voos[i].getCpf(j);
                        int pos_astro = buscarAstronauta(cpf);
                        Astronauta astronauta = astronautas[pos_astro];
                        cout << astronauta.getCpf() << " " << astronauta.getNome();
                        if (j < quant - 1)
                        {
                            cout << ", ";
                        }
                    }
                }
                else
                {
                    cout << "sem astronautas";
                }
                cout << endl;
            }
        
        }
        if (num_exp == 0)
            {
                cout << "(nenhum)" << endl;
            }
    }

    void listarMortos()
    {
        cout << "ASTRONAUTAS MORTOS" << endl;
        int num_mortos = 0;
        for (int i = 0; i < astronautas.size(); i++)
        {
            if (!astronautas[i].estaVivo())
            {
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " - voos:";
                num_mortos++;
                int num_voos = 0;
                for (int j = 0; j < voos.size(); j++)
                {
                    if (voos[j].temAstronauta(astronautas[i].getCpf()) && voos[j].getEstado() != "Planejado")
                    {
                        cout << " " << voos[j].getCodigo();
                        num_voos++;
                    }
                }
                if (num_voos == 0)
                {
                    cout << "(nenhum)";
                }
                cout << endl;
            }
        }
        if (num_mortos == 0)
        {
            cout << "(nenhum)" << endl;
        }
    }
};

// Depois, em cada comando, apague a linha do cout com "TODO" e descomente
// a chamada ao metodo da Agencia.

int main()
{
    Agencia agencia;
    string comando;

    while (cin >> comando)
    { // le uma palavra; para no FIM ou quando a entrada acaba
        if (comando == "FIM")
        {
            break;
        }
        else if (comando == "CADASTRAR_ASTRONAUTA")
        {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome); // o nome vem por ultimo e pode ter espacos

            agencia.cadastrarAstronauta(cpf, nome, idade);
        }
        else if (comando == "CADASTRAR_VOO")
        {
            int codigo;
            cin >> codigo;

            agencia.cadastrarVoo(codigo);
        }
        else if (comando == "ADICIONAR_ASTRONAUTA")
        {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.adicionarAstronauta(cpf, codigo);
        }
        else if (comando == "REMOVER_ASTRONAUTA")
        {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.removerAstronauta(cpf, codigo);
        }
        else if (comando == "LANCAR_VOO")
        {
            int codigo;
            cin >> codigo;

            agencia.lancarVoo(codigo);
        }
        else if (comando == "EXPLODIR_VOO")
        {
            int codigo;
            cin >> codigo;

            agencia.explodirVoo(codigo);
        }
        else if (comando == "FINALIZAR_VOO")
        {
            int codigo;
            cin >> codigo;

            agencia.finalizarVoo(codigo);
        }
        else if (comando == "LISTAR_VOOS")
        {

            agencia.listarVoos();
        }
        else if (comando == "LISTAR_MORTOS")
        {

            agencia.listarMortos();
        }
        else
        {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;}
