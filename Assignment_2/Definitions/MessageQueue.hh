#pragma once

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

class   MessageQueue {

private:
  int _identifier;
  msqid_ds _queue;
  bool _owner;

public:
  MessageQueue(const int identifier, const bool create = false);
  ~MessageQueue();
};
