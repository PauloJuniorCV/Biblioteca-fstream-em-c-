# Biblioteca fstream — C++

A biblioteca `fstream` do C++ é usada para **leitura e escrita de arquivos**. 

Tudo que um programa processa fica armazenado apenas na memória RAM, quando o programa é encerrado, esses dados são perdidos. Com o `fstream` é possível salvar essas informações em arquivos .txt.

---

## Classes principais 

- ifstream — leitura de arquivos
- ofstream — escrita em arquivos
- fstream — leitura e escrita ao mesmo tempo

---

## Comandos mais utilizados

- is_open() — verifica se o arquivo foi aberto corretamente
- getline() — lê o arquivo linha por linha
- eof() — verifica se chegou ao fim do arquivo
- close() — fecha o arquivo
- seekg() — move o cursor de leitura para uma posição específica
- seekp() — move o cursor de escrita para uma posição específica

---

## Exemplo de escrita

```cpp
#include 
using namespace std;

int main() {
    ofstream arquivo("dados.txt");
    arquivo << "Olá, mundo";
    arquivo.close();
    return 0;
}
```

## Exemplo de leitura

```cpp

#include 
using namespace std;
int main() {
    ifstream arquivo("dados.txt");
    string linha;

    while (getline(arquivo, linha)) {
        cout << linha << "\n";
    }

    arquivo.close();
    return 0;
}
```

---

## Modos de abertura utilizados no projeto

**Leitura e escrita, adicionando ao final do arquivo:**
```cpp
arquivo.open("produtos.txt", fstream::in | fstream::out | fstream::app);
```
**fstream::in** permite leitura, **fstream::out** permite escrita e **fstream::app** garante que tudo que for escrito seja adicionado ao final, sem apagar o que já existe.

---

**Somente leitura:**
```cpp
arquivo.open("produtos.txt", fstream::in);
```
Usado quando é necessário ler as informações do arquivo.

---

**Somente escrita — criação do arquivo de cópia:**
```cpp
copia.open("novo.txt", fstream::out);
```
Usado quando é necessário escrever as informações do arquivo.

---

## Outros modos disponíveis 

- fstream::trunc — apaga todo o conteúdo do arquivo ao abri-lo
- fstream::binary — abre o arquivo em modo binário, indicado para dados que não são texto puro
- fstream::ate — move o cursor para o final do arquivo ao abri-lo

---

## Funções utilizadas no projeto 

**open()** — abre o arquivo com o nome e os modos especificados. Se não existir cria automaticamente.
```cpp
fstream arquivo;
arquivo.open("produtos.txt", fstream::in | fstream::out | fstream::app);
```

---

**close()** — fecha o arquivo após o uso. Sempre utilizar quando terminar as operações.
```cpp
arquivo.close();
```

---

*getline()** — lê o arquivo linha por linha, armazenando o conteúdo em uma string e aceita espaços.
```cpp
string linha;
while(getline(arquivo, linha)){
    cout << linha << endl;
}
```

---

**clear()** — quando a leitura chega ao fim do arquivo, uma flag interna bloqueia novas leituras. O `clear()` limpa essa flag, liberando o arquivo para ser lido novamente.
```cpp
arquivo.clear();
```

---

**seekg()** — reposiciona o cursor de leitura no início do arquivo. Sempre usando junto com `clear()` para permitir uma segunda leitura.
```cpp
arquivo.clear();
arquivo.seekg(0);
```

---

**<<** — escreve informações no arquivo, da mesma forma que o `cout` exibe no terminal.
```cpp
arquivo << "Produto: Biscoito" << endl;
arquivo << "Quantidade de lotes: 5" << endl;
```

---

**remove()** — exclui um arquivo do sistema.
```cpp
remove("produtos.txt");
```

---

**rename()** — renomeia um arquivo.
```cpp
rename("novo.txt", "produtos.txt");
```

---

## Outras funções da biblioteca

**`s_open()** — verifica se o arquivo foi aberto corretamente. Recomendado usar antes de qualquer operação.
```cpp
if(arquivo.is_open()){
    cout << "Arquivo aberto com sucesso" << endl;
} else {
    cout << "Erro ao abrir o arquivo" << endl;
}
```

---

**eof()** — retorna verdadeiro quando a leitura chega ao fim do arquivo.
```cpp
if(arquivo.eof()){
    cout << "Fim do arquivo atingido" << endl;
}
```

---

**seekp()** — move o cursor de escrita para uma posição específica do arquivo.
```cpp
arquivo.seekp(0);
```

---

**tellg() e tellp()** — retornam a posição atual dos cursores de leitura e escrita, em bytes.
```cpp
streampos posLeitura = arquivo.tellg();
streampos posEscrita = arquivo.tellp();
```

---

## Estratégia de edição e exclusão

Como não é possível apagar ou modificar linhas diretamente em um arquivo de texto, a estratégia é a seguinte:

1. Abrir o arquivo original para leitura
2. Criar um novo arquivo para escrita
3. Copiar todas as linhas, pulando ou modificando apenas a desejada
4. Fechar os dois arquivos
5. Apagar o original com remove()
6. Renomear o novo com rename()

```cpp
arquivo.open("produtos.txt", fstream::in);
copia.open("novo.txt", fstream::out);

while(getline(arquivo, linha)){
    if(linha == produtoV){
        apagado = true;
    }
    if(apagado == false){
        copia << linha << endl;
    }
    apagado = false;
}

arquivo.close();
copia.close();

remove("produtos.txt");
rename("novo.txt", "produtos.txt");
```

---

## Usos comuns do fstream

- Armazenamento de cadastros
- Geração de relatórios
- Leitura de arquivos de configuração
- Registro de logs