import pygame, sys, random, pickle
import copy


WIDTH=500
HEIGHT=500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TEST")
square=pygame.Surface((1, 1))
x=0.
y=0.

def draw():
    scale=50
    square.fill((0,150,0))
    xc=WIDTH/2+x*scale
    yc=HEIGHT-y*scale
    pixel=pygame.Rect(xc,yc, 1, 1)
    screen.blit(square,pixel)

def nextPoint(x,y):
    xn=0.
    yn=0.
    r=random.randint(0,100)
    if r<1:
        xn=0.
        yn=.16*y
    elif r<86:
        xn=.85*x+.04*y
        yn=-.04*x+.85*y+1.6
    elif r<93:
        xn=.2*x-.26*y
        yn=.23*x+.22*y+1.6
    else:
        xn=-.15*x+.28*y
        yn=.26*x+.24*y+.44

    return xn,yn

done=False
while not done:
    events=pygame.event.get()
    for e in events:
        if e.type==pygame.KEYDOWN:
            if e.key==pygame.K_LEFT:
                done=True
            else:
                print(e.key)

    for i in range(500):
        draw()
        x,y=nextPoint(x,y)

    pygame.display.flip()
pygame.quit()
