from threading import Thread
import time

class myThread(Thread):
    def __init__(self, ID, numOfSec):
        Thread.__init__(self)
        self.ID = ID
        self.sec = numOfSec
    
    def run(self):
        print('Thread ' + str(self.ID) + ' nasce')
        time.sleep(self.sec)
        print('Thread ' + str(self.ID) + ' muore')

def main():
    process1 = myThread(1,10)
    process2 = myThread(2,5)
    process1.start()
    process2.start()
    process1.join()
    process2.join()
    print('Fine')

main()