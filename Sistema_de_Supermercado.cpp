#include <iostream>
#include <fstream>
using namespace std;

//adicionar produto novo
void adicionar (){

    fstream arquivo;
    string linha;
    
    arquivo.open("produtos.txt", fstream::in | fstream::out | fstream::app);//abrir o documento .txt para escrever, ler e 

    cout<<"Digite o nome do produto\n";//add nome
    string nome;
    cin.ignore();// para o /n nao interromper na escrita da string
    getline(cin, nome); //fazendo assim a string aceita espaços quando o usuario digita
        
    while(getline(arquivo,linha)){//loop que a string(linha) recebe todo o valor da linha, comaça na primeira, depois da segunda linha, terceira...
        if(linha=="Produto: "+ nome){ // se um produto tiver o mesmo nome do que o usuario quero colocar, vai cair nesse if
            cout<<"Ja tem um produto com esse nome\n";
            return; //encerra a funçao
        }
    }
        
    arquivo.clear(); //libera o arquivo para leituras novamente
    arquivo.seekg(0);//coloca ponteiro no inicio para a segunda verificaçao

    cout<<"Digite o codigo do produto\n";//add codigo
    long long codigo;
    cin>>codigo;

    while(getline(arquivo,linha)){ //a mesma verificaçao foi feita para o codigo 
        if(linha=="Codigo: "+ to_string(codigo)){ //to_string(codigo) transforma o numero em string
            cout<<"Ja tem um produto com esse codigo\n";
            return;
        }
    }

    arquivo.clear(); //libera o arquivo para leituras novamente

    arquivo<<"Produto: "<<nome<<endl; //adicioa o nome no artigo com uma identificação para saber que é o nome do produto
    //foi colocado aqui para nao ser escrito no artigo antes da verificaçao do codigo
    arquivo<<"Codigo: "<<codigo<<endl;

    //o resto das informações nao precisa da verificaçao,pois, por exemplo, é possivel ter dois produtos com a mesma validade

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

    }while(opcaoDePesquisa != 1 && opcaoDePesquisa != 2); //se for colocado um numero errado aparece novamente a opcao de escolha

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
        
        if(!achou){//caso nao encontre o produto
            cout<<"Produto nao encontrado\n";
            return;
        }
    }

    else if(opcaoDePesquisa==2){//buscar pelo produto pelo codigo
        
        arquivo.open("produtos.txt", fstream::in);
        cout<<"Digite o codigo do produto\n";
        cin.ignore();
        getline(cin,codigoBuscar);

        bool achou=false;//para se o produto nao for achado conseguir avidar

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
        if(!achou){//caso nao encontre o produto
            cout<<"Produto nao encontrado\n";
            return;
        }
    }    
    int opcao;
    do{ 
        cout<<endl<<"Deseja editar editar, excluir o produto ou sair?\n" 
        <<"[1]=Sair, [2]=Editar, [3]=Excluir\n"; //saber se precisa ser modificado algo ou nao
        cin>>opcao;

    }while(opcao != 1 && opcao != 2 && opcao != 3);   

    if(opcao==1){
        return; //sair da função
    }
    
    if(opcao==2){
        
        char resposta;
        
        do{//caso o usuario digite outra eltra
            cout<<"O que deseja editar?\n"
            <<"[N]=Nome [C]=Codigo [V]=Validade [Q]=Quantidade \n";//saber qual dado deseja editar
            cin>>resposta;

        }while(resposta!='n' && resposta!='N' && resposta!='c' && resposta!='C' && resposta!='v' && resposta!='V' && resposta!='q' && resposta!='Q');
        
        arquivo.open("produtos.txt",fstream::in);//abrir arquivo
        
        fstream copia;
        copia.open("novo.txt",fstream::out);
        /*criei um novo documento txt. Como nao é possivel apagar dados, iremos criar uma copia para armazenar as antigas
        informações, so nao iremos copiar a linha que foi editada, em vez disso, escreveremos as novas informaçoes na linha*/

        bool apagado=false; //quando for falsa copia as informaçoes no novo documento, quando for verdadeira para de copiar
        
        int contador=0; /*contador para colocar os numeros de linhas que nao precisa ser copiado para o novo documento
        (essas sao as linhas que escreveremos manualmente porque o usuario deseja editar)*/

        switch(resposta){
            case 'n':
            case 'N':{
                cout<<"Qual o novo nome?\n";//editar o nome
                string novoNome;
                cin.ignore();
                getline(cin, novoNome);

                while(getline(arquivo,linha)){ 
                    
                    if(linha==produtoV){
                        apagado=true; //quando apagado vira true nao é copiado a linha
                    }

                    if(apagado==false){
                        copia<<linha<<endl;
                    }

                    else if(apagado==true){
                        copia<<"Produto: "<<novoNome<<endl; // no lugar que a linha nao copiou é colocado a mudança
                    }
                    apagado=false; //depois é liberado para continuar copiando as linhas e colando normalmente
                }
                break;
            }
            
            case 'c':
            case 'C':{
                cout<<"Qual o novo codigo?\n";//editar o codigo do produto 
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
                    }/*porque para de copiar e colar na linha do codigo e nao no da validade? 
                    porque se colocar na validade ele pode mudar a validade de outros produtos que vencem no mesmo dia 
                    do produto escolhido, pois as linha serao iguais (o mesmo serve para quando for editar o volume). 
                    Colocando o codigo, ou o nome, não tem risco disso acontecer, ja que os codigos e os nomes 
                    de todos os produtos sao diferentes*/ 

                    if(contador==2){ //contador que faz o codigo parar de copiar por 2 linhas (linha do codigo e da validade)
                        apagado=false;
                    }

                    if(apagado==false){
                        copia<<linha<<endl;
                    }

                    if(apagado==true && contador==0){
                        copia<<codigo<<endl; //coloca novamente o codigo ja que ele parou de copiar nessa linha
                        copia<<"Validade: "<<data<<endl; //coloca a informaçao nova que foi editada

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
                    } /* 3 linhas nao seram copiadas, a do codigo, da validade(que esta entre a linha do codigo e 
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
        rename("novo.txt", "produtos.txt"); /*o novo que os dados foram passados e editados nas linhas pedidas 
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
                    apagado=true; //selecionar as linha ques nao seram reescritas no novo documento
                }
                
                if(apagado==false){
                    copia<<linha<<endl; //copia todas as informaçoes novamente menos a que usuario quer excluir
                }

                if(linha.empty()){ //selecionando linha em branco
                    apagado=false; //selecionar as linha para voltarem a serem copiadas para no novo documento
                }
            }
            arquivo.close();
            copia.close();

            remove("produtos.txt"); //deleta o antigo documento que a informaçao que queria excluir existe

            rename("novo.txt", "produtos.txt"); 
            //renomeou o documento, que nao foi copiado o produto que queria excluir, para o mesmo nome do que foi excluido 
            
            cout<<"Produto excluido com sucesso!\n";//avisa ao usuario que o conteudo foi "apagado"/excluido
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
    int contador=1; //para saber em qual linha está e poder salvar a linha correta com as suas respectivas informaçoes
    string produto, lotes;
    bool executado=false;//saber se nao tem produtos com o estoque baixo
    
    while(getline(arquivo,linha)){
                
        if(contador==1){ //quando o contador for 1 ele sempre vai estar na linha do nome do produto, pois é a primeira informaçao
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
        }/*quando encontra linha vazia (que tem antes de cada produto exeto o primeiro, por isso o contador começa em 1) 
        o contador reinicia para fazer a analise do proximo produto*/

        contador++;

    }
            
    if(!executado){
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