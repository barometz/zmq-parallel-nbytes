#include "zmq.h"

#include <future>
#include <list>
#include <string>

int main(int, char**)
{
  const int cycles = 500;

  std::list<std::future<void>> tasks;
  for (int task_number = 1; task_number < 9; task_number++)
  {
    tasks.emplace_back(std::async(std::launch::async, [&]
    {
      for (int i = 0; i < cycles; i++)
      {
        const std::string address = "udp://127.0.0." + std::to_string(task_number) + ";255.0.0.1:5599";

        void* ctx = zmq_ctx_new();
        auto dish = zmq_socket(ctx, ZMQ_DISH);
        auto radio = zmq_socket(ctx, ZMQ_RADIO);

        zmq_bind(dish, address.c_str());
        zmq_connect(radio, address.c_str());

        zmq_join(dish, "swp");

        zmq_close(dish);
        zmq_close(radio);
        zmq_ctx_term(ctx);
      }
    }));
  }
}
