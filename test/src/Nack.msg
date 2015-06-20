
packet Nack{
    int status;
    int num;
    int seq[20];
    int finalkey;
    int source;
    int dest;
}
