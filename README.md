# Money To Text

> Repositório dedicado a transformar valor monetário em texto por extenso

### 💡 Objetivo:

- Converter, por exemplo, R$ 1.234,56 → "mil duzentos e trinta e quatro reais e cinquenta e seis centavos"

### 🧠 Lógica Geral do Fluxo:

#### 1. Separar parte inteira e centavos
Separe o valor antes e depois da vírgula (ou ponto decimal, dependendo do formato).

- Exemplo: 1234,56

- Parte inteira = 1234

- Centavos = 56

#### 2. Decompor os números em grupos de três dígitos (classes)
- A parte inteira deve ser agrupada da direita para a esquerda em trios:

- 123456789 → 123 (milhão), 456 (mil), 789 (unidade)

- Cada grupo tem um nome: milhar, milhão, bilhão, etc.

#### 3. Converter cada grupo para texto
- Para cada grupo de três dígitos:

- Analise centena, dezena e unidade.

- 123 → "cento e vinte e três"

- **Regras especiais**:

    - 100 é "cem", mas 101 é "cento e um"

    - 11 a 19 têm nomes próprios: onze, doze, treze, etc.

    - Combine com a classe:

    - 123 mil → "cento e vinte e três mil"

    - 456000000 → "quatrocentos e cinquenta e seis milhões"

#### 4. Tratar singular e plural
- 1 real, 2 reais

- 1 centavo, 2 centavos

- 1 milhão, 2 milhões

- Isso exige verificação da quantidade em cada classe

#### 5. Inserir conectivos ("e") corretamente
- O “e” é necessário para fluidez da linguagem:

- Entre dezenas e unidades: vinte **e** três

- Entre centenas e dezenas/unidades: cento **e** cinco

- Entre classes: mil **e** duzentos reais

- Mas não é usado:

    - Entre classe e "mil": mil duzentos reais (sem vírgula ou "e")

#### 6. Adicionar unidade monetária
- Após a parte inteira, adicione "real/reais"

- Após os centavos, adicione "centavo/centavos"

- Use "e" para ligar:

- dois mil reais **e** trinta centavos

### 📌 Exemplo completo: 
- R$ 123456789,01

Quebra:

- Centena de milhão: 123 → "cento e vinte e três milhões"

- Milhar: 456 → "quatrocentos e cinquenta e seis mil"

- Unidade: 789 → "setecentos e oitenta e nove"

- Centavos: 01 → "um centavo"

#### Resultado final:
> "cento e vinte e três milhões quatrocentos e cinquenta e seis mil setecentos e oitenta e nove reais e um centavo"