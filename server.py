import socket
import pickle
import sys
import re
import thread
def main():

    host='127.0.0.1'
    port=8989
    try :
        s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    except socket.error,msg :
        print 'Failed to create socket. Error code: ' + str(msg[0])
        sys.exit();
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((host,port))
    print "waiting for connection : "
    x=0
    s.listen(20)
    while x <=2:
        c,addr=s.accept()
        print "connection from :" +str(addr)
      
        thread.start_new_thread(func,(c,addr))

        x=x+1
    s.close();
    

def func(c , addr):
     count=0

     while count ==0 :
        list=[]
        data=c.recv(1024)
        if("#" in data):
            count=count+1
        if not data:
            break
        list = re.findall("[+-]?\d+",data)
        
        list.sort(key=int)
        ans=' '.join(list)
        print("data sorted and sent")
        c.send(ans)
     c.close()


if __name__=='__main__':
    main()
