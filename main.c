#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <dir.h>
#include <time.h>

int menu(){

    int opcao;
     printf("\t\t\t**************************\n");
     printf("\t\t\t***       AGENDA       ***\n");
     printf("\t\t\t**************************");


     printf("\n\n\t\t  1  %c   CRIA TAREFA",26);
     printf("\n\n\t\t  2  %c   MOSTRAR TAREFAS",26);
     printf("\n\n\t\t  3  %c   EXCLUIR TAREFAS",26);
     printf("\n\n\t\t  4  %c   LISTAR TAREFAS POR: ",26);
     printf("\n\n\t\t  5  %c   SAIR  \n",26);


    scanf("%d",&opcao);

    return opcao;
}

void criarTarefa(){

    time_t horario = time(NULL);
    struct tm tm = *localtime(&horario);

    FILE *arquivo;
    char FraseTarefa[150];
    char NomeTarefa[100];
    char caminho[] = "Arquivos/Agenda_dados.txt";

    if(arquivo = fopen(caminho,"a")){

        printf("Arquivo Aberto. \n");
        printf("Digite o texto do seu arquivo. \t (MAX: 150 caracteres) \n");
        fflush(stdin);
        gets(FraseTarefa);

        if(fprintf(arquivo,"\t Titulo: %s \t Data Criação: %d/%d/%d  \n",FraseTarefa, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900)){
            fclose(arquivo);
            main();
        }else{
            main();
        }
    }

}
void MostrarTarefa(){
            int i = 1;

            char FraseTarefa[150];
            FILE *arquivo = fopen("Arquivos/Agenda_dados.txt", "r");

            system("cls");

            if(arquivo==NULL){
                printf("Arquivo nulo");
            }else{
                printf("Arquivo aberto. \n");
                while(fgets(FraseTarefa, 150, arquivo)){
                    printf("ID %d : %s",i, FraseTarefa);
                    i++;
                }
            }
            fclose(arquivo);

            main();
}
void PreferenciasTarefa(){
    system("cls");
    printf("Tarefas abaixo");
}

void ExcluirTarefa(){

    FILE *input = fopen("Arquivos/Agenda_dados.txt", "r"); //Arquivo de entrada.
    FILE *output = fopen("Arquivos/Transfere_dados.txt", "w"); //Arquivo de saída.
    char texto[1000] = ""; //Uma string larga o suficiente para extrair o texto total de cada linha.
    unsigned int linha_selecionada;
    unsigned int linha_atual = 1;

    printf("Qual linha desejas excluir? ");
    scanf("%d",&linha_selecionada);

    while(fgets(texto, 1001, input) != NULL){
        if(linha_atual != linha_selecionada){
            fputs(texto, output);
        }
        memset(texto, 0, sizeof(char) * 1001);
        linha_atual += 1;
    }
    fclose(input);
    fclose(output);
    remove("Arquivos/Agenda_dados.txt");
    rename("Arquivos/Transfere_dados.txt", "Arquivos/Agenda_dados.txt");
    printf("Linha excluída com sucesso! \n");

    main();

}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcaoMenu;

    do{
        opcaoMenu = menu();

    }while(opcaoMenu<1 || opcaoMenu>5);

    switch(opcaoMenu){
        case 1:
            criarTarefa();
        break;

        case 2:
            MostrarTarefa();
        break;

        case 3:
            ExcluirTarefa();

        break;

        case 0:
            system("pause");

        break;
        default:
            system("pause");
        }

    return 0;
}
