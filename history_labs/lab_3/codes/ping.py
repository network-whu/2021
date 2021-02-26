#!/usr/bin/python
__author__ = 'jicheng adapted from Rosefinch'
__date__ = 'May 6th, 2020'

import time
import struct
import socket
import select
import sys

def chesksum(data):
    n = len(data)
    m = n % 2
    sum = 0 
    for i in range(0, n - m ,2):
        sum += (data[i]) + ((data[i+1]) << 8)
    if m:
        sum += (data[-1])

    sum = (sum >> 16) + (sum & 0xffff)
    sum += (sum >> 16)
    answer = ~sum & 0xffff

    answer = answer >> 8 | (answer << 8 & 0xff00)
    return answer 

def raw_socket(dst_addr,imcp_packet):
    rawsocket = socket.socket(socket.AF_INET,socket.SOCK_RAW,socket.getprotobyname("icmp"))
    send_request_ping_time = time.time()
    #send data to the socket
    rawsocket.sendto(imcp_packet,(dst_addr,80))
    return send_request_ping_time,rawsocket,dst_addr

    '''
    request ping
    '''
def request_ping(data_type,data_code,data_checksum,data_ID,data_Sequence,payload_body):

    imcp_packet = struct.pack('>BBHHH32s',data_type,data_code,data_checksum,data_ID,data_Sequence,payload_body)
    icmp_chesksum = chesksum(imcp_packet)
    imcp_packet = struct.pack('>BBHHH32s',data_type,data_code,icmp_chesksum,data_ID,data_Sequence,payload_body)
    return imcp_packet
    '''
    reply ping
    '''
def reply_ping(send_request_ping_time,rawsocket,data_Sequence,timeout = 2):
    while True:
        started_select = time.time()
        what_ready = select.select([rawsocket], [], [], timeout)
        wait_for_time = (time.time() - started_select)
        if what_ready[0] == []:  # Timeout
            return -1
        time_received = time.time()
        received_packet, addr = rawsocket.recvfrom(4096)    # data length should not exceed this buffer
        icmpHeader = received_packet[20:28]
        type, code, checksum, packet_id, sequence = struct.unpack(
            ">BBHHH", icmpHeader
        )
        if type == 0 and sequence == data_Sequence:
            return time_received - send_request_ping_time
        timeout = timeout - wait_for_time
        if timeout <= 0:
            return -1

def ping(host):
    data_type = 8 # ICMP Echo Request
    data_code = 0 # must be zero
    data_checksum = 0 # "...with value 0 substituted for this field..."
    data_ID = 0 #Identifier
    data_Sequence = 1 #Sequence number
    payload_body = b'abcdefghijklmnopqrstuvwabcdefghi0123456789' #data
#    li=[]
#    for i in range(2000):
#        li.append(i)
    dst_addr = socket.gethostbyname(host)
    print("now Ping {0} [{1}] with 32 bytes of data:".format(host,dst_addr))
    for i in range(0,17):
        icmp_packet = request_ping(data_type,data_code,data_checksum,data_ID,data_Sequence + i,payload_body)
#        icmp_packet = request_ping(data_type,data_code,data_checksum,data_ID,data_Sequence + i,li)
        send_request_ping_time,rawsocket,addr = raw_socket(dst_addr,icmp_packet)
        times = reply_ping(send_request_ping_time,rawsocket,data_Sequence + i)
        if times > 0:
            print("reply from {0} bytes = 2000 time ={1}ms".format(addr,int(times*1000)))
            time.sleep(0.7)
        else:
            print("request time out")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit('Usage: ping.py <host>')
    ping(sys.argv[1])