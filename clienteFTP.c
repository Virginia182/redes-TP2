#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "tp_socket.h"

int main(int argc, char* argv[]){
  // Processa argumentos
  // host_do_servidor ||||| porto_servidor ||||| file_name ||||| tam_buffer
  /*=====================================ArgumentVariables===================================================================================*/
  if(argc < 5){
    printf("ERRO: Argumentos insuficientes\n");
    return 1;
  }
  char* host_do_servidor = argv[1];
  int   porto_servidor = atoi(argv[2]);
  char* file_name = argv[3];
  int   tam_buffer = atoi(argv[4]);
  //=====================================ClientVariables===================================================================================*/
  float   kbps_rate = 0;
  double  segundos;
  char*   buffer = (char*)malloc(tam_buffer * sizeof(char));
  int     ii = 0;
  int     n = 0;
  int     byte_count = 0; // contador de bytes
  time_t  time_init, time_final;
  FILE*   out_file;
  //=========================SocketVariables================================*/
  struct so_addr serv_addr;
  int    sokt;
  //============================TimeInfoCapture=============================*/
  time(&time_init);  //
  //=============================Conection==================================*/
  // Faz abertura ativa a host_do_servidor : porto_servidor
  tp_build_addr(serv_addr,INADDR_ANY,porto_servidor);
  sokt = tp_socket(AF_INET, SOCK_DGRAM, 0); // Inicia socket IPv4 para
  //===========================RecievingData=================================*/
  out_file = fopen (file_name,"wb"); // Abre arquivo como um b
  while((n = tp_recvfrom(sokt,buffer,tam_buffer,serv_addr) > 0){ // rec
    fwrite(buffer, sizeof(char), n, out_file); // escreve buffer
    byte_count+=n; // soma o numero de bytes ao contador de bytes
    fclose(out_file);
  }
  //=======================EfficiencyMeasurement============================*/
  return 0;
}
