// Min/Max Queue
//


template<typename T> struct MQueue{
  int tin, tout;
  deque<pair<T, int>> dq;
  function<T(T, T)> F;
  MQueue(function<T(T, T)> F) : tin(0), tout(0), F(F){}
  void push(T val){
    while(!dq.empty() && F(dq.back().first, val) == val) dq.pop_back();
    dq.push_back(pair(val, tin++));
  }
  void pop(){
    // assert(!dq.empty());
    if(dq.front().second == tout) dq.pop_front();
    tout++;
  }
  T front(){
    // assert(!dq.empty());
    return dq.front().first;
  }
};