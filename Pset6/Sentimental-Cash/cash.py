from cs50 import get_float

cantidad:float = 0

while True:
    cantidad = get_float("Change owed: ")
    if cantidad >=0: break
cambio:int = 0

while cantidad >0:
    if cantidad >=0.25:
        cantidad -=0.25

    elif cantidad >=0.10:
        cantidad -=0.10

    elif cantidad >=0.05:
        cantidad -=0.05

    else:
        cantidad -=0.01
    cantidad = round(cantidad,2)
    cambio+=1

print(cambio)
