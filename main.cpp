#include "zmq.h"

#include <future>
#include <list>
#include <string>

int main(int, char**)
{
  const int cycles = 200;
  const int task_count = 6;

  std::list<std::future<void>> tasks;
  for (int task = 0; task < task_count; task++)
  {
    tasks.emplace_back(std::async(std::launch::async, [&]
    {
      for (int i = 0; i < cycles; i++)
      {
        const std::string address = "udp://127.0.0." + std::to_string(task + 1) + ";255.0.0.1:5599";

        void* ctx = zmq_ctx_new();
        auto socket = zmq_socket(ctx, ZMQ_RADIO);
        zmq_close(socket);
        zmq_ctx_term(ctx);
      }
    }));
  }
}
