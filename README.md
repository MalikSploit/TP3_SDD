# TP3_SDD

## Pour compiler et executer séance1
`cd /TP3/TP3_Arbres_2023/Seance1`

`make clean`

`make`

`./arbres_construct_main`

## Pour executer avec valgrind
`valgrind -s --show-leak-kinds=all --track-origins=yes --leak-check=full ./arbres_construct_main`
