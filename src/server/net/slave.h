#ifndef SERVER_NET_SLAVE_H
#define SERVER_NET_SLAVE_H  

#define MASTER_READ 0
#define SLAVE_WRITE 1
#define SLAVE_READ 2
#define MASTER_WRITE 3

class Slave {
public:
  explicit Slave(int*);
  ~Slave();

  void Serve();

private:
  void InitReadFds();
  void SignalReady();
  void GetTask();

  int* pipes_;
};

void* create_slave(void*);

#endif
