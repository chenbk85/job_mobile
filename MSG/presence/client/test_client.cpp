#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include <iostream>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "presence.pb.h"

#define PORT        6000
#define HOST        "localhost"
#define DIRSIZE     8192

namespace gpio		= google::protobuf::io;

int send_request(PReqProtocol & presence_request, std::string cmdstr)
{
    std::cout << "request " << cmdstr << " to presence" << std::endl;

    static const int header_len = 4;

    char myHeader[4];
    std::vector<char> buffer;
    char recv_buffer[4096] = {0};

    buffer.resize(presence_request.ByteSize());

    gpio::ArrayOutputStream output(&buffer[0], buffer.size());

    bool result = presence_request.SerializeToZeroCopyStream(&output);

    assert(buffer.size() == std::size_t(output.ByteCount()));

    if (result == false)
    {
        std::cout << "we are fucked, aborting" << std::endl;
        return -1;
    }

    char hostname[9];

    int sd;
    struct sockaddr_in sin;
    struct sockaddr_in pin;
    struct hostent *hp;

    strcpy(hostname,HOST);

    /* go find out about the desired host machine */
    if ((hp = gethostbyname(hostname)) == 0) {
        perror("gethostbyname");
        exit(1);
    }

    /* fill in the socket structure with host information */
    memset(&pin, 0, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
    pin.sin_port = htons(PORT);

    /* grab an Internet domain socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /* connect to PORT on HOST */
    if (connect(sd, (struct sockaddr *)  &pin, sizeof(pin)) == -1) {
        perror("connect");
        exit(1);
    }

    // make the header
    int size_4byte = static_cast<int> (buffer.size());
    memcpy(&myHeader[0], &size_4byte, header_len);
    // send the header
    if (send(sd, &myHeader[0], header_len, 0) == -1) {
        perror("send");
        exit(1);
    }
    // send a message to the server PORT on machine HOST
    if (send(sd, &buffer[0], buffer.size(), 0) == -1) {
        perror("send");
        exit(1);
    }
    int received_bytes = -1;
    // wait for a message to come back from the server
    if ((received_bytes = recv(sd, &recv_buffer[0], 4096, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    int i;
    for(i = 0; i < received_bytes; i++)
        printf("[%x]", recv_buffer[i]);
    printf("\n");

    int *p_length = (int*)&recv_buffer[0];
    std::size_t body_length = std::size_t(*p_length);

    printf("body_length=%d\n", body_length);
    PAnsProtocol proto_ans;

    gpio::ArrayInputStream input(&recv_buffer[4], body_length);

    result = proto_ans.ParseFromZeroCopyStream(&input);

    if (result == false)
    {
        std::cout << "error parsing answer, aborting" << std::endl;
        return -1;
    }

    close(sd);
}

int main(int argc, char ** argv)
{
    PReqProtocol presence_request;

    presence_request.set_seqid(0); // authkeys는 사용 안함
    presence_request.set_svcid(1);
    presence_request.set_gameid(2);
    presence_request.set_category(3);

    presence_request.set_command(LOGIN);
    send_request(presence_request, "LOGIN");

    presence_request.set_command(GAMEENTER);
    send_request(presence_request, "GAMEENTER");

    presence_request.set_command(ROOMLIST);
    send_request(presence_request, "ROOMLIST");

    presence_request.set_command(GAMELEAVE);
    send_request(presence_request, "GAMELEAVE");

    presence_request.set_command(LOGOUT);
    send_request(presence_request, "LOGOUT");

    return 0;
}
