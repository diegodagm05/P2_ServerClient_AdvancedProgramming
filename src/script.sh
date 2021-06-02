#!/bin/bash
for N in {1..100}
do
    i=$(($RANDOM%100)) #numero aleatorio entre 0 y 100
    ./../bin/client.out $i & #el & es para ejecutar sin esperar a que termine el proceso 
done 
wait