  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
typedef struct {
    int horas_sono;
    int consumo_agua;
    int minutos_exercicio;
    int calorias_consumidas;
} Habito;

typedef struct {
    float media_horas_sono;
    float media_consumo_agua;
    float media_minutos_exercicio;
    float media_calorias_consumidas;
} Progresso;


void analisar_progresso(Habito *habitos, int total_habitos, Progresso *progresso) {
    int i;
    for (i = 0; i < total_habitos; i++) {
        progresso->media_horas_sono += habitos[i].horas_sono;
        progresso->media_consumo_agua += habitos[i].consumo_agua;
        progresso->media_minutos_exercicio += habitos[i].minutos_exercicio;
        progresso->media_calorias_consumidas += habitos[i].calorias_consumidas;
    }

    progresso->media_horas_sono /= total_habitos;
    progresso->media_consumo_agua /= total_habitos;
    progresso->media_minutos_exercicio /= total_habitos;
    progresso->media_calorias_consumidas /= total_habitos;
}

void exibir_progresso(Progresso *progresso) {
    printf("\nM�dia de horas de sono\n");
    printf("==================================\n\n");
    printf("M�dia de horas de sono: %.2f\n", progresso->media_horas_sono);
    printf("M�dia de consumo de �gua: %.2f ml\n", progresso->media_consumo_agua);
    printf("M�dia de minutos de exerc�cio: %.2f\n", progresso->media_minutos_exercicio);
    printf("M�dia de calorias consumidas: %.2f\n\n", progresso->media_calorias_consumidas);
    system("pause");
    system("cls");

}
void inserir_habito(Habito *habito) {

    time_t tempo_bruto;
    struct tm *informacao_tempo;
    printf("\nInserir H�bito\n");
    printf("==================================\n\n");
    time(&tempo_bruto);
    informacao_tempo = localtime(&tempo_bruto);
    printf("Data atual: %02d-%02d-%04d\n", informacao_tempo->tm_mday, informacao_tempo->tm_mon+1, informacao_tempo->tm_year +1900);
    printf("Digite as horas de sono di�rio: ");
    scanf("%d", &habito->horas_sono);

    printf("Digite o consumo de �gua em ml di�rio: ");
    scanf("%d", &habito->consumo_agua);

    printf("Digite os minutos de exerc�cio di�rio: ");
    scanf("%d", &habito->minutos_exercicio);

    printf("Digite as calorias consumidas di�rio: ");
    scanf("%d", &habito->calorias_consumidas);

    printf("Dados cadastrados...");
    system("pause");
    system("cls");

}

void salvar_habito(Habito *habito, const char *usuario) {
    FILE *arquivo = fopen("historico.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    time_t tempo_bruto;
    struct tm *informacao_tempo;

    time(&tempo_bruto);
    informacao_tempo = localtime(&tempo_bruto);
    fprintf (arquivo, "Usu�rio: %s\n", usuario); // Adicione o nome de usu�rio no arquivo de hist�rico
    fprintf(arquivo, "Data: %02d-%02d-%04d\n", informacao_tempo->tm_mday, informacao_tempo->tm_mon + 1, informacao_tempo->tm_year + 1900);
    fprintf(arquivo, "Horas de sono: %d\n", habito->horas_sono);
    fprintf(arquivo, "Consumo de �gua: %d ml\n", habito->consumo_agua);
    fprintf(arquivo, "Minutos de exerc�cio: %d\n", habito->minutos_exercicio);
    fprintf(arquivo, "Calorias consumidas: %d\n\n", habito->calorias_consumidas);

    fclose(arquivo);
}


void exibir_historico_usuario(const char *usuario) {
    FILE *arquivo = fopen("historico.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    char stored_usuario[50];
    int exibir_habito = 0;


    printf("\nHist�rico de H�bitos\n");
    printf("====================\n\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Usu�rio:") != NULL) {
            sscanf(linha, "Usu�rio: %s", stored_usuario);
            exibir_habito = strcmp(usuario, stored_usuario) == 0;
        }

        if (exibir_habito) {
            printf("%s", linha);
        }
    }

    fclose(arquivo);
}
void exibir_habito(Habito *habito, int total_habitos) {
    int saudavel = 0;
    printf("\nSeu H�bito atual\n");
    printf("==================================\n\n");
    int i;
    for (i = 0; i < total_habitos; i++) {
        if (habito[i].horas_sono >= 7) {
            printf("Horas de sono: %d\n", habito->horas_sono);
            printf("Parab�ns tem quantidade de sono agrad�vel.\n");



        }else{
            saudavel = saudavel+1;
        }

        if (habito[i].consumo_agua > 2000 && habito[i].consumo_agua < 5000) {
            saudavel = 0;
            printf("\nConsumo de �gua: %d ml\n", habito->consumo_agua);
            printf("Parab�ns tem quantidade de �gua agrad�vel.\n");



        }else if(habito[i].consumo_agua > 5000){
            printf("Consumo de �gua exagerado, cuidado!\n");
            saudavel = saudavel+1;


        } else{
            printf("Precisa consumir mais �gua.\n");
            saudavel = saudavel+1;

        }

        if (habito[i].minutos_exercicio >= 30) {
            saudavel = 0;
            printf("Minutos de exerc�cio: %d\n", habito->minutos_exercicio);
            printf("Parab�ns tem quantidade de exerc�cio agrad�vel.\n");


        }else{
        printf("Melhore nos exerc�cios, seu sedent�rio.\n");
        saudavel = saudavel+1;

        }

        if (habito[i].calorias_consumidas > 2000 && habito[i].calorias_consumidas < 2500) {
            saudavel = 0;
            printf("Calorias consumidas: %d\n", habito->calorias_consumidas);
            printf("Parab�ns tem quantidade de calorias agrad�vel.\n");


        }else{
        printf("Calorias fora da unidade da OMS.\n");
        saudavel = saudavel+1;

        }
    }

    if (saudavel==0) {
        printf("Todos os seus h�bitos s�o saud�veis. Parab�ns!\n");
    } else if (saudavel == 1) {
        printf("\nUm dos seus h�bitos n�o s�o saud�veis. Tente melhorar.\n\n");
    }else if(saudavel == 2) {
        printf("\nDois dos seus h�bitos n�o s�o saud�veis. Tente melhorar.\n\n");
    }else if (saudavel == 3) {
        printf("\nTr�s dos seus h�bitos n�o s�o saud�veis. Tente melhorar..\n\n");
    }else if (saudavel == 4) {
        printf("\nQuatro dos seus h�bitos n�o s�o saud�veis. Tente melhorar.\n\n");
    }
    getch();
    system("cls");

}

int limite_progresso = 100;

void personalizar_limite() {
    int resultado;
    printf("\nPersonalizar Limete de Progresso\n");
    printf("===================================\n\n");
    do {
        printf("Digite o novo limite de progresso: ");
        resultado = scanf("%d", &limite_progresso);
        while (getchar() != '\n'); // Limpa o buffer do teclado
        system("cls");
        if (!resultado) {
            printf("Entrada inv�lida. Por favor, insira um n�mero inteiro.\n");
        }
    } while (!resultado);
}


void personalizar_fundo(char cor[]) {
    printf("\nPersonalizador de Fundo\n");
    printf("==================================\n\n");
    char comando[50];
    sprintf(comando, "color %s", cor);
    system(comando);
    system("cls");

}

void registrar_user() {
    char usuario[50], senha[50];
    FILE *usuario_file, *senha_file;
    printf("\n Registrar Usu�rio\n");
    printf("=========================\n\n");
    printf("Digite o nome de usu�rio: ");
    scanf("%s", &usuario);

    printf("Digite a senha: ");
    scanf("%s", senha);

    usuario_file = fopen("user.txt", "a");
    senha_file = fopen("senha.txt", "a");

    fprintf(usuario_file, "%s\n", usuario);
    fprintf(senha_file, "%s\n", senha);

    fclose(usuario_file);
    fclose(senha_file);

    printf("Usu�rio registrado com sucesso!\n\n");
    system("pause");
    system("cls");
}
int login() {
    char usuario[50], senha[50], stored_usuario[50], stored_senha[50];
    FILE *usuario_file, *senha_file;
    int f = 0;
    printf("\nLogin\n");
    printf("===============\n\n");
    printf("Digite o nome de usu�rio: ");
    scanf("%s", &usuario);

    printf("Digite a senha: ");
    scanf("%s", senha);

    usuario_file = fopen("user.txt", "r");
    senha_file = fopen("senha.txt", "r");

    while (fscanf(usuario_file, "%s", stored_usuario) != EOF && fscanf(senha_file, "%s", stored_senha) != EOF) {
        if (strcmp(usuario, stored_usuario) == 0 && strcmp(senha, stored_senha) == 0) {
            f= 1;
            break;
        }
    }

    fclose(usuario_file);
    fclose(senha_file);

    return f;
}

int menu() {
    int opcao;
    printf("\nGerenciador de H�bitos Pessoais\n");
    printf("==============================\n");
    printf("1. Inserir h�bitos\n");
    printf("2. Exibir h�bitos\n");
    printf("3. M�dias do progresso\n");
    printf("4. Personalizar fundo da tela\n");
    printf("5. Personalizar limite de progresso\n");
    printf("6. Hist�rico de h�bitos\n");
    printf("7. Sair\n");
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);

    system ("cls");
    return opcao;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 9F");
    int opcao;
    int autenticado = 0;
    char u[20], v[20];
    int m,sucesso,j=0;
    char tentar_novamente ;

    printf("\nGerenciador de H�bitos Pessoais\n");
    printf("==================================\n");
    printf("A ajuda que seu dia a dia precisa!\n");
    printf("==================================\n");

    printf("1. Registrar\n");
    printf("2. Login\n");
    printf("Escolha uma op��o...");
    scanf("%d",&m);
    system("pause\n");
    system("cls");
    switch(m){
    case 1:
        registrar_user();
        system("pause");
        system("cls");
    case 2:
        do{
        sucesso = login();
                if (sucesso == 1) {
                    printf("Login bem-sucedido!\n");
                           system("pause");
                            j=1;
                            system("cls");
                } else {
                    printf("Usu�rio ou senha incorretos.\n");
                    printf("Deseja tentar novamente ou se registrar? (R para registrar, qualquer outra tecla para tentar novamente): ");
                    scanf(" %c", &tentar_novamente);
                    system("cls");
                    if (tentar_novamente == 'R' || tentar_novamente == 'r') {
                        registrar_user();
                    }
                }
                 } while (sucesso != 1);

    break;
    default:
    printf("Op��o inv�lida!");
    }while(j==0);

    system("cls");
    Habito habitos[100];
    int total_habitos = 0;
    Progresso progresso = {0};

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                if (total_habitos < 100) {
                inserir_habito(&habitos[total_habitos]);
                total_habitos++;
                salvar_habito(&habitos[total_habitos - 1], u);
                } else {
                printf("Limite de h�bitos atingido.\n");
                }

                break;
            case 2:
                if (total_habitos > 0) {
                    exibir_habito(&habitos[total_habitos - 1],total_habitos);
                } else {
                    printf("Nenhum h�bito registrado.\n");
                }
                break;
            case 3:
                if (total_habitos > 0) {
                    analisar_progresso(habitos, total_habitos, &progresso);
                    exibir_progresso(&progresso);
                } else {
                    printf("Nenhum h�bito registrado.\n");
                }
                break;
            case 4:
                printf("Digite a cor desejada para o fundo da tela: ");
                char cor[10];
                scanf("%s", cor);
                personalizar_fundo(cor);
                    printf("Dados cadastrados...");

                break;
            case 5:
                personalizar_limite();
                    printf("Dados cadastrados...");

                break;
            case 6:
                exibir_historico_usuario(&u);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 7);

    system("cls");

    exit(0);
}
