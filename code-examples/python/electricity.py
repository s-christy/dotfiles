import pygame, sys, random, pickle, math


WIDTH=500
HEIGHT=500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TEST")

def drawTree():
    length=150
    x=WIDTH/2
    y=HEIGHT
    rotScale=.7
    rot=3*math.pi/2
    for i in range(1,14):
        xn=length*math.cos(rot)/i+x
        yn=length*math.sin(rot)/i+y
        pygame.draw.line(screen,(255,255,255),[x,y],[xn,yn])
        rot+=rotScale*(random.randint(0,1)-.5)
        x=xn
        y=yn

done=False
while not done:
    events=pygame.event.get()
    for e in events:
        if e.type==pygame.KEYDOWN:
            if e.key==pygame.K_LEFT:
                done=True
            else:
                print(e.key)

    screen.fill((0,0,0))
    for x in range(10):
        drawTree()
    pygame.display.update()
pygame.quit()
