import pygame, sys, random, pickle
import copy


WIDTH=500
HEIGHT=500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TEST")
square=pygame.Surface((1, 1))
#a=(random.randint(0,255),random.randint(0,255),random.randint(0,255))
#b=(random.randint(0,255),random.randint(0,255),random.randint(0,255))
#c=(random.randint(0,255),random.randint(0,255),random.randint(0,255))
#print(a)
#print(b)
#print(c)
a=(44, 98, 175)
b=(140, 86, 73)
c=(212, 124, 228)

sand = [[0 for i in range(WIDTH)] for j in range(HEIGHT)]
maximum=WIDTH/2
def dothing(sand,maximum):
    nexts=sand
    marks=[]
    for x in range (WIDTH-maximum-5,maximum+5):
        for y in range (HEIGHT-maximum-5,maximum+5):
            if sand[x][y]>3:
                marks.append([x,y])
                if maximum<x:
                    maximum=x
    for x,y in marks:
        nexts[x][y]-=4
        nexts[x+1][y]+=1
        nexts[x-1][y]+=1
        nexts[x][y+1]+=1
        nexts[x][y-1]+=1
    return nexts,maximum

rate=1
done=False
while not done:
    for x in range(rate):
        sand[WIDTH/2][HEIGHT/2]=4
        sand,maximum=dothing(sand,maximum)
    events=pygame.event.get()
    for e in events:
        if e.type==pygame.KEYDOWN:
            if e.key==115:
                pickle.dump(sand,open("cache","wb"))
                print("saved")
            elif e.key==108:
                sand=pickle.load(open("cache","rb"))
                print("loaded")
            elif e.key==49:
                rate=1
            elif e.key==50:
                rate=1000
            elif e.key==pygame.K_LEFT:
                done=True
            else:
                print(e.key)
    for x in range (WIDTH-maximum-5,maximum+5):
        for y in range (HEIGHT-maximum-5,maximum+5):
            curr=sand[x][y]
            if(curr==0):
                square.fill([0,0,0])
            elif(curr==1):
                square.fill(a)
            elif(curr==2):
                square.fill(b)
            elif(curr>=3):
                square.fill(c)
            else:
                square.fill([0,0,0])
            pixel=pygame.Rect((x+1), (y+1), 1, 1)
            screen.blit(square,pixel)
    pygame.display.flip()
pygame.quit()
