from datetime import *
from subprocess import *
from time import sleep

def grid_to_time(x,y):
    dt = datetime(2017,1,1)+timedelta(days=7*x+y)
    return dt.strftime('%a, %d %b 2017 11:11:11 +0800'
                       )

grid = [
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,
    1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,
    1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,
    1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,0,1,1,0,1,1,1,0,0,0,1,1,0,0,1,0,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
]

def fill():
    for i in range(18,18+34):
        for j in range(7):
            if grid[(i-18)+j*34]:
                with open('rubbish.txt', mode='w') as f:
                    f.write('rubbish on '+grid_to_time(i,j))
                Popen('git add .')
                sleep(0.4)
                Popen('git commit -m "rubbish test" --date="'+grid_to_time(i,j)+'"')
                sleep(0.5)
                print(('rubbish on '+grid_to_time(i,j)))

fill()

