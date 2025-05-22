# 💸 Money To Text

Projeto em C para converter valores monetários em extenso. Inclui testes automatizados usando a Unity Test Framework.


### 🧪 Como rodar os testes com Unity

#### 1. Compile os testes com o framework Unity:

```bash
gcc -Iinclude -Isrc -Iunity test/test_m2t.c src/m2t.c unity/unity.c -o test_runner
````

#### 2. Execute os testes:

**Linux/WSL:**

```bash
./test_runner
```

**Windows:**

```bash
test_runner.exe
```

#### ✅ Exemplo de saída esperada:

```
test/test_m2t.c:69:test_money_split_should_split_correctly:PASS
test/test_m2t.c:70:test_money_split_without_comma_should_default_to_00:PASS
test/test_m2t.c:71:test_split_in_groups_of_three_should_split_7_digits:PASS
test/test_m2t.c:72:test_split_in_groups_of_three_should_split_4_digits:PASS

-----------------------
4 Tests 0 Failures 0 Ignored
OK
```

---

### 🚀 Como rodar o programa principal

#### 1. Compile o programa com `main.c`:

```bash
gcc -Iinclude src/main.c src/m2t.c -o program.exe
```

#### 2. Execute o programa:

**Linux/WSL:**

```bash
./program.exe
```

**Windows:**

```bash
program.exe
```

#### 🎯 Exemplo de saída:

```
quarenta e quatro mil duzentos e quarenta reais 
```

---

### ⚠️ Observações importantes

* O programa principal (`main.c`) **não deve ser compilado junto com os testes**, pois **C não permite múltiplas funções `main()` em um mesmo binário**.
* Sempre compile e execute os testes separadamente do programa principal.

---

### 📁 Estrutura sugerida do projeto

```
money-to-text/
│
├── src/
│   ├── m2t.c
│   └── main.c
│
├── include/
│   └── m2t.h
│
├── test/
│   └── test_m2t.c
│
├── unity/
│   └── unity.c / unity.h
│
├── program.exe         # gerado ao compilar main
├── test_runner.exe     # gerado ao compilar os testes
└── README.md
```

---

Se quiser posso gerar esse arquivo direto pra você salvar como `.md`. Quer?
