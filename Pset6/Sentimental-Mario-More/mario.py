from cs50 import get_int

height:int = 0

while not 0<height<=8:
    height = get_int("Height: ")

for i in range(height):
    for j in range(height-i-1):
        print(' ',end='')
    for j in range(i+1):
        print('#',end='')
    print("  ",end='')
    for j in range(i+1):
        print('#',end='')
    print()


