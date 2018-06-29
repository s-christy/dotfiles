#This doesn't work well
import pygame, sys, random, pickle, math


WIDTH=800
HEIGHT=800
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("TEST")

iterationSequence="AABAB"

def lpixel(x,y,iterationSequence,N):
    xn=.5
    avg=0
    for i in range(N):
        rn=y
        if iterationSequence[i%len(iterationSequence)]=="A":
            rn=x
        summand=0
        try:
            summand=math.log(rn*(1.-2.*xn))
        except:
            summand=0
        avg+=summand
        xn=rn*xn*(1-xn)
    return avg/N

minimum=1000
maximum=-1000
done=False
while not done:
    #screen.fill((0,0,0))
    region=[2,2,4,4]
    i=10
    for x in range(8*i,16*i):
        print(x)
        for y in range(8*i,16*i):
            color=lpixel(x/(i*4.),y/(i*4.),iterationSequence,2000)
            if color<minimum:
                minimum=color
            if color>maximum:
                maximum=color
            offset=0
            scale=400
            if color>=0:
                color=(0,0,(color+offset)*scale)
            else:
                color=abs(color)
                color=((color+offset)*scale,(color+offset)*scale,0)
            #print(color)
            try:
                pygame.draw.rect(screen,color,[x-8*i,y-8*i,1,1])
            except:
                pass
    pygame.display.update()
    while not done:
        events=pygame.event.get()
        for e in events:
            if e.type==pygame.KEYDOWN:
                if e.key==pygame.K_LEFT:
                    done=True
                else:
                    print(e.key)
pygame.quit()
print(minimum,maximum)
