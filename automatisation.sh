#!/bin/bash

# Supprimer les exécutables si il y en a
make clean

# Compiler le projet
make

# Exécution no_sol_1
echo "====== Exécution non solution n°1 ======"
echo "Le script d'aumatisation s'arrêtera pendant 3 secondes pour laisser la non solution n°1 s'exécuter correctement."
./no_sol_1/demo 2>/dev/null &
PID1=$!
sleep 3
kill $PID1
ipcrm -a
echo "====== Fin exécution de la non solution n°1 ======"
echo ""

# Exécution no_sol_2
echo "====== Exécution non solution n°2 ======"
echo "Le script d'aumatisation s'arrêtera pendant 10 secondes pour laisser la non solution n°2 s'exécuter correctement."
./no_sol_2/demo 2>/dev/null &
PID2=$!
sleep 10
kill $PID2
ipcrm -a
echo "====== Fin exécution de la non solution n°2 ======"
echo ""

# Exécution tanenbaum_sol
echo "====== Exécution solution de Tanenbaum ======"
echo "Le script d'aumatisation s'arrêtera pendant 10 secondes pour laisser la solution de Tanenbaum s'exécuter correctement."
./tanenbaum_sol/demo 2>/dev/null &
PID3=$!
sleep 10
kill $PID3
ipcrm -a
echo "====== Fin exécution de la solution de Tanenbaum ======"
echo ""

make clean

echo "====== Fin execution du script automatisation ======"
