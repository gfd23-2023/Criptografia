#Para nomear os gráficos
import os

i = 1
j = 1
#Enquanto houver arquivos com o mesmo nome - incrementa o contador
while os.path.exists(f"grafico_cifra_{i}.png"):
    i += 1

while os.path.exists(f"grafico_decifra_{j}.png"):
    j += 1


#Recurso matemático
import matplotlib.pyplot as plt

# Pede o arquivo pelo teclado
arq = input("Digite o caminho do arquivo trabalhado: ")

# Verifica se o arquivo existe
if not os.path.exists(arq):
    print("Arquivo não encontrado!")
    exit()

tamanho_bytes = os.path.getsize(arq)      #tamanho em bytes
tamanho_kb = tamanho_bytes / 1024         #tamanho em KB


#Abre o arquivo com os dados do tempo e converte para float
with open("dados_tempo.txt") as f:
    dados = [float(linha.strip()) for linha in f]

cifras = ['GI-PLAYFAIR-FENCE', 'AES']

#Gráfico da cifra.c:
tempo = [dados[0], dados[1]]

plt.figure()
plt.bar(cifras, tempo, color='skyblue', label=f"Tamanho do arquivo: {tamanho_kb:.2f} KB")
plt.legend()                           #mostra a legenda
plt.title("Cifra")
plt.xlabel("Cifra")
plt.ylabel("Sedundos")
plt.tight_layout()                     #arruma o layout
plt.savefig(f"grafico_cifra_{i}.png")  #salva
plt.show()

#Gráfico da decifra.c
tempo2 = [dados[2], dados[3]]

plt.figure()
plt.bar(cifras, tempo2, color='skyblue', label=f"Tamanho do arquivo: {tamanho_kb:.2f} KB")
plt.legend()                             #mostra a legenda
plt.title("Decifra")
plt.xlabel("Cifra")
plt.ylabel("Segundos")
plt.tight_layout()                       #arruma o layout
plt.savefig(f"grafico_decifra_{j}.png")  #salva
plt.show()