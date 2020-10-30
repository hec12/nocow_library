#include "problem_name.h"
#include "message.h"

struct IO {
    int id;
    IO(const int &id = 0) : id(id) {}
    inline IO &setId(const int &id = 0) { this->id = id; return *this; }
    inline IO &operator<<(const long long &x) {
        PutLL(id, x); Send(id);
        return *this;
    }
    inline IO &operator<<(const int &x) {
        PutInt(id, x); Send(id);
        return *this;
    }
    inline IO &operator<<(const char &c) {
        PutChar(id, c); Send(id);
        return *this;
    }
    inline IO &operator>>(int &x) {
        Receive(id); x = GetInt(id);
        return *this;
    }
    inline IO &operator>>(long long &x) {
        Receive(id); x = GetLL(id);
        return *this;
    }
    inline IO &operator>>(char &x) {
        Receive(id); x = GetChar(id);
        return *this;
    }
};

const int nodes = NumberOfNodes();
const int id    = MyNodeId();

inline int node_from(int id, ll n) {
    return n * id / nodes;
}

inline int node_to(int id, ll n) {
    return n * (id + 1) / nodes;
}
