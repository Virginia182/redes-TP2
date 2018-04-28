#include <stdio.h>
#include <string.h>

#include "tpFTP.h"
#include "tp_socket.h"

#define FILE_NAME_MAX_SIZE 256 // Tamanho máximo do nome do arquivo

int main(int argc, char* argv[]){
  /*=========================ArgumentVariables===============================*/
  // porto_servidor ||||| tam_buffer
  if(argc < 3){
    printf("ERRO: Argumentos insuficientes\n");
    return 1;
  }   // Testa se foram recebidos argumentos suficientes
  int porto_servidor = atoi(argv[1]);
  int tam_buffer = atoi(argv[2]);
  /*=====================ServerVariables=====================================*/
  int    flagEOF = 1; // Variável de comunicação entre loops while
  char   *buffer = malloc (tam_buffer);
  char*  file_name = malloc(FILE_NAME_MAX_SIZE);
  FILE * entr_file;
  /*=========================SocketVariables=================================*/
  int    sokt = 0;
  struct so_addr cl_addr;
  /*============================Conection====================================*/
  tp_init();
  tp_build_addr(cl_addr,INADDR_ANY,porto_servidor);
  sokt = tp_socket(porto_servidor);
  get_file_name (sokt,file_name);
  entr_file = fopen(file_name,"rb"); // Abre arquivo como um binário para leitura
  if (entr_file == NULL){ // verifica se realmente foi aberto algum arquivo
    return 1;
  }
  /*=========================SendingData=====================================*/
  while (1){    // enquanto o fim do arquivo nao for alcançado
    read_file_buffer(tam_buffer,entr_file,flagEOF);
    if (flagEOF == 0) break; // encerra o loop se o último vyte foi End Of file
    tp_sendto(sokt, buffer,tam_buffer,cl_addr); // envia buffer para cliente
  }
  fclose(entr_file); // fecha o arquivo
  free(buffer); // libera memórai do buffer
  return 0;
}
