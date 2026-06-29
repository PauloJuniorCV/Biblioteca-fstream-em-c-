#include <iostream>
#include <fstream>
using namespace std;

//adicionar produto novo
void adicionar (){

    fstream arquivo;
    string linha;
    
    arquivo.open("produtos.txt", fstream::in | fstream::out | fstream::app);/*abrir o documento .txt para escrever, ler e para que as novas informações 
    sejam acrescentadas ao final, sem apagar o que já existe*/

    cout<<"Digite o nome do produto\n";//add nome
    string nome;
    cin.ignore();// para o /n não interromper na escrita da string
    getline(cin, nome); //fazendo assim a string aceita espaços quando o usuário digita
        
    while(getline(arquivo,linha)){//loop que a string(linha) recebe todo o valor da linha, comaça na primeira, depois da segunda linha, terceira...
        if(linha=="Produto: "+ nome){ // se um produto tiver o mesmo nome do que o usuário quer colocar, vai cair nesse if
            cout<<"Ja tem um produto com esse nome\n";
            return; //encerra a funçao
        }
    }
        
    arquivo.clear(); //libera o arquivo para leituras novamente
    arquivo.seekg(0);//coloca ponteiro no início para a segunda verificação

    cout<<"Digite o codigo do produto\n";//add código
    long long codigo;
    cin>>codigo;

    while(getline(arquivo,linha)){ //a mesma verificação foi feita para o código 
        if(linha=="Codigo: "+ to_string(codigo)){ //to_string(codigo) transforma o numero em string
            cout<<"Ja tem um produto com esse codigo\n";
            return;
        }
    }

    arquivo.clear(); //libera o arquivo para leituras novamente

    arquivo<<"Produto: "<<nome<<endl; //adicioa o nome no artigo com uma identificação para saber que é o nome do produto
    
    //o nome foi colocado no arquivo só aqui para não ser escrito no artigo antes da verificaçao do código
    
    arquivo<<"Codigo: "<<codigo<<endl;

    //o resto das informações não precisa da verificação, pois, por exemplo, é possível ter dois produtos com a mesma validade

    cout<<"Digite a validade do lote\n"; //add data de validade
    string data;
    cin.ignore();
    getline(cin, data);
    arquivo<<"Validade: "<<data<<endl;

    cout<<"Digite a quantidade de lotes\n";//add quantidade de lote
    int quantidade;
    cin>>quantidade;
    arquivo<<"Quantidade de lotes: "<<quantidade<<endl<<endl;

    arquivo.close();
}

//pesquisa de um produto para consulta, editar ou excluir
void pesquisar(){
    fstream arquivo;            
    int opcaoDePesquisa;
    do{
        cout<<"Pesquisar produtos:"<<endl;
        cout<<"[1]=Pesquisar por nome"<<endl<<"[2]=Pesquisar pelo numero do codigo"<<endl;
        cin>>opcaoDePesquisa;

    }while(opcaoDePesquisa != 1 && opcaoDePesquisa != 2); //se for colocado um número errado aparece novamente a opcao de escolha

    string nomeBuscar, codigoBuscar, linha;
    string linhaAnterior, codigo, validade, quantidade, produtoV;

    if(opcaoDePesquisa==1){ //pesquisa feita pelo nome do produto
        arquivo.open("produtos.txt", fstream::in);
        cout<<"Digite o nome do produto\n";
        cin.ignore();
        getline(cin, nomeBuscar);

        bool achou=false;//para se o produto nao for achado conseguir avidar

        while (getline(arquivo, linha)){ //loop que a string(linha) recebe todo o valor da linha, comaça na primeira, depois da segunda linha, terceira...
            if(linha=="Produto: "+nomeBuscar){
                        
                produtoV=linha;
                getline(arquivo,codigo);
                getline(arquivo,validade);
                getline(arquivo,quantidade);

                cout<<endl<<produtoV<<endl<<codigo<<endl<<validade<<endl<<quantidade<<endl;
                achou= true;//o produto foi achado
            }
        }

        arquivo.close();
        
        if(!achou){//caso não encontre o produto
            cout<<"Produto nao encontrado\n";
            return;
        }
    }

    else if(opcaoDePesquisa==2){//buscar pelo produto pelo código
        
        arquivo.open("produtos.txt", fstream::in);
        cout<<"Digite o codigo do produto\n";
        cin.ignore();
        getline(cin,codigoBuscar);

        bool achou=false;//para se o produto não for achado conseguir avisar

        while(getline(arquivo, linha)){ 
            if(linha.empty()) continue; //impede que o produto receba o valor do enter (vazio)
            if(linha=="Codigo: "+codigoBuscar){

                produtoV=linhaAnterior;
                codigo=linha;
                getline(arquivo,validade);
                getline(arquivo,quantidade);

                cout<<endl<<produtoV<<endl<<codigo<<endl<<validade<<endl<<quantidade<<endl;
                achou=true;
            }
            linhaAnterior=linha;//para o nome do produto (que esta na linha anterior) seja salvo 
        }

        arquivo.close();
        if(!achou){//caso não encontre o produto
            cout<<"Produto nao encontrado\n";
            return;
        }
    }    
    int opcao;
    do{ 
        cout<<endl<<"Deseja editar editar, excluir o produto ou sair?\n" 
        <<"[1]=Sair, [2]=Editar, [3]=Excluir\n"; //saber se precisa ser modificado algo ou não
        cin>>opcao;

    }while(opcao != 1 && opcao != 2 && opcao != 3);   

    if(opcao==1){
        return; //sair da função
    }
    
    if(opcao==2){
        
        char resposta;
        
        do{//caso o usuário digite outra letra
            cout<<"O que deseja editar?\n"
            <<"[N]=Nome [C]=Codigo [V]=Validade [Q]=Quantidade \n";//saber qual dado deseja editar
            cin>>resposta;

        }while(resposta!='n' && resposta!='N' && resposta!='c' && resposta!='C' && resposta!='v' && resposta!='V' && resposta!='q' && resposta!='Q');
        
        arquivo.open("produtos.txt",fstream::in);//abrir arquivo
        
        fstream copia;
        copia.open("novo.txt",fstream::out);
        /*cria um novo documento txt. Como não é possivel apagar dados, iremos criar uma copia para armazenar as antigas
        informações, só não iremos copiar a linha que foi editada, em vez disso, escreveremos as novas informações na linha*/

        bool apagado=false; //quando for falsa copia as informações no novo documento, quando for verdadeira para de copiar
        
        int contador=0; /*contador para colocar os números de linhas que não precisa ser copiado para o novo documento
        (essas são as linhas que escreveremos manualmente porque o usuario deseja editar)*/

        switch(resposta){
            case 'n':
            case 'N':{
                cout<<"Qual o novo nome?\n";//editar o nome
                string novoNome;
                cin.ignore();
                getline(cin, novoNome);

                while(getline(arquivo,linha)){ 
                    
                    if(linha==produtoV){
                        apagado=true; //quando "apagado" vira true não é copiado a linha
                    }

                    if(apagado==false){
                        copia<<linha<<endl;
                    }

                    else if(apagado==true){
                        copia<<"Produto: "<<novoNome<<endl; // no lugar que a linha não copiou é colocado a mudança
                    }
                    apagado=false; //depois é liberado para continuar copiando as linhas e colando normalmente
                }
                break;
            }
            
            case 'c':
            case 'C':{
                cout<<"Qual o novo codigo?\n";//editar o código do produto 
                string novoCodigo;
                cin.ignore();
                getline(cin, novoCodigo);
                
                while(getline(arquivo,linha)){
                    
                    if(linha==codigo){
                        apagado=true;
                    }

                    if(apagado==false){
                        copia<<linha<<endl;
                    }
                    else if(apagado==true){
                        copia<<"Codigo: "<<novoCodigo<<endl;
                    }
                    apagado=false;
                }

                break;
            }

            case 'v':
            case 'V':{
                cout<<"Qual a nova validade? \n";//editar a validade
                string data;
                cin.ignore();
                getline(cin, data);

                while(getline(arquivo,linha)){
                    
                    if(linha==codigo){ 
                        apagado=true;
                    }/*por que parar de copiar e colar na linha do código e não no da validade? 
                    porque se colocar na validade, ele pode mudar a validade de outros produtos que vencem no mesmo dia 
                    do produto escolhido, pois as linha serão iguais nesse caso (o mesmo serve para quando for editar o volume). 
                    Colocando o código, ou o nome, não tem risco disso acontecer, ja que os códigos e os nomes 
                    de todos os produtos são diferentes*/ 

                    if(contador==2){ //contador que faz o código parar de copiar por 2 linhas (linha do codigo e da validade)
                        apagado=false;
                    }

                    if(apagado==false){
                        copia<<linha<<endl;
                    }

                    if(apagado==true && contador==0){
                        copia<<codigo<<endl; //coloca novamente o código ja que ele parou de copiar nessa linha
                        copia<<"Validade: "<<data<<endl; //coloca a informação nova que foi editada

                    }
                    if(apagado==true){
                        contador=contador+1;
                    }
                }
                break;
            }
            case 'q':
            case 'Q':{
                cout<<"Qual e a nova quantidade de lotes?\n"; //editar a quantidade de lotes
                string novaQuantidade;
                cin.ignore();
                getline(cin, novaQuantidade);

                while(getline(arquivo,linha)){
                    
                    if(linha==codigo){
                        apagado=true;
                    }

                    if(contador==3){ 
                        apagado=false;
                    } /* 3 linhas não seram copiadas, a do código, da validade(que esta entre a linha do código e 
                    entre a que queremos editar) e a linha da quantidade(a que queremos editar)*/

                    if(apagado==false){
                        copia<<linha<<endl;
                    }

                    if(apagado==true && contador==0){
                        copia<<codigo<<endl;
                        copia<<validade<<endl;
                        copia<<"Quantidade de lotes: "<<novaQuantidade<<endl;

                    }
                    if(apagado==true){
                        contador=contador+1;
                    }
                }
                break;
            }
        }
        arquivo.close();
        copia.close();
        //os dois arquivos foram fechados

        remove("produtos.txt"); //o antigo que estava sendo copiado foi apagado
        rename("novo.txt", "produtos.txt"); /*o "novo" que os dados foram passados e editados nas linhas pedidas 
        foi renomeado com o mesmo nome do artigo que foi apagado*/

        cout<<"Produto editado com sucesso!\n";
    }
    if(opcao==3){
        
        cout<<"Certeza que deseja excluir esse produto?\n"
        <<"[S]=Sim [N]=Nao\n"; //saber se essa realmente é a escolha desejada
        char resposta;
        cin>>resposta;
        
        if(resposta=='n' || resposta=='N' ){
            return;
        }
        
        else if(resposta=='s' || resposta=='S' ){
        
            arquivo.open("produtos.txt", fstream::in);
            
            fstream copia;
            copia.open("novo.txt",fstream::out); //cria e abre um novo documento .txt

            bool apagado=false; //selecionar as linha ques seram reescritas no novo documento
            while(getline(arquivo, linha)){
                if(linha==produtoV){
                    apagado=true; //selecionar as linha ques não seram reescritas no novo documento
                }
                
                if(apagado==false){
                    copia<<linha<<endl; //copia todas as informações novamente, menos a que o usuário quer excluir
                }

                if(linha.empty()){ //selecionando linha em branco (as que não tem nada)
                    apagado=false; //selecionar as linha para voltarem a serem copiadas para no novo documento
                }
            }
            arquivo.close();
            copia.close();

            remove("produtos.txt"); //deleta o antigo documento que a informação que queria excluir existe

            rename("novo.txt", "produtos.txt"); 
            //renomeou o documento, que não copiou o produto que queria excluir, para o mesmo nome do que foi excluido 
            
            cout<<"Produto excluido com sucesso!\n";//avisa ao usuário que o conteudo foi "apagado"/excluido
        }   
        else{
            cout<<"Resposta invalida\n";
        }
    }
}

void alerta(){

    fstream arquivo;
    arquivo.open("produtos.txt", fstream::in);
    
    string linha;
    int contador=1; //para saber em qual linha o loop está e poder salvar a linha correta com as suas respectivas informações
    string produto, lotes;
    bool executado=false;//saber caso não tenha produtos com o estoque baixo
    
    while(getline(arquivo,linha)){
                
        if(contador==1){ //quando o contador for 1 ele sempre vai estar na linha do nome do produto, pois é a primeira informação
            produto=linha;
        }

        if(contador==4){ //quando o contador for 4 vai estar na linha dos lotes
            lotes=linha;
            if(lotes=="Quantidade de lotes: 1" || lotes=="Quantidade de lotes: 2" || 
                lotes=="Quantidade de lotes: 3"){ //analiza para saber se o produto tem menos de 4 lotes
                            
                cout<<"Produtos com menos de 4 no estoque:\n";
                cout<<endl<<produto<<endl<<lotes<<endl; //exibe o nome do produto e a quantidade de lotes caso tenha mesmo de 4
                executado=true;
            }
        }
                    
        if(linha==""){ 
            contador=0;
        }/*quando encontra linha vazia (que tem antes de cada produto exceto o primeiro, por isso o contador começa em 1) 
        o contador reinicia para fazer a analise do próximo produto*/

        contador++;

    }
            
    if(!executado){ //se o executado for falso significa que não encontrou nenhum produto com estoque baixo
        cout<<"Nao ha produtos com estoque baixo\n";
    }

    arquivo.close();

}

int main(){

    int opcao;
    do{

        cout<<"Digite qual opcao deseja acessar\n";
        cout<<"[1]= Cadastro, [2]= Pesquisa, [3]= Alerta de pouco estoque\n";
        cin>>opcao;

    }while(opcao != 1 && opcao !=2 && opcao !=3);

    switch(opcao){
        case 1:{
            adicionar();
            break;
        }
        case 2:{
            pesquisar();
            break;
        }
        case 3:{
            alerta();
        }
    }
    return 0;
}