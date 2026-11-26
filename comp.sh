nome_build="trab2"

gcc main.c sistema.c -o $nome_build -lm
comp=$?

echo ""

if [ $comp -eq 0 ]; then
    echo "$nome_build compilado. Rode usando \"./$nome_build\""
else
    echo "Compilação de $nome_build falhou. Tente novamente."
fi
