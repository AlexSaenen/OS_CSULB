#include "MessageQueue.hh"


MessageQueue::MessageQueue(const int identifier, const bool create) {
  int flags = (create ? IPC_CREAT : 0);

  _identifier = msgget(identifier, flags);

  if (_identifier == -1) {
    cout << "Failed to get the message queue for identifier (" << identifier << ")" << endl;
  } else {
    msgctl(_identifier, IPC_STAT, &_queue);
  }

  _owner = create;
}

MessageQueue::~MessageQueue() {
  if (_owner && _identifier > -1) {
    msgctl(_identifier, IPC_RMID, &_queue);
  }
}
