#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PB {
    int codigo_prod , prato_ou_bebida;
    char nome_prod[50];
    float preco_prod;
};

struct garcom{
    char nome_garcom[20];
    int codigo_garcom;
};

struct pedido{
  int codigo_pedido , quantidade_pedido , cod_produto;
  struct pedido *prox;
};

struct mesa{
  int numero_mesa , cod_garcom;
  struct mesa *proximo , *anterior;
  struct pedido *pedidos;
  float total_pedido;
};

void inicializarListaPedidos(struct mesa *mesa) {
    mesa->pedidos = NULL;
    mesa->total_pedido = 0.0;
}

void cadastrarProd(struct PB listaPB[], int quantidade_PB , int iterador_prod){
    for (int i = iterador_prod; i < quantidade_PB; i++){
        scanf("%*c");
        printf("\nDigite 1 se o produto %d for prato | Digite 2 se o produto %d for bebida: ", i + 1 , i + 1);
        scanf("%d", &listaPB[i].prato_ou_bebida);

        printf("\nDigite o codigo do produto %d (numerico): ", i+1);
        scanf("%d", &listaPB[i].codigo_prod);

        printf("Digite o nome do produto %d: ", i+1);
        scanf("%s" , listaPB[i].nome_prod);

        printf("Digite o valor do produto %d: ", i+1);
        scanf("%f", &listaPB[i].preco_prod);
    }
}
void salvarProd(struct PB listaPB[], int quantidade_PB){
    FILE *arq;
    arq = fopen("PratoBebida.dat", "wb");
    if (arq){
        fwrite(listaPB , sizeof(struct PB) , quantidade_PB , arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);
    printf("\nArquivo salvo com sucesso.\n");
}

void cadastraGarcom(struct garcom lista_garcom[], int quantidade_garcom , int iterador_garcom){
    for (int i = iterador_garcom; i < quantidade_garcom; i++){
        scanf("%*c");
        printf("\nDigite o codigo do garcom %d (numerico): ", i+1);
        scanf("%d", &lista_garcom[i].codigo_garcom);

        printf("Digite o nome do garcom %d: ", i+1);
        scanf("%s", lista_garcom[i].nome_garcom);
    }
}
void salvarGarcom(struct garcom lista_garcom[], int quantidade_garcom) {
    FILE *arq = fopen("Garcom.dat" , "wb");
    if (arq){
        fwrite(lista_garcom, sizeof(struct garcom), quantidade_garcom, arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);
    printf("\nArquivo salvo com sucesso.\n");
}

void lerPratoBebida(int quantidade_PB) {
    struct PB listaPB[100];
    FILE *arq;
    arq = fopen("PratoBebida.dat", "rb");
    if (arq){
        fread(listaPB, sizeof(struct PB), 100, arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);

    printf("\n\n-=-=-=-=- Pratos e Bebidas -=-=-=-=-\n");
    for (int i = 0; i < quantidade_PB; i++) {
        if (listaPB[i].codigo_prod != 0) {
            if (listaPB[i].prato_ou_bebida == 1){
                printf("\nPRATO");
            } else if (listaPB[i].prato_ou_bebida == 2){
                printf("\nBEBIDA");
            }
            printf("\nCodigo: %d\n", listaPB[i].codigo_prod);
            printf("Nome: %s\n", listaPB[i].nome_prod);
            printf("Preco: %.2f\n", listaPB[i].preco_prod);
        }
    }
}
void lerGarcom(int quantidade_garcom){
    struct garcom lista_garcom[100];
    FILE *arq;
    arq = fopen("Garcom.dat", "rb");
    if (arq){
        fread(lista_garcom, sizeof(struct garcom), 100, arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);

    printf("\n\n----- Garcons -----\n");
    for (int i = 0; i < quantidade_garcom; i++) {
        if (lista_garcom[i].codigo_garcom != 0) {
            printf("\nCodigo: %d\n", lista_garcom[i].codigo_garcom);
            printf("Nome: %s\n", lista_garcom[i].nome_garcom);
        }
    }
}

void removerProd(struct PB listaPB[], int *quantidade_PB){
    int codigo_produto, posicao = -1;

    printf("Digite o codigo do produto que quer remover: ");
    scanf("%d", &codigo_produto);

    for (int i = 0; i < *quantidade_PB; i++) {
        if (listaPB[i].codigo_prod == codigo_produto) {
            posicao = i;
            break;
        }
    }
    if (posicao != -1) {
        for (int j = posicao; j < *quantidade_PB - 1; j++) {
            listaPB[j] = listaPB[j + 1];
        }
        (*quantidade_PB)--;
        printf("Produto removido com sucesso.\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}
void reescreverArquivoProd(struct PB listaPB[], int quantidade_PB){
    FILE *arq = fopen("PratoBebida.dat" , "wb");
    if (arq){
        fwrite(listaPB , sizeof(struct PB) , quantidade_PB , arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);

    printf("\n\n-=-=-=-=- Pratos e Bebidas -=-=-=-=-\n");
    for (int i = 0; i < quantidade_PB; i++) {
        if (listaPB[i].codigo_prod != 0) {
            if (listaPB[i].prato_ou_bebida == 1){
                printf("\nPRATO");
            } else if (listaPB[i].prato_ou_bebida == 2){
                printf("\nBEBIDA");
            }
            printf("\nCodigo: %d\n", listaPB[i].codigo_prod);
            printf("Nome: %s\n", listaPB[i].nome_prod);
            printf("Preco: %.2f\n", listaPB[i].preco_prod);
        }
    }
}
void alterarProd(struct PB listaPB[], int quantidade_PB) {
    int codigo_produto, posicao = -1;

    printf("Digite o codigo do produto que quer alterar: ");
    scanf("%d", &codigo_produto);

    for (int i = 0; i < quantidade_PB; i++) {
        if (listaPB[i].codigo_prod == codigo_produto){
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        printf("\n-=-=-=- Produto Atual -=-=-=-\n");
        printf("Nome do produto: %s\n", listaPB[posicao].nome_prod);
        printf("Codigo do produto: %d\n", listaPB[posicao].codigo_prod);
        printf("Preco do produto: %.2f\n", listaPB[posicao].preco_prod);

        printf("\n-=-=-=- Novas Informacoes -=-=-=-\n");

        printf("Digite o novo nome do produto: ");
        scanf("%*c");
        fgets(listaPB[posicao].nome_prod, 30 , stdin);

        printf("Digite o novo codigo do produto: ");
        scanf("%d", &listaPB[posicao].codigo_prod);

        printf("Digite o novo preco do produto: ");
        scanf("%f", &listaPB[posicao].preco_prod);

        printf("Produto alterado com sucesso.\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
}
void printaProd(struct PB listaPB[], int quantidade_PB) {
    int codigo_produto, posicao = -1;

    printf("Digite o codigo do produto para ver as informacoes do prato: ");
    scanf("%d", &codigo_produto);

    for (int k = 0; k < quantidade_PB; k++) {
        if (codigo_produto == listaPB[k].codigo_prod) {
            posicao = k;
            break;
        }
    }

    if (posicao != -1) {
        printf("\n-=-=-=- Produto -=-=-=-\n");
        printf("Nome do produto: %s\n", listaPB[posicao].nome_prod);
        printf("Codigo do produto: %d\n", listaPB[posicao].codigo_prod);
        printf("Preco do produto: %.2f\n", listaPB[posicao].preco_prod);
    } else {
        printf("Produto nao encontrado.\n");
    }
}

void removerGarcom(struct garcom lista_garcom[], int *quantidade_garcom){
    int codigo_garcom, posicao = -1;

    printf("Digite o codigo do garcom que quer remover: ");
    scanf("%d", &codigo_garcom);

    for (int i = 0; i < *quantidade_garcom; i++) {
        if (lista_garcom[i].codigo_garcom == codigo_garcom) {
            posicao = i;
            break;
        }
    }
    if (posicao != -1) {
        for (int j = posicao; j < *quantidade_garcom - 1; j++) {
            lista_garcom[j] = lista_garcom[j + 1];
        }
        (*quantidade_garcom)--;
        printf("Garcom removido com sucesso.\n");
    } else {
        printf("Garcom nao encontrado.\n");
    }
}
void reescreverArquivoGarcom(struct garcom lista_garcom[], int quantidade_garcom){
    FILE *arq = fopen("Garcom.dat" , "wb");
    if (arq){
        fwrite(lista_garcom , sizeof(struct garcom) , quantidade_garcom , arq);
    } else{
        printf("Arquivo falhou em abrir.");
    }
    fclose(arq);

    printf("\n\n----- Garcons -----\n");
    for (int i = 0; i < quantidade_garcom; i++) {
        if (lista_garcom[i].codigo_garcom != 0) {
            printf("\nCodigo: %d\n", lista_garcom[i].codigo_garcom);
            printf("Nome: %s\n", lista_garcom[i].nome_garcom);
        }
    }
    printf("\n");
}
void alteraGarcom(struct garcom lista_garcom[], int quantidade_garcom) {
    int codigo_garcom, posicao = -1;

    printf("Digite o codigo do garcom que quer alterar: ");
    scanf("%d", &codigo_garcom);

    for (int i = 0; i < quantidade_garcom; i++) {
        if (lista_garcom[i].codigo_garcom == codigo_garcom) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        printf("\n-=-=-=- Garcom Atual -=-=-=-\n");
        printf("Nome do garcom: %s\n", lista_garcom[posicao].nome_garcom);
        printf("Codigo do garcom: %d\n", lista_garcom[posicao].codigo_garcom);

        printf("\n-=-=-=- Novas Informacoes -=-=-=-\n");

        printf("Digite o novo nome do garcom: ");
        scanf("%*c");
        fgets(lista_garcom[posicao].nome_garcom, 20 , stdin);

        printf("Digite o novo codigo do garcom: ");
        scanf("%d", &lista_garcom[posicao].codigo_garcom);

        printf("Garcom alterado com sucesso.\n");
    } else {
        printf("Garcom nao encontrado.\n");
    }
}
void printaGarcom(struct garcom lista_garcom[], int quantidade_garcom) {
    int codigo_garcom, posicaoGarcom = -1;

    printf("Digite o codigo do garcom para ver as informacoes do prato: ");
    scanf("%d", &codigo_garcom);

    for (int k = 0; k < quantidade_garcom; k++) {
        if (codigo_garcom == lista_garcom[k].codigo_garcom) {
            posicaoGarcom = k;
            break;
        }
    }

    if (posicaoGarcom != -1) {
        printf("\n-=-=-=- Garcom -=-=-=-\n");
        printf("Nome do garcom: %s\n", lista_garcom[posicaoGarcom].nome_garcom);
        printf("Codigo do garcom: %d\n", lista_garcom[posicaoGarcom].codigo_garcom);
    } else {
        printf("Garcom nao encontrado.\n");
    }
}

void inserirFimMesa(struct mesa **lista_mesas, int numero_mesa, int cod_garcom) {
    struct mesa *aux, *nova_mesa = malloc(sizeof(struct mesa));
    if (nova_mesa) {
        nova_mesa->numero_mesa = numero_mesa;
        nova_mesa->cod_garcom = cod_garcom;
        nova_mesa->proximo = NULL;

        inicializarListaPedidos(nova_mesa);

        if (*lista_mesas == NULL) {
            *lista_mesas = nova_mesa;
            nova_mesa->anterior = NULL;
        } else {
            aux = *lista_mesas;
            while (aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = nova_mesa;
            nova_mesa->anterior = aux;
        }
    } else {
        printf("A memoria nao foi alocada corretamente para a mesa.\n");
    }
}
struct mesa* removerPedidoMesa(struct mesa **lista_mesa , int numero){
    struct mesa *aux , *remove = NULL;

    if(*lista_mesa){
        if((*lista_mesa)->numero_mesa == numero){
            remove = *lista_mesa;
            *lista_mesa = remove->proximo;
            if(*lista_mesa){
                (*lista_mesa)->anterior = NULL;
            }
        } else{
            aux = *lista_mesa;
            while((aux->proximo) && (aux->proximo->numero_mesa != numero)){
                aux = aux->proximo;
            }
            if(aux->proximo){
                remove = aux->proximo;
                aux->proximo = remove->proximo;
                if(aux->proximo != NULL){
                    aux->proximo->anterior = aux;
                }
            }
        }
    }
    return remove;
}
struct mesa* consultarMesaLista(struct mesa **lista_mesa , int numero_buscar){
    struct mesa *aux , *no_buscado = NULL;

    aux = *lista_mesa;
    while((aux) && (aux->numero_mesa != numero_buscar)){
        aux = aux->proximo;
    }
    if(aux){
        no_buscado = aux;
    }
    return no_buscado;
}
void alterarMesaLista(struct mesa **lista_mesa, int numero_alterar){
    struct mesa *aux = *lista_mesa;

    while (aux != NULL) {
        if (aux->numero_mesa == numero_alterar) {
            printf("Novo numero da mesa: ");
            scanf("%d", &aux->numero_mesa);
            printf("Novo codigo do garcom: ");
            scanf("%d", &aux->cod_garcom);
            return;
        }
        aux = aux->proximo;
    }

    printf("Mesa nao encontrada.\n");
}
void printaListaMesa(struct mesa *no){
    printf("\n-=-=-=-=- Lista -=-=-=-=- \n");
    while(no){
        printf("Numero da mesa: %d\n" , no->numero_mesa);
        printf("Codigo do garcom: %d\n\n" , no->cod_garcom);
        no = no->proximo;
    }
}

void adicionarPedido(struct mesa *mesa, struct PB listaPB[] , int codigo, int cod_prod , int quantidade) {
    struct pedido *novo = malloc(sizeof(struct pedido));
    if (novo) {
        novo->codigo_pedido = codigo;
        novo->cod_produto = cod_prod;
        novo->quantidade_pedido = quantidade;
        novo->prox = mesa->pedidos;
        mesa->pedidos = novo;

        for (int i = 0; i < 100; ++i) {
            if (listaPB[i].codigo_prod == codigo) {
                mesa->total_pedido += listaPB[i].preco_prod * novo->quantidade_pedido;
                break;
            }
        }
        
    } else {
        printf("A memoria nao foi alocada corretamente para o pedido.\n");
    }
}
void imprimirListaPedidos(struct mesa *mesa) {
    printf("Pedidos da mesa %d:\n", mesa->numero_mesa);
    struct pedido *temp = mesa->pedidos;
    while (temp != NULL) {
        printf("Codigo do pedido: %d | Codigo do produto: %d | Quantidade: %d\n", temp->codigo_pedido, temp->cod_produto , temp->quantidade_pedido);
        temp = temp->prox;
    }
    printf("Total do Pedido: %.2f\n", mesa->total_pedido);
    printf("\n");
}
void imprimirListaMesas(struct mesa *lista_mesas) {
    printf("\nLista de Mesas:\n");
    while (lista_mesas != NULL) {
        printf("Numero da Mesa: %d | Codigo do garcom: %d\n", lista_mesas->numero_mesa , lista_mesas->cod_garcom);
        imprimirListaPedidos(lista_mesas);
        lista_mesas = lista_mesas->proximo;
    }
}
void removerPedido(struct mesa *lista_mesa , struct PB listaPB[]) {
    int numero_mesa, numero_pedido;
    printf("Informe o numero da mesa para remover o pedido: ");
    scanf("%d", &numero_mesa);

    struct mesa *mesa_atual = lista_mesa;
    while (mesa_atual != NULL && mesa_atual->numero_mesa != numero_mesa) {
        mesa_atual = mesa_atual->proximo;
    }

    if (mesa_atual != NULL) {
        printf("Informe o numero do pedido que deseja remover: ");
        scanf("%d", &numero_pedido);

        struct pedido *atual = mesa_atual->pedidos;
        struct pedido *anterior = NULL;

        while (atual != NULL && atual->codigo_pedido != numero_pedido) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL) {
            if (anterior != NULL) {
                anterior->prox = atual->prox;
            } else {
                mesa_atual->pedidos = atual->prox;
            }

            for (int i = 0; i < 100; ++i) {
                if (listaPB[i].codigo_prod == atual->cod_produto) {
                    mesa_atual->total_pedido -= listaPB[i].preco_prod * atual->quantidade_pedido;
                    break;
                }
            }
            free(atual);
            printf("Pedido removido com sucesso.\n");
        } else {
            printf("Pedido nao encontrado na mesa %d.\n", numero_mesa);
        }
    } else {
        printf("Mesa nao encontrada.\n");
    }
}
void alterarPedido(struct mesa *lista_mesa , struct PB listaPB[]) {
    int numero_mesa, numero_pedido;
    printf("Informe o numero da mesa para alterar o pedido: ");
    scanf("%d", &numero_mesa);

    struct mesa *mesa_atual = lista_mesa;
    while (mesa_atual != NULL && mesa_atual->numero_mesa != numero_mesa) {
        mesa_atual = mesa_atual->proximo;
    }

    if (mesa_atual != NULL) {
        printf("Informe o numero do pedido que deseja alterar: ");
        scanf("%d", &numero_pedido);

        struct pedido *atual = mesa_atual->pedidos;
        while (atual != NULL && atual->codigo_pedido != numero_pedido) {
            atual = atual->prox;
        }

        if (atual != NULL) {
            printf("Informe o novo codigo do pedido: ");
            scanf("%d", &atual->codigo_pedido);
            printf("Informe o novo codigo do produto: ");
            scanf("%d", &atual->cod_produto);
            printf("Informe a nova quantidade do pedido: ");
            scanf("%d", &atual->quantidade_pedido);

            mesa_atual->total_pedido = 0.0;
            struct pedido *temp = mesa_atual->pedidos;
            while (temp != NULL) {
                for (int i = 0; i < 100; ++i) {
                    if (listaPB[i].codigo_prod == temp->cod_produto) {
                        mesa_atual->total_pedido += listaPB[i].preco_prod * temp->quantidade_pedido;
                        break;
                    }
                }
                temp = temp->prox;
            }

            printf("Pedido alterado com sucesso.\n");
        } else {
            printf("Pedido nao encontrado na mesa %d.\n", numero_mesa);
        }
    } else {
        printf("Mesa nao encontrada.\n");
    }
}
void consultarPedido(struct mesa *lista_mesa , struct PB listaPB[]) {
    int numero_mesa, numero_pedido;
    printf("Informe o numero da mesa para consultar o pedido: ");
    scanf("%d", &numero_mesa);

    struct mesa *mesa_atual = lista_mesa;
    while (mesa_atual != NULL && mesa_atual->numero_mesa != numero_mesa) {
        mesa_atual = mesa_atual->proximo;
    }

    if (mesa_atual != NULL) {
        printf("Informe o numero do pedido que deseja consultar: ");
        scanf("%d", &numero_pedido);

        struct pedido *atual = mesa_atual->pedidos;
        while (atual != NULL && atual->codigo_pedido != numero_pedido) {
            atual = atual->prox;
        }

        if (atual != NULL) {
            printf("Informacoes do Pedido:\n");
            printf("Numero da Mesa: %d\n", mesa_atual->numero_mesa);
            printf("Codigo do Pedido: %d\n", atual->codigo_pedido);
            printf("Codigo do Produto: %d\n", atual->cod_produto);
            printf("Quantidade: %d\n", atual->quantidade_pedido);
            
            for (int i = 0; i < 100; ++i) {
                if (listaPB[i].codigo_prod == atual->cod_produto) {
                    printf("Total do Pedido: %.2f\n", listaPB[i].preco_prod * atual->quantidade_pedido);
                    break;
                }
            }
        } else {
            printf("Pedido nao encontrado na mesa %d.\n", numero_mesa);
        }
    } else {
        printf("Mesa nao encontrada.\n");
    }
}

void fecharConta(struct mesa **lista_mesas, struct garcom lista_garcom[]) {
    int i , numero_mesa;
    
    printf("Informe o numero da mesa para fechar a conta: ");
    scanf("%d", &numero_mesa);

    struct mesa *mesa_atual = *lista_mesas;
    while (mesa_atual != NULL && mesa_atual->numero_mesa != numero_mesa) {
        mesa_atual = mesa_atual->proximo;
    }

    if (mesa_atual != NULL) {
        printf("\n\n=== Nota Fiscal ===\n");
        printf("Numero da Mesa: %d\n", mesa_atual->numero_mesa);

        for (i = 0 ; i < 100 ; i++){
            if (lista_garcom[i].codigo_garcom == mesa_atual->cod_garcom){
                printf("Nome do Garcom: %s\n", lista_garcom[i].nome_garcom);
                break;
            }
        }

        imprimirListaPedidos(mesa_atual);
        printf("Total da Conta: %.2f\n", mesa_atual->total_pedido);

        struct mesa *mesa_removida = removerPedidoMesa(lista_mesas, numero_mesa);

        struct pedido *temp = mesa_removida->pedidos;
        while (temp != NULL) {
            struct pedido *temp_next = temp->prox;
            free(temp);
            temp = temp_next;
        }

        free(mesa_removida);

        printf("\nConta da mesa %d fechada com sucesso.\n", numero_mesa);
    } else {
        printf("Mesa nao encontrada.\n");
    }
}

int main(){
    struct PB listaPB[100];
    struct garcom lista_garcom[100];
    struct mesa *r_mesa , *b_mesa , *lista_mesa = NULL;
    int quantidade_PB , quantidade_garcom;
    int numero_mesa , cod_garcom , quant_prod , cod_prod , cod_ped;
    int cont_prod = 0 , cont_garcons = 0 , cont_pedidos = 0 , cont_mesas = 0 , iterador_prod = 0 , iterador_garcom = 0;
    int escolha , numero_remover , numero_alterar , numero_buscar;

    do{
        printf("\n\nMODO DE USAR\n\n");
        printf("PARA PODER USAR AS FUNCOES 3 , 4 , 5 E 6 PRIMEIRO EH NECESSARIO CADASTRAR OS PRODUTOS E OS GARCONS NAS OPCOES 1 E 2.\n");
        printf("\nOU SEJA , PRIMEIRO USE AS FUNCOES 1 PARA CADASTRAR PRODUTOS E 9 PARA CADASTRAR GARCONS. ASSIM, O RESTO DO PROGRAMA PODERA SER USADO NORMALMENTE.");
        printf("\nSEMPRE ESCOLHA CÓDIGOS DIFERENTES PARA AS COISAS, NÃO DIGITE CÓDIGOS IGUAIS.");
        printf("\nPRIMEIRO DEVE-SE CADASTRAR AS MESAS NO CASE 4 PARA DEPOIS MANIPULAR PEDIDOS NO CASE 3.");

        printf("\n1 - Manipular produtos\n2 - Manipular garcom\n3 - Manipular pedidos\n4 - Manipular mesa\n");
        printf("5 - Printar as mesas e os pedidos\n6 - Fechar conta e gerar a nota fiscal de uma mesa\n");
        printf("0 - Sair do programa\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
            printf("\n1 - Cadastrar produto\n2 - Deletar produto\n3 - Alterar produto\n4 - Mostrar produto\n5 - Mostrar todos\n");
            printf("0 - Sair do programa\n");
            scanf("%d" , &escolha);
            switch(escolha){
                case 0:
                    printf("Sistema finalizado.\n");
                    break;
                case 1:
                    printf("Quantos produtos deseja cadastrar(maximo 100): ");
                    scanf("%d" , &quantidade_PB);
                    if (quantidade_PB > 100){
                        printf("Quantidade maior que a capacidade");
                    } else {
                        cont_prod += quantidade_PB;
                        quantidade_PB += iterador_prod;
                        cadastrarProd(listaPB , quantidade_PB , iterador_prod);
                        salvarProd(listaPB, quantidade_PB);
                        iterador_prod = 0;
                        iterador_prod = quantidade_PB;
                    }
                    break;
                case 2:
                    removerProd(listaPB , &quantidade_PB);
                    reescreverArquivoProd(listaPB , quantidade_PB);
                    break;

                case 3:
                    alterarProd(listaPB , quantidade_PB);
                    reescreverArquivoProd(listaPB , quantidade_PB);
                    break;

                case 4:
                    printaProd(listaPB , quantidade_PB);
                    break;

                case 5:
                    printf("Quantidade de produtos: %i\n" , cont_prod);
                    lerPratoBebida(quantidade_PB);
                    break;

                default:
                    printf("Escolha invalida.\n");
                    break;
            }
            break;
            
            case 2:
            printf("\n1 - Cadastrar garcom\n2 - Deletar garcom\n3 - Alterar garcom\n4 - Mostrar garcom\n5 - Mostrar tudo\n");
            printf("0 - Sair do programa\n");
            scanf("%d" , &escolha);
            switch(escolha){
                case 0:
                    printf("Sistema finalizado.\n");
                    break;
                case 1:
                    printf("Quantos garcons deseja cadastrar(maximo 100): ");
                    scanf("%d" , &quantidade_garcom);
                    if (quantidade_garcom > 100){
                        printf("Quantidade maior que a capacidade");
                    } else {
                        cont_garcons += quantidade_garcom;
                        quantidade_garcom += iterador_garcom;
                        cadastraGarcom(lista_garcom , quantidade_garcom , iterador_garcom);
                        salvarGarcom(lista_garcom, quantidade_garcom);
                        iterador_garcom = 0;
                        iterador_garcom = quantidade_garcom;
                    }
                    break;

                case 2:
                    removerGarcom(lista_garcom , &quantidade_garcom);
                    reescreverArquivoGarcom(lista_garcom , quantidade_garcom);
                    break;

                case 3:
                    alteraGarcom(lista_garcom, quantidade_garcom);
                    reescreverArquivoGarcom(lista_garcom , quantidade_garcom);
                    break;

                case 4:
                    printaGarcom(lista_garcom, quantidade_garcom);
                    break;

                case 5:
                    printf("Quantidade de garcons: %i\n" , cont_garcons);
                    lerGarcom(quantidade_garcom);
                    break;

                default:
                    printf("Escolha invalida.\n");
                    break;
            }
            break;

            case 3:
            printf("\n1 - Inserir pedido na mesa\n2 - Deletar pedido\n3 - Alterar pedido\n4 - Consultar pedido\n");
            printf("0 - Sair do programa\n");
            scanf("%d" , &escolha);
            switch(escolha){
                case 0:
                    printf("Sistema finalizado.\n");
                    break;
                case 1:
                    printf("Informe o numero da mesa para adicionar o pedido: ");
                    scanf("%d", &numero_mesa);

                    struct mesa *mesa_atual = lista_mesa;
                    while (mesa_atual != NULL && mesa_atual->numero_mesa != numero_mesa) {
                        mesa_atual = mesa_atual->proximo;
                    }

                    if (mesa_atual != NULL) {
                        printf("Informe o codigo do pedido: ");
                        scanf("%d", &cod_ped);
                        printf("Informe o codigo do produto que deseja consumir(informe um ja existente): ");
                        scanf("%d", &cod_prod);
                        printf("Informe a quantidade do pedido: ");
                        scanf("%d", &quant_prod);

                        for (int j = 0; j < 100; j++) {
                            if (listaPB[j].codigo_prod == cod_prod){
                                mesa_atual->total_pedido += listaPB[j].preco_prod * quant_prod;
                                adicionarPedido(mesa_atual, listaPB, cod_ped, cod_prod , quant_prod);
                                cont_pedidos++;
                                break;
                            }
                        }
                    } else {
                        printf("Mesa nao encontrada.\n");
                    }
                    break;

                case 2:
                    removerPedido(lista_mesa , listaPB);
                    cont_pedidos--;
                    break;

                case 3:
                    alterarPedido(lista_mesa , listaPB);
                    break;

                case 4:
                    consultarPedido(lista_mesa , listaPB);
                    break;

                default:
                    printf("Escolha invalida.\n");
                    break;
            }
            break;

            case 4:
            printf("\n1 - Inserir mesa(tambem insere por ordem de chegada)\n2 - Mostrar mesas em ordem\n");
            printf("3 - Deletar mesa\n4 - Alterar mesa\n5 - Consultar mesa\n");
            printf("0 - Sair do programa\n");
            scanf("%d" , &escolha);
            switch(escolha){
                case 0:
                    printf("Sistema finalizado.\n");
                    break;

                case 1:
                    printf("Informe o numero da mesa: ");
                    scanf("%d", &numero_mesa);
                    printf("Informe o codigo do garcom(informe um ja existente): ");
                    scanf("%d", &cod_garcom);
                    inserirFimMesa(&lista_mesa , numero_mesa , cod_garcom);
                    cont_mesas++;
                    break;

                case 2:
                    printf("\nQuantidade de mesas ao total: %d" , cont_mesas);
                    printaListaMesa(lista_mesa);
                    break;

                case 3:
                    printf("Informe o numero da mesa que quer remover: ");
                    scanf("%d", &numero_remover);
                    r_mesa = removerPedidoMesa(&lista_mesa , numero_remover);
                    if(r_mesa){
                        free(r_mesa);
                    }
                    cont_mesas--;
                    break;

                case 4:
                    printf("Informe o numero da mesa que quer alterar: ");
                    scanf("%d", &numero_alterar);
                    alterarMesaLista(&lista_mesa , numero_alterar);
                    break;

                case 5:
                    printf("Informe o numero da mesa que quer buscar: ");
                    scanf("%d", &numero_buscar);
                    b_mesa = consultarMesaLista(&lista_mesa , numero_buscar);
                    if(b_mesa){
                        printf("Numero da mesa: %d\n" , b_mesa->numero_mesa);
                        printf("Codigo do garcom: %d\n" , b_mesa->cod_garcom);
                        printf("Total do pedido: %.2f\n\n" , b_mesa->total_pedido);
                    } else{
                        printf("Nao foi possivel encontrar o pedido.");
                    }
                    break;

                default:
                    printf("Escolha invalida.\n");
                    break;
            }
            break;

            case 5:
                printf("\nQuantidade de mesas ao total: %d" , cont_mesas);
                printf("Quantidade de pedidos ao total: %d" , cont_pedidos);
                imprimirListaMesas(lista_mesa);
                break;

            case 6: 
                fecharConta(&lista_mesa, lista_garcom);
                break;
            case 0:
                printf("Sistema finalizado.\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (escolha != 0);
    
    return 0;
}
